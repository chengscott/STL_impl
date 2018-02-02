#include "../header/I2P_student.h"
#include <ostream>
using namespace std;

namespace I2P {
student::student(const student &rhs) : id_(rhs.id_), name_(rhs.name_) {}

student::student(uintmax_t id, const char *name) : id_(id), name_(name) {}

student::student(uintmax_t id, const string &name) : id_(id), name_(name) {}

student &student::operator=(const student &rhs) {
    if ((this != &rhs) && (id_ != rhs.id_)) {
        id_ = rhs.id_;
        name_ = rhs.name_;
    }
    return *this;
}

bool operator==(const student &lhs, const student &rhs) {
    return lhs.id() == rhs.id();
}

bool operator!=(const student &lhs, const student &rhs) {
    return lhs.id() != rhs.id();
}

bool operator<(const student &lhs, const student &rhs) {
    return lhs.id() < rhs.id();
}

bool operator>(const student &lhs, const student &rhs) {
    return lhs.id() > rhs.id();
}

bool operator<=(const student &lhs, const student &rhs) {
    return lhs.id() <= rhs.id();
}

bool operator>=(const student &lhs, const student &rhs) {
    return lhs.id() >= rhs.id();
}

ostream &operator<<(ostream &os, const student &stu) {
    return os << stu.id() << ' ' << stu.name();
}
} // namespace I2P