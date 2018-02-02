#include "../header/I2P_test.h"
#include "../header/I2P_student.h"
#include "../header/I2P_test_unit.h"
#include "../header/List.h"
#include "../header/Set.h"
#include "../header/Vector.h"
#include <algorithm>
#include <atomic>
#include <cassert>
#include <cstddef>
#include <functional>
#include <iostream>
#include <list>
#include <memory>
#include <random>
#include <set>
#include <string>
#include <type_traits>
#include <vector>
using namespace std;
using namespace I2P;

namespace I2P_test_util {
namespace {
const unsigned long op_test_cnt(1000000);
const auto arithmetic_range(20);

student gen_(true_type);
remove_cv<decltype(arithmetic_range)>::type gen_(false_type) {
    uniform_int_distribution<remove_cv<decltype(arithmetic_range)>::type>
        uniform(0, arithmetic_range);
    return uniform(I2P_test_util::mt);
}

struct Empty {
    template <class... Args> void operator()(Args &&... args) {}
};

template <class T> const T &as_const(T &val) { return val; }

template <class T, class... Args> void check_iterator_type_(Args &&... args) {
    T c(std::forward<Args>(args)...);
    I2P::iterator(c.begin());
    I2P::iterator(c.end());
    I2P::const_iterator(c.begin());
    I2P::const_iterator(c.end());
    I2P::const_iterator(as_const(c).begin());
    I2P::const_iterator(as_const(c).end());
}

template <class Test, class Std>
void check_set_(vector<unique_ptr<Test>> &usr, key_compare comp,
                vector<Std> &stdc) {
    using CheckAfter = yes_tag;
    using RandomIter = yes_tag;
    using Reallocation = no_tag;
    using WithCapacity = yes_tag;
    using WithPos = no_tag;
    using WithReserve = yes_tag;
    using WithShrink = yes_tag;
    uniform_int_distribution<> mode(0, 35);
    uniform_int_distribution<> which(0, 1);
    for (unsigned long i(0); i != op_test_cnt; ++i) {
        const auto select(which(mt));
        switch (mode(mt)) {
        case 0: // default constructor
            usr[select].reset(new Test(comp));
            stdc[select].clear();
            break;
        case 1: // copy constructor
        case 2:
            usr[select].reset(new Test(*usr[1 - select]));
            stdc[select] = stdc[1 - select];
            break;
        case 3:
        case 4:
            copy_assignment_operator()(*usr[select], *usr[1 - select],
                                       stdc[select], stdc[1 - select]);
            break;
        case 5:
        case 6:
            count()(*usr[select], stdc[select]);
            count().operator()<const Test &>(*usr[select], stdc[select]);
            break;
        case 7:
            clear()(*usr[select], stdc[select]);
            empty_and_size()(*usr[select], stdc[select]);
            break;
        case 8:
        case 9:
        case 10:
            erase<CheckAfter, RandomIter>()(*usr[select], stdc[select]);
            break;
        case 11:
        case 12:
        case 13:
            erase_range<CheckAfter, RandomIter>()(*usr[select], stdc[select]);
            break;
        case 14:
        case 15:
            find<RandomIter>()(*usr[select], stdc[select]);
            find<RandomIter>().operator()<const Test &>(*usr[select],
                                                        stdc[select]);
            break;
        case 16:
        case 17:
        case 18:
        case 19:
        case 20:
            insert_key_value<RandomIter>()(*usr[select], stdc[select]);
            break;
        case 21:
        case 22:
        case 23:
        case 24:
        case 25:
            insert_range<WithPos, Reallocation, WithCapacity, RandomIter>()(
                *usr[select], stdc[select]);
            break;
        case 26:
        case 27:
            lower_bound<RandomIter>()(*usr[select], stdc[select]);
            lower_bound<RandomIter>().operator()<const Test &>(*usr[select],
                                                               stdc[select]);
            break;
        case 28:
        case 29:
            upper_bound<RandomIter>()(*usr[select], stdc[select]);
            upper_bound<RandomIter>().operator()<const Test &>(*usr[select],
                                                               stdc[select]);
            break;
        case 30:
        case 31:
            key_access()(*usr[select], stdc[select]);
            break;
        case 32:
        case 33:
            conditional<is_same<WithReserve, yes_tag>::value,
                        reserve<WithCapacity>, Empty>::type()(*usr[select],
                                                              stdc[select]);
            break;
        case 34:
        case 35:
            conditional<is_same<WithShrink, yes_tag>::value, shrink_to_fit,
                        Empty>::type()(*usr[select], stdc[select]);
            break;
        default:
            assert(false);
        }
        iterator_iterate()(*usr[select]);
        iterator_iterate().operator()<const Test &>(*usr[select]);
        conditional<is_same<RandomIter, yes_tag>::value, iterator_random,
                    Empty>::type()(*usr[select]);
        conditional<is_same<RandomIter, yes_tag>::value, iterator_random,
                    Empty>::type()
            .
            operator()<const Test &>(*usr[select]);
    }
}
} // namespace

void check_hierarchy() {
#ifdef TEST_LIST
    using container_base_is_List_base =
        enable_if<is_base_of<container_base, List>::value>::type;
#endif
#ifdef TEST_SET
    using container_base_is_Set_base =
        enable_if<is_base_of<container_base, Set>::value>::type;
#endif
#ifdef TEST_VECTOR
    using container_base_is_Vector_base =
        enable_if<is_base_of<container_base, Vector>::value>::type;
#endif
}

void check_iterator_type() {
#ifdef TEST_LIST
    check_iterator_type_<List>();
#endif
#ifdef TEST_SET
    check_iterator_type_<Set>(smaller);
#endif
#ifdef TEST_VECTOR
    check_iterator_type_<Vector>();
#endif
}

#ifdef TEST_LIST
void check_list() {
    using test_type = List;
    using std_type = list<value_type>;
    using CheckAfter = yes_tag;
    using RandomIter = yes_tag;
    using Reallocation = no_tag;
    using StdEraseBegin = no_tag;
    using UsrEraseBegin = no_tag;
    using WithAlgo = yes_tag;
    using WithCapacity = yes_tag;
    using WithPos = yes_tag;
    using WithReserve = yes_tag;
    using WithShrink = yes_tag;
    vector<unique_ptr<test_type>> usr;
    usr.push_back(unique_ptr<test_type>(new test_type()));
    usr.push_back(unique_ptr<test_type>(new test_type()));
    vector<std_type> stdc(2);
    uniform_int_distribution<> mode(0, 36);
    uniform_int_distribution<> which(0, 1);
    for (unsigned long i(0); i != op_test_cnt; ++i) {
        const auto select(which(mt));
        switch (mode(mt)) {
        case 0: // default constructor
            usr[select].reset(new test_type());
            stdc[select].clear();
            break;
        case 1: // copy constructor
        case 2:
            usr[select].reset(new test_type(*usr[1 - select]));
            stdc[select] = stdc[1 - select];
            break;
        case 3:
        case 4:
            copy_assignment_operator()(*usr[select], *usr[1 - select],
                                       stdc[select], stdc[1 - select]);
            break;
        case 5:
            back_and_front()(*usr[select], stdc[select]);
            back_and_front().operator()<const test_type &>(*usr[select],
                                                           stdc[select]);
            break;
        case 6:
            clear()(*usr[select], stdc[select]);
            empty_and_size()(*usr[select], stdc[select]);
            break;
        case 7:
        case 8:
        case 9:
            erase<CheckAfter, RandomIter>()(*usr[select], stdc[select]);
            break;
        case 10:
        case 11:
        case 12:
            erase_range<CheckAfter, RandomIter>()(*usr[select], stdc[select]);
            break;
        case 13:
        case 14:
        case 15:
        case 16:
        case 17:
            insert<Reallocation, WithCapacity, RandomIter>()(*usr[select],
                                                             stdc[select]);
            break;
        case 18:
        case 19:
        case 20:
        case 21:
        case 22:
            insert_range<WithPos, Reallocation, WithCapacity, RandomIter>()(
                *usr[select], stdc[select]);
            break;
        case 23:
            pop_back()(*usr[select], stdc[select]);
            break;
        case 24:
        case 25:
            pop_front<CheckAfter, UsrEraseBegin, StdEraseBegin>()(*usr[select],
                                                                  stdc[select]);
            break;
        case 26:
            push_back<Reallocation, WithCapacity>()(*usr[select], stdc[select]);
            break;
        case 27:
        case 28:
            push_front<CheckAfter, UsrEraseBegin, StdEraseBegin>()(
                *usr[select], stdc[select]);
            break;
        case 29:
        case 30:
        case 31:
        case 32:
            random_algo<WithAlgo>()(*usr[select], stdc[select]);
            break;
        case 33:
        case 34:
            conditional<is_same<WithReserve, yes_tag>::value,
                        reserve<WithCapacity>, Empty>::type()(*usr[select],
                                                              stdc[select]);
            break;
        case 35:
        case 36:
            conditional<is_same<WithShrink, yes_tag>::value, shrink_to_fit,
                        Empty>::type()(*usr[select], stdc[select]);
            break;
        default:
            assert(false);
        }
        iterator_iterate()(*usr[select]);
        iterator_iterate().operator()<const test_type &>(*usr[select]);
        conditional<is_same<RandomIter, yes_tag>::value, iterator_random,
                    Empty>::type()(*usr[select]);
        conditional<is_same<RandomIter, yes_tag>::value, iterator_random,
                    Empty>::type()
            .
            operator()<const test_type &>(*usr[select]);
    }
}
#endif

#ifdef TEST_VECTOR
void check_vec() {
    using test_type = Vector;
    using std_type = vector<value_type>;
    using CheckAfter = no_tag;
    using RandomIter = yes_tag;
    using Reallocation = yes_tag;
    using StdEraseBegin = yes_tag;
    using UsrEraseBegin = no_tag;
    using WithAlgo = no_tag;
    using WithCapacity = yes_tag;
    using WithPos = yes_tag;
    using WithReserve = yes_tag;
    using WithShrink = yes_tag;
    vector<unique_ptr<test_type>> usr;
    usr.push_back(unique_ptr<test_type>(new test_type()));
    usr.push_back(unique_ptr<test_type>(new test_type()));
    vector<std_type> stdc(2);
    uniform_int_distribution<> mode(0, 37);
    uniform_int_distribution<> which(0, 1);
    for (unsigned long i(0); i != op_test_cnt; ++i) {
        const auto select(which(mt));
        switch (mode(mt)) {
        case 0: // default constructor
            usr[select].reset(new test_type());
            stdc[select].clear();
            break;
        case 1: // copy constructor
        case 2:
            usr[select].reset(new test_type(*usr[1 - select]));
            stdc[select] = stdc[1 - select];
            break;
        case 3:
        case 4:
            copy_assignment_operator()(*usr[select], *usr[1 - select],
                                       stdc[select], stdc[1 - select]);
            break;
        case 5:
            back_and_front()(*usr[select], stdc[select]);
            back_and_front().operator()<const test_type &>(*usr[select],
                                                           stdc[select]);
            break;
        case 6:
            clear()(*usr[select], stdc[select]);
            empty_and_size()(*usr[select], stdc[select]);
            break;
        case 7:
        case 8:
        case 9:
            erase<CheckAfter, RandomIter>()(*usr[select], stdc[select]);
            break;
        case 10:
        case 11:
        case 12:
            erase_range<CheckAfter, RandomIter>()(*usr[select], stdc[select]);
            break;
        case 13:
        case 14:
        case 15:
        case 16:
        case 17:
            insert<Reallocation, WithCapacity, RandomIter>()(*usr[select],
                                                             stdc[select]);
            break;
        case 18:
        case 19:
        case 20:
        case 21:
        case 22:
            insert_range<WithPos, Reallocation, WithCapacity, RandomIter>()(
                *usr[select], stdc[select]);
            break;
        case 23:
            pop_back()(*usr[select], stdc[select]);
            break;
        case 24:
        case 25:
            pop_front<CheckAfter, UsrEraseBegin, StdEraseBegin>()(*usr[select],
                                                                  stdc[select]);
            break;
        case 26:
            push_back<Reallocation, WithCapacity>()(*usr[select], stdc[select]);
            break;
        case 27:
        case 28:
            push_front<CheckAfter, UsrEraseBegin, StdEraseBegin>()(
                *usr[select], stdc[select]);
            break;
        case 29:
            random_access()(*usr[select], stdc[select]);
            random_access().operator()<const test_type &>(*usr[select],
                                                          stdc[select]);
            break;
        case 30:
        case 31:
        case 32:
        case 33:
            random_algo<WithAlgo>()(*usr[select], stdc[select]);
            break;
        case 34:
        case 35:
            conditional<is_same<WithReserve, yes_tag>::value,
                        reserve<WithCapacity>, Empty>::type()(*usr[select],
                                                              stdc[select]);
            break;
        case 36:
        case 37:
            conditional<is_same<WithShrink, yes_tag>::value, shrink_to_fit,
                        Empty>::type()(*usr[select], stdc[select]);
            break;
        default:
            assert(false);
        }
        iterator_iterate()(*usr[select]);
        iterator_iterate().operator()<const test_type &>(*usr[select]);
        conditional<is_same<RandomIter, yes_tag>::value, iterator_random,
                    Empty>::type()(*usr[select]);
        conditional<is_same<RandomIter, yes_tag>::value, iterator_random,
                    Empty>::type()
            .
            operator()<const test_type &>(*usr[select]);
    }
}
#endif

#ifdef TEST_SET
void check_set() {
    {
        cout << "test smaller\n";
        vector<unique_ptr<Set>> usr;
        usr.push_back(unique_ptr<Set>(new Set(smaller)));
        usr.push_back(unique_ptr<Set>(new Set(smaller)));
        vector<set<value_type>> stdc(2);
        check_set_(usr, smaller, stdc);
    }
    {
        cout << "test bigger\n";
        vector<unique_ptr<Set>> usr;
        usr.push_back(unique_ptr<Set>(new Set(bigger)));
        usr.push_back(unique_ptr<Set>(new Set(bigger)));
        vector<set<value_type, greater<value_type>>> stdc(2);
        check_set_(usr, bigger, stdc);
    }
}
#endif

value_type gen() { return gen_(is_same<value_type, student>::type{}); }

namespace {
student gen_(true_type) {
    static atomic<uintmax_t> id(0);
    string str(3, 0);
    generate(str.begin(), str.end(),
             []() -> char { return 97 + (I2P_test_util::mt() % 3); });
    return student(id++, str);
}
} // namespace
} // namespace I2P_test_util