// Copyright (C) 2009-2010 Lorenzo Caminiti.
// Use, modification, and distribution is subject to the
// Contract++ Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt.)

// Show workarounds to pass commas within macro parameters.

#include <contract.hpp>
#include <iostream>
#include <map>

template<typename K, typename T>
void print(const K& key, const T& element) {
    std::cout << key << " -> " << element << std::endl;
}

//[ commas_cpp

template<typename K, typename T>
std::map<K, T> fill(const std::map<K, T>& source,
        const K& key, const T& element)
CONTRACT_FUNCTION(
        (template)( (typename)(K) (typename)(T) )
        // Commas within type expression using the macro.
        (typename CONTRACT_WRAP_TYPE( (std::map<K, T>) )) (set)( 
                // Or equivalently, not using the macro.
                (typename contract::wrap<void 
                        (const std::map<K, T>&) >::type)(source)
                (const K&)(key) (const T&)(element) )
(precondition) ({
    // Commas within value expressions must be wrapped by `()`.
    CONTRACT_ASSERT( (std::map<K, T>().empty()) );
})
(body) ({
    // Commas within code blocks use same workarounds as above
    // wrapping differently commas within type or value expressions. 
    // Or better, separate body definition so it is outside the macro.

    // OK, commas already wrapped by function call `()`.
    print(key, element);
    
    // Commas within type expression wrapped using the macro.
    typename CONTRACT_WRAP_TYPE((std::map<K, T>)) m = source;
    
    // OK, commas already wrapped by if-statement `()`.
    if (0 == std::map<K, T>().empty()) m[key] = element;
    
    return m;
}) )

//]

int main() {
    std::map<int, double> m1;
    std::map<int, double> m2 = set(m1, 1, 2.3);
    return 0;
}

