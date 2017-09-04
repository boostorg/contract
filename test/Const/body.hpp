/**
 * @file
 * @author Copyright (C) 2009 Lorenzo Caminiti.
 *  Distributed under DBC++ Software License (see file LICENSE_1_0.txt).
 */

#include <dbc.hpp>

class integer DBC_INHERIT_OBJECT(integer) {
public:
    integer(const int& i = 0): i_()
    DBC_CONSTRUCTOR( (public) (integer)( (const int&)(i) ), {
    }, {
        DBC_ASSERT(self.now.get() == i.now, "set");
    }, {
        i_ = i;
    })
    
    virtual ~integer()
    DBC_DESTRUCTOR( (public) (virtual) (integer)(), {})

    // These operations are impl in .cpp once to compile and then to fail.

    void set(const int& i)
    DBC_MEM_FUN( (public) (void) (integer) (set)( (const int&)(i) ), {
    }, {
        DBC_ASSERT(self.now.get() == i.now, "set");
    }, ;)

    int get() const
    DBC_MEM_FUN( (public) (int) (integer) (get)() (const), {
    }, {
        DBC_ASSERT(result == self.now.i_, "returning value");
    }, ;)

private:
    int i_;

    DBC_INVARIANT(integer, {})
};

