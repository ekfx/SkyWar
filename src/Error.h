#ifndef ERROR_H
#define ERROR_H

#include <cstdint>

enum class ERRORCODE : std::uint16_t{
    // Global
    SUCCESS              = 0x0000,
    ERROR                = 0xffff,

    // Configurator.hpp -> a namespace is pretty good here.
    FILE_DONT_EXIST      = 0x0001,
    COULDNT_OPEN_FILE    = 0x0002,
    INVALID_READ         = 0x0003,
    NOT_FOUND_KEY        = 0x0004
};

#endif // ERROR_H