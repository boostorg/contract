/**
 * @file
 * @author Copyright (C) 2009 Lorenzo Caminiti.
 *  Distributed under DBC++ Software License (see file LICENSE_1_0.txt).
 */
/* $Id$ */

#include "Counter.hpp"
#include "DecrementButton.hpp"
#include "ViewOfCounter.hpp"
#include <iostream>

int main() {
    Counter cnt(3);
    ViewOfCounter view(cnt);
    DecrementButton dec(cnt);

    char ch = '\0';
    while (ch != 'q') {
        std::cout << std::endl;
        std::cout << "-- Counter value printer above as "
                << "\"Counter started at <VALUE>\" or "
                << "\"Counter changed to <VALUE>\" --" << std::endl;
        if (dec.enabled()) {
            std::cout << "(-) Decrement" << std::endl;
        }
        std::cout << "(q) Quit" << std::endl;
        std::cout << "Select: ";
        
        std::cin >> ch;
        if ('q' == ch) {
            return 0;
        } else if ('-' == ch && dec.enabled()) { 
            dec.onBnClicked(); 
        } else {
            std::cout << "Invalid selection '" << ch << "'" << std::endl;
        }
    }

    return 0;
}

