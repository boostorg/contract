
#ifndef BOOST_CONTRACT_TEST_FUNCTION_DECL_HPP_
#define BOOST_CONTRACT_TEST_FUNCTION_DECL_HPP_

// Test with and without pre and post declarations.

#include "../aux_/oteststream.hpp"
#include <boost/contract/function.hpp>
#include <boost/contract/guard.hpp>
#include <boost/contract/assert.hpp>

boost::contract::test::aux::oteststream out;

bool f_pre = true, f_post = true;
void f() {
    boost::contract::guard c = boost::contract::function()
        #ifndef BOOST_CONTRACT_TEST_NO_F_PRE
            .precondition([&] {
                out << "f::pre" << std::endl;
                BOOST_CONTRACT_ASSERT(f_pre);
            })
        #endif
        .old([] { out << "f::old" << std::endl; })
        #ifndef BOOST_CONTRACT_TEST_NO_F_POST
            .postcondition([] {
                out << "f::post" << std::endl;
                BOOST_CONTRACT_ASSERT(f_post);
            })
        #endif
    ;
    out << "f::body" << std::endl;
}

#endif // #include guard

