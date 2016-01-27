
// Test contract compilation on/off.

#include "../aux_/oteststream.hpp"
#include <boost/contract/core/config.hpp>
#if BOOST_CONTRACT_PUBLIC_FUNCTIONS
    #include <boost/contract/public_function.hpp>
    #include <boost/contract/base_types.hpp>
    #include <boost/contract/override.hpp>
    #include <boost/contract/guard.hpp>
    #include <boost/contract/old.hpp>
#endif
#include <boost/detail/lightweight_test.hpp>
#include <sstream>

boost::contract::test::aux::oteststream out;

struct b {
    #if BOOST_CONTRACT_INVARIANTS
        static void static_invariant() { out << "b::static_inv" << std::endl; }
        void invariant() const { out << "b::inv" << std::endl; }
    #endif

    virtual void f(int x, boost::contract::virtual_* v = 0) = 0;
};

void b::f(int x, boost::contract::virtual_* v) {
    #if BOOST_CONTRACT_POSTCONDITIONS
        boost::contract::old_ptr<int> old_x = BOOST_CONTRACT_OLDOF(v, x);
    #endif
    #if BOOST_CONTRACT_PUBLIC_FUNCTIONS
        boost::contract::guard c = boost::contract::public_function(v, this)
            #if BOOST_CONTRACT_PRECONDITIONS
                .precondition([] { out << "b::f::pre" << std::endl; })
            #endif
            #if BOOST_CONTRACT_POSTCONDITIONS
                .old([] { out << "b::f::old" << std::endl; })
                .postcondition([] { out << "b::f::post" << std::endl; })
            #endif
        ;
    #endif
    out << "b::f::body" << std::endl;
}

struct a
    #define BASES public b
    : BASES
{
    #if BOOST_CONTRACT_PUBLIC_FUNCTIONS
        typedef BOOST_CONTRACT_BASE_TYPES(BASES) base_types;
        BOOST_CONTRACT_OVERRIDE(f)
    #endif

    #if BOOST_CONTRACT_INVARIANTS
        static void static_invariant() { out << "a::static_inv" << std::endl; }
        void invariant() const { out << "a::inv" << std::endl; }
    #endif

    virtual void f(int x, boost::contract::virtual_* v = 0) {
        #if BOOST_CONTRACT_POSTCONDITIONS
            boost::contract::old_ptr<int> old_x = BOOST_CONTRACT_OLDOF(v, x);
        #endif
        #if BOOST_CONTRACT_PUBLIC_FUNCTIONS
            boost::contract::guard c = boost::contract::public_function<
                    override_f>(v, &a::f, this, x)
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
    
    a aa;
    out.str("");
    aa.f(123);
    ok.str(); ok
        #if BOOST_CONTRACT_ENTRY_INVARIANTS
            << "b::static_inv" << std::endl
            << "b::inv" << std::endl
            << "a::static_inv" << std::endl
            << "a::inv" << std::endl
        #endif
        #if BOOST_CONTRACT_PRECONDITIONS
            << "b::f::pre" << std::endl
        #endif
        #if BOOST_CONTRACT_POSTCONDITIONS
            << "b::f::old" << std::endl
            << "a::f::old" << std::endl
        #endif
        << "a::f::body" << std::endl
        #if BOOST_CONTRACT_EXIT_INVARIANTS
            << "b::static_inv" << std::endl
            << "b::inv" << std::endl
            << "a::static_inv" << std::endl
            << "a::inv" << std::endl
        #endif
        #if BOOST_CONTRACT_POSTCONDITIONS
            << "b::f::old" << std::endl
            << "b::f::post" << std::endl
            << "a::f::post" << std::endl
        #endif
    ;
    BOOST_TEST(out.eq(ok.str()));

    return boost::report_errors();
}

