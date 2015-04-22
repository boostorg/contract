
#include "aux_/oteststream.hpp"
#include <boost/contract/constructor.hpp>
#include <boost/contract/type.hpp>
#include <boost/contract/base_types.hpp>
#include <boost/contract/assert.hpp>
#include <boost/detail/lightweight_test.hpp>
#include <sstream>

// Test constructor contracts for classes with and without bases.

boost::contract::aux::test::oteststream out;

struct d
#   define BASES private boost::contract::constructor_precondition<d>
    : BASES
{
    typedef BOOST_CONTRACT_BASE_TYPES(BASES) base_types;
#   undef BASES

    void invariant() const {
        out << "d::inv" << std::endl;
    }

    static void static_invariant() {
        out << "d::static_inv" << std::endl;
    }
    
    explicit d(unsigned const) :
        boost::contract::constructor_precondition<d>([&] {
            out << "d::ctor::pre" << std::endl;
        })
    {
        boost::contract::type c = boost::contract::constructor(this)
            .postcondition([&] {
                out << "d::ctor::post" << std::endl;
            })
        ;
        out << "d::ctor::body" << std::endl;
    }
};

struct c
#   define BASES private boost::contract::constructor_precondition<c>, \
        public d
    : BASES
{
    typedef BOOST_CONTRACT_BASE_TYPES(BASES) base_types;
#   undef BASES

    void invariant() const {
        out << "c::inv" << std::endl;
    }

    static void static_invariant() {
        out << "c::static_inv" << std::endl;
    }
    
    explicit c(unsigned const x) :
        boost::contract::constructor_precondition<c>([&] {
            out << "c::ctor::pre" << std::endl;
        }),
        d(x)
    {
        boost::contract::type c = boost::contract::constructor(this)
            .postcondition([&] {
                out << "c::ctor::post" << std::endl;
            })
        ;
        out << "c::ctor::body" << std::endl;
    }
};

struct b
#   define BASES private boost::contract::constructor_precondition<b>
    : BASES
{
    typedef BOOST_CONTRACT_BASE_TYPES(BASES) base_types;
#   undef BASES

    void invariant() const {
        out << "b::inv" << std::endl;
    }

    static void static_invariant() {
        out << "b::static_inv" << std::endl;
    }
    
    explicit b(unsigned const) :
        boost::contract::constructor_precondition<b>([&] {
            out << "b::ctor::pre" << std::endl;
        })
    {
        boost::contract::type c = boost::contract::constructor(this)
            .postcondition([&] {
                out << "b::ctor::post" << std::endl;
            })
        ;
        out << "b::ctor::body" << std::endl;
    }
};

struct a
#   define BASES private boost::contract::constructor_precondition<a>, \
        public b, public c
    : BASES
{
    typedef BOOST_CONTRACT_BASE_TYPES(BASES) base_types;
#   undef BASES

    void invariant() const {
        out << "a::inv" << std::endl;
        BOOST_CONTRACT_ASSERT(value > 0);
    }

    static void static_invariant() {
        out << "a::static_inv" << std::endl;
    }

    explicit a(unsigned const x) :
        boost::contract::constructor_precondition<a>([&] {
            out << "a::ctor::pre" << std::endl;
            BOOST_CONTRACT_ASSERT(x > 0);
        }),
        b(x),
        c(x),
        value(x)
    {
        boost::contract::type c = boost::contract::constructor(this)
            .postcondition([&] {
                out << "a::ctor::post" << std::endl;
                BOOST_CONTRACT_ASSERT(this->value == x);
            })
        ;
        out << "a::ctor::body" << std::endl;
    }

    unsigned value;
};

int main() {
    std::ostringstream ok;

    out.str("");
    a aa(123);
    ok.str("");
    ok
        << "a::ctor::pre" << std::endl

        << "b::ctor::pre" << std::endl
        << "b::static_inv" << std::endl
        << "b::ctor::body" << std::endl
        << "b::static_inv" << std::endl
        << "b::inv" << std::endl
        << "b::ctor::post" << std::endl

        << "c::ctor::pre" << std::endl

        << "d::ctor::pre" << std::endl
        << "d::static_inv" << std::endl
        << "d::ctor::body" << std::endl
        << "d::static_inv" << std::endl
        << "d::inv" << std::endl
        << "d::ctor::post" << std::endl
        
        << "c::static_inv" << std::endl
        << "c::ctor::body" << std::endl
        << "c::static_inv" << std::endl
        << "c::inv" << std::endl
        << "c::ctor::post" << std::endl
        
        << "a::static_inv" << std::endl
        << "a::ctor::body" << std::endl
        << "a::static_inv" << std::endl
        << "a::inv" << std::endl
        << "a::ctor::post" << std::endl
    ;
    BOOST_TEST(out.check(ok.str()));

    return boost::report_errors();
}

