// SPDX-License-Identifier: GPL-v3.0
#pragma once

#include <queue>
#include <string>
#include "utils/utils.hpp"

namespace SherpadCaesar{

//Forward Declaration.
class Arguments_t;

/// @class Data_t
/// @brief Interprets the parameters stored in the Arguments_t class, updating the necessary data, 
///        verifies that the data is correct, and performs the transformations according to the Caesar_t class.

    class Data_t{
        private:
                                                              /// @brief Indicates whether the user wants the help to be displayed or not.
                                                       bool   m_flagHelp            { false };

                                                              /// @brief Indicates whether the user wants the information to be displayed or not.
                                                       bool   m_flagInformation     { false };

                                                              /// @brief Indicates whether the user wants the warranty to be displayed or not.
                                                       bool   m_flagWarranty        { false };

                                                              /// @brief Indicates whether the user wants the conditions to be displayed or not.
                                                       bool   m_flagConditions      { false };

                                                              /// @brief Indicates whether the user wants to encrypt or not.
                                                       bool   m_flagEncrypt         { false };

                                                              /// @brief Indicates whether the user wants to decrypt or not.
                                                       bool   m_flagDecrypt         { false };

                                                              /// @brief Indicates whether the user wants to transform a string or not.
                                                       bool   m_flagString          { false };

                                                              /// @brief Indicates whether the user wants to transform a data file or not.
                                                       bool   m_flagFile            { false };

                                                              /// @brief Indicates whether the user wants to transform in a specific language or not.
                                                       bool   m_flagLanguage        { false };

                                                              /// @brief Indicates whether the user wants to transform in a specific level or not.
                                                       bool   m_flagLevel           { false };

                                                              /// @brief Contains the text to be transformed.
                                                std::string   m_data                { "" };

                                                              /// @brief Contains the path of the text to be transformed if it comes from a file.
                                                std::string   m_path                { "" };

                                                              /// @brief Contains the language of the text to be transformed. If not specified, it will default to English. 
                                                std::string   m_language            { "" };

                                                              /// @brief Contains the specific level at which to perform the transformation. If it is 0, a bulk transformation will be performed.
                                                        int   m_level               { 0 };

                                                              /// @brief Contains the minimum level to transform the message. It will always be 1.
                                      const             int   m_minLevel            { MIN_LEVEL };

                                                              /// @brief Contains the maximum level to transform the message. Depends on the language. It will be the maximum level in English by default.
                                                        int   m_maxLevel            { MAX_LEVEL_ENGLISH };

                                                              /// @brief A queue that contains the order in which the flags were entered. It is expected that the input data is in the same order as the flags.
                                            std::queue<char>  m_nextParameters      { };

                                                              /// @brief Alphabet in uppercase letters. English alphabet by default.
                                                std::string   m_alphabetUppercase   { englishUppercaseAlphabet.data() };

                                                              /// @brief Alphabet in lowercase letters. English alphabet by default.
                                                std::string   m_alphabetLowercase   { englishLowercaseAlphabet.data() };
                                                
                                                              /// @brief Contains the number of flags that require parameters.
                                                        int   m_flagsWithParameters { 0 };

                                                       void   processArgument(std::string&);
                                                       bool   isAValidPath(const std::string&)                                                                         const noexcept;
                                                       bool   isAValidLanguage(const std::string&)                                                                     const noexcept;
                                                       bool   isAValidLevelValue(const std::string&)                                                                   const;
                                                       bool   canTransformToInteger(const std::string&)                                                                const noexcept;
                                                       void   loadDataFromFile(const std::string_view, std::string&);
                                                       bool   searchCharacter(const std::string&, DataCharacter_t&, const std::string&, const TypeCharacter_t)         const noexcept;
                                                        int   nextDecryptPosition(const int, const std::string&)                                                       const noexcept;

        public:
                explicit                                      Data_t(Arguments_t&);
                                                              Data_t(const Data_t&)              = delete;
                                                              Data_t(      Data_t&&)             = delete;
                                                             ~Data_t()                                     = default;
                                                              Data_t&  operator=(const Data_t&)  = delete;
                                                              Data_t&  operator=(      Data_t&&) = delete;
                                                       void   initEncryptOrDecrypt()                                                                                            noexcept;
                                                       void   initFileOrString()                                                                                                noexcept;
                                                       void   initLanguage()                                                                                                    noexcept;
                                                       void   initLevel()                                                                                                       noexcept;
                                                       bool   assignInformation(std::string&);
                                                       bool   needDisplayHelp()                                                                                           const noexcept;
                                                       bool   needDisplayInformation()                                                                                    const noexcept;
                                                       bool   needDisplayWarranty()                                                                                       const noexcept;
                                                       bool   needDisplayConditions()                                                                                     const noexcept;
                                                       bool   wantEncrypt()                                                                                               const noexcept;
                                                       bool   wantDecrypt()                                                                                               const noexcept;
                                                       bool   isFromString()                                                                                              const noexcept;
                                                       bool   isFromFile()                                                                                                const noexcept;
                                                       bool   isEnglishLanguage()                                                                                         const noexcept;
                                                       bool   isSpanishLanguage()                                                                                         const noexcept;
                                                       bool   isBulk()                                                                                                    const noexcept;
                                                       bool   isSpecific()                                                                                                const noexcept;
                                                       void   setFlagEncrypt(const bool)                                                                                        noexcept;
                                                       void   setFlagDecrypt(const bool)                                                                                        noexcept;
                                                       void   setFlagString(const bool)                                                                                         noexcept;
                                                       void   setFlagFile(const bool)                                                                                           noexcept;
                                                       void   setFlagLanguage(const bool)                                                                                       noexcept;
                                                       void   setFlagLevel(const bool)                                                                                          noexcept;
                                                       void   pushNextParameter(const char)                                                                                     noexcept;
                                          const         int   getLevel()                                                                                                  const noexcept;
                                          const         int   getMinLevel()                                                                                               const noexcept;
                                          const         int   getMaxLevel()                                                                                               const noexcept;
                                          const std::string&  getData()                                                                                                   const noexcept;
                                          const std::string&  getAlphabetUppercase()                                                                                      const noexcept;
                                          const std::string&  getAlphabetLowercase()                                                                                      const noexcept;
                                                       bool   findCharacterData(const std::string&, DataCharacter_t&)                                                     const noexcept;
                                                std::string   getCharacter(const std::string&, const int)                                                                 const noexcept;
                                                       void   loadOtherAlphabet()                                                                                               noexcept;
                                                       void   loadNewAlphabet(const std::string_view, const std::string_view, const int)                                        noexcept;
                                                std::string   getTransformedCharacter(const std::string&, const int, const int)                                           const noexcept;
                                                std::string   transformEnglishCharacter(const std::string&, const int)                                                    const noexcept;
                                                std::string   transformOtherLanguageCharacter(const std::string&, const int, const int)                                   const noexcept;
                                                std::string   getEncryptedCharacter(const std::string&, const int, const int)                                             const noexcept;
                                                std::string   getDecryptedCharacter(const std::string&, const int, const int)                                             const noexcept;
                                                        int   getUTF8CharLength(unsigned char)                                                                            const noexcept;
                                                       
    };

} // namespace SherpadCaesar
