// SPDX-License-Identifier: GPL-v3.0
#pragma once

#include <string>
#include "dat/utils/utils.hpp"

/// @class Caesar_t
/// @brief Manages the actions to be performed based on the data from the Data_t class.

namespace SherpadCaesar{

//Forward Declaration.
class Data_t;

    class Caesar_t {
        private:
                       const     std::string    VERSION                        { "1.0.0" };
                       const     std::string    PROGRAMMER                     { "Sherpad" };
                       const     std::string    YEAR                           { "2025" };  
                       const     std::string    STANDARD                       { "-std=c++17" };
                       const     std::string    LICENSE                        { "GPLv3" };

                                                /// @brief Contains the data that the program will work with.
                                      Data_t&   m_inputData;

                                        void    writeHelp()                                                    const noexcept;
                                        void    writeInfo()                                                    const noexcept;
                                        void    writeWarranty()                                                const noexcept;
                                        void    writeConditions()                                              const noexcept;
                                        void    askEncryptOrDecrypt()                                                noexcept;
                                        void    askFileOrString();
                                        void    askPathOrStringValue(const bool);
                                        void    askLanguage();
                                        void    askSpecificLanguage();
                                        void    askLevel();
                                        void    askForSpecificLevel();
                                        void    bulkEncryptionOrDecryption(const std::string&)                 const noexcept;
                                        void    encryptionOrDecryption(const std::string&, const int)          const noexcept;
                                        void    transform(const std::string&, const int)                       const noexcept;

        public:
               explicit                         Caesar_t(Data_t&);
                                                Caesar_t(const Caesar_t&)  = delete;
                                                Caesar_t(      Caesar_t&&) = delete;
                                               ~Caesar_t()                           = default; 
                                    Caesar_t&   operator=(const Caesar_t&) = delete;
                                    Caesar_t&   operator=(      Caesar_t&&)= delete;
                                        void    ask();
                                        void    performTransformation();
                                        void    validateInputParameters();
                                        void    process();
                           
    };

} // SherpadCaesar
