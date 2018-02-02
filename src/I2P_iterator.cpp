#include "../header/I2P_iterator.h"

namespace I2P {
iterator_impl_base::~iterator_impl_base() {}
} // namespace I2P

namespace I2P {
const_iterator::const_iterator() : p_(nullptr) {}
const_iterator::const_iterator(const const_iterator &rhs)
    : p_(rhs.p_->clone()) {}
const_iterator::const_iterator(iterator_impl_base *p) : p_(p) {}
const_iterator &const_iterator::operator=(const const_iterator &rhs) {
    if (this != &rhs) {
        delete p_;
        p_ = rhs.p_->clone();
    }
    return *this;
}
const_iterator::~const_iterator() {
    delete p_;
}
const_iterator::reference const_iterator::operator*() const {
    return p_->operator*();
}
const_iterator::pointer const_iterator::operator->() const {
    return p_->operator->();
}
const_iterator &const_iterator::operator++() {
    p_->operator++();
    return *this;
}
const_iterator const_iterator::operator++(int) {
    const_iterator ret(*this);
    p_->operator++();
    return ret;
}
const_iterator &const_iterator::operator--() {
    p_->operator--();
    return *this;
}
const_iterator const_iterator::operator--(int) {
    const_iterator ret(*this);
    p_->operator--();
    return ret;
}
const_iterator &const_iterator::operator+=(difference_type offset) {
    p_->operator+=(offset);
    return *this;
}
const_iterator const_iterator::operator+(difference_type offset) const {
    const_iterator ret(*this);
    ret.p_->operator+=(offset);
    return ret;
}
const_iterator &const_iterator::operator-=(difference_type offset) {
    p_->operator-=(offset);
    return *this;
}
const_iterator const_iterator::operator-(difference_type offset) const {
    const_iterator ret(*this);
    ret.p_->operator-=(offset);
    return ret;
}
difference_type const_iterator::operator-(const const_iterator &rhs) const {
    return p_->operator-(*rhs.p_);
}
const_iterator::reference const_iterator::
operator[](difference_type offset) const {
    return p_->operator[](offset);
}
bool const_iterator::operator==(const const_iterator &rhs) const {
    return p_->operator==(*rhs.p_);
}
bool const_iterator::operator!=(const const_iterator &rhs) const {
    return p_->operator!=(*rhs.p_);
}
bool const_iterator::operator<(const const_iterator &rhs) const {
    return p_->operator<(*rhs.p_);
}
bool const_iterator::operator>(const const_iterator &rhs) const {
    return p_->operator>(*rhs.p_);
}
bool const_iterator::operator<=(const const_iterator &rhs) const {
    return p_->operator<=(*rhs.p_);
}
bool const_iterator::operator>=(const const_iterator &rhs) const {
    return p_->operator>=(*rhs.p_);
}
} // namespace I2P

namespace I2P {
iterator::iterator() : const_iterator(nullptr) {}
iterator::iterator(iterator_impl_base *p) : const_iterator(p) {}
iterator::iterator(const iterator &rhs) : const_iterator(rhs) {}
iterator::~iterator() {
    // delete p_;
}
iterator::reference iterator::operator*() const { return p_->operator*(); }
iterator::pointer iterator::operator->() const { return p_->operator->(); }
iterator &iterator::operator++() {
    p_->operator++();
    return *this;
}
iterator iterator::operator++(int) {
    iterator ret(*this);
    p_->operator++();
    return ret;
}
iterator &iterator::operator--() {
    p_->operator--();
    return *this;
}
iterator iterator::operator--(int) {
    iterator ret(*this);
    p_->operator--();
    return ret;
}
iterator &iterator::operator+=(difference_type offset) {
    p_->operator+=(offset);
    return *this;
}
iterator iterator::operator+(difference_type offset) const {
    iterator ret(*this);
    ret.p_->operator+=(offset);
    return ret;
}
iterator &iterator::operator-=(difference_type offset) {
    p_->operator-=(offset);
    return *this;
}
iterator iterator::operator-(difference_type offset) const {
    iterator ret(*this);
    ret.p_->operator-=(offset);
    return ret;
}
difference_type iterator::operator-(const iterator &rhs) const {
    return p_->operator-(*rhs.p_);
}
iterator::reference iterator::operator[](difference_type offset) const {
    return p_->operator[](offset);
}
} // namespace I2P

namespace I2P {
vector_iterator::vector_iterator(pointer rhs) : it_(rhs) {}
vector_iterator *vector_iterator::clone() {
    vector_iterator *ret = new vector_iterator(it_);
    return ret;
}
reference_type vector_iterator::operator*() const { return *it_; }
pointer vector_iterator::operator->() const { return &(operator*()); }
vector_iterator &vector_iterator::operator++() {
    ++it_;
    return *this;
}
vector_iterator &vector_iterator::operator--() {
    --it_;
    return *this;
}
vector_iterator &vector_iterator::operator+=(difference_type offset) {
    it_ += offset;
    return *this;
}
vector_iterator &vector_iterator::operator-=(difference_type offset) {
    it_ -= offset;
    return *this;
}
difference_type vector_iterator::
operator-(const iterator_impl_base &rhs) const {
    const vector_iterator &res = dynamic_cast<const vector_iterator &>(rhs);
    return it_ - res.it_;
}
reference_type vector_iterator::operator[](difference_type offset) const {
    return it_[offset];
}
bool vector_iterator::operator==(const iterator_impl_base &rhs) const {
    return it_ == dynamic_cast<const vector_iterator &>(rhs).it_;
}
bool vector_iterator::operator!=(const iterator_impl_base &rhs) const {
    return it_ != dynamic_cast<const vector_iterator &>(rhs).it_;
}
bool vector_iterator::operator<(const iterator_impl_base &rhs) const {
    return it_ < dynamic_cast<const vector_iterator &>(rhs).it_;
}
bool vector_iterator::operator>(const iterator_impl_base &rhs) const {
    return it_ > dynamic_cast<const vector_iterator &>(rhs).it_;
}
bool vector_iterator::operator<=(const iterator_impl_base &rhs) const {
    return it_ <= dynamic_cast<const vector_iterator &>(rhs).it_;
}
bool vector_iterator::operator>=(const iterator_impl_base &rhs) const {
    return it_ >= dynamic_cast<const vector_iterator &>(rhs).it_;
}
vector_iterator::~vector_iterator() {}
} // namespace I2P

namespace I2P {
list_iterator::list_iterator(Node *rhs) : it_(rhs) {}
list_iterator *list_iterator::clone() {
    list_iterator *ret = new list_iterator(it_);
    return ret;
}
reference_type list_iterator::operator*() const { return *it_->v; }
pointer list_iterator::operator->() const { return &(operator*()); }
list_iterator &list_iterator::operator++() {
    if (!it_->isHead)
        it_ = it_->next;
    return *this;
}
list_iterator &list_iterator::operator--() {
    if (!it_->prev->isHead)
        it_ = it_->prev;
    return *this;
}
list_iterator &list_iterator::operator+=(difference_type offset) {
    if (offset >= 0)
        while (offset--)
            it_ = it_->next;
    else {
        offset = -offset;
        while (offset--)
            it_ = it_->prev;
    }
    return *this;
}
list_iterator &list_iterator::operator-=(difference_type offset) {
    operator+=(-offset);
    return *this;
}
difference_type list_iterator::operator-(const iterator_impl_base &rhs) const {
    Node *cur = it_;
    difference_type d1 = 0, d2 = 0;
    if (cur->isHead)
        cur = cur->prev, ++d1;
    while (!cur->isHead)
        cur = cur->prev, ++d1;
    const list_iterator &res = dynamic_cast<const list_iterator &>(rhs);
    cur = res.it_;
    if (cur->isHead)
        cur = cur->prev, ++d2;
    while (!cur->isHead)
        cur = cur->prev, ++d2;
    return d1 - d2;
}
reference_type list_iterator::operator[](difference_type offset) const {
    Node *cur = it_;
    if (offset >= 0)
        while (offset--)
            cur = cur->next;
    else {
        offset = -offset;
        while (offset--)
            cur = cur->prev;
    }
    return *cur->v;
}
bool list_iterator::operator==(const iterator_impl_base &rhs) const {
    return it_ == dynamic_cast<const list_iterator &>(rhs).it_;
}
bool list_iterator::operator!=(const iterator_impl_base &rhs) const {
    return it_ != dynamic_cast<const list_iterator &>(rhs).it_;
}
bool list_iterator::operator<(const iterator_impl_base &rhs) const {
    return operator-(rhs) < 0;
}
bool list_iterator::operator>(const iterator_impl_base &rhs) const {
    return operator-(rhs) > 0;
}
bool list_iterator::operator<=(const iterator_impl_base &rhs) const {
    return operator-(rhs) <= 0;
}
bool list_iterator::operator>=(const iterator_impl_base &rhs) const {
    return operator-(rhs) >= 0;
}
list_iterator::~list_iterator() {}
} // namespace I2P

namespace I2P {
set_iterator::set_iterator(Node *rhs) : it_(rhs) {}
set_iterator *set_iterator::clone() {
    set_iterator *ret = new set_iterator(it_);
    return ret;
}
reference_type set_iterator::operator*() const { return *it_->v; }
pointer set_iterator::operator->() const { return &(operator*()); }
set_iterator &set_iterator::operator++() {
    it_ = Next(it_);
    return *this;
}
set_iterator &set_iterator::operator--() {
    it_ = Prev(it_);
    return *this;
}
set_iterator &set_iterator::operator+=(difference_type offset) {
    if (offset >= 0)
        while (offset--)
            it_ = Next(it_);
    else {
        offset = -offset;
        while (offset--)
            it_ = Prev(it_);
    }
    return *this;
}
set_iterator &set_iterator::operator-=(difference_type offset) {
    operator+=(-offset);
    return *this;
}
difference_type set_iterator::operator-(const iterator_impl_base &rhs) const {
    Node *cur = it_;
    difference_type d1 = 0, d2 = 0;
    while (!cur->isHead)
        cur = Next(cur), ++d1;
    const set_iterator &res = dynamic_cast<const set_iterator &>(rhs);
    cur = res.it_;
    while (!cur->isHead)
        cur = Next(cur), ++d2;
    return d2 - d1; // == (size_ - d1) - (size_ - d2)
}
reference_type set_iterator::operator[](difference_type offset) const {
    Node *cur = it_;
    if (offset >= 0)
        while (offset--)
            cur = Next(cur);
    else {
        offset = -offset;
        while (offset--)
            cur = Prev(cur);
    }
    return *cur->v;
}
bool set_iterator::operator==(const iterator_impl_base &rhs) const {
    return it_ == dynamic_cast<const set_iterator &>(rhs).it_;
}
bool set_iterator::operator!=(const iterator_impl_base &rhs) const {
    return it_ != dynamic_cast<const set_iterator &>(rhs).it_;
}
bool set_iterator::operator<(const iterator_impl_base &rhs) const {
    return operator-(rhs) < 0;
}
bool set_iterator::operator>(const iterator_impl_base &rhs) const {
    return operator-(rhs) > 0;
}
bool set_iterator::operator<=(const iterator_impl_base &rhs) const {
    return operator-(rhs) <= 0;
}
bool set_iterator::operator>=(const iterator_impl_base &rhs) const {
    return operator-(rhs) >= 0;
}
set_iterator::~set_iterator() {}
Node *set_iterator::Next(Node *node) const {
    if (node->next == nullptr) {
        Node *cur = node;
        while (cur != cur->parent->prev)
            cur = cur->parent;
        return cur->parent;
    }
    Node *cur = node->next;
    while (cur->prev != nullptr)
        cur = cur->prev;
    return cur;
}
Node *set_iterator::Prev(Node *node) const {
    if (node->prev == nullptr) {
        Node *cur = node;
        while (cur != cur->parent->next && cur->parent->parent != nullptr)
            cur = cur->parent;
        return cur->parent;
    }
    Node *cur = node->prev;
    while (cur->next != nullptr)
        cur = cur->next;
    return cur;
}
} // namespace I2P
