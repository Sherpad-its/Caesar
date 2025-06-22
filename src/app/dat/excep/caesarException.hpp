// SPDX-License-Identifier: GPL-v3.0
#pragma once

#include <exception>

namespace SherpadCaesar {

///  @class CaesarException_t
///  @brief Manages the exceptions in the Caesar application.

    class CaesarException_t: public std::exception {
        private:
                                      /// @brief Stores the reason why the exception was generated.
                                int   m_reason { 0 };

        public:
                explicit              CaesarException_t(const int r);
                                     ~CaesarException_t()= default;
                         const char*  what()                          const noexcept override;
    };

} // namespace SherpadCaesar
