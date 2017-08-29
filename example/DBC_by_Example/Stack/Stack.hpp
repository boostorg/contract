/* $Id$ */

#ifndef STACK_HPP_
#define STACK_HPP_

#include <dbc.hpp>
#include <vector>

/** Simple stack. */
template<typename T>
class Stack DBC_INHERIT_OBJECT(Stack<T>) {
public:
    // Creation //

    /** Creates an empty stack. */
    Stack(): items_()
    DBC_CONSTRUCTOR( (public) (template)(Stack)(), {
    }, {
        DBC_ASSERT(0 == self.now.count(), "empty");
    }, {})

    // Basic Queries //

    /** Return number of items on stack. */
    int count() const
    DBC_MEM_FUN( (public) (int) (template)(Stack) (count)() (const), {
    }, {
    }, { 
        return items_.size(); 
    })

    /** Return item at specified position. 
     * Position count() is the top of stack, position 1 is bottom. */
    const T& itemAt(const int& index) const
    DBC_MEM_FUN( (public) (const T&) (template)(Stack) 
            (itemAt)( (const int&)(index) ) (const), {
        DBC_ASSERT(index >= 1, "index big enough");
        DBC_ASSERT(index <= self.count(), "index small enough");
    }, {
    }, {
        return items_.at(index - 1);
    })

    // Derived Queries //

    /** If stack contains no items. */
    bool isEmpty() const
    DBC_MEM_FUN( (public) (bool) (template)(Stack) (isEmpty)() (const), {
    }, {
        DBC_ASSERT(result == (self.now.count() == 0), 
                "consistent with count");
    }, {
        return items_.size() == 0;
    })

    /* Item at top of stack. */
    const T& item() const
    DBC_MEM_FUN( (public) (const T&) (template)(Stack) (item)() (const), {
        DBC_ASSERT(self.count() > 0, "not empty");
    }, {
        const int count = self.now.count();
        const T& top = self.now.itemAt(count);
        DBC_ASSERT(result == top, "consisten with item at");
    }, {
        return items_.at(items_.size() - 1);
    })

    // Commands //

    /** Push specified item on top of stack. */
    void put(const T& item)
    DBC_MEM_FUN( (public) (void) (template)DBC_COPYABLE(Stack)
            (put)( (const T&)(item) ), {
    }, {
        const int count = self.now.count();
        const T& top = self.now.itemAt(count);
        DBC_ASSERT(count == (self.old.count() + 1), "count increased");
        DBC_ASSERT(top == item.now, "item on top");
    }, {
        size_t end = items_.size();
        items_.resize(end + 1);
        items_.at(end) = item;
    })

    /** Pop top item from top of stack. */
    void remove()
    DBC_MEM_FUN( (public) (void) (template)DBC_COPYABLE(Stack) (remove)(), {
        DBC_ASSERT(self.count() > 0, "not empty");
    }, {
        DBC_ASSERT(self.now.count() == (self.old.count() - 1),
                "count decreased");
    }, {
        items_.resize(items_.size() - 1);
    })

private:
    std::vector<T> items_;
    
    DBC_INVARIANT(Stack, {
        DBC_ASSERT(self.count() >= 0, "count never negative");
    })
};

#endif // STACK_HPP_

