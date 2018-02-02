#ifndef I2P_STUDENT
#define I2P_STUDENT
#include <cstdint>
#include <iosfwd>
#include <string>

namespace I2P {
class student {
    std::uintmax_t id_;
    std::string name_;

  public:
    student(const student &rhs);
    student(std::uintmax_t id, const char *name);
    student(std::uintmax_t id, const std::string &name);
    std::uintmax_t id() const { return id_; }
    const std::string &name() const { return name_; }
    student &operator=(const student &rhs);
};

bool operator==(const student &lhs, const student &rhs);
bool operator!=(const student &lhs, const student &rhs);
bool operator<(const student &lhs, const student &rhs);
bool operator>(const student &lhs, const student &rhs);
bool operator<=(const student &lhs, const student &rhs);
bool operator>=(const student &lhs, const student &rhs);

std::ostream &operator<<(std::ostream &os, const student &stu);
} // namespace I2P

#endif