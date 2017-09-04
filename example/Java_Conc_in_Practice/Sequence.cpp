/**
 * @file
 * @author Copyright (C) 2009 Lorenzo Caminiti.
 *  Distributed under DBC++ Software License (see file LICENSE_1_0.txt).
 */

#include <dbc/separate.hpp>
#include <iostream>

class Sequence {
public:
    // If not sync, subsequent calls to getNext() from different threads might
    // return the same value if the 2nd call reads value_ before the 1st call
    // has completed the increment "++" operation -- race condition.
    int getNext() { return value_++; }

private:
    static int value_;
};

int Sequence::value_ = 0;

int main() {
    // In this example, SCOOP rules require all sequential execution (only
    // queries are invoked). Therefore, dbc::separate<> not only sync all the
    // call automatically but it does not even create separate threads (saving
    // the thread creation and sync overhead).

    // Typedefs can be used to facilitate code maintainance in case a separate
    // object type changes. E.g., in this case if the type of u1 changes, then
    // it is enough to change the U1 typedef -- whereas if the type of u2
    // changes, then also all the operator->* invocation will need to change to
    // use the new type (all of those will generate compiler errors).
    typedef Sequence S1;
    dbc::separate<S1> s1;
    dbc::separate<Sequence> s2;

    std::cout << (s1->*&S1::getNext)() << std::endl;
    std::cout << (s2->*&Sequence::getNext)() << std::endl;
    
    return 0;
};

