#ifndef ADVANCED_HPP
#define ADVANCED_HPP

/*
    This is my header that contains all my meta functions
    to debug better the code. For more info, acess:
    ekfx.github.io/eriksander-code/news.html

    If you wanna use one of these, use the FUNCTION NUMBER 1, is the best one
    and is easy to understand:
    1. We get the RAW_ERROR and the TARGET (that will receive the 
    value).
    2. We verify if is success, if true, TARGET receive the value
    and return SUCCESS.
    3. Else, we do a compiling time for loop passing for all enumerators 
    of ERRORCODE (after we transformed it into an array to the compiler)
    checking for one that matches with our error, turning the current meta
    member of the array a data inside our program and comparing with 
    the error, which both are hexadecimal, so the comparasion is possible.
    4. If matches, we get the member and get its identifier e return as
    string_view.
    5. If none of that steps runs successfuly, it means that is a unknown
    error.
*/

#include <iostream>
#include <filesystem>
#include <string>
#include <fstream>
#include <map>
#include <expected>
#include <optional>
#include <memory>
#include <variant>
#include <meta>
#include <type_traits>
#include <cstdint>
#include "Error.h"

// you can create your own types of error:
// enum class ERRORCODE : std::uint16_t{
//     // Global
//     SUCCESS              = 0x0000,
//     ERROR                = 0xffff,

//     // Configurator.hpp
//     FILE_DONT_EXIST      = 0x0001,
//     COULDNT_OPEN_FILE    = 0x0002,
//     INVALID_READ         = 0x0003,
//     NOT_FOUND_KEY        = 0x0004
// };

// FUNCTION NUMBER 1
// this returns the error and puts the value in a parameter
template<typename u_type, typename u_val>
std::string_view err(const u_type& raw_error, u_val& target) {
    ERRORCODE error;
    error = raw_error.error_or(ERRORCODE::SUCCESS);
    if (error == ERRORCODE::SUCCESS) {
        // caso seja sucesso:
        target = raw_error.value();
        return std::string_view(std::meta::identifier_of(^^ERRORCODE::SUCCESS));
    } else {    // se for erro.

        template for (constexpr auto member : define_static_array(std::meta::enumerators_of(^^ERRORCODE))) {
            if ([:member:] == error) {
                return std::string_view(std::meta::identifier_of(member));
            }
        }

        return std::string_view("UNKNOWN_ERROR");
    }
}

// FUNCTION NUMBER 1.1
// This receive just ERRORCODE and return the error.
inline std::string_view err(const ERRORCODE& error) {
    if (error == ERRORCODE::SUCCESS) 
        return std::string_view(std::meta::identifier_of(^^ERRORCODE::SUCCESS));

    template for (constexpr auto member : define_static_array(std::meta::enumerators_of(^^ERRORCODE))) {
        if ([:member:] == error) {
            return std::string_view(std::meta::identifier_of(member));
        }
    }

    return std::string_view("UNKNOWN_ERROR");
}

// FUNCTION NUMBER 2
// this returns the value and puts the error in the parameter
// I don't make sure this one works correctly
template<typename u_type, typename u_val>
auto err(const u_type& raw_error, std::string_view& target) -> decltype(raw_error.value()) {
    ERRORCODE error;
    error = raw_error.error_or(ERRORCODE::SUCCESS);
    if (error == ERRORCODE::SUCCESS) {
        // caso seja sucesso:
        target = std::string_view(std::meta::identifier_of(^^ERRORCODE::SUCCESS));
        return raw_error.value();
    } else {    // se for erro.

        template for (constexpr auto member : define_static_array(std::meta::enumerators_of(^^ERRORCODE))) {
            if ([:member:] == error) {
                target = std::string_view(std::meta::identifier_of(member));
            }
        }

        target = std::string_view("UNKNOWN_ERROR");
        return -1;  // in every fail, return -1;
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// FUNCTION NUMBER 3
// this just returns the message if fail or success
template<typename u_type>
std::string_view err(const u_type& raw_error) {
    ERRORCODE error;
    error = raw_error.error_or(ERRORCODE::SUCCESS);

    template for (constexpr auto member : define_static_array(std::meta::enumerators_of(^^ERRORCODE))) {
        if ([:member:] == error) {
            return std::string_view(std::meta::identifier_of(member));
        }
    }

    return std::string_view("UNKNOWN_ERROR");
}

#endif // ADVANCED_H