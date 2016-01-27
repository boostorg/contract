
// Test contract compilation on/off.

#include "../aux_/oteststream.hpp"
#include <boost/contract/core/config.hpp>
#if BOOST_CONTRACT_DESTRUCTORS
    #include <boost/contract/destructor.hpp>
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

    virtual ~b() {
        #if BOOST_CONTRACT_POSTCONDITIONS
            boost::contract::old_ptr<int> old_y = BOOST_CONTRACT_OLDOF(y);
        #endif
        #if BOOST_CONTRACT_DESTRUCTORS
            boost::contract::guard c = boost::contract::destructor(this)
                #if BOOST_CONTRACT_POSTCONDITIONS
                    .old([] { out << "b::dtor::old" << std::endl; })
                    .postcondition([] { out << "b::dtor::post" << std::endl; })
                #endif
            ;
        #endif
        out << "b::dtor::body" << std::endl;
    }
    
    static int y;
};
int b::y = 0;

struct a : public b {
    #if BOOST_CONTRACT_INVARIANTS
        static void static_invariant() { out << "a::static_inv" << std::endl; }
        void invariant() const { out << "a::inv" << std::endl; }
    #endif

    virtual ~a() {
        #if BOOST_CONTRACT_POSTCONDITIONS
            boost::contract::old_ptr<int> old_x = BOOST_CONTRACT_OLDOF(x);
        #endif
        #if BOOST_CONTRACT_DESTRUCTORS
            boost::contract::guard c = boost::contract::destructor(this)
                #if BOOST_CONTRACT_POSTCONDITIONS
                    .old([] { out << "a::dtor::old" << std::endl; })
                    .postcondition([] { out << "a::dtor::post" << std::endl; })
                #endif
            ;
        #endif
        out << "a::dtor::body" << std::endl;
    }
    
    static int x;
};
int a::x = 0;

int main() {
    std::ostringstream ok;
    {
        a aa;
        out.str("");
    }
    ok.str(""); ok
        #if BOOST_CONTRACT_ENTRY_INVARIANTS
            << "a::static_inv" << std::endl
            << "a::inv" << std::endl
        #endif
        #if BOOST_CONTRACT_POSTCONDITIONS
            << "a::dtor::old" << std::endl
        #endif
        << "a::dtor::body" << std::endl
        #if BOOST_CONTRACT_EXIT_INVARIANTS
            << "a::static_inv" << std::endl
        #endif
        #if BOOST_CONTRACT_POSTCONDITIONS
            << "a::dtor::post" << std::endl
        #endif

        #if BOOST_CONTRACT_ENTRY_INVARIANTS
            << "b::static_inv" << std::endl
            << "b::inv" << std::endl
        #endif
        #if BOOST_CONTRACT_POSTCONDITIONS
            << "b::dtor::old" << std::endl
        #endif
        << "b::dtor::body" << std::endl
        #if BOOST_CONTRACT_EXIT_INVARIANTS
            << "b::static_inv" << std::endl
        #endif
        #if BOOST_CONTRACT_POSTCONDITIONS
            << "b::dtor::post" << std::endl
        #endif
    ;
    BOOST_TEST(out.eq(ok.str()));
    return boost::report_errors();
}

