// SPDX-License-Identifier: GPL-v3.0
#include "arguments.hpp"

namespace SherpadCaesar {

///==============================================================================
/// @brief Constructor of the Arguments_t class.
/// @param numArgs Number of arguments.
/// @param args[] List of arguments.
///==============================================================================
Arguments_t::Arguments_t(const int numArgs, const char* args[]) noexcept{

    m_vectorArguments.reserve(numArgs - 1);

    saveArguments(numArgs, args);
}

///==============================================================================
/// @brief Stores all input arguments in a strings´s vector.
/// @param numArgs Number of arguments.
/// @param args[] List of arguments.
///==============================================================================
void
Arguments_t::saveArguments(const int numArgs, const char* args[]) noexcept{

    for (int i= 1; i < numArgs; i++){
        m_vectorArguments.emplace_back(args[i]);
    }
}

///==============================================================================
/// @brief Returns the read-only strings's vector.
/// @return m_vectorArguments String vector.
///==============================================================================
const std::vector<std::string>&
Arguments_t::getAllArguments() const noexcept{

    return m_vectorArguments;
}

///==============================================================================
/// @brief Returns the strings´s vector.
/// @return m_vectorArguments String vector.
///==============================================================================
std::vector<std::string>&
Arguments_t::getAllArguments() noexcept{

    return m_vectorArguments;
}

///==============================================================================
/// @brief Returns the number of elements of the strings´s vector.
/// @return m_vectorArguments.size().
///==============================================================================
const int
Arguments_t::getNumArguments() const noexcept{

	return m_vectorArguments.size();
}

///==============================================================================
/// @brief Returns wheather the strings´s vector is empty.
/// @return m_vectorArguments.empty().
///==============================================================================
const bool
Arguments_t::isEmpty() const noexcept{

    return m_vectorArguments.empty();
}

} // namespace SherpadCaesar
