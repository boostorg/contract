
// Test throw from public static member function .old().

#include "../aux_/oteststream.hpp"
#include <boost/contract/public_function.hpp>
#include <boost/contract/guard.hpp>
#include <boost/detail/lightweight_test.hpp>
#include <sstream>

boost::contract::aux::test::oteststream out;

struct a {
    static void static_invariant() { out << "a::static_inv" << std::endl; }
    void invariant() const { out << "a::inv" << std::endl; }

    struct err {};

    static void f() {
        boost::contract::guard c = boost::contract::public_function<a>()
            .precondition([] { out << "a::f::pre" << std::endl; })
            .old([] {
                out << "a::f::old" << std::endl;
                throw a::err();
            })
            .postcondition([] { out << "a::f::post" << std::endl; })
        ;
        out << "a::f::body" << std::endl;
    }
};

int main() {
    std::ostringstream ok;

    boost::contract::set_postcondition_failure(
            [] (boost::contract::from) { throw; });

    try {
        out.str("");
        a::f();
        #if BOOST_CONTRACT_POSTCONDITIONS
                BOOST_TEST(false);
            } catch(a::err const&) {
        #endif
        ok.str(""); ok
            #if BOOST_CONTRACT_ENTRY_INVARIANTS
                << "a::static_inv" << std::endl
            #endif
            #if BOOST_CONTRACT_PRECONDITIONS
                << "a::f::pre" << std::endl
            #endif
            #if BOOST_CONTRACT_POSTCONDITIONS
                << "a::f::old" << std::endl // Test this threw.
            #else
                << "a::f::body" << std::endl
                // Test no post (but still static inv) because .old() threw.
                #if BOOST_CONTRACT_EXIT_INVARIANTS
                    << "a::static_inv" << std::endl
                #endif
            #endif
        ;
        BOOST_TEST(out.eq(ok.str()));
    } catch(...) { BOOST_TEST(false); }

    return boost::report_errors();
}

