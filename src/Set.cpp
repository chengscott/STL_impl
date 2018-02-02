#include "../header/Set.h"

namespace I2P {
Set::Set() {
    DBG("ctor\n", 0);

    // initialize root with less
    Set(less);
}
Set::Set(key_compare comp) {
    DBG("key_compare ctor\n", 0);

    // initialize root with key_compare
    root_ = new Node();
    root_->isHead = true;
    size_ = 0;
    cmp_ = comp;
}
Set::Set(const Set &rhs) {
    DBG("copy ctor\n", 0);

    root_ = CopyTree(nullptr, rhs.root_);
    size_ = rhs.size_;
    cmp_ = rhs.cmp_;
}
Set &Set::operator=(const Set &rhs) {
    DBG("operator=\n", 0);

    if (root_ != rhs.root_) {
        DestoryTree(root_);
        root_ = CopyTree(nullptr, rhs.root_);
        size_ = rhs.size_;
        cmp_ = rhs.cmp_;
    }
    if (root_ == nullptr)
        Set(less);
    return *this;
}
Set::~Set() { DestoryTree(root_); }
// Iterators
iterator Set::begin() {
    Node *ret = root_;
    while (ret->prev != nullptr)
        ret = ret->prev;
    return iterator(new set_iterator(ret));
}
const_iterator Set::begin() const {
    Node *ret = root_;
    while (ret->prev != nullptr)
        ret = ret->prev;
    return const_iterator(new set_iterator(ret));
}
iterator Set::end() {
    Node *ret = root_;
    while (ret->next != nullptr)
        ret = ret->next;
    return iterator(new set_iterator(ret));
}
const_iterator Set::end() const {
    Node *ret = root_;
    while (ret->next != nullptr)
        ret = ret->next;
    return const_iterator(new set_iterator(ret));
}
// Capacity
size_type Set::size() const { return size_; }
bool Set::empty() const { return size_ == 0; }
size_type Set::capacity() const {
    // NO IMPL
    return 0;
}
void Set::reserve(size_type new_capacity) {
    // NO IMPL
}
void Set::shrink_to_fit() {
    // NO IMPL
}
// Modifiers
reference_type Set::operator[](const key_type &key) {
    DBG("operator[]\n", 0);

    Node *ret = InsertNode(nullptr, &root_, key);
    return *ret->v;
}
const_reference_type Set::operator[](const key_type &key) const {
    DBG("operator[]\n", 0);

    Node *ret = FindNode(key);
    return *ret->v;
}
void Set::insert(const key_type &key, const_reference_type val) {
    DBG("insert\n", 0);

    InsertNode(nullptr, &root_, key);
}
void Set::insert(const_iterator lhs, const_iterator rhs) {
    DBG("insert range\n", 0);

    const_iterator it = lhs;
    while (it != rhs) {
        InsertNode(nullptr, &root_, *it++);
    }
}
void Set::erase(const_iterator pos) {
    DBG("erase\n", 0);

    DeleteNode(
        dynamic_cast<set_iterator *>(static_cast<iterator_impl_base *>(pos))
            ->it_);
    --size_;
}
void Set::erase(const_iterator begin, const_iterator end) {
    DBG("erase range\n", 0);

    const_iterator it = begin;
    while (it != end) {
        erase(it++);
    }
}
void Set::clear() {
    DBG("clear\n", 0);

    DestoryTree(root_);
    root_ = new Node();
    root_->isHead = true;
    size_ = 0;
}
// Operations
iterator Set::find(const key_type &key) {
    DBG("find\n", 0);

    Node *res = FindNode(key);
    if (res == nullptr)
        return end();
    return iterator(new set_iterator(res));
}
const_iterator Set::find(const key_type &key) const {
    DBG("find\n", 0);

    Node *res = FindNode(key);
    if (res == nullptr)
        return end();
    return const_iterator(new set_iterator(res));
}
size_type Set::count(const key_type &key) const {
    DBG("count\n", 0);

    return FindNode(key) == nullptr ? 0 : 1;
}
iterator Set::lower_bound(const key_type &key) {
    DBG("lower bound\n", 0);

    return iterator(new set_iterator(FindLB(key)));
}
const_iterator Set::lower_bound(const key_type &key) const {
    DBG("lower bound\n", 0);

    return const_iterator(new set_iterator(FindLB(key)));
}
iterator Set::upper_bound(const key_type &key) {
    DBG("upper bound\n", 0);

    return iterator(new set_iterator(FindUB(key)));
}
const_iterator Set::upper_bound(const key_type &key) const {
    DBG("upper bound\n", 0);

    return const_iterator(new set_iterator(FindUB(key)));
}
// My
Node *Set::CopyTree(Node *parent, Node *root) {
    if (root == nullptr)
        return nullptr;
    Node *ret = nullptr;
    if (root->isHead) {
        ret = new Node(nullptr, nullptr, parent);
        ret->isHead = true;
    } else
        ret = new Node(nullptr, nullptr, parent, *root->v);
    ret->prev = CopyTree(ret, root->prev);
    ret->next = CopyTree(ret, root->next);
    return ret;
}
void Set::DestoryTree(Node *root) {
    if (root != nullptr) {
        DestoryTree(root->prev);
        DestoryTree(root->next);
        delete root->v;
        delete root;
    }
}
Node *Set::FindNode(const key_type &key) const {
    Node *ret = root_;
    while (ret != nullptr) {
        if (ret->isHead)
            ret = ret->prev;
        else if (*ret->v == key)
            return ret;
        else if (cmp_(key, *ret->v))
            ret = ret->prev;
        else
            ret = ret->next;
    }
    return nullptr;
}
Node *Set::InsertNode(Node *parent, Node **root, const key_type &key) {
    if (*root == nullptr) {
        *root = new Node(nullptr, nullptr, parent, key);
        ++size_;
    } else if ((*root)->isHead) {
        return InsertNode(*root, &(*root)->prev, key);
    } else if (key == *(*root)->v)
        ;
    else if (cmp_(key, *(*root)->v))
        return InsertNode(*root, &(*root)->prev, key);
    else
        return InsertNode(*root, &(*root)->next, key);
    return *root;
}
void Set::DeleteNode(Node *d) {
    if (d == nullptr)
        return;
    Node *lhs = d->prev, *rhs = d->next, *parent = d->parent,
         **node = parent == nullptr
                      ? &root_
                      : (parent->prev == d ? &parent->prev : &parent->next);
    if (lhs == nullptr && rhs == nullptr)
        *node = nullptr;
    else if (lhs == nullptr) {
        rhs->parent = parent;
        *node = rhs;
    } else if (rhs == nullptr) {
        lhs->parent = parent;
        *node = lhs;
    } else {
        Node *cur = rhs;
        while (cur->prev != nullptr)
            cur = cur->prev;
        if (cur->parent != d) {
            if (cur->next != nullptr)
                cur->next->parent = cur->parent;
            cur->parent->prev = cur->next;
            rhs->parent = cur;
            cur->next = rhs;
        }
        lhs->parent = cur;
        cur->prev = lhs;
        cur->parent = parent;
        *node = cur;
    }
    delete d->v;
    delete d;
}
Node *Set::FindLB(const key_type &key) const {
    Node *cur = root_, *ret = root_;
    while (cur != nullptr) {
        if (!cur->isHead && cmp_(*cur->v, key)) {
            cur = cur->next;
        } else {
            ret = cur;
            cur = cur->prev;
        }
    }
    return ret;
}
Node *Set::FindUB(const key_type &key) const {
    Node *cur = root_, *ret = root_;
    while (cur != nullptr) {
        if (!cur->isHead && cmp_(*cur->v, key)) {
            ret = cur;
            cur = cur->next;
        } else {
            cur = cur->prev;
        }
    }
    return ret;
}

} // namespace I2P
