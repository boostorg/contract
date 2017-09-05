// Copyright (C) 2009-2010 Lorenzo Caminiti.
// Use, modification, and distribution is subject to the
// Contract++ Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt.)

// Test overloaded and overridden functions.
// This is important because the library implementation uses function
// pointer so this tests compilers can resolve the calls of
// ovierloaded (overridden and templated) function pointers correctly.

#include <contract.hpp>
#include <string>
#include <sstream>
#include <iostream>

class name_list {

    CONTRACT_INVARIANT( ({}) )

public:
    virtual void put(const std::string& name)
    CONTRACT_FUNCTION( (class) (name_list)
            (public) (virtual) (void) (put)(
                    (const std::string&)(name) )
    (precondition) ({
        std::cout << "base pre put(string)\n";
    })
    (postcondition) ({
        std::cout << "base post put(string)\n";
    })
    (body) ({
        std::cout << "base body put(string)\n";
        std::cout << name << std::endl;
    }) )
    
    virtual void put(const std::string& name) const
    CONTRACT_FUNCTION( (class) (name_list)
            (public) (virtual) (void) (put)(
                    (const std::string&)(name) ) (const)
    (precondition) ({
        std::cout << "base pre put(string) const\n";
    })
    (postcondition) ({
        std::cout << "base post put(string) const\n";
    })
    (body) ({
        std::cout << "base body put(string) const\n";
        std::cout << name << std::endl;
    }) )
};

class relaxed_name_list: public name_list {

    CONTRACT_INVARIANT( ({}) )

public:
    virtual void put(const std::string& name)
    CONTRACT_FUNCTION( (class) (relaxed_name_list) (inherit)(name_list)
            (public) (virtual) (void) (put)(
                    (const std::string&)(name) )
    (precondition) ({
        std::cout << "derived pre put(string)\n";
    })
    (postcondition) ({
        std::cout << "derived post put(string)\n";
    })
    (body) ({
        std::cout << "derived body put(string)\n";
        std::cout << name << std::endl;
    }) )
    
    // Overload based on const qualifier.
    virtual void put(const std::string& name) const
    CONTRACT_FUNCTION( (class) (relaxed_name_list) (inherit)(name_list)
            (public) (virtual) (void) (put)(
                    (const std::string&)(name) ) (const)
    (precondition) ({
        std::cout << "derived pre put(string) const\n";
    })
    (postcondition) ({
        std::cout << "derived post put(string) const\n";
    })
    (body) ({
        std::cout << "derived body put(string) const\n";
        std::cout << name << std::endl;
    }) )

    // Library requires that all but const qualified overloads must
    // use different argument names (not just different types).

    // No subcontractin for the following because they have no
    // matching functions in base class.
    
    // Overload based on argument type.
    virtual void put(const int& number)
    CONTRACT_FUNCTION( (class) (relaxed_name_list)
            (public) (virtual) (void) (put)( (const int&)(number) )
    (precondition) ({
        std::cout << "derived pre put(int)\n";
    })
    (postcondition) ({
        std::cout << "derived post put(int)\n";
    })
    (body) ({
        std::cout << "derived body put(int)\n";
        std::cout << number << std::endl;
    }) )
    
    // Overload based on argument number.
    virtual void put(const std::string& name, const int& number)
    CONTRACT_FUNCTION( (class) (relaxed_name_list)
            (public) (virtual) (void) (put)( 
                    (const std::string&)(name) (const int&)(number) )
    (precondition) ({
        std::cout << "derived pre put(string, int)\n";
    })
    (postcondition) ({
        std::cout << "derived post put(string, int)\n";
    })
    (body) ({
        std::cout << "derived body put(string, int)\n";
        std::cout << name << " " << number << std::endl;
    }) )
    
    // Overload based on templated parameter.
    template<typename T>
    void put(const T& element) // Template cannot be virtual.
    CONTRACT_FUNCTION( (class) (relaxed_name_list)
            (public) (template)( (typename)(T) )
            (void) (put)( (const T&)(element) )
    (precondition) ({
        std::cout << "derived pre put(T)\n";
    })
    (postcondition) ({
        std::cout << "derived post put(T)\n";
    })
    (body) ({
        std::cout << "derived body put(T)\n";
        std::cout << element << std::endl;
    }) )
};

int main() {
    std::string s; // Make sure string type is used (not char*).

    name_list n;
    const name_list& const_n = n;
    std::cout << std::endl;
    n.put(s = "abc"); // Call put(string).
    std::cout << std::endl;
    const_n.put(s = "ijk"); // Call put(string) const.
    
    relaxed_name_list r;
    const relaxed_name_list& const_r = r;
    std::cout << std::endl;
    r.put(s = "xyz"); // Call put(string).
    std::cout << std::endl;
    const_r.put(s = "uvw"); // Call put(string) const.
    std::cout << std::endl;
    r.put(3); // Call put(int).
    std::cout << std::endl;
    r.put(s = "rst", 5); // Call put(string, int).
    std::cout << std::endl;
    r.put(1.23); // Call put(T) T=double.

    return 0;
}
