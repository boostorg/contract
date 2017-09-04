/**
 * @file
 * @author Copyright (C) 2009 Lorenzo Caminiti.
 *  Distributed under DBC++ Software License (see file LICENSE_1_0.txt).
 */

#include <dbc.hpp>
#include <cassert>
#include <iostream>

class integer DBC_INHERIT_OBJECT(integer) {
public:
    int value;

    integer(const int& i = 0): value(i)
    DBC_CONSTRUCTOR( (public) (integer)( (const int&)(i) ), {
    }, {
        DBC_ASSERT(self.now.value == i.now, "set");
    }, {})

    virtual ~integer()
    DBC_DESTRUCTOR( (public) (virtual) (integer)(), {})

    // Non-const self and const arg.
    void increment(const int& i)
    DBC_MEM_FUN( (public) (void) DBC_COPYABLE(integer)
            (increment)( (const int&)(i) ), {
    }, {
        DBC_ASSERT(self.now.value == self.old.value + i.now, "incremented");
    }, {
        value += i;
    })
    
    // Non-const self and arg.
    void swap(int& i)
    DBC_MEM_FUN( (public) (void) DBC_COPYABLE(integer) 
            (swap)( DBC_COPYABLE(int&)(i) ), {
    }, {
        DBC_ASSERT(self.now.value == i.old, "set new");
        DBC_ASSERT(i.now == self.old.value, "returning old");
    }, {
        int orig = value;
        value = i;
        i = orig;
    })

    // Const self and non-const arg.
    void offset(int& i) const
    DBC_MEM_FUN( (public) (void) (integer) 
            (offset)( DBC_COPYABLE(int&)(i) ) (const), {
    }, {
        DBC_ASSERT(i.now == i.old + self.now.value, "offset");
    }, {
        i += value;
    })

private:
    DBC_INVARIANT(integer, {})
};

int main() {
    std::cout << std::endl;
    int i = 5;
    integer j(i);
    i = 2;
    std::cout << "Init: " << i << " " << j.value << std::endl;
    assert(i == 2 && j.value == 5);

    std::cout << std::endl;
    j.increment(i);
    assert(i == 2 && j.value == 7);
    std::cout << "Incremented: " << i << " " << j.value << std::endl;
    
    std::cout << std::endl;
    j.swap(i);
    assert(i == 7 && j.value == 2);
    std::cout << "Swapped: " << i << " " << j.value << std::endl;
    
    std::cout << std::endl;
    j.offset(i);
    assert(i == 9 && j.value == 2);
    std::cout << "Offset: " << i << " " << j.value << std::endl;
    
    std::cout << std::endl << "Done." << std::endl;

    return 0;
}

