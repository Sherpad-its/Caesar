// SPDX-License-Identifier: GPL-v3.0
#pragma once

#include <vector>
#include <string>

namespace SherpadCaesar {

/// @class Arguments_t
/// @brief Stores input arguments in a vector of strings.

    class Arguments_t{
        private:
                                                          /// @brief Stores the arguments.
                                std::vector<std::string>  m_vectorArguments { };

                                                   void   saveArguments(const int, const char*[])     noexcept;

        public:
                explicit                                  Arguments_t(const int, const char*[])       noexcept;
                                                          Arguments_t(const Arguments_t&)   = delete;
                                                          Arguments_t(      Arguments_t&&)  = delete;
                                                         ~Arguments_t() = default;
                                            Arguments_t&  operator=(const Arguments_t&)     = delete;
                                            Arguments_t&  operator=(      Arguments_t&&)    = delete;
                         const std::vector<std::string>&  getAllArguments() const                     noexcept;
                               std::vector<std::string>&  getAllArguments()                           noexcept;
                                              const int   getNumArguments() const                     noexcept;
                                             const bool   isEmpty()         const                     noexcept;
    };

} // namespace SherpadCaesar
