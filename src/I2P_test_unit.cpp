#include "../header/I2P_test_unit.h"
#include "../header/I2P_def.h"
#include "../header/I2P_test.h"
#include "../header/List.h"
#include "../header/Set.h"
#include "../header/Vector.h"
#include <chrono>
#include <iostream>
#include <random>
using namespace std;

namespace I2P_test_util {
const size_t insert_cnt(20);
thread_local mt19937_64
    mt(chrono::high_resolution_clock::now().time_since_epoch().count());

bool bigger(const I2P::key_type &lhs, const I2P::key_type &rhs) {
    return lhs > rhs;
}

bool check(bool correct, const char *message) {
    if (correct)
        ;
    else
        cerr << message << '\n';
    return correct;
}

#ifdef TEST_LIST
I2P::List create_list(size_t count) {
    I2P::List lst;
    for (size_t i(0); i != count; ++i)
        lst.push_back(gen());
    return lst;
}
#endif

#ifdef TEST_SET
I2P::Set create_set(size_t count) {
    uniform_int_distribution<> uniform(0, 1);
    I2P::Set set(uniform(mt) ? bigger : smaller);
    for (size_t i(0); i != count; ++i)
        set.insert(gen(), gen());
    return set;
}
#endif

#ifdef TEST_VECTOR
I2P::Vector create_vector(size_t count) {
    I2P::Vector vec;
    for (size_t i(0); i != count; ++i)
        vec.push_back(gen());
    return vec;
}
#endif

bool smaller(const I2P::key_type &lhs, const I2P::key_type &rhs) {
    return lhs < rhs;
}
} // namespace I2P_test_util