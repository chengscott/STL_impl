#include "../header/Vector.h"

namespace I2P {
Vector::Vector()
    : data_((pointer) operator new[](1 * sizeof(value_type))), size_(0),
      cap_(1), trivial_(std::is_trivial<value_type>::value) {}
Vector::Vector(const Vector &rhs) {
    DBG("copy ctor\n", 0);

    size_ = rhs.size_;
    cap_ = rhs.size_ < rhs.cap_ / 4
               ? rhs.cap_ / 2
               : rhs.size_ == rhs.cap_ ? 2 * rhs.cap_ : rhs.cap_;
    cap_ = cap_ == 0 ? 1 : cap_;
    trivial_ = std::is_trivial<value_type>::value;
    // copy rhs
    data_ = (pointer) operator new[](cap_ * sizeof(value_type));
    if (trivial_)
        memcpy(data_, rhs.data_, rhs.size_ * sizeof(value_type));
    else
        for (size_type i = 0; i < size_; ++i)
            new (data_ + i) value_type(rhs.data_[i]);
}
Vector::~Vector() {
    if (!trivial_)
        for (size_type i = 0; i < size_; ++i)
            data_[i].~value_type();
    operator delete[](data_);
}
Vector &Vector::operator=(const Vector &rhs) {
    DBG("operator=\n", 0);

    // if not self-asigned
    if (data_ != rhs.data_) {
        size_ = rhs.size_;
        cap_ = rhs.size_ < rhs.cap_ / 4
                   ? rhs.cap_ / 2
                   : rhs.size_ == rhs.cap_ ? 2 * rhs.cap_ : rhs.cap_;
        cap_ = cap_ == 0 ? 1 : cap_;
        trivial_ = std::is_trivial<value_type>::value;
        // clear this
        operator delete[](data_);
        // copy rhs
        data_ = (pointer) operator new[](cap_ * sizeof(value_type));
        if (trivial_)
            memcpy(data_, rhs.data_, rhs.size_ * sizeof(value_type));
        else
            for (size_type i = 0; i < size_; ++i)
                new (data_ + i) value_type(rhs.data_[i]);
    }
    return *this;
}
// Iterators
iterator Vector::begin() { return iterator(new vector_iterator(data_)); }
const_iterator Vector::begin() const {
    return const_iterator(new vector_iterator(data_));
}
iterator Vector::end() { return iterator(new vector_iterator(data_ + size_)); }
const_iterator Vector::end() const {
    return const_iterator(new vector_iterator(data_ + size_));
}
// Capacity
size_type Vector::size() const { return size_; }
size_type Vector::capacity() const { return cap_; }
bool Vector::empty() const { return size_ == 0; }
void Vector::reserve(size_type new_capacity) {
    DBG("reserve %d\n", new_capacity);

    if (new_capacity <= cap_)
        return;
    pointer old = data_;
    data_ = (pointer) operator new[](new_capacity * sizeof(value_type));
    if (trivial_)
        memcpy(data_, old, size_ * sizeof(value_type));
    else
        for (size_type i = 0; i < size_; ++i)
            new (data_ + i) value_type(old[i]);
    operator delete[](old);
    cap_ = new_capacity;
}
void Vector::shrink_to_fit() {
    // NO IMPL
}
// Modifiers
void Vector::push_front(const_reference_type val) {
    DBG("push_front %d\n", val);

    aquire(1);
    shiftBack(1, 0);
    if (trivial_)
        data_[0] = val;
    else
        new (data_) value_type(val);
    ++size_;
}
void Vector::push_back(const_reference_type val) {
    DBG("push_back %d\n", val);

    aquire(1);
    if (trivial_)
        data_[size_] = val;
    else
        new (data_ + size_) value_type(val);
    ++size_;
}
// If the container is empty, it causes undefined behavior.
void Vector::pop_front() {
    DBG("pop_front\n", 0);

    shiftFront(0, 1);
    --size_;
}
// If the container is empty, it causes undefined behavior.
void Vector::pop_back() {
    DBG("pop_back\n", 0);

    if (trivial_)
        --size_;
    else
        data_[--size_].~value_type();
}
void Vector::insert(const_iterator lhs, size_type count,
                    const_reference_type val) {
    DBG("insert %d times of %d\n", count, val);

    size_type pos = lhs - begin();
    aquire(count);
    shiftBack(pos + count, pos);
    if (trivial_)
        for (size_type i = 0; i < count; ++i)
            data_[i + pos] = val;
    else
        for (size_type i = 0; i < count; ++i)
            new (data_ + i + pos) value_type(val);
    size_ += count;
}
void Vector::insert(const_iterator lhs, const_iterator start,
                    const_iterator end) {
    DBG("insert range\n", 0);

    size_type pos = lhs - begin(), dx = end - start;
    aquire(dx);
    shiftBack(pos + dx, pos);
    if (trivial_)
        for (size_type i = 0; i < dx; ++i)
            data_[i + pos] = *(start + i);
    else
        for (size_type i = 0; i < dx; ++i)
            new (data_ + i + pos) value_type(*(start + i));
    size_ += dx;
}
void Vector::erase(const_iterator rhs) {
    DBG("erase\n", 0);

    size_type pos = rhs - begin();
    shiftFront(pos, pos + 1);
    --size_;
}
void Vector::erase(const_iterator start, const_iterator end) {
    DBG("erase range\n", 0);

    size_type pos = start - begin(), dx = end - start;
    shiftFront(pos, pos + dx);
    size_ -= dx;
}
void Vector::clear() {
    DBG("clear\n", 0);

    if (!trivial_)
        for (size_type i = 0; i < size_; ++i)
            data_[i].~value_type();
    size_ = 0;
}
// Element access
// If the container is empty, it causes undefined behavior.
reference_type Vector::front() { return data_[0]; }
const_reference_type Vector::front() const { return data_[0]; }
reference_type Vector::back() { return data_[size_ - 1]; }
const_reference_type Vector::back() const { return data_[size_ - 1]; }
// If the container size is greater than pos, it causes undefined behavior.
reference_type Vector::operator[](size_type pos) { return data_[pos]; }
const_reference_type Vector::operator[](size_type pos) const {
    return data_[pos];
}
// My
void Vector::shiftFront(size_type dest, size_type src) {
    DBG("shiftFront from %d to %d\n", src, dest);

    size_type dx = src - dest;
    if (dx == 0)
        return;
    if (trivial_)
        memmove(data_ + dest, data_ + src, (size_ - src) * sizeof(value_type));
    else {
        // shift content
        for (size_type i = dest; i + dx < size_; ++i)
            data_[i] = data_[i + dx];
        // last dx element dtor
        for (size_type i = 0; i < dx; ++i)
            data_[size_ - 1 - i].~value_type();
    }
}
void Vector::shiftBack(size_type dest, size_type src) {
    DBG("shiftBack from %d to %d\n", src, dest);

    size_type dx = dest - src;
    if (dx == 0)
        return;
    if (trivial_)
        memmove(data_ + dest, data_ + src, (size_ - src) * sizeof(value_type));
    else
        for (size_type i = size_ + dx; i > dest; --i)
            if (i > size_)
                new (data_ + i - 1) value_type(data_[i - 1 - dx]);
            else
                data_[i - 1] = data_[i - 1 - dx];
}
void Vector::aquire(size_type dx) {
    DBG("aquire %d\n", dx);

    size_type size = size_ + dx;
    if (size > cap_)
        reserve(size > 2 * cap_ ? size : 2 * cap_);
}
} // namespace I2P
