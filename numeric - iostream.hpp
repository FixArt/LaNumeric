#ifndef LANUMERIC_USED_IOSTREAM
#pragma once 

//#include <cstdint>
#include <string>
#include <iostream>
// #include <utility>
// #include <type_traits>
// #include <errno.h>

#include "numeric.hpp"
#include "numeric - dynamic.hpp"

/**
 * @brief Namespace of LaNumeric.
 * 
 */
namespace LANUM
{
    template<size_t size>
    std::ostream& operator<<(std::ostream& stream, const LANUM::auint_t<size>& number)
    {
        stream << (std::string)number;
        return stream;
    }

    template<size_t size>
    std::istream& operator>>(std::istream& stream, LANUM::auint_t<size>& number)
    {
        std::string get;
        stream >> get;
        number = get;
        return stream;
    }
};
#define LANUMERIC_USED_IOSTREAM 1
#endif
