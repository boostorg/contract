
// Test public static member function contract compilation on/off.

#include "../aux_/oteststream.hpp"
#include <boost/contract/core/config.hpp>
#if BOOST_CONTRACT_PUBLIC_FUNCTIONS
    #include <boost/contract/public_function.hpp>
    #include <boost/contract/guard.hpp>
    #include <boost/contract/old.hpp>
#endif
#include <boost/detail/lightweight_test.hpp>
#include <sstream>

boost::contract::aux::test::oteststream out;

struct a {
    #if BOOST_CONTRACT_INVARIANTS
        static void static_invariant() { out << "a::static_inv" << std::endl; }
        void invariant() const { out << "a::inv" << std::endl; }
    #endif

    static void f(int x) {
        #if BOOST_CONTRACT_POSTCONDITIONS
            boost::contract::old_ptr<int> old_x = BOOST_CONTRACT_OLDOF(x);
        #endif
        #if BOOST_CONTRACT_PUBLIC_FUNCTIONS
            boost::contract::guard c = boost::contract::public_function<a>()
                #if BOOST_CONTRACT_PRECONDITIONS
                    .precondition([] { out << "a::f::pre" << std::endl; })
                #endif
                #if BOOST_CONTRACT_POSTCONDITIONS
                    .old([] { out << "a::f::old" << std::endl; })
                    .postcondition([] { out << "a::f::post" << std::endl; })
                #endif
            ;
        #endif
        out << "a::f::body" << std::endl;
    }
};

int main() {
    std::ostringstream ok;

    out.str("");
    a::f(123);
    ok.str(""); ok
        #if BOOST_CONTRACT_ENTRY_INVARIANTS
            << "a::static_inv" << std::endl
        #endif
        #if BOOST_CONTRACT_PRECONDITIONS
            << "a::f::pre" << std::endl
        #endif
        #if BOOST_CONTRACT_POSTCONDITIONS
            << "a::f::old" << std::endl
        #endif
        << "a::f::body" << std::endl
        // Test no post (but still static inv) because body threw.
        #if BOOST_CONTRACT_EXIT_INVARIANTS
            << "a::static_inv" << std::endl
        #endif
        #if BOOST_CONTRACT_POSTCONDITIONS
            << "a::f::post" << std::endl
        #endif
    ;
    BOOST_TEST(out.eq(ok.str()));

    return boost::report_errors();
}

