
// Test making all contract extra declarations (base types, inv, etc.) private.

#include "../aux_/oteststream.hpp"
#include <boost/contract/constructor.hpp>
#include <boost/contract/base_types.hpp>
#include <boost/contract/guard.hpp>
#include <boost/detail/lightweight_test.hpp>
#include <sstream>

boost::contract::aux::test::oteststream out;

class b
    #define BASES private boost::contract::constructor_precondition<b>
    : BASES
{
    friend class boost::contract::access;

    typedef BOOST_CONTRACT_BASE_TYPES(BASES) base_types;
    #undef BASES

    static void static_invariant() { out << "b::static_inv" << std::endl; }
    void invariant() const { out << "b::inv" << std::endl; }

public:
    b() : boost::contract::constructor_precondition<b>([] {
        out << "b::ctor::pre" << std::endl;
    }) {
        boost::contract::guard c = boost::contract::constructor(this)
            .old([] { out << "b::ctor::old" << std::endl; })
            .postcondition([] { out << "b::ctor::post" << std::endl; })
        ;
        out << "b::ctor::body" << std::endl;
    }
};

class a
    #define BASES private boost::contract::constructor_precondition<a>, public b
    : BASES
{
    friend class boost::contract::access;
    
    // Private base types (always OK because never used by ctors).
    typedef BOOST_CONTRACT_BASE_TYPES(BASES) base_types;
    #undef BASES

    // Private invariants.
    static void static_invariant() { out << "a::static_inv" << std::endl; }
    void invariant() const { out << "a::inv" << std::endl; }
    
public:
    a() : boost::contract::constructor_precondition<a>([] {
        out << "a::ctor::pre" << std::endl;
    }) {
        boost::contract::guard c = boost::contract::constructor(this)
            .old([] { out << "a::ctor::old" << std::endl; })
            .postcondition([] { out << "a::ctor::post" << std::endl; })
        ;
        out << "a::ctor::body" << std::endl;
    }
};

int main() {
    std::ostringstream ok;

    out.str("");
    a aa;
    ok.str(""); ok
        << "a::ctor::pre" << std::endl

        << "b::ctor::pre" << std::endl
        << "b::static_inv" << std::endl
        << "b::ctor::old" << std::endl
        << "b::ctor::body" << std::endl
        << "b::static_inv" << std::endl
        << "b::inv" << std::endl
        << "b::ctor::post" << std::endl

        << "a::static_inv" << std::endl
        << "a::ctor::old" << std::endl
        << "a::ctor::body" << std::endl
        << "a::static_inv" << std::endl
        << "a::inv" << std::endl
        << "a::ctor::post" << std::endl
    ;
    BOOST_TEST(out.eq(ok.str()));

    out.str("");
    b bb;
    ok.str(""); ok
        << "b::ctor::pre" << std::endl
        << "b::static_inv" << std::endl
        << "b::ctor::old" << std::endl
        << "b::ctor::body" << std::endl
        << "b::static_inv" << std::endl
        << "b::inv" << std::endl
        << "b::ctor::post" << std::endl
    ;
    BOOST_TEST(out.eq(ok.str()));

    return boost::report_errors();
}

