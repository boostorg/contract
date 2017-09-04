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
    int* value_ptr;

    integer(const int* p = 0): value_ptr(new int(p ? *p : 0))
    DBC_CONSTRUCTOR( (public) (integer)( (const int*)(p) ), {
    }, {
        DBC_ASSERT(*(self.now.value_ptr) == *(p.now), "set");
    }, {})

    // Copy contructor must impl deep copy. Because inv must have held for 
    // other, other.valute_ptr != 0.
    integer(const integer& other): value_ptr(new int(*other.value_ptr))
    DBC_CONSTRUCTOR( (public) (integer)( (const integer&)(other) ), {
    }, {
    }, {})

    virtual ~integer(void)
    DBC_DESTRUCTOR( (public) (virtual) (integer)( (void) ), {
        delete value_ptr;
    })

    // Non-const self and const arg.
    void increment(const int* p)
    DBC_MEM_FUN( (public) (void) DBC_COPYABLE(integer)
            (increment)( (const int*)(p) ), {
    }, {
        DBC_ASSERT(*(self.now.value_ptr) == *(self.old.value_ptr) + *(p.now), 
                "incremented");
    }, {
        *value_ptr += *p;
    })
    
    // Non-const self and arg.
    void swap(int* p)
    DBC_MEM_FUN( (public) (void) DBC_COPYABLE(integer) 
            (swap)( DBC_COPYABLE(int*)(p) ), {
    }, {
        DBC_ASSERT(*(self.now.value_ptr) == *(p.old), "set new");
        DBC_ASSERT(*(p.now) == *(self.old.value_ptr), "returning old");
    }, {
        int orig = *value_ptr;
        *value_ptr = *p;
        *p = orig;
    })

    // Const self and non-const arg.
    void offset(int* p) const
    DBC_MEM_FUN( (public) (void) (integer) 
            (offset)( DBC_COPYABLE(int*)(p) ) (const), {
    }, {
        DBC_ASSERT(*(p.now) == *(p.old) + *(self.now.value_ptr), "offset");
    }, {
        *p += *value_ptr;
    })

private:
    DBC_INVARIANT(integer, {
        DBC_ASSERT(self.value_ptr, "value exists");
    })
};

int main() {
    std::cout << std::endl;
    int i = 5;
    integer j(&i);
    i = 2;
    std::cout << "Init: " << i << " " << *(j.value_ptr) << std::endl;
    assert(i == 2 && *(j.value_ptr) == 5);

    std::cout << std::endl;
    j.increment(&i);
    assert(i == 2 && *(j.value_ptr) == 7);
    std::cout << "Incremented: " << i << " " << *(j.value_ptr) << std::endl;
    
    std::cout << std::endl;
    j.swap(&i);
    assert(i == 7 && *(j.value_ptr) == 2);
    std::cout << "Swapped: " << i << " " << *(j.value_ptr) << std::endl;
    
    std::cout << std::endl;
    j.offset(&i);
    assert(i == 9 && *(j.value_ptr) == 2);
    std::cout << "Offset: " << i << " " << *(j.value_ptr) << std::endl;
    
    std::cout << std::endl << "Done." << std::endl;

    return 0;
}

