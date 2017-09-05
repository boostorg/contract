// Copyright (C) 2009-2010 Lorenzo Caminiti.
// Use, modification, and distribution is subject to the
// Contract++ Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt.)

// Exception specifications supported only for member functions.

#include <contract.hpp>
#include <string>

// NOTE: If contract failure handlers are redefined to throw
// exceptions, exceptions specifications apply to exceptions thrown
// by both the body and by the contract failure handlers.
//
// LIMITATION: Non-member functions with exception specifications
// cannot be contracted.
//
//  void some(const std::string& what) throw(char, int)
//  CONTRACT_FUNCTION( ... ) // Error.
//  void none(const std::string& what) throw()
//  CONTRACT_FUNCTION( ... ) // Error.
//
// WORKAROUND: Make these functions static member functions of some
// artificial class and then contract them.

//[ exspecs_cpp

class c { // Some artificially introduced class.

    CONTRACT_INVARIANT( ({}) )

public:
    static void some(const std::string& what) throw(char, int)
    CONTRACT_FUNCTION( (class) (c) // Ex. specs not repeated in signature.
            (public) (static) (void) (some)( (const std::string&)(what) )
    (body) ({
        if (what == "none") return; // OK.
        if (what == "char") throw char('a'); // OK.
        if (what == "int") throw int(-1); // OK.
        throw what; // Not in specs so terminate() is called.
    }) )
    
    static void none(const std::string& what) throw()
    CONTRACT_FUNCTION( (class) (c) // Ex. specs not repeated in signature.
            (public) (static) (void) (none)( (const std::string&)(what) )
    (body) ({
        if (what == "none") return; // OK.
        throw what; // Not in specs so terminate() is called.
    }) )
};

//]

int main() {
    std::cout << "some:" << std::endl;
    c::some("none");
    try { c::some("char"); }
    catch (char& ex) { std::cerr << ex << std::endl; }
    try { c::some("int"); }
    catch (int& ex) { std::cerr << ex << std::endl; }
    // Exceptions specs correctly call terminate() for the following.
    // try { c::some("string"); }
    // catch (std::string& ex) { std::cerr << ex << std::endl; }
    
    std::cout << "none:" << std::endl;
    c::none("none");
    // Exceptions specs correctly call terminate for the following.
    // try { c::none("string"); }
    // catch (std::string& ex) { std::cerr << ex << std::endl; }
    
    return 0;
}

