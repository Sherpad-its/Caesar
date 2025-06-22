// SPDX-License-Identifier: GPL-v3.0
#include "caesarException.hpp"

namespace SherpadCaesar {

///==============================================================================
/// @brief Constructor of the CaesarException_t class.
/// @param r Reason why the exception was thrown.
///==============================================================================
CaesarException_t::CaesarException_t(const int r)
    : exception(), m_reason { r } {

}

//==============================================================================
/// @brief Returs the error message depending on the value of the reason.
/// @return The menssage to display.
//==============================================================================
const char*
CaesarException_t::what() const noexcept{

   switch(m_reason) {
      case 0:
         return "[-] FATAL ERROR!!! Exception caught: There is a flag that isn't correct. Correct flags: h, i, w, c, e, d, k, s, f and l.\n";
      case 1:
         return "[-] FATAL ERROR!!! Exception caught: Value without flag. Please, remember to write the flags before writting the values.\n";
      case 2:
         return "[-] FATAL ERROR!!! Exception caught: Call to function processData with incorrect value for first element of queue in m_nextParameters.\n";
      case 3:
         return "[-] FATAL ERROR!!! Exception caught: Error opening input file.\n";
      case 4:
         return "[-] FATAL ERROR!!! Exception caught: The language must be selected before the string/file and level. Please rewrite the command correctly. \n";
      case 5:
         return "[-] FATAL ERROR!!! Exception caught: The number of flags that require parameters and the number of parameters are diferent. \n";
      default:
         return "[-] FATAL ERROR!!! Exception not covered.\n";
   }
}

} // namespace SherpadCaesar
