#ifndef VECTOR_H
#define VECTOR_H
#include "I2P_container.h"
#include "I2P_iterator.h"
#include <cstring>
#include <type_traits>

namespace I2P {
class Vector : public randomaccess_container {
  public:
    Vector();
    Vector(const Vector &rhs);
    reference_type back();
    const_reference_type back() const;
    iterator begin();
    const_iterator begin() const;
    size_type capacity() const;
    void clear();
    bool empty() const;
    iterator end();
    const_iterator end() const;
    void erase(const_iterator pos);
    void erase(const_iterator begin, const_iterator end);
    reference_type front();
    const_reference_type front() const;
    void insert(const_iterator pos, size_type count, const_reference_type val);
    void insert(const_iterator pos, const_iterator begin, const_iterator end);
    void pop_back();
    void pop_front();
    void push_back(const_reference_type val);
    void push_front(const_reference_type val);
    void reserve(size_type new_capacity);
    void shrink_to_fit();
    size_type size() const;
    Vector &operator=(const Vector &rhs);
    reference_type operator[](size_type pos);
    const_reference_type operator[](size_type pos) const;
    ~Vector();

  private:
    void shiftFront(size_type, size_type);
    void shiftBack(size_type, size_type);
    void aquire(size_type);
    pointer data_;
    size_type size_, cap_;
    bool trivial_;
};
} // namespace I2P

#endif
