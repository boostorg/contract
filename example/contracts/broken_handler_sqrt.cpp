
// Copyright (C) 2008-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://sourceforge.net/projects/contractpp

#if defined(__GNUC__) && defined(__GXX_EXPERIMENTAL_CXX0X__)
#   warning "ignored known failure on G++ with C++0x"
#   warning "note: maybe a compiler bug catching re-throws"
    int main ( void ) { return 0; } // Trivial success.
#else

#include <contract.hpp>
#include <boost/detail/lightweight_test.hpp>
#include <iostream>

//[broken_handler_sqrt
struct not_a_number {}; // User defined exception.

CONTRACT_FUNCTION(
    double (sqrt) ( double x )
        precondition(
            x >= 0.0 ? true : throw not_a_number() // Throw user exception.
        )
        postcondition(
            auto root = return,
            root * root == x // Failure throws `contract::broken` exception.
        )
) {
    return 0.0; // Intentionally incorrect to fail postcondition.
}

void throwing_handler ( contract::from const& context )
{
    // Failure handlers always called with active exception that failed the
    // contract, so re-throw it to catch it below for logging.
    try {
        throw;
    } catch(contract::broken& failure) {
        std::cerr << failure.file_name() << "(" << failure.line_number() <<
                "): contract assertion \"" << failure.assertion_code() <<
                "\" failed " << std::endl;
    } catch(std::exception& failure) {
        std::cerr << "contract failed: " << failure.what() << std::endl;
    } catch(...) {
        std::cerr << "contract failed with unknown error" << std::endl;
    }
    
    // Cannot throw from destructors to comply with STL exception safety,
    // otherwise re-throw active exception that failed the contract.
    if(context == contract::FROM_DESTRUCTOR)
        std::cerr << "Ignoring destructor contract failure (probably "
            << "something bad has happened)" << std::endl;
    else throw; // Never terminates.
}

int main ( void )
{
    // Customize contract broken handlers to throw exceptions instead of
    // terminating the program (default).
    contract::set_precondition_broken(&throwing_handler);
    contract::set_postcondition_broken(&throwing_handler);

#ifndef CONTRACT_CONFIG_NO_PRECONDITIONS
    bool pre = false;
    try {
        sqrt(-1.0); // Fails precondition.
    } catch(not_a_number&) {
        pre = true;
        std::clog << "Ignoring not-a-number exception" << std::endl;
    }
    BOOST_TEST(pre);
#endif

#ifndef CONTRACT_CONFIG_NO_POSTCONDITIONS
    bool post = false;
    try {
        sqrt(4.0); // Fails postcondition.
    } catch(...) {
        post = true;
        std::clog << "Unable to calculate square root" << std::endl;
    }
    BOOST_TEST(post);
#endif

    return boost::report_errors();
}
//]

#endif // known failures

