/**
 * @file
 * @author Copyright (C) 2009 Lorenzo Caminiti.
 *  Distributed under DBC++ Software License (see file LICENSE_1_0.txt).
 */
/* $Id$ */

#ifndef STACK4_HPP_
#define STACK4_HPP_

#include <dbc.hpp>
#include <vector>

/** 
 * Dispenser structures with a Last-In, First-Out access policy, and a fixed
 * maximum capacity.
 */
template<typename T>
class Stack4 DBC_INHERIT_OBJECT(Stack4<T>) {
public:
    // Initialization //

    /** Create stack for a maximum of n elements. */
    Stack4(const int& n): capacity_(0), count_(0), representation_() 
        { init(n); } // init() used to split implementation from declaration.

    /** Destroy this stack. (Just checks the invariant at entry.) */
    virtual ~Stack4(void)
    DBC_DESTRUCTOR( (public) (virtual) (template)(Stack4)( (void) ), ; )

    // Access //

    /** Maximum number of stack elements. */
    int capacity(void) const
    DBC_MEM_FUN( (public) (int) (template)(Stack4)
            (capacity)( (void) ) (const), {
    }, {
    }, ; )

    /** Number of stack elements. */
    int count(void) const
    DBC_MEM_FUN( (public) (int) (template)(Stack4) (count)( (void) ) (const), {
    }, {
    }, ; )

    /** Top element. */
    const T& item(void) const
    DBC_MEM_FUN( (public) (const T&) (template)(Stack4)
            (item)( (void) ) (const), {
        DBC_ASSERT(!self.empty(), "not empty");
    }, {
    }, ; )

    // Status Report //

    /** If stack is empty. */
    bool empty(void) const 
    DBC_MEM_FUN( (public) (bool) (template)(Stack4)
            (empty)( (void) ) (const), {
    }, {
        DBC_ASSERT(result == (self.now.count() == 0),
                "result consistent with count");
    }, ; )

    /** If stack is full. */
    bool full(void) const
    DBC_MEM_FUN( (public) (bool) (template)(Stack4) (full)( (void) ) (const), {
    }, {
        DBC_ASSERT(result == (self.now.count() == self.now.capacity()),
                "result consistent with count");
    }, ; )

    // Element Change //

    /** Add x on top. */
    void put(const T& x)
    DBC_MEM_FUN( (public) (void) (template)DBC_COPYABLE(Stack4)
            (put)( (const T&) (x) ), {
        DBC_ASSERT(!self.full(), "not full");
    }, {
        DBC_ASSERT(!self.now.empty(), "not empty");
        DBC_ASSERT(self.now.item() == x.now, "added to top");
        DBC_ASSERT(self.now.count() == (self.old.count() + 1),
                "count increased");
        DBC_ASSERT(self.now.representation_.at(self.now.count() - 1) == x.now,
                "at top array entry");
    }, ; )

    /** Remove top item. */
    void remove(void)
    DBC_MEM_FUN( (public) (void) (template)DBC_COPYABLE(Stack4)
            (remove)( (void) ), {
        DBC_ASSERT(!self.empty(), "not empty");
    }, {
        DBC_ASSERT(!self.now.full(), "not full");
        DBC_ASSERT(self.now.count() == (self.old.count() - 1),
                "count decreased");
    }, ; )

private:
    void init(const int& n)
    DBC_CONSTRUCTOR( (private) (template)(Stack4)( (const int&) (n) ), {
        DBC_ASSERT(n >= 0, "non negative capacity");
    }, {
        DBC_ASSERT(self.now.capacity() == n.now, "capacity set");
        DBC_ASSERT(self.now.empty(), "is empty");
    }, ; )

    int capacity_;
    int count_;
    std::vector<T> representation_;

    DBC_INVARIANT(Stack4, {
        DBC_ASSERT(self.count() >= 0, "count non negative");
        DBC_ASSERT_STREAM(self.count() <= self.capacity(), 
                "count no greater than capacity",
                err << "count " << self.count() << " bounded by capacity "
                << self.capacity());
        DBC_ASSERT(
                self.capacity() == int(self.representation_.capacity()),
                "capacity consistent with array capacity");
        DBC_ASSERT(self.empty() == (self.count() == 0),
                "empty when no elements");
        if (self.count() > 0) DBC_ASSERT(
                self.representation_.at(self.count() - 1) == self.item(),
                "if positive count, item at top");
    })
};

// Implementation //
    
template<typename T>
void Stack4<T>::DBC_BODY(init)(const int& n) {
    capacity_ = n;
    representation_.resize(capacity_);
}

template<typename T>
DBC_DESTRUCTOR_BODY(Stack4<T>)() {}

template<typename T>
int Stack4<T>::DBC_BODY(capacity)() const { return capacity_; }

template<typename T>
int Stack4<T>::DBC_BODY(count)() const { return count_; }

template<typename T>
const T& Stack4<T>::DBC_BODY(item)() const 
    { return representation_.at(count() - 1); }

template<typename T>
bool Stack4<T>::DBC_BODY(empty)() const { return count() == 0; }

template<typename T>
bool Stack4<T>::DBC_BODY(full)() const { return count() == capacity(); }

template<typename T>
void Stack4<T>::DBC_BODY(put)(const T& x) 
    { representation_.at(count_++) = x; }

template<typename T>
void Stack4<T>::DBC_BODY(remove)() { --count_; }

#endif // STACK4_HPP_

