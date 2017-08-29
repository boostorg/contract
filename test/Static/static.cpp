/**
 * @file
 * @author Copyright (C) 2009 Lorenzo Caminiti.
 *  Distributed under DBC++ Software License (see file LICENSE_1_0.txt).
 */

#include <dbc.hpp>
#include <iostream>

class C DBC_INHERIT_OBJECT(C) {
public:
    C(const int& fact = 0): fact_(fact) {}

    int m(const int& x) const
    DBC_MEM_FUN( (public) (int) (C) (m)( (const int&)(x) ) (const), {
    }, {
    }, {
        return x + fact_;
    })

    static int s(const int& x) /* can't say const */ 
    /*DBC_MEM_FUN( (public) (int) (C) (s)( (const int&)(x) ), {
    }, {
    }, */{
        return x * x;
    }//)

private:
    int fact_;

    DBC_INVARIANT(C, {})
};

int f(const int& x)
DBC_MEM_FUN( (public) (int) (C) (f)( (const int&)(x) ), {
 }, {
 }, {
    return x *x; 
 })

int main() {
    C c(-10);

    std::cout << "Mem Fun\n";
    std::cout << c.m(10) << std::endl;

    std::cout << "Static Mem Fun\n";
    std::cout << c.s(10) << std::endl;
    std::cout << C::s(10) << std::endl;
    
    std::cout << "Non-Mem Fun\n";
    std::cout << f(10) << std::endl;
    
    return 0;
};

