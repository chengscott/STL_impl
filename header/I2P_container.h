#ifndef I2P_CONTAINER
#define I2P_CONTAINER
#include "I2P_def.h"

namespace I2P {
class iterator;
class const_iterator;

struct container_base {
    virtual bool empty() const = 0;
    virtual size_type size() const = 0;
    virtual ~container_base() = 0;
};

// class array:public container_base{...};

struct dynamic_size_container : container_base {
    virtual iterator begin() = 0;
    virtual const_iterator begin() const = 0;
    virtual iterator end() = 0;
    virtual const_iterator end() const = 0;

    virtual size_type capacity() const // not necessary
    {
        return size();
    }
    virtual void clear() = 0;
    virtual void reserve(size_type new_capacity) {} // not necessary

    virtual void erase(const_iterator pos) = 0;
    virtual void erase(const_iterator begin, const_iterator end) = 0;

    virtual void shrink_to_fit() {} // not necessary
};

struct ordered_container : dynamic_size_container {
    virtual reference_type back() = 0;
    virtual const_reference_type back() const = 0;
    virtual reference_type front() = 0;
    virtual const_reference_type front() const = 0;

    virtual void insert(const_iterator pos, size_type count,
                        const_reference_type val) = 0;
    virtual void insert(const_iterator pos, const_iterator begin,
                        const_iterator end) = 0;

    virtual void pop_back() = 0;
    virtual void pop_front() = 0;

    virtual void push_back(const_reference_type val) = 0;
    virtual void push_front(const_reference_type val) = 0;
};

// class list:public ordered_container{...};
// class forward_list:public ordered_container{...};

struct randomaccess_container : ordered_container {
    virtual reference_type operator[](size_type pos) = 0;
    virtual const_reference_type operator[](size_type pos) const = 0;
};

// class vector:public randomaccess_container{...};
// class deque:public randomaccess_container{...};

struct associative_container : dynamic_size_container {
    virtual reference_type operator[](const key_type &key) = 0;
    virtual const_reference_type
    operator[](const key_type &key) const = 0; // remove this in the future

    virtual size_type count(const key_type &key) const = 0;
    virtual iterator find(const key_type &key) = 0;
    virtual const_iterator find(const key_type &key) const = 0;

    virtual void insert(const key_type &key, const_reference_type val) = 0;
    virtual void insert(const_iterator begin, const_iterator end) = 0;

    // virtual void erase(const key_type &key)=0;
};

struct sorted_container : associative_container {
    virtual iterator lower_bound(const key_type &key) = 0;
    virtual const_iterator lower_bound(const key_type &key) const = 0;
    virtual iterator upper_bound(const key_type &key) = 0;
    virtual const_iterator upper_bound(const key_type &key) const = 0;
};

// class set:public sorted_container{...};
// class map:public sorted_container{...};
} // namespace I2P

#endif