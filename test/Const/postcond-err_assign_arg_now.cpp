/**
 * @file
 * @author Copyright (C) 2009 Lorenzo Caminiti.
 *  Distributed under DBC++ Software License (see file LICENSE_1_0.txt).
 */

/** @file
 * Postcond attempt to change argument value (must fail). Arg is const in 
 * contract even if it is not in body.
 */

#include <dbc.hpp>
#include <iostream>

class integer DBC_INHERIT_OBJECT(integer) {
public:
    integer(const int& i = 0): i_()
    DBC_CONSTRUCTOR( (public) (integer)( (const int&)(i) ), {
    }, {
        DBC_ASSERT(self.now.i_ == i.now, "set");
    }, {
        i_ = i;
    })
    
    virtual ~integer(void)
    DBC_DESTRUCTOR( (public) (virtual) (integer)( (void) ), {})

    // These operations are impl in .cpp once to compile and then to fail.

    void swap(int& i)
    DBC_MEM_FUN( (public) (void) DBC_COPYABLE(integer)
            (swap)( DBC_COPYABLE(int&)(i) ), {
    }, {
        i.now = -1; // Must fail.
        DBC_ASSERT(self.old.i_ == i.now, "i set");
        DBC_ASSERT(self.now.i_ == i.old, "value set");
    }, {
        int orig = i_;
        set(i);
        i = orig;
    })

private:
    int i_;

    void set(const int& i) { i_ = i; }

    DBC_INVARIANT(integer, {})
};

int main() {
    integer i(+10);
    int x = -10;
    i.swap(x);
    std::cout << x << std::endl;

    return 0;
}

