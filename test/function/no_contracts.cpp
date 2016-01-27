
// Test contract compilation on/off.

#include "../aux_/oteststream.hpp"
#include <boost/contract/core/config.hpp>
#if BOOST_CONTRACT_FUNCTIONS
    #include <boost/contract/function.hpp>
    #include <boost/contract/guard.hpp>
    #include <boost/contract/old.hpp>
#endif
#include <boost/detail/lightweight_test.hpp>
#include <sstream>

boost::contract::test::aux::oteststream out;

void f(int x) {
    #if BOOST_CONTRACT_POSTCONDITIONS
        boost::contract::old_ptr<int> old_x = BOOST_CONTRACT_OLDOF(x);
    #endif
    #if BOOST_CONTRACT_FUNCTIONS
        boost::contract::guard c = boost::contract::function()
            #if BOOST_CONTRACT_PRECONDITIONS
                .precondition([] { out << "f::pre" << std::endl; })
            #endif
            #if BOOST_CONTRACT_POSTCONDITIONS
                .old([] { out << "f::old" << std::endl; })
                .postcondition([] { out << "f::post" << std::endl; })
            #endif
        ;
    #endif
    out << "f::body" << std::endl;
}

int main() {
    std::ostringstream ok;
    out.str("");
    f(123);
    ok.str(""); ok
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
    BOOST_TEST(out.eq(ok.str()));
    return boost::report_errors();
}

