// Copyright (C) 2009-2010 Lorenzo Caminiti.
// Use, modification, and distribution is subject to the
// Contract++ Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt.)

#include "counter.hpp"
#include "decrement_button.hpp"
#include "view_of_counter.hpp"
#include <iostream>

int main() {
    counter cnt(3);
    view_of_counter view(cnt);
    decrement_button dec(cnt);

    // Simple text-based menu selection.
    char ch = '\0';
    while (ch != 'q') {
        if (dec.enabled()) {
            std::cout << "(-) Decrement counter" << std::endl;
        }
        std::cout << "(q) Quit" << std::endl;
        std::cout << "Select: ";
        
        std::cin >> ch;
        if ('q' == ch) {
            return 0;
        } else if ('-' == ch && dec.enabled()) { 
            dec.on_bn_clicked(); 
        } else {
            std::cout << "Invalid selection '" << ch << "'"
                    << std::endl;
        }
    }

    return 0;
}

