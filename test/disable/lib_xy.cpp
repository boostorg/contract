
// Test contracts in .cpp have no post as NO_POST in Jamfile (but not in .hpp).

#include "lib_x.hpp"
#include "lib_y.hpp"
#include <boost/contract/function.hpp>
#include <boost/contract/guard.hpp>
#include <boost/detail/lightweight_test.hpp>
#include <sstream>

void f() {
    boost::contract::guard c = boost::contract::function()
        .precondition([] { out("f::pre\n"); })
        .old([] { out("f::old\n"); })
        .postcondition([] { out("f::post\n"); })
    ;
    out("f::body\n");
}

int main() {
    std::ostringstream ok;

    out("");
    f();
    ok.str(""); ok // Test normal (no lib) case.
        #if BOOST_CONTRACT_PRECONDITIONS
            << "f::pre" << std::endl
        #endif
        #if BOOST_CONTRACT_POSTCONDITIONS
            << "f::old" << std::endl
        #endif
        << "f::body" << std::endl
        #if BOOST_CONTRACT_POSTCONDITIONS
            << "f::post" << std::endl
        #endif
    ;
    BOOST_TEST(boost::contract::test::aux::oteststream::eq(out(), ok.str()));

    out("");
    x();
    ok.str(""); ok // Test contracts in .cpp so no post (NO_POST in Jamfile).
        #if BOOST_CONTRACT_PRECONDITIONS
            << "x::pre" << std::endl
        #endif
        << "x::body" << std::endl
    ;
    BOOST_TEST(boost::contract::test::aux::oteststream::eq(out(), ok.str()));
    
    out("");
    y();
    ok.str(""); ok // Test contracts in .hpp so maybe post (NO_POST in Jamfile).
        #if BOOST_CONTRACT_PRECONDITIONS
            << "y::pre" << std::endl
        #endif
        #if BOOST_CONTRACT_POSTCONDITIONS
            << "y::old" << std::endl
        #endif
        << "y::body" << std::endl
        #if BOOST_CONTRACT_POSTCONDITIONS
            << "y::post" << std::endl
        #endif
    ;
    BOOST_TEST(boost::contract::test::aux::oteststream::eq(out(), ok.str()));
    
    return boost::report_errors();
}

