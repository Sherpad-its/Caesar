// SPDX-License-Identifier: GPL-v3.0
#include <algorithm>
#include <fstream>
#include <filesystem>
#include <iostream>
#include "args/arguments.hpp"
#include "excep/caesarException.hpp"
#include "data.hpp"

namespace SherpadCaesar {

///==============================================================================
/// @brief Constructor of the Data_t class.
/// @param args Input arguments.
///==============================================================================
Data_t::Data_t(Arguments_t& args){

    if (!args.isEmpty()){
       std::vector<std::string>& allArguments { args.getAllArguments() };

       for (std::string& currentArgument : allArguments)
           processArgument(currentArgument);
       
       if (m_flagsWithParameters != 0)
           throw CaesarException_t(EXCEPTION_5);
    }
}

///==============================================================================
/// @brief Initialize the encryption and decryption flags.
///==============================================================================
void
Data_t::initEncryptOrDecrypt() noexcept{
    
    m_flagEncrypt= false;
    m_flagDecrypt= false; 
}

///==============================================================================
/// @brief Initialize the string and file flags and data.
///==============================================================================
void
Data_t::initFileOrString() noexcept{
    
    m_flagString = false;
    m_flagFile= false;
    m_data= STRING_EMPTY.data();
    m_path= STRING_EMPTY.data();
}

///==============================================================================
/// @brief Initialize the language flag and the language.
///==============================================================================
void
Data_t::initLanguage() noexcept{
    
    m_flagLanguage= false;
    m_language= STRING_EMPTY.data();
}

///==============================================================================
/// @brief Initializes the level flag and the level.
///==============================================================================
void
Data_t::initLevel() noexcept{
    m_flagLevel= false;
    m_level= 0;
}

///==============================================================================
/// @brief Interprets the data and decides where to store it.
/// @param cArg Current argument to process.
/// @return isArgValid Indicates whether the currently entered parameter is valid 
///         or not.
///==============================================================================
bool
Data_t::assignInformation(std::string& cArg){

    bool isArgValid { false };

    if (!m_nextParameters.empty()){
       switch (m_nextParameters.front()){
          case CHARACTER_k:
             if ((m_flagLanguage && m_language == STRING_EMPTY.data()) && (isAValidLanguage(cArg))){
                isArgValid= true;
                m_language= std::move(cArg);
                loadOtherAlphabet();
             }
             break;
          case CHARACTER_s:
             if (m_flagString && m_data == STRING_EMPTY.data()){
                isArgValid= true;
                m_data= std::move(cArg);
             }
             break;
          case CHARACTER_f:
             if ((m_flagFile && m_path == STRING_EMPTY.data()) && (isAValidPath(cArg))){
                isArgValid= true;
                m_path= std::move(cArg);
                loadDataFromFile(m_path, m_data);
             }
             break;
          case CHARACTER_l:
             if ((m_flagLevel && m_level == 0) && (isAValidLevelValue(cArg))){
                isArgValid= true;
                m_level= std::stoi(cArg.data());
             }
             break;
          default:
             throw CaesarException_t(EXCEPTION_2);
       }

       m_nextParameters.pop();
       m_flagsWithParameters--;
    }
    else{
       throw CaesarException_t(EXCEPTION_1);
    }

    return isArgValid;
}


///==============================================================================
/// @brief Returns the flag's help.
/// @return m_flagHelp Flag´s help.
///==============================================================================
bool
Data_t::needDisplayHelp() const noexcept{

    return m_flagHelp;
}

///==============================================================================
/// @brief Returns the flag's information.
/// @return m_flagInformation Flag´s information.
///==============================================================================
bool
Data_t::needDisplayInformation() const noexcept{

    return m_flagInformation;
}

///==============================================================================
/// @brief Returns the flag's warranty.
/// @return m_flagWarranty Flag´s warranty.
///==============================================================================
bool
Data_t::needDisplayWarranty() const noexcept{

    return m_flagWarranty;
}

///==============================================================================
/// @brief Returns the flag's conditions.
/// @return m_flagConditions Flag´s conditions.
///==============================================================================
bool
Data_t::needDisplayConditions() const noexcept{

    return m_flagConditions;
}

///==============================================================================
/// @brief Indicates whether the user wants to encrypt or not.
/// @return true whether encryption's flag is activated and decryption's flag is
///         disactivated.
///==============================================================================
bool
Data_t::wantEncrypt() const noexcept{
    
    return (m_flagEncrypt && !m_flagDecrypt);
}

///==============================================================================
/// @brief Indicates whether the user wants to decrypt or not.
/// @return true whether decryption's flag is activated and encryption's flag is
///         disactivated.
///==============================================================================
bool
Data_t::wantDecrypt() const noexcept{
    
    return (!m_flagEncrypt && m_flagDecrypt);
}
///==============================================================================
/// @brief Indicates whether the user wants to transform a string.
/// @return true whether string's flag is activated and the data is informed and
///         file's flag is disactivated.
///==============================================================================
bool
Data_t::isFromString() const noexcept{

    return (m_flagString && m_data != STRING_EMPTY.data() && !m_flagFile);
}

///==============================================================================
/// @brief Indicates whether the user wants to transform a file's content.
/// @return true whether file's flag is activated and the path is informed and
///         string's flag is disactivated.
///==============================================================================
bool
Data_t::isFromFile() const noexcept{

    return (m_flagFile && m_path != STRING_EMPTY.data() && !m_flagString);
}

///==============================================================================
/// @brief Indicates whether the selected language is English.
/// @return true whether language´s flag is disactivated and the field 
///         m_language is empty or language´s flag is activated and the field 
///         m_language is "en".
///==============================================================================
bool
Data_t::isEnglishLanguage() const noexcept{

    return ((!m_flagLanguage && m_language == STRING_EMPTY.data()) || (m_flagLanguage && m_language == ENGLISH_LANGUAGE.data()));
}

///==============================================================================
/// @brief Indicates whether the selected language is Spanish.
/// @return true whether language´s flag is activated and the field 
///         m_language is "sp".
///==============================================================================
bool
Data_t::isSpanishLanguage() const noexcept{

    return (m_flagLanguage && m_language == SPANISH_LANGUAGE.data());
}

///==============================================================================
/// @brief Indicates whether the transformation is bulk.
/// @return true whether level's flag isn't activated and the level's 
///         encryption/decryption is equal to 0.
///==============================================================================
bool
Data_t::isBulk() const noexcept{

    return (!m_flagLevel && m_level == 0);
}

///==============================================================================
/// @brief Indicates whether the transformation is specific.
/// @return true whether level's flag is activated and the level's 
///         encryption/decryption is greather than 0.
///==============================================================================
bool
Data_t::isSpecific() const noexcept{

    return (m_flagLevel && m_level > 0);
}

///==============================================================================
/// @brief Sets the encryption flag.
/// @param fE Value to assign to the encryption flag.
///==============================================================================
void
Data_t::setFlagEncrypt(const bool fE) noexcept{

    m_flagEncrypt= fE;
}

///==============================================================================
/// @brief Sets the decryption flag.
/// @param fD Value to assign to the decryption flag.
///==============================================================================
void
Data_t::setFlagDecrypt(const bool fD) noexcept{

    m_flagDecrypt= fD;
}

///==============================================================================
/// @brief Sets the string flag.
/// @param fS Value to assign to the string flag.
///==============================================================================
void
Data_t::setFlagString(const bool fS) noexcept{

    m_flagString= fS;
}

///==============================================================================
/// @brief Sets the file flag.
/// @param fF Value to assign to the file flag.
///==============================================================================
void
Data_t::setFlagFile(const bool fF) noexcept{

    m_flagFile= fF;
}

///==============================================================================
/// @brief Sets the language flag.
/// @param fLg Value to assign to the language flag.
///==============================================================================
void
Data_t::setFlagLanguage(const bool fLg) noexcept{

    m_flagLanguage= fLg;
}

///==============================================================================
/// @brief Sets the level flag.
/// @param fLv Value to assign to the level flag.
///==============================================================================
void
Data_t::setFlagLevel(const bool fLv) noexcept{

    m_flagLevel= fLv;
}

///==============================================================================
/// @brief Pushes input flags in the queue.
/// @param cChar Current character to be pushed in the queue. 
///==============================================================================
void
Data_t::pushNextParameter(const char cChar) noexcept{

    m_nextParameters.push(cChar);
}

///==============================================================================
/// @brief Gets the current selected level.
/// @return m_level that contains the currently selected level.
///==============================================================================
const int
Data_t::getLevel() const noexcept{

    return m_level;
}

///==============================================================================
/// @brief Gets the minimum level that can be selected.
/// @return m_minLevel that contains the minimum level that can be selected.
///==============================================================================
const int
Data_t::getMinLevel() const noexcept{

    return m_minLevel;
}

///==============================================================================
/// @brief Gets the maximum level that can be selected.
/// @return m_minLevel that contains the maximum level that can be selected.
///==============================================================================
const int
Data_t::getMaxLevel() const noexcept{

    return m_maxLevel;
}

///==============================================================================
/// @brief Gets the data to transform.
/// @return m_data that contains the data to transform.
///==============================================================================
const std::string&
Data_t::getData() const noexcept{

    return m_data;
}

///==============================================================================
/// @brief Gets the alphabet in uppercase letters.
/// @return m_alphabetUppercase that contains the alphabet in uppercase letters.
///==============================================================================
const std::string&
Data_t::getAlphabetUppercase() const noexcept{

    return m_alphabetUppercase;
}

///==============================================================================
/// @brief Gets the alphabet in lowercase letters.
/// @return m_alphabetLowercase that contains the alphabet in lowercase letters.
///==============================================================================
const std::string&
Data_t::getAlphabetLowercase() const noexcept{

    return m_alphabetLowercase;
}

///==============================================================================
/// @brief Searches the data of the current character to be transformed.
/// @param c Current character to search for in the alphabets.
/// @param dC Current character data if found.
/// @return true whether the current character was found in any of the alphabets.
///==============================================================================
bool
Data_t::findCharacterData(const std::string& c, DataCharacter_t& dC) const noexcept{

    return (searchCharacter(c, dC, m_alphabetUppercase, capitalLetter) || searchCharacter(c, dC, m_alphabetLowercase, smallLetter));
}

///==============================================================================
/// @brief Gets the transformed character either encrypted or decrypted 
///        regard of language.
/// @param alphabet String containing all the characters of the selected 
///        language.
/// @param initialPosition Current character position in the alphabet.
/// @param currentLevel Current level to perform the transformation.
/// @return A character considering the shift and the number of letters in 
///         the alphabet.
///==============================================================================
std::string
Data_t::getTransformedCharacter(const std::string& alphabet, const int initialPosition, const int currentLevel) const noexcept{
    
    if (isEnglishLanguage())
       return transformEnglishCharacter(alphabet, initialPosition + currentLevel);
    else
       return transformOtherLanguageCharacter(alphabet, initialPosition, currentLevel);
}

///==============================================================================
/// @brief Gets the transformed character either encrypted or decrypted in 
///        English language.
/// @param alphabet String containing all the characters of the selected 
///        language.
/// @param scrolling Shift for performing the transformation.
/// @return A character considering the shift and the number of letters in 
///         the English alphabet.
///==============================================================================
std::string
Data_t::transformEnglishCharacter(const std::string& alphabet, const int scrolling) const noexcept{
    
    if (scrolling >= 0)
       return alphabet.substr(scrolling % alphabet.length(), 1);
    else
       return alphabet.substr((alphabet.length() + scrolling) % alphabet.length(), 1);
}

///==============================================================================
/// @brief Gets the transformed character either encrypted or decrypted in 
///        other language.
/// @param alphabet String containing all the characters of the selected 
///        language.
/// @param initialPosition Current character position in the alphabet.
/// @param currentLevel Current level to perform the transformation.
/// @return A character considering the shift and the number of letters in 
///         other alphabet.
///==============================================================================
std::string
Data_t::transformOtherLanguageCharacter(const std::string& alphabet, const int initialPosition, const int currentLevel) const noexcept{
    
    if (currentLevel > 0)
       return getEncryptedCharacter(alphabet, initialPosition, currentLevel);
    else
       return getDecryptedCharacter(alphabet, initialPosition, currentLevel);
}

///==============================================================================
/// @brief Gets the transformed character to encrypt in other language.
/// @param alphabet String containing all the characters of the selected 
///        language.
/// @param initialPosition Current character position in the alphabet.
/// @param currentLevel Current level to perform the transformation.
/// @return A character encrypted.
///==============================================================================
std::string
Data_t::getEncryptedCharacter(const std::string& alphabet, const int initialPosition, const int currentLevel) const noexcept{
    
    int currentPosition { initialPosition };
    int length          { getUTF8CharLength(static_cast<unsigned char>(alphabet[currentPosition])) };
    int distance        { currentLevel };
    
    while (distance > 0){
       currentPosition= (currentPosition + length) % alphabet.length();
                length= getUTF8CharLength(static_cast<unsigned char>(alphabet[currentPosition]));

       distance--;
    }
                     
    return alphabet.substr(currentPosition, length);
}

///==============================================================================
/// @brief Gets the transformed character to decrypt in other language.
/// @param alphabet String containing all the characters of the selected 
///        language.
/// @param initialPosition Current character position in the alphabet.
/// @param currentLevel Current level to perform the transformation.
/// @return A character decrypted.
///==============================================================================
std::string
Data_t::getDecryptedCharacter(const std::string& alphabet, const int initialPosition, const int currentLevel) const noexcept{
    
    int currentPosition { initialPosition };
    int length          { getUTF8CharLength(static_cast<unsigned char>(alphabet[currentPosition])) };
    int distance        { currentLevel };
    
    while (distance < 0){
       currentPosition= nextDecryptPosition(currentPosition,alphabet);
       length= getUTF8CharLength(static_cast<unsigned char>(alphabet[currentPosition]));
       
       //We reposition until we find the start of a UTF-8 characters.
       while (length < 0){
          currentPosition= nextDecryptPosition(currentPosition,alphabet);
                   length= getUTF8CharLength(static_cast<unsigned char>(alphabet[currentPosition]));
       }

       distance++;
    }
                     
    return alphabet.substr(currentPosition, length);
}

///==============================================================================
/// @brief Loads the uppercase and lowercase alphabets when the language is 
///        diferent to English.
///==============================================================================
void
Data_t::loadOtherAlphabet() noexcept{
    
    if (isSpanishLanguage())
        loadNewAlphabet(spanishUppercaseAlphabet, spanishLowercaseAlphabet, MAX_LEVEL_SPANISH);    
}

///==============================================================================
/// @brief Loads the data of the selected language.
/// @param uppercase Alphabet of the selected language in uppercase.
/// @param lowercase Alphabet of the selected language in lowercase.
/// @param maxLevel Maximum level that can be selected for that alphabet.
/// @param loc Locale settings of the language.
///==============================================================================
void   
Data_t::loadNewAlphabet(const std::string_view uppercase, const std::string_view lowercase, const int maxLevel) noexcept{

    m_alphabetUppercase= uppercase.data();
    m_alphabetLowercase= lowercase.data();
    m_maxLevel= maxLevel;
}

///==============================================================================
/// @brief Interprets the current argument to store it in the correct data 
///        member.
/// @param cArg Current argument to process.
///==============================================================================
void
Data_t::processArgument(std::string& cArg){

//==============================================================================
//                         LAMBDA processFlags
//==============================================================================
    auto processFlags= [&](const char &c){

        char lowerChar= static_cast<char>(std::tolower(static_cast<unsigned char>(c)));

        switch (lowerChar){
           case CHARACTER_h:
              m_flagHelp= true;
              break;
           case CHARACTER_i:
              m_flagInformation= true;
              break;
           case CHARACTER_w:
              m_flagWarranty= true;
              break;
           case CHARACTER_c:
              m_flagConditions= true;
              break;
           case CHARACTER_e:
              m_flagEncrypt= true;
              break;
           case CHARACTER_d:
              m_flagDecrypt= true;
              break;
           case CHARACTER_s:
              m_flagString= true;
              m_nextParameters.emplace(lowerChar);
              m_flagsWithParameters++;
              break;
           case CHARACTER_f:
              m_flagFile= true;
              m_nextParameters.emplace(lowerChar);
              m_flagsWithParameters++;
              break;
           case CHARACTER_k:
              if (!m_flagString && !m_flagFile && !m_flagLevel){
                 m_flagLanguage= true;
                 m_nextParameters.emplace(lowerChar);
                 m_flagsWithParameters++;
              }
              else{
                 throw CaesarException_t(EXCEPTION_4);
              }
              break;
           case CHARACTER_l:
              m_flagLevel= true;
              m_nextParameters.emplace(lowerChar);
              m_flagsWithParameters++;
              break;
           default:
              throw CaesarException_t(EXCEPTION_0);
        }
    };

    switch (cArg.front()){
       case CHARACTER_less:
          std::for_each(cArg.begin() + 1, cArg.end(), processFlags);
          break;
       default:
          assignInformation(cArg);
    }
}

///==============================================================================
/// @brief Validates whether the path exists and the file is a regular file.
/// @param cPath Path where the file is located.
/// @return isValid is true whether the path exists and the file is a regular 
///         file.
///==============================================================================
bool    
Data_t::isAValidPath(const std::string& cPath) const noexcept{
    
    bool isValid { true };
    //Get the path with the input file.
    std::filesystem::path currentPath { cPath };
    //We use for Non-throw Exceptions. 
    std::error_code eCode;
    
    //We check if exist input file.
    if (!std::filesystem::exists(cPath, eCode)){
       isValid= false;
       std::cout << "[+] No such file. Check if the current working directory has such a file or try it again with absolute path. \n";
       std::cout << "[+] \n";
    }
    else{
       //If exist the input file we check if the input file is a regular file.
       if (!std::filesystem::is_regular_file(cPath, eCode)){
          isValid= false;
          std::cout << "[+] This isn't a regular file. Must be a regular file. \n";
          std::cout << "[+] \n";
       }
    }
    
    return isValid;
}

///==============================================================================
/// @brief Validates whether the language is English or Spanish.
/// @param cLanguage The language selected.
/// @return isValid is true whether the language is English or Spanish.
///==============================================================================
bool    
Data_t::isAValidLanguage(const std::string& cLanguage) const noexcept{

    bool isValid { false };

    if (cLanguage == ENGLISH_LANGUAGE.data() ||
        cLanguage == SPANISH_LANGUAGE.data())
       isValid= true;
    else{
       std::cout << "[+] The language entered is not correct. It must be " << std::quoted("en") << " to ENGLISH and " << std::quoted("sp") << " to SPANISH. \n";
       std::cout << "[+] \n";
    }
    
    return isValid;
}

///==============================================================================
/// @brief Validates whether the selected level is valid.
/// @param sLevel The level selected.
/// @return isValid is true whether the level is valid.
///==============================================================================
bool
Data_t::isAValidLevelValue(const std::string& sLevel) const{

    bool isValid { false };

    if (sLevel.length() > 0 && canTransformToInteger(sLevel)){
       int level { std::stoi(sLevel) };

       if (level >= m_minLevel && level <= m_maxLevel)
          isValid= true;
       else{
          std::cout << "[+] Invalid value. You must enter a number between " << m_minLevel << " and " << m_maxLevel  << ". Including both. \n";
          std::cout << "[+] \n";
       }
    }
    
    return isValid;
}

///==============================================================================
/// @brief Validates whether the string has a possible format to transform to 
///        integer.
/// @param sLevel String with the level selected.
/// @return canIt is true whether the level can to be transform in integer.
///==============================================================================
bool
Data_t::canTransformToInteger(const std::string& sLevel) const noexcept{

    bool canIt { false };
    int  value { -1 };

    if (sLevel.length() == 1)
       value= sLevel[0] - '0';
    else{ // if (sLevel.length() > 1)
       if (sLevel[0] == '+' || sLevel[0] == '-')
          value= sLevel[1] - '0';
       else
          value= sLevel[0] - '0';
    }

    if (value >= 0 && value <= 9)
       canIt= true;
    else{
       std::cout << "[+] Invalid value. You must enter a numerical value. \n";
       std::cout << "[+] \n";
    }
    
    return canIt;
}

///==============================================================================
/// @brief Loads data from a file.
/// @param fileName Path where the file is located.
/// @param data The file information will be stored.
///==============================================================================
void
Data_t::loadDataFromFile(const std::string_view fileName, std::string& data){

    std::ifstream  inputFileStream { };
    
    //Open the input file.    
    inputFileStream.open(fileName.data(), std::ios_base::in);
    
    if (inputFileStream.is_open()){
       //Load the file in the string.
       std::string buffer { std::istreambuf_iterator<char> { inputFileStream }, std::istreambuf_iterator<char> { } };

       data= std::move(buffer);

       inputFileStream.close();
    }
    else
       throw CaesarException_t(EXCEPTION_3);
}

///==============================================================================
/// @brief Searches for the current character's data in the alphabet.
/// @param c Character to search.
/// @param dC The searched information will be stored.
/// @param alphabet String containing all the characters of the selected 
///        language.
/// @param type Indicates the type of characters in the alphabet: lowercase or 
///        uppercase.
/// @return true whether the current character is found in the alphabet.
///==============================================================================
bool
Data_t::searchCharacter(const std::string& c, DataCharacter_t& dC, const std::string& alphabet, const TypeCharacter_t type) const noexcept{

                 bool found  { false };
    long unsigned int pivot  { 0 };

    while ((!found) && (pivot < alphabet.length())){
               int      length { getUTF8CharLength(static_cast<unsigned char>(alphabet[pivot])) };
       std::string currentChar { alphabet.substr(pivot, length) };
       
       if (c == currentChar){
          dC.character= c;
          dC.type= type;
          dC.position= pivot;
          found= true;
       }
        else
           pivot+= length;
    }
    
    return found;
}

///==============================================================================
/// @brief Calculates the size of a UTF-8 character in bytes.
/// @param byte current byte to validate.
/// @return the size of a UTF-8 character in bytes. If the byte is not one of the 
///         expected ones, it returns -1
///==============================================================================
int 
Data_t::getUTF8CharLength(unsigned char byte) const noexcept{
    
    if ((byte & 0x80) == 0x00)      // 0xxxxxxx - One-byte character.
       return 1;
    else if ((byte & 0xE0) == 0xC0) // 110xxxxx - Two-byte character.
       return 2;
    else if ((byte & 0xF0) == 0xE0) // 1110xxxx - Three-byte character.
       return 3;
    else if ((byte & 0xF8) == 0xF0) // 11110xxx - Four-byte character.
       return 4;
    else                            // Not valid.
       return -1;

}

///==============================================================================
/// @brief Gets the next position to validate when descrypting.
/// @param initialPosition Current character position in the alphabet.
/// @param alphabet String containing all the characters of the selected 
///        language. 
/// @return The next position to validate.
///==============================================================================
int
Data_t::nextDecryptPosition(const int initialPosition, const std::string& alphabet) const noexcept{

    int currentPosition { initialPosition };
    
    if (currentPosition == 0)
       currentPosition= alphabet.length() - 1;
    else
       currentPosition--;
    
    return currentPosition;
}

} // namespace SherpadCaesar
