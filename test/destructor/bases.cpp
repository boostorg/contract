
// Test destructor subcontracting.

#include "../aux_/oteststream.hpp"
#include "../aux_/counter.hpp"
#include <boost/contract/destructor.hpp>
#include <boost/contract/base_types.hpp>
#include <boost/contract/assert.hpp>
#include <boost/contract/old.hpp>
#include <boost/contract/guard.hpp>
#include <boost/detail/lightweight_test.hpp>
#include <sstream>

boost::contract::aux::test::oteststream out;

template<char Id>
struct t {
    void invariant() const {
        out << Id << "::inv" << std::endl;
        BOOST_CONTRACT_ASSERT(k_ < 0);
    }
    static void static_invariant() {
        out << Id << "::static_inv" << std::endl;
        BOOST_CONTRACT_ASSERT(l.value >= 0);
    }

    struct l_tag;
    typedef boost::contract::aux::test::counter<l_tag, int> l_type;
    static l_type l;

    explicit t() : k_(-1) { ++l.value; }

    virtual ~t() {
        boost::contract::old_ptr<l_type> old_l;
        boost::contract::guard c = boost::contract::destructor(this)
            .old([&] {
                out << Id << "::dtor::old" << std::endl;
                old_l = BOOST_CONTRACT_OLDOF(l_type::eval(l));
            })
            .postcondition([&old_l] {
                out << Id << "::dtor::post" << std::endl;
                BOOST_CONTRACT_ASSERT(t<Id>::l.value == old_l->value - 1);
            })
        ;
        out << Id << "::dtor::body" << std::endl;
        --l.value;
    }

private:
    int k_;
};
template<char Id> typename t<Id>::l_type t<Id>::l;

// Test deep inheritance (2 vertical levels), multiple inheritance (4
// horizontal levels), and that all public/protected/private part of
// subcontracting for destructors (not just public, because all access levels
// are part of C++ object destruction mechanism).
struct c
    #define BASES public t<'d'>, protected t<'p'>, private t<'q'>, public t<'e'>
    : BASES
{
    typedef BOOST_CONTRACT_BASE_TYPES(BASES) base_types;
    #undef BASES

    void invariant() const {
        out << "c::inv" << std::endl;
        BOOST_CONTRACT_ASSERT(j_ < 0);
    }
    static void static_invariant() {
        out << "c::static_inv" << std::endl;
        BOOST_CONTRACT_ASSERT(m.value >= 0);
    }
    
    struct m_tag;
    typedef boost::contract::aux::test::counter<m_tag, int> m_type;
    static m_type m;

    explicit c() : j_(-1) { ++m.value; }

    virtual ~c() {
        boost::contract::old_ptr<m_type> old_m =
                BOOST_CONTRACT_OLDOF(m_type::eval(m));
        boost::contract::guard c = boost::contract::destructor(this)
            .old([&] {
                out << "c::dtor::old" << std::endl;
                // Test old-of assignment above instead.
            })
            .postcondition([&old_m] {
                out << "c::dtor::post" << std::endl;
                BOOST_CONTRACT_ASSERT(c::m.value == old_m->value - 1);
            })
        ;
        out << "c::dtor::body" << std::endl;
        --m.value;
    }

private:
    int j_;
};
c::m_type c::m;

// Test not (fully) contracted base is not part of destructor subcontracting.
struct b {
    void invariant() const { out << "b::inv" << std::endl; }
    static void static_invariant() { out << "b::static_inv" << std::endl; }

    explicit b() {}
    virtual ~b() {} // No contract.
};

// Test destructor with both non-contracted and contracted bases.
struct a
    #define BASES public b, public c
    : BASES
{
    typedef BOOST_CONTRACT_BASE_TYPES(BASES) base_types;
    #undef BASES

    void invariant() const {
        out << "a::inv" << std::endl;
        BOOST_CONTRACT_ASSERT(i_ < 0);
    }
    static void static_invariant() {
        out << "a::static_inv" << std::endl;
        BOOST_CONTRACT_ASSERT(n.value >= 0);
    }
    
    struct n_tag;
    typedef boost::contract::aux::test::counter<n_tag, int> n_type;
    static n_type n;

    explicit a() : i_(-1) { ++n.value; }

    virtual ~a() {
        boost::contract::old_ptr<n_type> old_n;
        boost::contract::guard c = boost::contract::destructor(this)
            .old([&] {
                out << "a::dtor::old" << std::endl;
                old_n = BOOST_CONTRACT_OLDOF(n_type::eval(n));
            })
            .postcondition([&old_n] {
                out << "a::dtor::post" << std::endl;
                BOOST_CONTRACT_ASSERT(a::n.value == old_n->value - 1);
            })
        ;
        out << "a::dtor::body" << std::endl;
        --n.value;
    }

private:
    int i_;
};
a::n_type a::n;

int main() {
    std::ostringstream ok;

    {
        a aa;
        out.str("");
    } // Call aa's destructor.
    ok.str(""); ok
        << "a::static_inv" << std::endl
        << "a::inv" << std::endl
        << "a::dtor::old" << std::endl
        << "a::dtor::body" << std::endl
        // Test static inv, but not const inv, checked after destructor body.
        << "a::static_inv" << std::endl
        << "a::dtor::post" << std::endl

        << "c::static_inv" << std::endl
        << "c::inv" << std::endl
        << "c::dtor::old" << std::endl
        << "c::dtor::body" << std::endl
        << "c::static_inv" << std::endl
        << "c::dtor::post" << std::endl
        
        << "e::static_inv" << std::endl
        << "e::inv" << std::endl
        << "e::dtor::old" << std::endl
        << "e::dtor::body" << std::endl
        << "e::static_inv" << std::endl
        << "e::dtor::post" << std::endl
       
        // Test check also private bases (because part of C++ destruction).
        << "q::static_inv" << std::endl
        << "q::inv" << std::endl
        << "q::dtor::old" << std::endl
        << "q::dtor::body" << std::endl
        << "q::static_inv" << std::endl
        << "q::dtor::post" << std::endl
        
        // Test check also protected bases (because part of C++ destruction).
        << "p::static_inv" << std::endl
        << "p::inv" << std::endl
        << "p::dtor::old" << std::endl
        << "p::dtor::body" << std::endl
        << "p::static_inv" << std::endl
        << "p::dtor::post" << std::endl
        
        << "d::static_inv" << std::endl
        << "d::inv" << std::endl
        << "d::dtor::old" << std::endl
        << "d::dtor::body" << std::endl
        << "d::static_inv" << std::endl
        << "d::dtor::post" << std::endl
    ;
    BOOST_TEST(out.eq(ok.str()));

    // Following destroy only copies (actual objects are static data members).

    BOOST_TEST_EQ(a::n_type::copies(), 1);
    BOOST_TEST_EQ(a::n_type::evals(), 1);
    BOOST_TEST_EQ(a::n_type::copies(), a::n_type::dtors()); // No leak.
    
    BOOST_TEST_EQ(c::m_type::copies(), 1);
    BOOST_TEST_EQ(c::m_type::evals(), 1);
    BOOST_TEST_EQ(c::m_type::copies(), c::m_type::dtors()); // No leak.
    
    BOOST_TEST_EQ(t<'d'>::l_type::copies(), 1);
    BOOST_TEST_EQ(t<'d'>::l_type::evals(), 1);
    BOOST_TEST_EQ(t<'d'>::l_type::copies(), t<'d'>::l_type::dtors()); // No leak
    
    BOOST_TEST_EQ(t<'p'>::l_type::copies(), 1);
    BOOST_TEST_EQ(t<'p'>::l_type::evals(), 1);
    BOOST_TEST_EQ(t<'p'>::l_type::copies(), t<'p'>::l_type::dtors()); // No leak
    
    BOOST_TEST_EQ(t<'q'>::l_type::copies(), 1);
    BOOST_TEST_EQ(t<'q'>::l_type::evals(), 1);
    BOOST_TEST_EQ(t<'q'>::l_type::copies(), t<'q'>::l_type::dtors()); // No leak
    
    BOOST_TEST_EQ(t<'e'>::l_type::copies(), 1);
    BOOST_TEST_EQ(t<'e'>::l_type::evals(), 1);
    BOOST_TEST_EQ(t<'e'>::l_type::copies(), t<'e'>::l_type::dtors()); // No leak

    return boost::report_errors();
}

