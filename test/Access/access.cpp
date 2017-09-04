/**
 * @file
 * @author Copyright (C) 2009 Lorenzo Caminiti.
 *  Distributed under DBC++ Software License (see file LICENSE_1_0.txt).
 */

#include <dbc.hpp>
#include <iostream>

class number DBC_INHERIT_OBJECT(number) {
public:
    int* publ_ptr;
    int publ_get() const { return *publ_ptr; }
protected:
    int* prot_ptr;
    int prot_get() const { return *prot_ptr; }
private:
    int* priv_ptr;
    int priv_get() const { return *priv_ptr; }

public:
    number(const int& value = 0): publ_ptr(new int(value)),
            prot_ptr(new int(value)), priv_ptr(new int(value)) {}

    virtual ~number() {
        delete priv_ptr;
        delete prot_ptr;
        delete publ_ptr;
    }

    void set(const int& value)
    DBC_MEM_FUN( (public) (void) (number) (set)( (const int&)(value) ), {
        // NOTE: Preconditions that access non public members are essentially
        // ill-written. This library leaves it up to the programmer to avoid
        // this (Eiffel generates a compiler error intead).

        // Silly example of preconditions, just re-check invariant...
        // Preconditions can access public, protected, and private mem var.
        DBC_ASSERT(self.publ_ptr, "public value exists");
        DBC_ASSERT(self.prot_ptr, "protected value exists");
        DBC_ASSERT(self.priv_ptr, "private value exists");
        // Preconditions can access public, protected, and private mem fun.
        DBC_ASSERT((self.publ_get() == self.prot_get()) 
                && (self.publ_get() == self.priv_get()),
                "public, protected, and private get consistent");
    } , {
        // Postcondition can access public mem var and fun.
        DBC_ASSERT(*self.now.publ_ptr == value.now, "publlic value set");
        DBC_ASSERT(self.now.publ_get() == value.now, 
                "publlic get returns value");
        // Postcondition can access protected mem var and fun.
        DBC_ASSERT(*self.now.prot_ptr == value.now, "protected value set");
        DBC_ASSERT(self.now.prot_get() == value.now, 
                "protected get returns value");
        // Postcondition can access private mem var and fun.
        DBC_ASSERT(*self.now.priv_ptr == value.now, "private value set");
        DBC_ASSERT(self.now.priv_get() == value.now,
                "private get returns value");
    }, {
        *priv_ptr = *prot_ptr = *publ_ptr = value; 
    })

private:
    DBC_INVARIANT(number, {
        // Invariant can access public, protected, and private mem var.
        DBC_ASSERT(self.publ_ptr, "public value exists");
        DBC_ASSERT(self.prot_ptr, "protected value exists");
        DBC_ASSERT(self.priv_ptr, "private value exists");
        // Invariant can access public, protected, and private mem fun.
        DBC_ASSERT((self.publ_get() == self.prot_get()) 
                && (self.publ_get() == self.priv_get()),
                "public, protected, and private get consistent");
    })
};

int main() {
    number n(5);
    n.set(10);
    std::cout << n.publ_get() << std::endl;

    return 0;
}

