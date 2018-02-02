#ifndef I2P_ITERATOR
#define I2P_ITERATOR
#include "I2P_def.h"
#include <iterator>
#define XDEBUG
#ifdef DEBUG
#define DBG(fmt, ...) printf(fmt, __VA_ARGS__);
#else
#define DBG(fmt, ...)
#endif
#pragma GCC optimize("O3")
#pragma clang optimize on

namespace I2P {
struct iterator_impl_base {
    virtual iterator_impl_base *clone() = 0;
    virtual reference_type operator*() const = 0;
    virtual pointer operator->() const = 0;
    virtual iterator_impl_base &operator++() = 0;
    virtual iterator_impl_base &operator--() = 0;
    virtual iterator_impl_base &operator+=(difference_type offset) = 0;
    virtual iterator_impl_base &operator-=(difference_type offset) = 0;
    virtual difference_type operator-(const iterator_impl_base &rhs) const = 0;
    virtual reference_type operator[](difference_type offset) const = 0;
    virtual bool operator==(const iterator_impl_base &rhs) const = 0;
    virtual bool operator!=(const iterator_impl_base &rhs) const = 0;
    virtual bool operator<(const iterator_impl_base &rhs) const = 0;
    virtual bool operator>(const iterator_impl_base &rhs) const = 0;
    virtual bool operator<=(const iterator_impl_base &rhs) const = 0;
    virtual bool operator>=(const iterator_impl_base &rhs) const = 0;
    virtual ~iterator_impl_base() = 0;
};

class vector_iterator : public iterator_impl_base {
  public:
    vector_iterator(pointer);
    vector_iterator *clone();
    reference_type operator*() const;
    pointer operator->() const;
    vector_iterator &operator++();
    vector_iterator &operator--();
    vector_iterator &operator+=(difference_type offset);
    vector_iterator &operator-=(difference_type offset);
    difference_type operator-(const iterator_impl_base &rhs) const;
    reference_type operator[](difference_type offset) const;
    bool operator==(const iterator_impl_base &rhs) const;
    bool operator!=(const iterator_impl_base &rhs) const;
    bool operator<(const iterator_impl_base &rhs) const;
    bool operator>(const iterator_impl_base &rhs) const;
    bool operator<=(const iterator_impl_base &rhs) const;
    bool operator>=(const iterator_impl_base &rhs) const;
    ~vector_iterator();

  private:
    pointer it_;
};

struct Node {
    value_type *v;
    Node *prev, *next, *parent;
    bool isHead;
    Node()
        : v(nullptr), prev(nullptr), next(nullptr), parent(nullptr),
          isHead(false) {}
    Node(Node *lhs, Node *rhs)
        : v(nullptr), prev(lhs), next(rhs), parent(nullptr), isHead(false) {}
    Node(Node *lhs, Node *rhs, Node *p)
        : v(nullptr), prev(lhs), next(rhs), parent(p), isHead(false) {}
    Node(Node *lhs, Node *rhs, const value_type &val)
        : v(new value_type(val)), prev(lhs), next(rhs), parent(nullptr),
          isHead(false) {}
    Node(Node *lhs, Node *rhs, Node *p, const value_type &val)
        : v(new value_type(val)), prev(lhs), next(rhs), parent(p),
          isHead(false) {}
};

class list_iterator : public iterator_impl_base {
    friend class List;

  public:
    list_iterator(Node *);
    list_iterator *clone();
    reference_type operator*() const;
    pointer operator->() const;
    list_iterator &operator++();
    list_iterator &operator--();
    list_iterator &operator+=(difference_type offset);
    list_iterator &operator-=(difference_type offset);
    difference_type operator-(const iterator_impl_base &rhs) const;
    reference_type operator[](difference_type offset) const;
    bool operator==(const iterator_impl_base &rhs) const;
    bool operator!=(const iterator_impl_base &rhs) const;
    bool operator<(const iterator_impl_base &rhs) const;
    bool operator>(const iterator_impl_base &rhs) const;
    bool operator<=(const iterator_impl_base &rhs) const;
    bool operator>=(const iterator_impl_base &rhs) const;
    ~list_iterator();

  private:
    Node *it_;
};

class set_iterator : public iterator_impl_base {
    friend class Set;

  public:
    set_iterator(Node *);
    set_iterator *clone();
    reference_type operator*() const;
    pointer operator->() const;
    set_iterator &operator++();
    set_iterator &operator--();
    set_iterator &operator+=(difference_type offset);
    set_iterator &operator-=(difference_type offset);
    difference_type operator-(const iterator_impl_base &rhs) const;
    reference_type operator[](difference_type offset) const;
    bool operator==(const iterator_impl_base &rhs) const;
    bool operator!=(const iterator_impl_base &rhs) const;
    bool operator<(const iterator_impl_base &rhs) const;
    bool operator>(const iterator_impl_base &rhs) const;
    bool operator<=(const iterator_impl_base &rhs) const;
    bool operator>=(const iterator_impl_base &rhs) const;
    ~set_iterator();
    Node *Next(Node *node) const;
    Node *Prev(Node *node) const;

  private:
    Node *it_;
};

class const_iterator {
  public:
    using difference_type = I2P::difference_type;
    using value_type = I2P::value_type;
    using pointer = I2P::const_pointer;
    using reference = I2P::const_reference_type;
    using iterator_category = std::random_access_iterator_tag;

  protected:
    iterator_impl_base *p_;

  public:
    const_iterator();
    const_iterator(const const_iterator &rhs);
    const_iterator(iterator_impl_base *p);
    const_iterator &operator=(const const_iterator &rhs);
    reference operator*() const;
    pointer operator->() const;
    const_iterator &operator++();
    const_iterator operator++(int);
    const_iterator &operator--();
    const_iterator operator--(int);
    const_iterator &operator+=(difference_type offset);
    const_iterator operator+(difference_type offset) const;
    const_iterator &operator-=(difference_type offset);
    const_iterator operator-(difference_type offset) const;
    difference_type operator-(const const_iterator &rhs) const;
    reference operator[](difference_type offset) const;
    bool operator==(const const_iterator &rhs) const;
    bool operator!=(const const_iterator &rhs) const;
    bool operator<(const const_iterator &rhs) const;
    bool operator>(const const_iterator &rhs) const;
    bool operator<=(const const_iterator &rhs) const;
    bool operator>=(const const_iterator &rhs) const;
    virtual ~const_iterator();
    explicit operator iterator_impl_base *() const { return p_; }
};

class iterator : public const_iterator {
  public:
    using difference_type = I2P::difference_type;
    using value_type = I2P::value_type;
    using pointer = I2P::pointer;
    using reference = I2P::reference_type;
    using iterator_category = std::random_access_iterator_tag;

  public:
    iterator();
    iterator(iterator_impl_base *p);
    iterator(const iterator &rhs);
    reference operator*() const;
    pointer operator->() const;
    iterator &operator++();
    iterator operator++(int);
    iterator &operator--();
    iterator operator--(int);
    iterator &operator+=(difference_type offset);
    iterator operator+(difference_type offset) const;
    iterator &operator-=(difference_type offset);
    iterator operator-(difference_type offset) const;
    difference_type operator-(const iterator &rhs) const;
    reference operator[](difference_type offset) const;
    ~iterator();
};
} // namespace I2P

#endif
