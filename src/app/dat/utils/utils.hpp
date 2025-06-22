// SPDX-License-Identifier: GPL-v3.0
#pragma once

#include <string_view>

namespace SherpadCaesar{

/// @brief Indicates the type of character.
enum TypeCharacter_t {capitalLetter, smallLetter, other};

/// @brief Structure that stores the information of the selected character.
struct DataCharacter_t {
                      /// @brief character Selected character.
          std::string character { "" };

                      /// @brief type Indicates the type of character: lowercase, uppercase, or other.
      TypeCharacter_t type      { other };

                      /// @brief position Position of the character in the alphabet.
                  int position  { -1 };

    explicit                   DataCharacter_t()                                 = default;
                               DataCharacter_t(const DataCharacter_t&) = delete;
                               DataCharacter_t(      DataCharacter_t&&)= delete;
                              ~DataCharacter_t()                                 = default;
             DataCharacter_t&  operator=(const DataCharacter_t&)       = delete;
             DataCharacter_t&  operator=(      DataCharacter_t&&)      = delete;
};

/// @brief Flag's characters.
constexpr         char CHARACTER_less { '-' };
constexpr         char CHARACTER_h    { 'h' };
constexpr         char CHARACTER_i    { 'i' };
constexpr         char CHARACTER_w    { 'w' };
constexpr         char CHARACTER_c    { 'c' };
constexpr         char CHARACTER_e    { 'e' };
constexpr         char CHARACTER_d    { 'd' };
constexpr         char CHARACTER_s    { 's' };
constexpr         char CHARACTER_f    { 'f' };
constexpr         char CHARACTER_k    { 'k' };
constexpr         char CHARACTER_l    { 'l' };

/// @brief Yes/No characters.
constexpr         char CHARACTER_y    { 'y' };
constexpr         char CHARACTER_n    { 'n' };

/// @brief Exception's values.
constexpr          int EXCEPTION_0  { 0 };
constexpr          int EXCEPTION_1  { 1 };
constexpr          int EXCEPTION_2  { 2 };
constexpr          int EXCEPTION_3  { 3 };
constexpr          int EXCEPTION_4  { 4 };
constexpr          int EXCEPTION_5  { 5 };

/// @brief Levels.
constexpr          int MIN_LEVEL         {  1 };
constexpr          int MAX_LEVEL_ENGLISH { 25 };
constexpr          int MAX_LEVEL_SPANISH { 26 };

/// @brief Empty string.
constexpr std::string_view STRING_EMPTY { "" };

/// @brief Languages.
constexpr std::string_view ENGLISH_LANGUAGE { "en" };
constexpr std::string_view SPANISH_LANGUAGE { "sp" };

/// @brief Alfabets.
constexpr std::string_view englishUppercaseAlphabet { "ABCDEFGHIJKLMNOPQRSTUVWXYZ" };
constexpr std::string_view englishLowercaseAlphabet { "abcdefghijklmnopqrstuvwxyz" };
constexpr std::string_view spanishUppercaseAlphabet { "ABCDEFGHIJKLMNÑOPQRSTUVWXYZ" };
constexpr std::string_view spanishLowercaseAlphabet { "abcdefghijklmnñopqrstuvwxyz" };

} // SherpadCaesar
