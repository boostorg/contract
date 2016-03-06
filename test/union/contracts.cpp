
// Test contracts for unions.

#include "../detail/oteststream.hpp"
#include <boost/contract/constructor.hpp>
#include <boost/contract/destructor.hpp>
#include <boost/contract/public_function.hpp>
#include <boost/contract/function.hpp>
#include <boost/contract/guard.hpp>
#include <boost/detail/lightweight_test.hpp>
#include <sstream>

boost::contract::test::detail::oteststream out;

union u {
    int i;
    double d;

    static void static_invariant() { out << "u::static_inv" << std::endl; }
    void invariant() const { out << "u::inv" << std::endl; }

    u() {
        boost::contract::constructor_precondition<u> pre(
            [] { out << "u::ctor::pre" << std::endl; }
        );
        boost::contract::guard c = boost::contract::constructor(this)
            .old([] { out << "u::ctor::old" << std::endl; })
            .postcondition([] { out << "u::ctor::post" << std::endl; })
        ;
        out << "u::ctor::body" << std::endl;
    }

    ~u() {
        boost::contract::guard c = boost::contract::destructor(this)
            .old([] { out << "u::dtor::old" << std::endl; })
            .postcondition([] { out << "u::dtor::post" << std::endl; })
        ;
        out << "u::dtor::body" << std::endl;
    }

    void f() {
        boost::contract::guard c = boost::contract::public_function(this)
            .precondition([] { out << "u::f::pre" << std::endl; })
            .old([] { out << "u::f::old" << std::endl; })
            .postcondition([] { out << "u::f::post" << std::endl; })
        ;
        out << "u::f::body" << std::endl;
    }

    static void s() {
        boost::contract::guard c = boost::contract::public_function<u>()
            .precondition([] { out << "u::s::pre" << std::endl; })
            .old([] { out << "u::s::old" << std::endl; })
            .postcondition([] { out << "u::s::post" << std::endl; })
        ;
        out << "u::s::body" << std::endl;
    }

protected:
    void g() {
        boost::contract::guard c = boost::contract::function()
            .precondition([] { out << "u::g::pre" << std::endl; })
            .old([] { out << "u::g::old" << std::endl; })
            .postcondition([] { out << "u::g::post" << std::endl; })
        ;
        out << "u::g::body" << std::endl;
    }

    friend void call_g(u& me) { me.g(); }

private:
    void h() {
        boost::contract::guard c = boost::contract::function()
            .precondition([] { out << "u::h::pre" << std::endl; })
            .old([] { out << "u::h::old" << std::endl; })
            .postcondition([] { out << "u::h::post" << std::endl; })
        ;
        out << "u::h::body" << std::endl;
    }
    
    friend void call_h(u& me) { me.h(); }
};

int main() {
    std::ostringstream ok;

    {
        out.str("");
        u uu;
        ok.str(""); ok
            #ifndef BOOST_CONTRACT_NO_PRECONDITIONS
                << "u::ctor::pre" << std::endl
            #endif
            #ifndef BOOST_CONTRACT_NO_ENTRY_INVARIANTS
                << "u::static_inv" << std::endl
            #endif
            #ifndef BOOST_CONTRACT_NO_POSTCONDITIONS
                << "u::ctor::old" << std::endl
            #endif
            << "u::ctor::body" << std::endl
            #ifndef BOOST_CONTRACT_NO_EXIT_INVARIANTS
                << "u::static_inv" << std::endl
                << "u::inv" << std::endl
            #endif
            #ifndef BOOST_CONTRACT_NO_POSTCONDITIONS
                << "u::ctor::post" << std::endl
            #endif
        ;
        BOOST_TEST(out.eq(ok.str()));
    
        out.str("");
        uu.f();
         ok.str(""); ok
            #ifndef BOOST_CONTRACT_NO_ENTRY_INVARIANTS
                << "u::static_inv" << std::endl
                << "u::inv" << std::endl
            #endif
            #ifndef BOOST_CONTRACT_NO_PRECONDITIONS
                << "u::f::pre" << std::endl
            #endif
            #ifndef BOOST_CONTRACT_NO_POSTCONDITIONS
                << "u::f::old" << std::endl
            #endif
            << "u::f::body" << std::endl
            #ifndef BOOST_CONTRACT_NO_EXIT_INVARIANTS
                << "u::static_inv" << std::endl
                << "u::inv" << std::endl
            #endif
            #ifndef BOOST_CONTRACT_NO_POSTCONDITIONS
                << "u::f::post" << std::endl
            #endif
        ;
        BOOST_TEST(out.eq(ok.str()));
        
        out.str("");
        uu.s();
         ok.str(""); ok
            #ifndef BOOST_CONTRACT_NO_ENTRY_INVARIANTS
                << "u::static_inv" << std::endl
            #endif
            #ifndef BOOST_CONTRACT_NO_PRECONDITIONS
                << "u::s::pre" << std::endl
            #endif
            #ifndef BOOST_CONTRACT_NO_POSTCONDITIONS
                << "u::s::old" << std::endl
            #endif
            << "u::s::body" << std::endl
            #ifndef BOOST_CONTRACT_NO_EXIT_INVARIANTS
                << "u::static_inv" << std::endl
            #endif
            #ifndef BOOST_CONTRACT_NO_POSTCONDITIONS
                << "u::s::post" << std::endl
            #endif
        ;
        BOOST_TEST(out.eq(ok.str()));
        
        out.str("");
        call_g(uu);
         ok.str(""); ok
            #ifndef BOOST_CONTRACT_NO_PRECONDITIONS
                << "u::g::pre" << std::endl
            #endif
            #ifndef BOOST_CONTRACT_NO_POSTCONDITIONS
                << "u::g::old" << std::endl
            #endif
            << "u::g::body" << std::endl
            #ifndef BOOST_CONTRACT_NO_POSTCONDITIONS
                << "u::g::post" << std::endl
            #endif
        ;
        BOOST_TEST(out.eq(ok.str()));
        
        out.str("");
        call_h(uu);
         ok.str(""); ok
            #ifndef BOOST_CONTRACT_NO_PRECONDITIONS
                << "u::h::pre" << std::endl
            #endif
            #ifndef BOOST_CONTRACT_NO_POSTCONDITIONS
                << "u::h::old" << std::endl
            #endif
            << "u::h::body" << std::endl
            #ifndef BOOST_CONTRACT_NO_POSTCONDITIONS
                << "u::h::post" << std::endl
            #endif
        ;
        BOOST_TEST(out.eq(ok.str()));

        out.str("");
    } // Call destructor.
    ok.str(""); ok
        #ifndef BOOST_CONTRACT_NO_ENTRY_INVARIANTS
            << "u::static_inv" << std::endl
            << "u::inv" << std::endl
        #endif
        #ifndef BOOST_CONTRACT_NO_POSTCONDITIONS
            << "u::dtor::old" << std::endl
        #endif
        << "u::dtor::body" << std::endl
        #ifndef BOOST_CONTRACT_NO_EXIT_INVARIANTS
            << "u::static_inv" << std::endl
        #endif
        #ifndef BOOST_CONTRACT_NO_POSTCONDITIONS
            << "u::dtor::post" << std::endl
        #endif
    ;
    BOOST_TEST(out.eq(ok.str()));

    return boost::report_errors();
}

