#ifndef I2P_DEF
#define I2P_DEF
#include "I2P_student.h"
#include <cstddef>
#include <cstdint>

namespace I2P {
using difference_type = std::ptrdiff_t;
using key_type = student; // when you use Set, please set key_type to value_type
using size_type = std::size_t;
// when measure performance, value_type will be int8_t, int64_t, long double and
// student  iterators should points to value_type
using value_type = student;
using pointer = value_type *;
using const_pointer = const value_type *;
using reference = value_type &;
using reference_type = value_type &; // do not use this
using const_reference = const value_type &;
using const_reference_type = const value_type &; // do not use this

// for simplicity, we use function pointer
using key_compare = bool (*)(const key_type &lhs,
                             const key_type &rhs); // for sorted_container

using key_equal = bool (*)(const key_type &lhs,
                           const key_type &rhs); // future work
using hash = size_type (*)(const key_type &key); // future work
} // namespace I2P

#endif