// Copyright (C) 2009-2010 Lorenzo Caminiti.
// Use, modification, and distribution is subject to the
// Contract++ Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt.)

#include "simple_queue.hpp"
#include <iostream>

int main() {
    std::cout << std::endl << "constructor()" << std::endl;
    simple_queue<char> q(10);
    
    std::cout << std::endl << "count()" << std::endl;
    std::cout << q.count() << std::endl;

    std::cout << std::endl << "put()" << std::endl;
    q.put('a');
    std::cout << std::endl << "put() (again)" << std::endl;
    q.put('b');

    std::cout << std::endl << "items()" << std::endl;
    const std::vector<char>& items = q.items();
    for (std::vector<char>::const_iterator i = items.begin(); 
            items.end() != i; ++i) {
        std::cout << *i << std::endl;
    }

    std::cout << std::endl << "capacity()" << std::endl;
    std::cout << q.capacity() << std::endl;
    
    std::cout << std::endl << "head()" << std::endl;
    std::cout << q.head() << std::endl;
    
    std::cout << std::endl << "is_empty()" << std::endl;
    std::cout << q.is_empty() << std::endl;
    
    std::cout << std::endl << "is_full()" << std::endl;
    std::cout << q.is_full() << std::endl;
    
    std::cout << std::endl << "remove()" << std::endl;
    q.remove();
    
    std::cout << std::endl << "destructor()" << std::endl;
    return 0;
}

