#ifndef TYPES_H
#define TYPES_H

#include <cstdint>

//Quanto maior os bits, maior tamanho pode comportar
// algo como: 2^8 = 512 numeros diferentes
using u8 = uint8_t;   // short unsigned
using u16 = uint16_t;   // short unsigned
using u32 = uint32_t;   // Mais usado no OpenGL
using u64 = uint64_t;   // long long unsigned

using i8 = int8_t;    // short int
using i16 = int16_t;    // short int
using i32 = int32_t;    // Padrão
using i64 = int64_t;    // long long int

using f32 = float;
using f64 = double;

#endif //TYPES_H