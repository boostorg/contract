
// Test base and derived classes mixing boost::optional and non- result types.

#include "../aux_/oteststream.hpp"
#include "../aux_/counter.hpp"
#include <boost/contract/base_types.hpp>
#include <boost/contract/public_function.hpp>
#include <boost/contract/override.hpp>
#include <boost/contract/guard.hpp>
#include <boost/contract/assert.hpp>
#include <boost/optional.hpp>
#include <boost/detail/lightweight_test.hpp>
#include <boost/config.hpp>
#include <sstream>
#include <cassert>

boost::contract::aux::test::oteststream out;

struct ch_tag;
typedef boost::contract::aux::test::counter<ch_tag, char> ch_type;

#ifdef BOOST_CONTRACT_AUX_TEST_ref // Test with result types by reference.
#   define BOOST_CONTRACT_AUX_TEST_ch_type ch_type&
#   define BOOST_CONTRACT_AUX_TEST_ch_init = ch_init
ch_type ch_init;
#else // Test with result types by value.
#   define BOOST_CONTRACT_AUX_TEST_ch_type ch_type
#   define BOOST_CONTRACT_AUX_TEST_ch_init /* nothing */
#endif

bool tested_d_copies = false;
struct d {
    static void static_invariant() { out << "d::static_inv" << std::endl; }
    void invariant() const { out << "d::inv" << std::endl; }
    
    virtual BOOST_CONTRACT_AUX_TEST_ch_type f(
            ch_type& ch, boost::contract::virtual_* v = 0) {
        unsigned const old_ch_copies = ch_type::copies();
        boost::optional<BOOST_CONTRACT_AUX_TEST_ch_type> result;
        boost::contract::guard c = boost::contract::public_function(
                v, result, this)
            .precondition([&] {
                out << "d::f::pre" << std::endl;
                BOOST_CONTRACT_ASSERT(ch.value == 'd');
            })
            .old([&] { out << "d::f::old" << std::endl; })
            .postcondition([&] (boost::optional<ch_type const&> const& result) {
                out << "d::f::post" << std::endl;
                BOOST_CONTRACT_ASSERT(result->value == ch.value);
            })
        ;
        BOOST_TEST_EQ(ch_type::copies(), old_ch_copies);
        tested_d_copies = true;

        out << "d::f::body" << std::endl;
        return *(result = ch);
    }
};

bool tested_c_copies = false;
struct c
    #define BASES public d
    : BASES
{
    typedef BOOST_CONTRACT_BASE_TYPES(BASES) base_types;
    #undef BASES

    static void static_invariant() { out << "c::static_inv" << std::endl; }
    void invariant() const { out << "c::inv" << std::endl; }
    
    virtual BOOST_CONTRACT_AUX_TEST_ch_type f(
            ch_type& ch, boost::contract::virtual_* v = 0) /* override */ {
        unsigned const old_ch_copies = ch_type::copies();
        boost::optional<BOOST_CONTRACT_AUX_TEST_ch_type> result;
        boost::contract::guard c = boost::contract::public_function<override_f>(
                v, result, &c::f, this, ch)
            .precondition([&] {
                out << "c::f::pre" << std::endl;
                BOOST_CONTRACT_ASSERT(ch.value == 'c');
            })
            .old([&] { out << "c::f::old" << std::endl; })
            .postcondition([&] (boost::optional<ch_type const&> const& result) {
                out << "c::f::post" << std::endl;
                BOOST_CONTRACT_ASSERT(result->value == ch.value);
            })
        ;
        BOOST_TEST_EQ(ch_type::copies(), old_ch_copies);
        tested_c_copies = true;

        out << "c::f::body" << std::endl;
        return *(result = ch);
    }
    BOOST_CONTRACT_OVERRIDE(f)
};

bool tested_b_copies = false;
struct b
    #define BASES public c
    : BASES
{
    typedef BOOST_CONTRACT_BASE_TYPES(BASES) base_types;
    #undef BASES
    
    static void static_invariant() { out << "b::static_inv" << std::endl; }
    void invariant() const { out << "b::inv" << std::endl; }

    virtual BOOST_CONTRACT_AUX_TEST_ch_type f(
            ch_type& ch, boost::contract::virtual_* v = 0) /* override */ {
        unsigned const old_ch_copies = ch_type::copies();
        BOOST_CONTRACT_AUX_TEST_ch_type result BOOST_CONTRACT_AUX_TEST_ch_init;
        boost::contract::guard c = boost::contract::public_function<override_f>(
                v, result, &b::f, this, ch)
            .precondition([&] {
                out << "b::f::pre" << std::endl;
                BOOST_CONTRACT_ASSERT(ch.value == 'b');
            })
            .old([&] { out << "b::f::old" << std::endl; })
            .postcondition([&] (ch_type const& result) {
                out << "b::f::post" << std::endl; 
                BOOST_CONTRACT_ASSERT(result.value == ch.value);
            })
        ;
        BOOST_TEST_EQ(ch_type::copies(), old_ch_copies);
        tested_b_copies = true;

        out << "b::f::body" << std::endl;
        return result = ch;
    }
    BOOST_CONTRACT_OVERRIDE(f)
};

bool tested_a_copies = false;
struct a
    #define BASES public b
    : BASES
{
    typedef BOOST_CONTRACT_BASE_TYPES(BASES) base_types;
    #undef BASES

    static void static_invariant() { out << "a::static_inv" << std::endl; }
    void invariant() const { out << "a::inv" << std::endl; }

    virtual BOOST_CONTRACT_AUX_TEST_ch_type f(
            ch_type& ch, boost::contract::virtual_* v = 0) /* override */ {
        unsigned const old_ch_copies = ch_type::copies();
        boost::optional<BOOST_CONTRACT_AUX_TEST_ch_type> result;
        boost::contract::guard c = boost::contract::public_function<override_f>(
                v, result, &a::f, this, ch)
            .precondition([&] {
                out << "a::f::pre" << std::endl;
                BOOST_CONTRACT_ASSERT(ch.value == 'a');
            })
            .old([&] { out << "a::f::old" << std::endl; })
            .postcondition([&] (boost::optional<ch_type const&> const& result) {
                out << "a::f::post" << std::endl;
                BOOST_CONTRACT_ASSERT(result->value == ch.value);
            })
        ;
        BOOST_TEST_EQ(ch_type::copies(), old_ch_copies);
        tested_a_copies = true;

        out << "a::f::body" << std::endl;
        return *(result = ch);
    }
    BOOST_CONTRACT_OVERRIDE(f)
};

bool tested_e_copies = false;
struct e
    #define BASES public b
    : BASES
{
    typedef BOOST_CONTRACT_BASE_TYPES(BASES) base_types;
    #undef BASES
    
    static void static_invariant() { out << "e::static_inv" << std::endl; }
    void invariant() const { out << "e::inv" << std::endl; }

    virtual BOOST_CONTRACT_AUX_TEST_ch_type f(
            ch_type& ch, boost::contract::virtual_* v = 0) /* override */ {
        unsigned const old_ch_copies = ch_type::copies();
        BOOST_CONTRACT_AUX_TEST_ch_type result BOOST_CONTRACT_AUX_TEST_ch_init;
        boost::contract::guard c = boost::contract::public_function<override_f>(
                v, result, &e::f, this, ch)
            .precondition([&] {
                out << "e::f::pre" << std::endl;
                BOOST_CONTRACT_ASSERT(ch.value == 'e');
            })
            .old([&] { out << "e::f::old" << std::endl; })
            .postcondition([&] (ch_type const& result) {
                out << "e::f::post" << std::endl; 
                BOOST_CONTRACT_ASSERT(result.value == ch.value);
            })
        ;
        BOOST_TEST_EQ(ch_type::copies(), old_ch_copies);
        tested_e_copies = true;

        out << "e::f::body" << std::endl;
        return result = ch;
    }
    BOOST_CONTRACT_OVERRIDE(f)
};

int main() {
    std::ostringstream ok;
    ch_type ch;
#ifdef BOOST_CONTRACT_AUX_TEST_ref
    ch_init.value = '\0';
#endif

    // Test optional in overriding a::f and non-optional in overridden b::f.
    a aa;
    ch.value = 'a';
    out.str("");
    aa.f(ch);
    ok.str(""); ok
        << "d::static_inv" << std::endl
        << "d::inv" << std::endl
        << "c::static_inv" << std::endl
        << "c::inv" << std::endl
        << "b::static_inv" << std::endl
        << "b::inv" << std::endl
        << "a::static_inv" << std::endl
        << "a::inv" << std::endl

        << "d::f::pre" << std::endl
        << "c::f::pre" << std::endl
        << "b::f::pre" << std::endl
        << "a::f::pre" << std::endl
        
        << "d::f::old" << std::endl
        << "c::f::old" << std::endl
        << "b::f::old" << std::endl
        << "a::f::old" << std::endl
        
        << "a::f::body" << std::endl
        
        << "d::static_inv" << std::endl
        << "d::inv" << std::endl
        << "c::static_inv" << std::endl
        << "c::inv" << std::endl
        << "b::static_inv" << std::endl
        << "b::inv" << std::endl
        << "a::static_inv" << std::endl
        << "a::inv" << std::endl
        
        << "d::f::old" << std::endl
        << "d::f::post" << std::endl
        << "c::f::old" << std::endl
        << "c::f::post" << std::endl
        << "b::f::old" << std::endl
        << "b::f::post" << std::endl
        // No old call here because not a base object.
        << "a::f::post" << std::endl
    ;
    BOOST_TEST(out.eq(ok.str()));
    BOOST_TEST(tested_a_copies);

    // Test non-optional in overriding b::f and optional in overridden c::f.
    b bb;
    ch.value = 'b';
    out.str("");
    bb.f(ch);
    ok.str(""); ok
        << "d::static_inv" << std::endl
        << "d::inv" << std::endl
        << "c::static_inv" << std::endl
        << "c::inv" << std::endl
        << "b::static_inv" << std::endl
        << "b::inv" << std::endl

        << "d::f::pre" << std::endl
        << "c::f::pre" << std::endl
        << "b::f::pre" << std::endl
        
        << "d::f::old" << std::endl
        << "c::f::old" << std::endl
        << "b::f::old" << std::endl
        
        << "b::f::body" << std::endl
        
        << "d::static_inv" << std::endl
        << "d::inv" << std::endl
        << "c::static_inv" << std::endl
        << "c::inv" << std::endl
        << "b::static_inv" << std::endl
        << "b::inv" << std::endl
        
        << "d::f::old" << std::endl
        << "d::f::post" << std::endl
        << "c::f::old" << std::endl
        << "c::f::post" << std::endl
        // No old call here because not a base object.
        << "b::f::post" << std::endl
    ;
    BOOST_TEST(out.eq(ok.str()));
    BOOST_TEST(tested_b_copies);
    
    // Test optional in both overriding c::f and overridden d::f.
    c cc;
    ch.value = 'c';
    out.str("");
    cc.f(ch);
    ok.str(""); ok
        << "d::static_inv" << std::endl
        << "d::inv" << std::endl
        << "c::static_inv" << std::endl
        << "c::inv" << std::endl
        
        << "d::f::pre" << std::endl
        << "c::f::pre" << std::endl
        
        << "d::f::old" << std::endl
        << "c::f::old" << std::endl
        
        << "c::f::body" << std::endl
        
        << "d::static_inv" << std::endl
        << "d::inv" << std::endl
        << "c::static_inv" << std::endl
        << "c::inv" << std::endl
        
        << "d::f::old" << std::endl
        << "d::f::post" << std::endl
        // No old call here because not a base object.
        << "c::f::post" << std::endl
    ;
    BOOST_TEST(out.eq(ok.str()));
    BOOST_TEST(tested_c_copies);
    
    // Test non-optional in both overriding c::f and overridden d::f.
    e ee;
    ch.value = 'e';
    out.str("");
    ee.f(ch);
    ok.str(""); ok
        << "d::static_inv" << std::endl
        << "d::inv" << std::endl
        << "c::static_inv" << std::endl
        << "c::inv" << std::endl
        << "b::static_inv" << std::endl
        << "b::inv" << std::endl
        << "e::static_inv" << std::endl
        << "e::inv" << std::endl

        << "d::f::pre" << std::endl
        << "c::f::pre" << std::endl
        << "b::f::pre" << std::endl
        << "e::f::pre" << std::endl

        << "d::f::old" << std::endl
        << "c::f::old" << std::endl
        << "b::f::old" << std::endl
        << "e::f::old" << std::endl

        << "e::f::body" << std::endl
        
        << "d::static_inv" << std::endl
        << "d::inv" << std::endl
        << "c::static_inv" << std::endl
        << "c::inv" << std::endl
        << "b::static_inv" << std::endl
        << "b::inv" << std::endl
        << "e::static_inv" << std::endl
        << "e::inv" << std::endl
        
        << "d::f::old" << std::endl
        << "d::f::post" << std::endl
        << "c::f::old" << std::endl
        << "c::f::post" << std::endl
        << "b::f::old" << std::endl
        << "b::f::post" << std::endl
        // No old call here because not a base object.
        << "e::f::post" << std::endl
    ;
    BOOST_TEST(out.eq(ok.str()));
    BOOST_TEST(tested_e_copies);

    return boost::report_errors();
}

#undef BOOST_CONTRACT_AUX_TEST_ref
#undef BOOST_CONTRACT_AUX_TEST_ch_type
#undef BOOST_CONTRACT_AUX_TEST_ch_init

