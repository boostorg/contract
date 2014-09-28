
// Copyright (C) 2008-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://sourceforge.net/projects/contractpp

//[stroustrup97_string_main
// File: string_main.cpp
#include "string.hpp"
#include <boost/detail/lightweight_test.hpp>

// Handler that re-throws contract broken exceptions instead of terminating.
void throwing_handler ( contract::from const& context )
{
    if(context == contract::FROM_DESTRUCTOR) {
        // Destructor cannot throw for STL exception safety (ignore error).
        std::clog << "Ignored destructor contract failure" << std::endl;
    } else {
        // Failure handlers always called with active an exception.
        throw; // Re-throw active exception thrown by precondition.
    }
}

int main ( void )
{
    // Setup all contract failure handlers to throw (instead of terminate).
    contract::set_precondition_broken(&throwing_handler);
    contract::set_postcondition_broken(&throwing_handler);
    contract::set_class_invariant_broken(&throwing_handler);
    contract::set_block_invariant_broken(&throwing_handler);
    contract::set_loop_variant_broken(&throwing_handler);
    
    string s("abc");
    BOOST_TEST(s[0] == 'a');

#ifndef CONTRACT_CONFIG_NO_PRECONDITIONS
    bool pass = false;
    try { s[3]; } // Out of range.
    catch(string::range_error) { pass = true; }
    BOOST_TEST(pass);
#endif

    return boost::report_errors();
}
//]

