/**
 * @file
 * @author Copyright (C) 2009 Lorenzo Caminiti.
 *  Distributed under DBC++ Software License (see file LICENSE_1_0.txt).
 */

#include "throwing_number.hpp"

int main() {
    try {
        std::cout << std::endl;
        {
            std::cout << number<int>("abc").value() << std::endl;
        } // Would normally invoke destructor.
    } catch (dbc::invariant_violation& ex) {
        std::cout << "Ignoring " << ex.what() << std::endl;
        assert(!destructor_called);
        std::cout << ">>> Destructor body not called because object not fully "
                << "contructed yet" << std::endl;
    }

    return 0;
}

