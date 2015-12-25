
// Test contract compilation on/off.

#include "../aux_/oteststream.hpp"
#include <boost/contract/core/config.hpp>
#if BOOST_CONTRACT_CONSTRUCTORS
    #include <boost/contract/constructor.hpp>
    #include <boost/contract/guard.hpp>
    #include <boost/contract/old.hpp>
#endif
#include <boost/detail/lightweight_test.hpp>
#include <sstream>

boost::contract::aux::test::oteststream out;

struct b
    #if BOOST_CONTRACT_PRECONDITIONS
        : private boost::contract::constructor_precondition<b>
    #endif
{
    #if BOOST_CONTRACT_INVARIANTS
        static void static_invariant() { out << "b::static_inv" << std::endl; }
        void invariant() const { out << "b::inv" << std::endl; }
    #endif

    explicit b(int x)
        #if BOOST_CONTRACT_PRECONDITIONS
            : boost::contract::constructor_precondition<b>(
                [] { out << "b::ctor::pre" << std::endl; }
            )
        #endif
    {
        #if BOOST_CONTRACT_POSTCONDITIONS
            boost::contract::old_ptr<int> old_x = BOOST_CONTRACT_OLDOF(x);
        #endif
        #if BOOST_CONTRACT_CONSTRUCTORS
            boost::contract::guard c = boost::contract::constructor(this)
                #if BOOST_CONTRACT_POSTCONDITIONS
                    .old([] { out << "b::f::old" << std::endl; })
                    .postcondition([] { out << "b::ctor::post" << std::endl; })
                #endif
            ;
        #endif
        out << "b::ctor::body" << std::endl;
    }
};

struct a :
    #if BOOST_CONTRACT_PRECONDITIONS
        private boost::contract::constructor_precondition<a>,
    #endif
    public b
{
    #if BOOST_CONTRACT_INVARIANTS
        static void static_invariant() { out << "a::static_inv" << std::endl; }
        void invariant() const { out << "a::inv" << std::endl; }
    #endif

    explicit a(int x) :
        #if BOOST_CONTRACT_PRECONDITIONS
            boost::contract::constructor_precondition<a>(
                [] { out << "a::ctor::pre" << std::endl; }
            ),
        #endif
        b(x)
    {
        #if BOOST_CONTRACT_POSTCONDITIONS
            boost::contract::old_ptr<int> old_x = BOOST_CONTRACT_OLDOF(x);
        #endif
        #if BOOST_CONTRACT_CONSTRUCTORS
            boost::contract::guard c = boost::contract::constructor(this)
                #if BOOST_CONTRACT_POSTCONDITIONS
                    .old([] { out << "a::f::old" << std::endl; })
                    .postcondition([] { out << "a::ctor::post" << std::endl; })
                #endif
            ;
        #endif
        out << "a::ctor::body" << std::endl;
    }
};

int main() {
    std::ostringstream ok;
    out.str("");
    a aa(123);
    ok.str(""); ok
        #if BOOST_CONTRACT_PRECONDITIONS
            << "a::ctor::pre" << std::endl
            << "b::ctor::pre" << std::endl
        #endif
        
        #if BOOST_CONTRACT_ENTRY_INVARIANTS
            << "b::static_inv" << std::endl
        #endif
        #if BOOST_CONTRACT_POSTCONDITIONS
            << "b::f::old" << std::endl
        #endif
        << "b::ctor::body" << std::endl
        #if BOOST_CONTRACT_EXIT_INVARIANTS
            << "b::static_inv" << std::endl
            << "b::inv" << std::endl
        #endif
        #if BOOST_CONTRACT_POSTCONDITIONS
            << "b::ctor::post" << std::endl
        #endif

        #if BOOST_CONTRACT_ENTRY_INVARIANTS
            << "a::static_inv" << std::endl
        #endif
        #if BOOST_CONTRACT_POSTCONDITIONS
            << "a::f::old" << std::endl
        #endif
        << "a::ctor::body" << std::endl
        #if BOOST_CONTRACT_EXIT_INVARIANTS
            << "a::static_inv" << std::endl
            << "a::inv" << std::endl
        #endif
        #if BOOST_CONTRACT_POSTCONDITIONS
            << "a::ctor::post" << std::endl
        #endif
    ;
    BOOST_TEST(out.eq(ok.str()));
    return boost::report_errors();
}

