
// Test throw form constructor .old() (in middle branch of inheritance tree).

#include "../aux_/oteststream.hpp"
#include <boost/contract/constructor.hpp>
#include <boost/contract/base_types.hpp>
#include <boost/contract/guard.hpp>
#include <boost/detail/lightweight_test.hpp>
#include <sstream>

boost::contract::aux::test::oteststream out;

struct c
    #define BASES private boost::contract::constructor_precondition<c>
    : BASES
{
    typedef BOOST_CONTRACT_BASE_TYPES(BASES) base_types;
    #undef BASES

    static void static_invariant() { out << "c::static_inv" << std::endl; }
    void invariant() const { out << "c::inv" << std::endl; }

    c() :
        boost::contract::constructor_precondition<c>([&] {
            out << "c::ctor::pre" << std::endl;
        })
    {
        boost::contract::guard c = boost::contract::constructor(this)
            .old([&] { out << "c::ctor::old" << std::endl; })
            .postcondition([&] { out << "c::ctor::post" << std::endl; })
        ;
        out << "c::ctor::body" << std::endl;
        // Do not throw (from inheritance root).
    }
};

struct b
    #define BASES private boost::contract::constructor_precondition<b>, public c
    : BASES
{
    typedef BOOST_CONTRACT_BASE_TYPES(BASES) base_types;
    #undef BASES

    static void static_invariant() { out << "b::static_inv" << std::endl; }
    void invariant() const { out << "b::inv" << std::endl; }

    struct err {};

    b() :
        boost::contract::constructor_precondition<b>([] {
            out << "b::ctor::pre" << std::endl;
        })
    {
        boost::contract::guard c = boost::contract::constructor(this)
            .old([&] {
                out << "b::ctor::old" << std::endl;
                throw b::err(); // Test .old() throws (from mid branch).
            })
            .postcondition([&] { out << "b::ctor::post" << std::endl; })
        ;
        out << "b::ctor::body" << std::endl;
    }
};

struct a
    #define BASES private boost::contract::constructor_precondition<a>, public b
    : BASES
{
    typedef BOOST_CONTRACT_BASE_TYPES(BASES) base_types;
    #undef BASES

    static void static_invariant() { out << "a::static_inv" << std::endl; }
    void invariant() const { out << "a::inv" << std::endl; }

    a() :
        boost::contract::constructor_precondition<a>([&] {
            out << "a::ctor::pre" << std::endl;
        })
    {
        boost::contract::guard c = boost::contract::constructor(this)
            .old([&] { out << "a::ctor::old" << std::endl; })
            .postcondition([&] { out << "a::ctor::post" << std::endl; })
        ;
        out << "a::ctor::body" << std::endl;
        // Do not throw (from inheritance leaf).
    }
};

int main() {
    std::ostringstream ok;

    boost::contract::set_postcondition_failure(
            [] (boost::contract::from) { throw; });
    
    try {
        out.str("");
        a aa;
        BOOST_TEST(false);
    } catch(b::err const&) { 
        ok.str(""); ok
            << "a::ctor::pre" << std::endl
            << "b::ctor::pre" << std::endl
            
            << "c::ctor::pre" << std::endl
            << "c::static_inv" << std::endl
            << "c::ctor::old" << std::endl
            << "c::ctor::body" << std::endl
            << "c::static_inv" << std::endl
            << "c::inv" << std::endl
            << "c::ctor::post" << std::endl
            
            << "b::static_inv" << std::endl
            << "b::ctor::old" << std::endl // Test this threw.
        ;
        BOOST_TEST(out.eq(ok.str()));
    } catch(...) { BOOST_TEST(false); }
    
    return boost::report_errors();
}

