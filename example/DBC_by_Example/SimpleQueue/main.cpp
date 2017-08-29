/**
 * @file
 * @author Copyright (C) 2009 Lorenzo Caminiti.
 *  Distributed under DBC++ Software License (see file LICENSE_1_0.txt).
 */
/* $Id$ */

#include "SimpleQueue.hpp"
#include <iostream>

int main() {
    std::cout << std::endl << "init()..." << std::endl;
    SimpleQueue<char> q(10);
    
    std::cout << std::endl << "count()..." << std::endl;
    std::cout << q.count() << std::endl;

    std::cout << std::endl << "put()..." << std::endl;
    q.put('a');
    std::cout << std::endl << "put() again..." << std::endl;
    q.put('b');

    std::cout << std::endl << "items()..." << std::endl;
    const std::vector<char>& items = q.items();
    for (std::vector<char>::const_iterator i = items.begin(); 
            items.end() != i; ++i) { std::cout << *i << std::endl; }

    std::cout << std::endl << "capacity()..." << std::endl;
    std::cout << q.capacity() << std::endl;
    
    std::cout << std::endl << "head()..." << std::endl;
    std::cout << q.head() << std::endl;
    
    std::cout << std::endl << "isEmpty()..." << std::endl;
    std::cout << q.isEmpty() << std::endl;
    
    std::cout << std::endl << "isFull()..." << std::endl;
    std::cout << q.isFull() << std::endl;
    
    std::cout << std::endl << "remove()..." << std::endl;
    q.remove();
    
    std::cout << std::endl << "del()..." << std::endl;
    return 0;
}

