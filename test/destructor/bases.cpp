
// Test destructor subcontracting.

#include "../aux_/oteststream.hpp"
#include "../aux_/cpcnt.hpp"
#include <boost/contract/destructor.hpp>
#include <boost/contract/base_types.hpp>
#include <boost/contract/assert.hpp>
#include <boost/contract/oldof.hpp>
#include <boost/contract/var.hpp>
#include <boost/detail/lightweight_test.hpp>
#include <sstream>

boost::contract::aux::test::oteststream out;

template<char Id>
struct t {
    void invariant() const {
        out << Id << "::inv" << std::endl;
        BOOST_CONTRACT_ASSERT(i_ < 0);
    }
    static void static_invariant() {
        out << Id << "::static_inv" << std::endl;
        BOOST_CONTRACT_ASSERT(n.value >= 0);
    }

    struct n_tag; typedef boost::contract::aux::test::cpcnt<n_tag, int> n_cnt;
    static n_cnt n;

    explicit t() : i_(-1) { ++n.value; }

    virtual ~t() {
        boost::shared_ptr<n_cnt const> old_n =
                BOOST_CONTRACT_OLDOF(n_cnt::eval(n));
        boost::contract::var contract = boost::contract::destructor(this)
            .postcondition([old_n] {
                out << Id << "::dtor::post" << std::endl;
                BOOST_CONTRACT_ASSERT(t<Id>::n.value == old_n->value - 1);
            })
        ;
        out << Id << "::dtor::body" << std::endl;
        --n.value;
    }

private:
    int i_;
};
template<char Id> typename t<Id>::n_cnt t<Id>::n;

// Test deep inheritance (2 vertical levels), multiple inheritance (4
// horizontal levels), and that all public/protected/private part of
// subcontracting for destructors (not just public, because all access levels
// are part of C++ object destruction mechanism).
struct c
    #define BASES public t<'d'>, protected t<'e'>, private t<'f'>
    : BASES
{
    typedef BOOST_CONTRACT_BASE_TYPES(BASES) base_types;
    #undef BASES

    void invariant() const {
        out << "c::inv" << std::endl;
        BOOST_CONTRACT_ASSERT(i_ < 0);
    }
    static void static_invariant() {
        out << "c::static_inv" << std::endl;
        BOOST_CONTRACT_ASSERT(n.value >= 0);
    }
    
    struct n_tag; typedef boost::contract::aux::test::cpcnt<n_tag, int> n_cnt;
    static n_cnt n;

    explicit c() : i_(-1) { ++n.value; }

    virtual ~c() {
        boost::shared_ptr<n_cnt const> old_n =
                BOOST_CONTRACT_OLDOF(n_cnt::eval(n));
        boost::contract::var contract = boost::contract::destructor(this)
            .postcondition([old_n] {
                out << "c::dtor::post" << std::endl;
                BOOST_CONTRACT_ASSERT(c::n.value == old_n->value - 1);
            })
        ;
        out << "c::dtor::body" << std::endl;
        --n.value;
    }

private:
    int i_;
};
c::n_cnt c::n;

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
    
    struct n_tag; typedef boost::contract::aux::test::cpcnt<n_tag, int> n_cnt;
    static n_cnt n;

    explicit a() : i_(-1) { ++n.value; }

    virtual ~a() {
        boost::shared_ptr<n_cnt const> old_n =
                BOOST_CONTRACT_OLDOF(n_cnt::eval(n));
        boost::contract::var contract = boost::contract::destructor(this)
            .postcondition([old_n] {
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
a::n_cnt a::n;

int main() {
    std::ostringstream ok;

    {
        a aa;
        out.str("");
    } // Call aa's destructor.
    ok.str("");
    ok
        << "a::static_inv" << std::endl
        << "a::inv" << std::endl
        << "a::dtor::body" << std::endl
        // Test static inv, but not const inv, checked after destructor body.
        << "a::static_inv" << std::endl
        << "a::dtor::post" << std::endl

        << "c::static_inv" << std::endl
        << "c::inv" << std::endl
        << "c::dtor::body" << std::endl
        << "c::static_inv" << std::endl
        << "c::dtor::post" << std::endl
        
        << "f::static_inv" << std::endl
        << "f::inv" << std::endl
        << "f::dtor::body" << std::endl
        << "f::static_inv" << std::endl
        << "f::dtor::post" << std::endl
        
        << "e::static_inv" << std::endl
        << "e::inv" << std::endl
        << "e::dtor::body" << std::endl
        << "e::static_inv" << std::endl
        << "e::dtor::post" << std::endl
        
        << "d::static_inv" << std::endl
        << "d::inv" << std::endl
        << "d::dtor::body" << std::endl
        << "d::static_inv" << std::endl
        << "d::dtor::post" << std::endl
    ;
    BOOST_TEST(out.eq(ok.str()));

    BOOST_TEST_EQ(a::n.copies(), 1); BOOST_TEST_EQ(a::n.evals(), 1);
    BOOST_TEST_EQ(c::n.copies(), 1); BOOST_TEST_EQ(c::n.evals(), 1);
    BOOST_TEST_EQ(t<'d'>::n.copies(), 1); BOOST_TEST_EQ(t<'d'>::n.evals(), 1);
    BOOST_TEST_EQ(t<'e'>::n.copies(), 1); BOOST_TEST_EQ(t<'e'>::n.evals(), 1);
    BOOST_TEST_EQ(t<'f'>::n.copies(), 1); BOOST_TEST_EQ(t<'f'>::n.evals(), 1);

    return boost::report_errors();
}

