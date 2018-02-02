#ifndef I2P_TEST
#define I2P_TEST
#include "I2P_def.h"
#include <string>

//#define TEST_LIST
//#define TEST_SET
#define TEST_VECTOR

// I will test all of the containers if you disable all macros
#if !(defined(TEST_LIST) || defined(TEST_SET) || defined(TEST_VECTOR))
#define TEST_LIST
#define TEST_SET
#define TEST_VECTOR
#endif

namespace I2P_test_util {
void check_hierarchy();
void check_iterator_type();
#ifdef TEST_LIST
void check_list();
#endif
#ifdef TEST_SET
void check_set();
#endif
#ifdef TEST_VECTOR
void check_vec();
#endif
I2P::value_type gen();
} // namespace I2P_test_util

#endif
