
// Test subcontracting with sparse and complex inheritance graph.

#include "../aux_/oteststream.hpp"
#include <boost/contract/public_function.hpp>
#include <boost/contract/assert.hpp>
#include <boost/contract/guard.hpp>
#include <boost/contract/override.hpp>
#include <boost/contract/base_types.hpp>
#include <boost/detail/lightweight_test.hpp>
#include <sstream>

boost::contract::aux::test::oteststream out;

struct j {
    void invariant() const { out << "j::inv" << std::endl; }
    static void static_invariant() { out << "j::static_inv" << std::endl; }

    virtual void f(char ch, boost::contract::virtual_* v = 0) {
        boost::contract::guard c = boost::contract::public_function(v, this)
            .precondition([&] {
                out << "j::f::pre" << std::endl;
                BOOST_CONTRACT_ASSERT(ch == 'j');
            })
            .old([&] { out << "j::f::old" << std::endl; })
            .postcondition([&] { out << "j::f::post" << std::endl; })
        ;
        out << "j::f::body" << std::endl;
    }
};

struct i {
    void invariant() const { out << "i::inv" << std::endl; }
    static void static_invariant() { out << "i::static_inv" << std::endl; }

    virtual void f(char ch, boost::contract::virtual_* v = 0) {
        boost::contract::guard c = boost::contract::public_function(v, this)
            .precondition([&] {
                out << "i::f::pre" << std::endl;
                BOOST_CONTRACT_ASSERT(ch == 'i');
            })
            .old([&] { out << "i::f::old" << std::endl; })
            .postcondition([&] { out << "i::f::post" << std::endl; })
        ;
        out << "i::f::body" << std::endl;
    }
};

struct k {};

struct h
    #define BASES public j
    : BASES
{
    typedef BOOST_CONTRACT_BASE_TYPES(BASES) base_types;
    #undef BASES
    
    void invariant() const { out << "h::inv" << std::endl; }
    static void static_invariant() { out << "h::static_inv" << std::endl; }

    virtual void f(char ch, boost::contract::virtual_* v = 0) /* override */ {
        boost::contract::guard c = boost::contract::public_function<
                override_f>(v, &h::f, this, ch)
            .precondition([&] {
                out << "h::f::pre" << std::endl;
                BOOST_CONTRACT_ASSERT(ch == 'h');
            })
            .old([&] { out << "h::f::old" << std::endl; })
            .postcondition([&] { out << "h::f::post" << std::endl; })
        ;
        out << "h::f::body" << std::endl;
    }
    BOOST_CONTRACT_OVERRIDE(f)
};

struct e
    #define BASES public virtual i
    : BASES
{
    typedef BOOST_CONTRACT_BASE_TYPES(BASES) base_types;
    #undef BASES
    
    void invariant() const { out << "e::inv" << std::endl; }
    static void static_invariant() { out << "e::static_inv" << std::endl; }

    virtual void f(char ch, boost::contract::virtual_* v = 0) /* override */ {
        boost::contract::guard c = boost::contract::public_function<
                override_f>(v, &e::f, this, ch)
            .precondition([&] {
                out << "e::f::pre" << std::endl;
                BOOST_CONTRACT_ASSERT(ch == 'e');
            })
            .old([&] { out << "e::f::old" << std::endl; })
            .postcondition([&] { out << "e::f::post" << std::endl; })
        ;
        out << "e::f::body" << std::endl;
    }
    BOOST_CONTRACT_OVERRIDE(f)
};

struct d
    #define BASES public k, virtual public i
    : BASES
{
    typedef BOOST_CONTRACT_BASE_TYPES(BASES) base_types;
    #undef BASES
    
    void invariant() const { out << "d::inv" << std::endl; }
    static void static_invariant() { out << "d::static_inv" << std::endl; }
};

struct c {
    void invariant() const { out << "c::inv" << std::endl; }
    static void static_invariant() { out << "c::static_inv" << std::endl; }
    
    virtual void f(char ch, boost::contract::virtual_* v = 0) {
        boost::contract::guard c = boost::contract::public_function(v, this)
            .precondition([&] {
                out << "c::f::pre" << std::endl;
                BOOST_CONTRACT_ASSERT(ch == 'c');
            })
            .old([&] { out << "c::f::old" << std::endl; })
            .postcondition([&] { out << "c::f::post" << std::endl; })
        ;
        out << "c::f::body" << std::endl;
    }
};

struct b
    #define BASES public c, public d
    : BASES
{
    typedef BOOST_CONTRACT_BASE_TYPES(BASES) base_types;
    #undef BASES
    
    void invariant() const { out << "b::inv" << std::endl; }
    static void static_invariant() { out << "b::static_inv" << std::endl; }
};

struct x {};
struct y {};
struct z {};

struct a
    #define BASES public b, public x, public e, protected y, public h, \
            private z
    : BASES
{
    typedef BOOST_CONTRACT_BASE_TYPES(BASES) base_types;
    #undef BASES
    
    void invariant() const { out << "a::inv" << std::endl; }
    static void static_invariant() { out << "a::static_inv" << std::endl; }

    virtual void f(char ch, boost::contract::virtual_* v = 0) /* override */ {
        boost::contract::guard c = boost::contract::public_function<
                override_f>(v, &a::f, this, ch)
            .precondition([&] {
                out << "a::f::pre" << std::endl;
                BOOST_CONTRACT_ASSERT(ch == 'a');
            })
            .old([&] { out << "a::f::old" << std::endl; })
            .postcondition([&] { out << "a::f::post" << std::endl; })
        ;
        out << "a::f::body" << std::endl;
    }
    BOOST_CONTRACT_OVERRIDE(f)
};

int main() {
    std::ostringstream ok;

    a aa;
    out.str("");
    aa.f('a');
    ok.str(""); ok
        << "c::static_inv" << std::endl
        << "c::inv" << std::endl
        << "i::static_inv" << std::endl
        << "i::inv" << std::endl
        << "e::static_inv" << std::endl
        << "e::inv" << std::endl
        << "j::static_inv" << std::endl
        << "j::inv" << std::endl
        << "h::static_inv" << std::endl
        << "h::inv" << std::endl
        << "a::static_inv" << std::endl
        << "a::inv" << std::endl

        << "c::f::pre" << std::endl
        << "i::f::pre" << std::endl
        << "e::f::pre" << std::endl
        << "j::f::pre" << std::endl
        << "h::f::pre" << std::endl
        << "a::f::pre" << std::endl
        
        << "c::f::old" << std::endl
        << "i::f::old" << std::endl
        << "e::f::old" << std::endl
        << "j::f::old" << std::endl
        << "h::f::old" << std::endl
        << "a::f::old" << std::endl

        << "a::f::body" << std::endl
        
        << "c::static_inv" << std::endl
        << "c::inv" << std::endl
        << "i::static_inv" << std::endl
        << "i::inv" << std::endl
        << "e::static_inv" << std::endl
        << "e::inv" << std::endl
        << "j::static_inv" << std::endl
        << "j::inv" << std::endl
        << "h::static_inv" << std::endl
        << "h::inv" << std::endl
        << "a::static_inv" << std::endl
        << "a::inv" << std::endl
        
        << "c::f::old" << std::endl
        << "c::f::post" << std::endl
        << "i::f::old" << std::endl
        << "i::f::post" << std::endl
        << "e::f::old" << std::endl
        << "e::f::post" << std::endl
        << "j::f::old" << std::endl
        << "j::f::post" << std::endl
        << "h::f::old" << std::endl
        << "h::f::post" << std::endl
        // No old call here because not a base object.
        << "a::f::post" << std::endl
    ;
    BOOST_TEST(out.eq(ok.str()));

    c cc;
    out.str("");
    cc.f('c');
    ok.str(""); ok
        << "c::static_inv" << std::endl
        << "c::inv" << std::endl
        << "c::f::pre" << std::endl
        << "c::f::old" << std::endl
        << "c::f::body" << std::endl
        << "c::static_inv" << std::endl
        << "c::inv" << std::endl
        // No old call here because not a base object.
        << "c::f::post" << std::endl
    ;
    BOOST_TEST(out.eq(ok.str()));
    
    d dd;
    out.str("");
    dd.f('i'); // d's f inherited from i.
    ok.str(""); ok
        << "i::static_inv" << std::endl
        << "i::inv" << std::endl
        << "i::f::pre" << std::endl
        << "i::f::old" << std::endl
        << "i::f::body" << std::endl
        << "i::static_inv" << std::endl
        << "i::inv" << std::endl
        // No old call here because not a base object.
        << "i::f::post" << std::endl
    ;
    BOOST_TEST(out.eq(ok.str()));

    e ee;
    out.str("");
    ee.f('e');
    ok.str(""); ok
        << "i::static_inv" << std::endl
        << "i::inv" << std::endl
        << "e::static_inv" << std::endl
        << "e::inv" << std::endl

        << "i::f::pre" << std::endl
        << "e::f::pre" << std::endl
        
        << "i::f::old" << std::endl
        << "e::f::old" << std::endl
        
        << "e::f::body" << std::endl
        
        << "i::static_inv" << std::endl
        << "i::inv" << std::endl
        << "e::static_inv" << std::endl
        << "e::inv" << std::endl
        
        << "i::f::old" << std::endl
        << "i::f::post" << std::endl
        // No old call here because not a base object.
        << "e::f::post" << std::endl
    ;
    BOOST_TEST(out.eq(ok.str()));

    i ii;
    out.str("");
    ii.f('i');
    ok.str(""); ok
        << "i::static_inv" << std::endl
        << "i::inv" << std::endl
        << "i::f::pre" << std::endl
        << "i::f::old" << std::endl
        << "i::f::body" << std::endl
        << "i::static_inv" << std::endl
        << "i::inv" << std::endl
        // No old call here because not a base object.
        << "i::f::post" << std::endl
    ;
    BOOST_TEST(out.eq(ok.str()));

    h hh;
    out.str("");
    hh.f('h');
    ok.str(""); ok
        << "j::static_inv" << std::endl
        << "j::inv" << std::endl
        << "h::static_inv" << std::endl
        << "h::inv" << std::endl
        
        << "j::f::pre" << std::endl
        << "h::f::pre" << std::endl
        
        << "j::f::old" << std::endl
        << "h::f::old" << std::endl
        
        << "h::f::body" << std::endl
        
        << "j::static_inv" << std::endl
        << "j::inv" << std::endl
        << "h::static_inv" << std::endl
        << "h::inv" << std::endl
        
        << "j::f::old" << std::endl
        << "j::f::post" << std::endl
        // No old call here because not a base object.
        << "h::f::post" << std::endl
    ;
    BOOST_TEST(out.eq(ok.str()));

    j jj;
    out.str("");
    jj.f('j');
    ok.str(""); ok
        << "j::static_inv" << std::endl
        << "j::inv" << std::endl
        << "j::f::pre" << std::endl
        << "j::f::old" << std::endl
        << "j::f::body" << std::endl
        << "j::static_inv" << std::endl
        << "j::inv" << std::endl
        // No old call here because not a base object.
        << "j::f::post" << std::endl
    ;
    BOOST_TEST(out.eq(ok.str()));

    return boost::report_errors();
}

