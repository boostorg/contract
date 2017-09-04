/**
 * @file
 * @author Copyright (C) 2009 Lorenzo Caminiti.
 *  Distributed under DBC++ Software License (see file LICENSE_1_0.txt).
 */

#include <dbc/separate.hpp>
#include <iostream>
#include <string>

class B { // Base variables and functions.
public:
    std::string bv0;
    
    B(): bv0("bbb") {}
    
    std::string bq0c() const { return bv0; }
    std::string bq1(const std::string& i) { return bv0 + "<base>" + i; }
};

class C: public B {
public:
    // separate<> rule: If return value or argument then sync, else async.

    // Variables (set async, get sync).
    std::string v0;
    std::string v0c;

    C(const std::string& theV0): v0(theV0), v0c(theV0) {}

    // Queries (sync).
    std::string q0() const { return v0; }
    std::string q1(const std::string& i) { return v0 + i; }

    // Commands (async).
    void c1(const std::string& theV0) { v0 = theV0; }

    // Overloading and optional arguments.
    // Optional arguments are not supported via mem ptr and functors.
    // Overloading can be used to obtain the same effect (the 2nd definition
    // below makes i optional). However, mem ptr and functors require huggly
    // stati_cast to resolve type selection ambiugities manually -- static_cast
    // will result in compiler error if function not declared, other casting
    // will result in runtime segfault, ONLY USE STATIC CASTING!!!
    std::string opt(const std::string& i) { return v0 + i; }
    std::string opt() { return opt("<default-argument>"); }
};

void f(const dbc::separate<C>::arg s) {
    // Correctly, only C's const mem can be accessed here because arg is const.
    std::cout << "Entering f()" << std::endl;
//    s->*&C::v0c = "xyz"; // Correctly, this does not compile.
    std::cout << "v0c = " << std::string(s->*&C::v0c) << std::endl;
//    (s->*&C::q0)(); // Correctly, this does not compile.
    std::cout << "bq0c() = " << (s->*&C::bq0c)() << std::endl;
    std::cout << "Exiting f()" << std::endl;
}

int main() {
    std::cout << "Access via operator->*():" << std::endl;
    C c("abc");
    C* p = &c;
    p->*&C::v0 = "xyz";
    std::cout << "v0 = " << p->*&C::v0 << std::endl;
    std::string pi = (p->*&C::q1)("uvw");
    std::cout << "q1 = " << pi << std::endl;

    std::cout << std::endl << "Access via dbc::separate<>:" << std::endl;
    std::cout << "-- constructing" << std::endl;
    dbc::separate<C> s("abc");
    std::cout << "-- setting variable" << std::endl;
    s->*&C::v0 = "xyz";
    std::cout << "-- getting variable" << std::endl;
    std::cout << "v0 = " << (s->*&C::v0).operator std::string() << std::endl;
    std::cout << "-- calling query q0()" << std::endl;
    std::cout << "q0 = " << (s->*&C::q0)() << std::endl;
    std::cout << "-- calling command c1()" << std::endl;
    (s->*&C::c1)("1_2_3");
    std::cout << "-- calling query q1()" << std::endl;
    std::string s1 = (s->*&C::q1)("uvw");
    // Bad practise -- extra code to pass invalid mem ptr.
//    std::string (C::* fp)(const std::string&) = 0;
//    s1 = (s.operator->*(fp))("uvw");
    std::cout << "q1(\"uvw\") = " << s1 << std::endl;
    // Accesing inherited members.
    std::cout << "-- setting bv0" << std::endl;
    s->*&C::bv0 = "<base>xyz";
    std::cout << "-- getting bv0" << std::endl;
    std::cout << "bv0 = " << std::string(s->*&C::bv0) << std::endl;
    std::cout << "-- calling query bq1()" << std::endl;
    std::string bi = (s->*&C::bq1)("uvw");
    std::cout << "bq1 = " << bi << std::endl;
    // Overloading and optinal arg (requires huggly static_casts<>...).
    std::cout << "-- calling overloaded opt(with-argument)" << std::endl;
    std::cout << "opt(\"zzz\") = " << (s->*static_cast
            <std::string (C::*)(const std::string&)>(&C::opt))("zzz")
            << std::endl;
    std::cout << "-- calling overloaded opt(with-no-argument)" << std::endl;
    std::cout << "opt() = " << (s->*static_cast
            <std::string (C::*)()>(&C::opt))()
            << std::endl;
    
    // Argument passing (locking).
    std::cout << std::endl << "Locking via dbc::separate<>::arg:" << std::endl;
    std::cout << "-- invoking f()" << std::endl;
    f(s);
    std::cout << "-- invoked f()" << std::endl;

    return 0;
}

