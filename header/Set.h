#ifndef SET_H
#define SET_H
#include "I2P_container.h"
#include "I2P_iterator.h"

namespace I2P {
class Set : public sorted_container {
  public:
    Set();
    Set(const Set &rhs);
    Set(key_compare comp);
    iterator begin();
    const_iterator begin() const;
    size_type capacity() const;
    void clear();
    size_type count(const key_type &key) const;
    bool empty() const;
    iterator end();
    const_iterator end() const;
    void erase(const_iterator pos);
    void erase(const_iterator begin, const_iterator end);
    iterator find(const key_type &key);
    const_iterator find(const key_type &key) const;
    void insert(const key_type &key, const_reference_type val);
    void insert(const_iterator begin, const_iterator end);
    iterator lower_bound(const key_type &key);
    const_iterator lower_bound(const key_type &key) const;
    void reserve(size_type new_capacity);
    void shrink_to_fit();
    size_type size() const;
    iterator upper_bound(const key_type &key);
    const_iterator upper_bound(const key_type &key) const;
    Set &operator=(const Set &rhs);
    reference_type operator[](const key_type &key);
    const_reference_type operator[](const key_type &key) const;
    ~Set();

  private:
    bool less(const key_type &lhs, const key_type &rhs) { return lhs < rhs; }
    Node *CopyTree(Node *, Node *);
    void DestoryTree(Node *);
    Node *FindNode(const key_type &) const;
    Node *InsertNode(Node *, Node **, const key_type &);
    void DeleteNode(Node *);
    Node *FindLB(const key_type &) const;
    Node *FindUB(const key_type &) const;
    Node *root_;
    size_type size_;
    key_compare cmp_;
};
} // namespace I2P

#endif
