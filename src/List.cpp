#include "../header/List.h"

namespace I2P {
List::List() {
    DBG("ctor\n", 0);

    // initialize head node
    head_ = new Node();
    head_->isHead = true;
    head_->prev = head_->next = head_;
    size_ = 0;
}
List::List(const List &rhs) {
    DBG("copy ctor\n", 0);

    // initialize head node
    head_ = new Node();
    head_->isHead = true;
    head_->prev = head_->next = head_;
    // copy rhs
    Node *cur = head_, *rcur = rhs.head_;
    for (size_type i = 0; i < rhs.size_; ++i) {
        cur->next = new Node(cur, head_);
        head_->prev = cur->next;
        cur = cur->next, rcur = rcur->next;
        cur->v = new value_type(*rcur->v);
    }
    size_ = rhs.size_;
}
List &List::operator=(const List &rhs) {
    DBG("operator =\n", 0);

    // initialize head node
    if (head_ == nullptr) {
        head_ = new Node();
        head_->isHead = true;
        head_->prev = head_->next = head_;
        size_ = 0;
    }
    // if not self-assigned
    if (head_ != rhs.head_) {
        // copy rhs
        Node *cur = head_, *rcur = rhs.head_, *d;
        for (size_type i = 0; i < rhs.size_; ++i) {
            // add node if less than rhs
            if (i >= size_) {
                cur->next = new Node(cur, head_);
                head_->prev = cur->next;
            }
            cur = cur->next, rcur = rcur->next;
            // copy-assigned if initialized
            if (cur->v == nullptr)
                cur->v = new value_type(*rcur->v);
            else
                *cur->v = *rcur->v;
        }
        // delete node if more than rhs
        if (rhs.size_ < size_) {
            d = cur->next;
            // delete extra node
            while (d != head_) {
                d = d->next;
                delete d->prev->v;
                delete d->prev;
            }
            cur->next = head_, head_->prev = cur;
        }
        size_ = rhs.size_;
    }
    return *this;
}
List::~List() {
    Node *cur = head_->next;
    while (cur != head_) {
        cur = cur->next;
        delete cur->prev->v;
        delete cur->prev;
    }
    delete head_;
}
// Iterators
iterator List::begin() { return iterator(new list_iterator(head_->next)); }
const_iterator List::begin() const {
    return const_iterator(new list_iterator(head_->next));
}
iterator List::end() { return iterator(new list_iterator(head_)); }
const_iterator List::end() const {
    return const_iterator(new list_iterator(head_));
}
// Capacity
size_type List::size() const { return size_; }
size_type List::capacity() const { return size_; }
bool List::empty() const { return size_ == 0; }
void List::reserve(size_type new_capacity) {
    // NO IMPL
}
void List::shrink_to_fit() {
    // NO IMPL
}
// Modifiers
void List::push_front(const_reference_type val) {
    DBG("push_front %d\n", val);

    Node *res = new Node(head_, head_->next, val);
    head_->next->prev = res;
    head_->next = res;
    ++size_;
}
void List::push_back(const_reference_type val) {
    DBG("push_back %d\n", val);

    Node *res = new Node(head_->prev, head_, val);
    head_->prev->next = res;
    head_->prev = res;
    ++size_;
}
void List::pop_front() {
    DBG("pop_front\n", 0);

    if (size_ == 0)
        return;
    Node *d = head_->next;
    head_->next = head_->next->next;
    head_->next->prev = head_;
    delete d->v;
    delete d;
    --size_;
}
void List::pop_back() {
    DBG("pop_back\n", 0);

    if (size_ == 0)
        return;
    Node *d = head_->prev;
    head_->prev = head_->prev->prev;
    head_->prev->next = head_;
    delete d->v;
    delete d;
    --size_;
}
void List::insert(const_iterator lhs, size_type count,
                  const_reference_type val) {
    DBG("insert %d times of %d\n", count, val);

    list_iterator *it =
        dynamic_cast<list_iterator *>(static_cast<iterator_impl_base *>(lhs));
    // insert nodes before lhs
    Node *cur = it->it_->prev;
    for (size_type i = 0; i < count; ++i) {
        Node *res = new Node(cur, cur->next, val);
        cur->next->prev = res;
        cur->next = res;
        cur = cur->next;
    }
    size_ += count;
}
void List::insert(const_iterator lhs, const_iterator start,
                  const_iterator end) {
    DBG("insert\n", 0);

    list_iterator *it =
        dynamic_cast<list_iterator *>(static_cast<iterator_impl_base *>(lhs));
    // insert nodes before lhs from start to end
    Node *cur = it->it_->prev;
    while (start != end) {
        Node *res = new Node(cur, cur->next, *start);
        cur->next->prev = res;
        cur->next = res;
        cur = cur->next;
        ++size_;
        ++start;
    }
}
void List::erase(const_iterator rhs) {
    DBG("erase\n", 0);

    list_iterator *it =
        dynamic_cast<list_iterator *>(static_cast<iterator_impl_base *>(rhs));
    Node *cur = it->it_;
    cur->prev->next = cur->next;
    cur->next->prev = cur->prev;
    delete cur->v;
    delete cur;
    --size_;
}
void List::erase(const_iterator start, const_iterator end) {
    DBG("erase range\n", 0);

    Node *cur = dynamic_cast<list_iterator *>(
                    static_cast<iterator_impl_base *>(start))
                    ->it_,
         *rhs = dynamic_cast<list_iterator *>(
                    static_cast<iterator_impl_base *>(end))
                    ->it_,
         *next;
    // erase nodes from start to end
    while (cur != rhs) {
        next = cur->next;
        cur->prev->next = cur->next;
        cur->next->prev = cur->prev;
        delete cur->v;
        delete cur;
        --size_;
        cur = next;
    }
}
void List::clear() {
    DBG("clear\n", 0);

    // dtor except for head node
    Node *cur = head_->next;
    while (cur != head_) {
        cur = cur->next;
        delete cur->prev->v;
        delete cur->prev;
    }
    // initialize head node
    head_->next = head_->prev = head_;
    size_ = 0;
}
// Element access
reference_type List::front() { return *head_->next->v; }
const_reference_type List::front() const { return *head_->next->v; }
reference_type List::back() { return *head_->prev->v; }
const_reference_type List::back() const { return *head_->prev->v; }
} // namespace I2P
