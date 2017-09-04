/* $Id$ */

#ifndef STACK3_HPP_
#define STACK3_HPP_

#include "../Stack4/Stack4.hpp"
#include <dbc.hpp>

/** 
 * Dispenser structures with a Last-In, First-Out access policy, and a fixed
 * maximum capacity.
 * Tollerant version, setting an error code in case of impossible operations.
 */
template<typename T>
class Stack3 DBC_INHERIT_OBJECT(Stack3<T>) {
public:
    /** Default stack item (sometime returned in case of error). */
    const T DEFAULT_ITEM;

    /** Error codes. */
    enum Error {
        NONE = 0, // no error (success).
        OVERFLOW,
        UNDERFLOW,
        NEGATIVE_SIZE,
    };

    // Initializtion //
    
    /** Create stack for a maximum of n elements. If n <0, set error to 
     * NEGATIVE_SIZE (no precondition). */
    Stack3(const int& n): DEFAULT_ITEM(), representation_(0), capacity_(), 
            error_(NONE)
    DBC_CONSTRUCTOR( (public) (template)(Stack3)( (const int&)(n) ), {
    }, {
        DBC_ASSERT((n.now < 0) == (self.now.error() == NEGATIVE_SIZE),
                "error code if impossible");
        DBC_ASSERT((n.now >= 0) == !self.now.error(),
                "no error if possible");
        if (!self.now.error()) DBC_ASSERT(self.now.capacity() == n.now,
                "capacity set if no error");
    }, {
        if (n >= 0) {
            capacity_ = n;
            representation_ = Stack4<T>(capacity_);
        } else {
            error_ = NEGATIVE_SIZE;
        }
    })

    /** Destroy this stack. (Just check invariant at entry.) */
    virtual ~Stack3()
    DBC_DESTRUCTOR( (public) (virtual) (template)(Stack3)(), {})

    // Access //

    /** Maximum number of stack elements. */
    int capacity() const
    DBC_MEM_FUN( (public) (int) (template)(Stack3) (capacity)() (const), {
    }, {
    }, {
        return capacity_; 
    })
    
    /** Number of stack elements. */
    int count() const
    DBC_MEM_FUN( (public) (int) (template)(Stack3) (count)() (const), {
    }, {
    }, {
        return representation_.count(); 
    })

    /** Top element if present. Otherwise, type's default value and error set 
     * to UNDERFLOW (no precondition). */
    const T& item() const
    DBC_MEM_FUN( (public) (const T&) (template)DBC_COPYABLE(Stack3)
            (item)() (const), {
    }, {
        // This is a cont operation (a query), so it does not change the object
        // state and there is no need to use self.old. self.now could have been
        // used without making Stack3 DBC_COPYABLE() in the contract definition
        // above (and saving the need of making a copy of the object). I am 
        // using self.old because it is used in the book where I got this 
        // example from -- possibly so not to have to make item() a const
        // operation...
        DBC_ASSERT(self.old.empty() == (self.now.error() == UNDERFLOW),
                "error code if impossible");
        DBC_ASSERT(!self.old.empty() == !self.now.error(),
                "no error if possible");
    }, {
        if (!empty()) {
            error_ = NONE;
            return representation_.item();
        } else {
            error_ = UNDERFLOW;
            return DEFAULT_ITEM;
        }
    })

    // Status Report //

    /** Error indicator, set by various operations to a non-zero (not NONE) 
     * value if the cannot perform their job. */
    Error error() const
    DBC_MEM_FUN( (public) (Error) (template)(Stack3) (error)() (const), {
    }, {
    }, { return error_; 
    })
    
    /** If stack has no item. */
    bool empty() const
    DBC_MEM_FUN( (public) (bool) (template)(Stack3) (empty)() (const), {
    }, {
    }, { 
        return (capacity_ == 0) || representation_.empty(); 
    })

    /** If stack cannot accept any more item. */
    bool full() const
    DBC_MEM_FUN( (public) (bool) (template)(Stack3) (full)() (const), {
    }, {
    }, {
        return (capacity_ == 0) || representation_.full(); 
    })

    // Element Change //

    /** Add x to top, othwerwise set error (no precondition). */
    void put(const T& x)
    DBC_MEM_FUN( (public) (void) (template)DBC_COPYABLE(Stack3) 
            (put)( (const T&)(x) ), {
    }, {
        DBC_ASSERT(self.old.full() == (self.now.error() == OVERFLOW),
                "error code if impossible");
        DBC_ASSERT(!self.old.full() == !self.now.error(),
                "no error if possible");
        if (!self.now.error()) DBC_ASSERT(!self.now.empty(),
                "not empty if no error");
        if (!self.now.error()) DBC_ASSERT(self.now.item() == x.now,
                "added to top if no error");
        if (!self.now.error()) DBC_ASSERT(
                self.now.count() == (self.old.count() + 1),
                "one more item if no error");
    }, {
        if (full()) { error_ = OVERFLOW; }
        else {
            representation_.put(x);
            error_ = NONE;
        }
    })

    /** Remove to element, othewise set error (no precondition). */
    void remove()
    DBC_MEM_FUN( (public) (void) (template)DBC_COPYABLE(Stack3) (remove)(), {
    }, {
        DBC_ASSERT(self.old.empty() == (self.now.error() == UNDERFLOW),
                "error code if impossible");
        DBC_ASSERT(!self.old.empty() == !self.now.error(),
                "no error if possible");
        if (!self.now.error()) DBC_ASSERT(!self.now.full(),
                "not full if no error");
        if (!self.now.error()) DBC_ASSERT(
                self.now.count() == (self.old.count() - 1),
                "one fewer item if no error");
    }, {
        if (empty()) { error_ = UNDERFLOW; }
        else {
            representation_.remove();
            error_ = NONE;
        }
    })

private:
    // Implementation //
    
    Stack4<T> representation_;
    int capacity_;
    mutable Error error_; // Changed by logically const op to report errors.

    DBC_INVARIANT(Stack3, {})
};

#endif // STACK3_HPP_

