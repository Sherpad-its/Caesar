// SPDX-License-Identifier: GPL-v3.0
#include <algorithm>
#include <iostream>
#include <iomanip>
#include <limits>
#include "dat/data.hpp"
#include "caesar.hpp"

namespace SherpadCaesar{

///==============================================================================
/// @brief Constructor of the Caesar_t class.
/// @param d Data used to manage what needs to be performed.
///==============================================================================
Caesar_t::Caesar_t(Data_t& d)
    : m_inputData { d } {

}

///==============================================================================
/// @brief Ask for the data needed to work.
///==============================================================================
void
Caesar_t::ask(){

    writeInfo();

    askEncryptOrDecrypt();
    askLanguage();
    askFileOrString();
    askForSpecificLevel();
}

///==============================================================================
/// @brief Manages whether the transformation is bulk or at a specific level.
///==============================================================================
void
Caesar_t::performTransformation(){

    if (m_inputData.isBulk())
       bulkEncryptionOrDecryption(m_inputData.getData());
    else
       encryptionOrDecryption(m_inputData.getData(), m_inputData.getLevel());
}

///==============================================================================
/// @brief Validates the input data and, if any errors are detected, takes care 
///        of asking the user.
///==============================================================================
void
Caesar_t::validateInputParameters(){
    
    if (!m_inputData.needDisplayHelp()     && !m_inputData.needDisplayInformation() &&
        !m_inputData.needDisplayWarranty() && !m_inputData.needDisplayConditions()){

       if (!m_inputData.wantEncrypt() && !m_inputData.wantDecrypt()){
          m_inputData.initEncryptOrDecrypt();
          askEncryptOrDecrypt();
       }

       if (!m_inputData.isEnglishLanguage() && !m_inputData.isSpanishLanguage()){
          m_inputData.initLanguage();
          askLanguage();
       }

       if (!m_inputData.isFromFile() && !m_inputData.isFromString()){
          m_inputData.initFileOrString();
          askFileOrString();
       }

       if (!m_inputData.isSpecific() && !m_inputData.isBulk()){
          m_inputData.initLevel();
          askForSpecificLevel();
       }
    }
}

///==============================================================================
/// @brief Manages what needs to be done based on the input data.
///==============================================================================
void
Caesar_t::process(){

    if (m_inputData.needDisplayHelp())
       writeHelp();
    else if (m_inputData.needDisplayInformation())
       writeInfo();
    else if (m_inputData.needDisplayWarranty())
       writeWarranty();
    else if (m_inputData.needDisplayConditions())
       writeConditions();
    else
       performTransformation();
}

///==============================================================================
/// @brief Displays the help.
///==============================================================================
void 
Caesar_t::writeHelp() const noexcept{

    std::cout << "[+] This program will perform Caesar encryption or decryption by 2 ways: \n";
    std::cout << "[+]    - 1º: Without parameters: Ask to user. \n";
    std::cout << "[+]    - 2º: With parameters: The program interprets the parameters in order to be able to encrypt or decrypt. \n";
    std::cout << "[+] \n";
    std::cout << "[+]    - The flags are: \n";
    std::cout << "[+]         -h: Displays the help. \n";
    std::cout << "[+]         -i: Displays the information. \n";
    std::cout << "[+]         -w: Displays the warranty. \n";
    std::cout << "[+]         -c: Displays the conditions. \n";
    std::cout << "[+]         -e: Encrypt the message. \n";
    std::cout << "[+]         -d: Decrypt the message. \n";
    std::cout << "[+]         -s: Encrypt or decrypt a text string. \n";
    std::cout << "[+]         -f: Encrypt or decrypt data from text file. \n";
    std::cout << "[+]         -k: Choose the language. English language (en) or Spanish language (sp). The default language is English. \n";
    std::cout << "[+]         -l: Level of encryption or decryption you want to use specifically. \n";
    std::cout << "[+]             If there isn't level, it performs bulk encryption or decryption. \n";
    std::cout << "[+] \n";
    std::cout << "[+] Examples with inputs parameter: \n";
    std::cout << "[+]      caesar -e -s word \n";
    std::cout << "[+]      caesar -es word \n";
    std::cout << "[+]      caesar -e -s word -l 5 \n";
    std::cout << "[+]      caesar -esl word 5 \n";
    std::cout << "[+]      caesar -e -k sp -s word -l 5 \n";
    std::cout << "[+]      caesar -eksl sp word 5 \n";
    std::cout << "[+]      caesar -e -s " << std::quoted("my text") << " \n";
    std::cout << "[+]      caesar -es " << std::quoted("my text") << " \n";
    std::cout << "[+]      caesar -e -s " << std::quoted("my text") << " -l 5 \n";
    std::cout << "[+]      caesar -esl " << std::quoted("my text") << " 5 \n";
    std::cout << "[+]      caesar -e -k sp -s " << std::quoted("my text") << " -l 5 \n";
    std::cout << "[+]      caesar -eksl sp " << std::quoted("my text") << " 5 \n";
    std::cout << "[+]      caesar -d -s word \n";
    std::cout << "[+]      caesar -ds word \n";
    std::cout << "[+]      caesar -d -s word -l 5 \n";
    std::cout << "[+]      caesar -dsl word 5 \n";
    std::cout << "[+]      caesar -d -k sp -s word -l 5 \n";
    std::cout << "[+]      caesar -dksl sp word 5 \n";
    std::cout << "[+]      caesar -d -s " << std::quoted("my text") << " \n";
    std::cout << "[+]      caesar -ds " << std::quoted("my text") << " \n";
    std::cout << "[+]      caesar -d -s " << std::quoted("my text") << " -l 5 \n";
    std::cout << "[+]      caesar -dsl " << std::quoted("my text") << " 5 \n";
    std::cout << "[+]      caesar -d -k sp -s " << std::quoted("my text") << " -l 5 \n";
    std::cout << "[+]      caesar -dksl sp " << std::quoted("my text") << " 5 \n";
    std::cout << "[+]      caesar -e -f file.txt \n";
    std::cout << "[+]      caesar -ef file.txt \n";
    std::cout << "[+]      caesar -e -f file.txt -l 5 \n";
    std::cout << "[+]      caesar -efl file.txt 5 \n";
    std::cout << "[+]      caesar -e -k sp -f file.txt -l 5 \n";
    std::cout << "[+]      caesar -ekfl sp file.txt 5 \n";
    std::cout << "[+]      caesar -e -f " << std::quoted("my file.txt") << " \n";
    std::cout << "[+]      caesar -ef " << std::quoted("my file.txt") << " \n";
    std::cout << "[+]      caesar -e -f " << std::quoted("my file.txt") << " -l 5 \n";
    std::cout << "[+]      caesar -efl " << std::quoted("my file.txt") << " 5 \n";
    std::cout << "[+]      caesar -e -k sp -f " << std::quoted("my file.txt") << " -l 5 \n";
    std::cout << "[+]      caesar -ekfl sp " << std::quoted("my file.txt") << " 5 \n";
    std::cout << "[+]      caesar -d -f file.txt \n";
    std::cout << "[+]      caesar -df file.txt \n";
    std::cout << "[+]      caesar -d -f file.txt -l 5 \n";
    std::cout << "[+]      caesar -dfl file.txt 5 \n";
    std::cout << "[+]      caesar -d -k sp -f file.txt -l 5 \n";
    std::cout << "[+]      caesar -dkfl sp file.txt 5 \n";
    std::cout << "[+]      caesar -d -f " << std::quoted("my file.txt") << " \n";
    std::cout << "[+]      caesar -df " << std::quoted("my file.txt") << " \n";
    std::cout << "[+]      caesar -d -f " << std::quoted("my file.txt") << " -l 5 \n";
    std::cout << "[+]      caesar -dfl " << std::quoted("my file.txt") << " 5 \n";
    std::cout << "[+]      caesar -d -k sp -f " << std::quoted("my file.txt") << " -l 5 \n";
    std::cout << "[+]      caesar -dkfl sp " << std::quoted("my file.txt") << " 5 \n";
    std::cout << "[+] \n";
}

///==============================================================================
/// @brief Displays the information.
///==============================================================================
void 
Caesar_t::writeInfo() const noexcept{

    std::cout << "[+] Caesar, version " << VERSION << " Copyright (C) " << YEAR << " " << PROGRAMMER << ". \n";
    std::cout << "[+] \n";
    std::cout << "[+] This program is free software: you can redistribute it and/or modify \n";
    std::cout << "[+] it under the terms of the GNU General Public License as published by \n";
    std::cout << "[+] the Free Software Foundation "<< LICENSE << ". \n";
    std::cout << "[+] \n";
    std::cout << "[+] This program comes with ABSOLUTELY NO WARRANTY; for details type 'caesar -w'. \n";
    std::cout << "[+] This is free software, and you are welcome to redistribute it under certain \n";
    std::cout << "[+] conditions; type 'caesar -c' for details. \n";
    std::cout << "[+] \n";
    std::cout << "[+] To show more help on how to use the program type 'caesar -h' for details. \n";
    std::cout << "[+] \n";
    std::cout << "[+] This program has been inplemented in C++ with standard " << STANDARD << ". \n";
    std::cout << "[+] \n";
}

///==============================================================================
/// @brief Displays the warranty.
///==============================================================================
void 
Caesar_t::writeWarranty() const noexcept{

    std::cout << "[+] Copyright (C) " << YEAR << " " << PROGRAMMER << ". \n";
    std::cout << "[+] \n";
    std::cout << "[+] This program is distributed in the hope that it will be useful, \n";
    std::cout << "[+] but WITHOUT ANY WARRANTY; without even the implied warranty of \n";
    std::cout << "[+] MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. \n";
    std::cout << "[+] \n";
    std::cout << "[+] THE ENTIRE RISK AS TO THE QUALITY AND PERFORMANCE OF THE PROGRAM \n";
    std::cout << "[+] IS WITH YOU. SHOULD THE PROGRAM PROVE DEFECTIVE, YOU ASSUME THE \n";
    std::cout << "[+] COST OF ALL NECESSARY SERVICING, REPAIR OR CORRECTION. \n";
    std::cout << "[+] \n";
    std::cout << "[+] GNU General Public License for more details. \n";
    std::cout << "[+] \n";
    std::cout << "[+] You should have received a copy of the GNU General Public License \n";
    std::cout << "[+] along with this program.  If not, see <https://www.gnu.org/licenses/>. \n";
    std::cout << "[+] \n";
}

///==============================================================================
/// @brief Displays the conditions.
///==============================================================================
void 
Caesar_t::writeConditions() const noexcept{

    std::cout << "[+] Copyright (C) " << YEAR << " " << PROGRAMMER << ". \n";
    std::cout << "[+] \n";
    std::cout << "[+] This program is free software: you can redistribute it and/or modify \n";
    std::cout << "[+] it under the terms of the GNU General Public License as published by \n";
    std::cout << "[+] the Free Software Foundation "<< LICENSE << ". \n";
    std::cout << "[+] \n";
    std::cout << "[+] GPL license give you 4 freedoms: \n";
    std::cout << "[+] 1st: Freedom to use the software for any purpose. \n";
    std::cout << "[+] 2nd: Freedom to study how the software works and adapt it to your needs. \n";
    std::cout << "[+] 3rd: Freedom to distribute copies of the software. \n";
    std::cout << "[+] 4th: Freedom to improve the software and share those improvements. \n";
    std::cout << "[+] \n";
    std::cout << "[+] Any other program derived from it must be distributed under the same license. \n";
    std::cout << "[+] In addition, any program under this license must be distributed with source code. \n";
    std::cout << "[+] This license does not prohibited commercial distribution of the software \n";
    std::cout << "[+] if the source code is distributed. \n";
    std::cout << "[+] \n";    
    std::cout << "[+] GNU General Public License for more details. \n";
    std::cout << "[+] \n";
    std::cout << "[+] You should have received a copy of the GNU General Public License \n";
    std::cout << "[+] along with this program.  If not, see <https://www.gnu.org/licenses/>. \n";
    std::cout << "[+] \n";
}

///==============================================================================
/// @brief Asks the user whether to encrypt or decrypt.
///==============================================================================
void
Caesar_t::askEncryptOrDecrypt() noexcept{

    char whatToDo { ' ' };

    do{
       std::cout << "[+] Do you want encrypt or decrypt?: [e/d]\n";

       std::cin >> whatToDo;
       std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

       whatToDo= static_cast<char>(std::tolower(static_cast<unsigned char>(whatToDo)));
    }while (whatToDo != CHARACTER_e && whatToDo != CHARACTER_d);

    m_inputData.setFlagEncrypt(whatToDo == CHARACTER_e);
    m_inputData.setFlagDecrypt(whatToDo == CHARACTER_d);
}

///==============================================================================
/// @brief Asks the user whether to transform a string or a file.
///==============================================================================
void
Caesar_t::askFileOrString(){

    char whatIs   { ' ' };
    bool isString { false };
    bool isFile   { false };

    do{
       std::cout << "[+] Is a file or string?: [f/s]\n";

       std::cin >> whatIs;
       std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

       whatIs= static_cast<char>(std::tolower(static_cast<unsigned char>(whatIs)));
    }while (whatIs != CHARACTER_f && whatIs != CHARACTER_s);

    isString= whatIs == CHARACTER_s;
    isFile  = whatIs == CHARACTER_f;

    m_inputData.setFlagString(isString);
    m_inputData.setFlagFile(isFile);
    
    askPathOrStringValue(isFile);
}

///==============================================================================
/// @brief Asks the user the path of the file or the string according to the 
///        answer of the previous question above.
/// @param isFile It is true if it was specified in the previous question that 
///               the transformation should be from a file, and false otherwise.
///==============================================================================
void
Caesar_t::askPathOrStringValue(const bool isFile){

    std::string sVar { "" };

    do{
       if (isFile){
          m_inputData.pushNextParameter(CHARACTER_f);
          std::cout << "[+] Write the path (including regular file): \n";
       }
       else{
          m_inputData.pushNextParameter(CHARACTER_s);
          std::cout << "[+] Write the value of the string: \n";
       }

       std::getline(std::cin, sVar);
     }while (!m_inputData.assignInformation(sVar));
     
}

///==============================================================================
/// @brief Asks the user whether to transform from specific language.
///==============================================================================
void
Caesar_t::askLanguage(){

    char wantLanguage    { ' ' };
    bool isOtherLanguage { false };

    do{
       std::cout << "[+] Do you want a specific characters?: [y/n]. If you don't want a specific characters. English's characters will be used by default.\n";

       std::cin >> wantLanguage;
       std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

       wantLanguage= static_cast<char>(std::tolower(static_cast<unsigned char>(wantLanguage)));
    }while (wantLanguage != CHARACTER_y && wantLanguage != CHARACTER_n);
    
    isOtherLanguage= wantLanguage == CHARACTER_y;
    
    m_inputData.setFlagLanguage(isOtherLanguage);
    
    if (isOtherLanguage)
       askSpecificLanguage();
}

///==============================================================================
/// @brief Asks the user the language according to the answer of the previous 
///        question above.
///==============================================================================
void
Caesar_t::askSpecificLanguage(){

//==============================================================================
//                         LAMBDA toLowercase
//==============================================================================
    auto toLowercase= [&](char &c){
        c= static_cast<char>(std::tolower(static_cast<unsigned char>(c)));
    };

    std::string sVar { "" };

    do{
       m_inputData.pushNextParameter(CHARACTER_k);

       std::cout << "[+] Type the characters you want the program to use: (en=ENGLISH/sp=SPANISH): \n";
       std::getline(std::cin, sVar);

       std::for_each(sVar.begin(), sVar.end(), toLowercase);    
    }while (!m_inputData.assignInformation(sVar));
}

///==============================================================================
/// @brief Asks the user whether to transform at a specific level.
///==============================================================================
void
Caesar_t::askForSpecificLevel(){

    char wantLevel   { ' ' };
    bool isWithLevel { false };

    do{
       std::cout << "[+] Do you want a specific level?: [y/n]\n";

       std::cin >> wantLevel;
       std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

       wantLevel= static_cast<char>(std::tolower(static_cast<unsigned char>(wantLevel)));
    }while (wantLevel != CHARACTER_y && wantLevel != CHARACTER_n);

    isWithLevel= wantLevel == CHARACTER_y;

    m_inputData.setFlagLevel(isWithLevel);

    if (isWithLevel)
       askLevel();
}

///==============================================================================
/// @brief Asks for the specific level according to the answer of the previous 
///        question above. 
///==============================================================================
void
Caesar_t::askLevel(){

    std::string sLevel { "" };

    do{
       m_inputData.pushNextParameter('l');
       std::cout << "[+] Write the level: [MIN: " << m_inputData.getMinLevel() << " - MAX: " << m_inputData.getMaxLevel()  << "] \n";

       std::getline(std::cin, sLevel);
    }while (!m_inputData.assignInformation(sLevel));
}

///==============================================================================
/// @brief Manages bulk encryption or decryption.
/// @param data Data to be transformed.
///==============================================================================
void 
Caesar_t::bulkEncryptionOrDecryption(const std::string& data) const noexcept{

    for (int currentLevel= m_inputData.getMinLevel(); currentLevel <= m_inputData.getMaxLevel(); currentLevel++){
       std::cout << "[+]--- Level: " << currentLevel << " ---\n";
       std::cout << "[+] \n";
       encryptionOrDecryption(data, currentLevel);
       std::cout << "[+]----------------------------------------------------------------------\n";
       std::cout << "[+] \n";
    }
}

///==============================================================================
/// @brief Manages specific encryption or decryption.
/// @param data Data to be transformed.
/// @param currentLevel Current level to perform the transformation.
///==============================================================================
void
Caesar_t::encryptionOrDecryption(const std::string& data, const int currentLevel) const noexcept{

    if (m_inputData.wantEncrypt())
       transform(data, currentLevel);
    else
       transform(data, currentLevel*(-1));
    
}

///==============================================================================
/// @brief Manages encryption or decryption.
/// @param data Data to be transformed.
/// @param currentLevel Current level to perform the transformation.
///==============================================================================
void
Caesar_t::transform(const std::string& data, const int currentLevel) const noexcept{

    size_t index { 0 };

    while (index < data.length()){

                      int length { m_inputData.getUTF8CharLength(static_cast<unsigned char>(data[index])) };
              std::string c      { data.substr(index, length) };
          DataCharacter_t dC     { };

          m_inputData.findCharacterData(c, dC);

          switch (dC.type){
             case capitalLetter:
                std::cout << m_inputData.getTransformedCharacter(m_inputData.getAlphabetUppercase(), dC.position, currentLevel);

                break;
             case smallLetter:
                std::cout << m_inputData.getTransformedCharacter(m_inputData.getAlphabetLowercase(), dC.position, currentLevel);

                break;
             default:
                std::cout << c;
          }
          
          index+= length;
    }
    
    std::cout << '\n';
}

} // SherpadCaesar
