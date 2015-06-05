
// Test constructor subcontracting.

#include "../aux_/oteststream.hpp"
#include "../aux_/cpcnt.hpp"
#include <boost/contract/constructor.hpp>
#include <boost/contract/base_types.hpp>
#include <boost/contract/assert.hpp>
#include <boost/contract/oldof.hpp>
#include <boost/contract/guard.hpp>
#include <boost/bind.hpp>
#include <boost/ref.hpp>
#include <boost/detail/lightweight_test.hpp>
#include <sstream>

boost::contract::aux::test::oteststream out;

template<char Id>
struct t
    #define BASES private boost::contract::constructor_precondition<t<Id> >
    : BASES
{
    typedef BOOST_CONTRACT_BASE_TYPES(BASES) base_types;
    #undef BASES

    void invariant() const {
        out << Id << "::inv" << std::endl;
        BOOST_CONTRACT_ASSERT(k_ < 0);
    }
    static void static_invariant() {
        out << Id << "::static_inv" << std::endl;
        BOOST_CONTRACT_ASSERT(l.value >= 0);
    }

    struct l_tag; typedef boost::contract::aux::test::cpcnt<l_tag, int> l_type;
    static l_type l;

    struct z_tag; typedef boost::contract::aux::test::cpcnt<z_tag, int> z_type;

    // MSVC 2010 errors on lambdas in template member initializations...
    static void constructor_precondition(z_type const& z) {
        out << Id << "::ctor::pre" << std::endl;
        BOOST_CONTRACT_ASSERT(z.value < 0);
    }
    explicit t(z_type& z) :
        boost::contract::constructor_precondition<t<Id> >(
                boost::bind(&t::constructor_precondition, boost::cref(z)))
    {
        boost::shared_ptr<z_type const> old_z =
                BOOST_CONTRACT_OLDOF(z_type::eval(z));
        boost::shared_ptr<l_type const> old_l =
                BOOST_CONTRACT_OLDOF(l_type::eval(l));
        boost::contract::guard c = boost::contract::constructor(this)
            .postcondition([&] {
                out << Id << "::ctor::post" << std::endl;
                BOOST_CONTRACT_ASSERT(k_ == old_z->value);
                BOOST_CONTRACT_ASSERT(z.value == l.value);
                BOOST_CONTRACT_ASSERT(l.value == old_l->value + 1);
            })
        ;
        out << Id << "::ctor::body" << std::endl;
        k_ = z.value;
        z.value = ++l.value;
    }

    virtual ~t() { --l.value; }

private:
    int k_;
};
template<char Id> typename t<Id>::l_type t<Id>::l;

// Test deep inheritance (2 vertical levels), multiple inheritance (4
// horizontal levels), and that all public/protected/private part of
// subcontracting for constructors (not just public, because all access levels
// are part of C++ object construction mechanism).
struct c
    #define BASES private boost::contract::constructor_precondition<c>, \
            public t<'d'>, protected t<'p'>, private t<'q'>, public t<'e'>
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
    
    struct m_tag; typedef boost::contract::aux::test::cpcnt<m_tag, int> m_type;
    static m_type m;

    struct y_tag; typedef boost::contract::aux::test::cpcnt<y_tag, int> y_type;

    explicit c(y_type& y, t<'d'>::z_type& dz, t<'p'>::z_type& pz,
            t<'q'>::z_type& qz, t<'e'>::z_type& ez) :
        boost::contract::constructor_precondition<c>([&] {
            out << "c::ctor::pre" << std::endl;
            BOOST_CONTRACT_ASSERT(y.value < 0);
        }),
        t<'d'>(dz), t<'p'>(pz), t<'q'>(qz), t<'e'>(ez)
    {
        boost::shared_ptr<y_type const> old_y =
                BOOST_CONTRACT_OLDOF(y_type::eval(y));
        boost::shared_ptr<m_type const> old_m =
                BOOST_CONTRACT_OLDOF(m_type::eval(m));
        boost::contract::guard c = boost::contract::constructor(this)
            .postcondition([&] {
                out << "c::ctor::post" << std::endl;
                BOOST_CONTRACT_ASSERT(j_ == old_y->value);
                BOOST_CONTRACT_ASSERT(y.value == m.value);
                BOOST_CONTRACT_ASSERT(m.value == old_m->value + 1);
            })
        ;
        out << "c::ctor::body" << std::endl;
        j_ = y.value;
        y.value = ++m.value;
    }

    virtual ~c() { --m.value; }

private:
    int j_;
};
c::m_type c::m;

// Test not (fully) contracted base is not part of constructor subcontracting.
struct b
    #define BASES private boost::contract::constructor_precondition<b>
    : BASES
{
    typedef BOOST_CONTRACT_BASE_TYPES(BASES) base_types;
    #undef BASES

    void invariant() const { out << "b::inv" << std::endl; }
    static void static_invariant() { out << "b::static_inv" << std::endl; }

    explicit b() {} // No contract.
    virtual ~b() {}
};

// Test constructor with both non-contracted and contracted bases.
struct a
    #define BASES private boost::contract::constructor_precondition<a>, \
            public b, public c
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
    
    struct n_tag; typedef boost::contract::aux::test::cpcnt<n_tag, int> n_type;
    static n_type n;

    struct x_tag; typedef boost::contract::aux::test::cpcnt<x_tag, int> x_type;

    explicit a(x_type& x, c::y_type& y, t<'d'>::z_type& dz,
            t<'p'>::z_type& pz, t<'q'>::z_type& qz, t<'e'>::z_type& ez) :
        boost::contract::constructor_precondition<a>([&] {
            out << "a::ctor::pre" << std::endl;
            BOOST_CONTRACT_ASSERT(x.value < 0);
        }),
        b(), c(y, dz, pz, qz, ez)
    {
        boost::shared_ptr<x_type const> old_x =
                BOOST_CONTRACT_OLDOF(x_type::eval(x));
        boost::shared_ptr<n_type const> old_n =
                BOOST_CONTRACT_OLDOF(n_type::eval(n));
        boost::contract::guard c = boost::contract::constructor(this)
            .postcondition([&] {
                out << "a::ctor::post" << std::endl;
                BOOST_CONTRACT_ASSERT(i_ == old_x->value);
                BOOST_CONTRACT_ASSERT(x.value == n.value);
                BOOST_CONTRACT_ASSERT(n.value == old_n->value + 1);
            })
        ;
        out << "a::ctor::body" << std::endl;
        i_ = x.value;
        x.value = ++n.value;
    }

    virtual ~a() { --n.value; }

private:
    int i_;
};
a::n_type a::n;

int main() {
    std::ostringstream ok;

    t<'e'>::z_type ez; ez.value = -5;
    t<'q'>::z_type qz; qz.value = -5;
    t<'p'>::z_type pz; pz.value = -4;
    t<'d'>::z_type dz; dz.value = -3;
    c::y_type y; y.value = -2;
    a::x_type x; x.value = -1;

    out.str("");
    a aa(x, y, dz, pz, qz, ez);
    ok.str(""); ok
        // Test all constructor pre checked first.
        << "a::ctor::pre" << std::endl

        << "c::ctor::pre" << std::endl

        // Test static inv, but not const inv, checked before constructor body.
        << "d::ctor::pre" << std::endl
        << "d::static_inv" << std::endl
        << "d::ctor::body" << std::endl
        << "d::static_inv" << std::endl
        << "d::inv" << std::endl
        << "d::ctor::post" << std::endl
        
        // Test check also protected bases (because part of C++ construction).
        << "p::ctor::pre" << std::endl
        << "p::static_inv" << std::endl
        << "p::ctor::body" << std::endl
        << "p::static_inv" << std::endl
        << "p::inv" << std::endl
        << "p::ctor::post" << std::endl
        
        // Test check also private bases (because part of C++ construction).
        << "q::ctor::pre" << std::endl
        << "q::static_inv" << std::endl
        << "q::ctor::body" << std::endl
        << "q::static_inv" << std::endl
        << "q::inv" << std::endl
        << "q::ctor::post" << std::endl

        << "e::ctor::pre" << std::endl
        << "e::static_inv" << std::endl
        << "e::ctor::body" << std::endl
        << "e::static_inv" << std::endl
        << "e::inv" << std::endl
        << "e::ctor::post" << std::endl

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
    BOOST_TEST(out.eq(ok.str()));

    BOOST_TEST_EQ(x.copies(), 1); BOOST_TEST_EQ(x.evals(), 1);
    BOOST_TEST_EQ(y.copies(), 1); BOOST_TEST_EQ(y.evals(), 1);
    BOOST_TEST_EQ(dz.copies(), 1); BOOST_TEST_EQ(dz.evals(), 1);
    BOOST_TEST_EQ(pz.copies(), 1); BOOST_TEST_EQ(pz.evals(), 1);
    BOOST_TEST_EQ(qz.copies(), 1); BOOST_TEST_EQ(qz.evals(), 1);
    BOOST_TEST_EQ(ez.copies(), 1); BOOST_TEST_EQ(ez.evals(), 1);

    BOOST_TEST_EQ(a::n.copies(), 1); BOOST_TEST_EQ(a::n.evals(), 1);
    BOOST_TEST_EQ(c::m.copies(), 1); BOOST_TEST_EQ(c::m.evals(), 1);
    BOOST_TEST_EQ(t<'d'>::l.copies(), 1); BOOST_TEST_EQ(t<'d'>::l.evals(), 1);
    BOOST_TEST_EQ(t<'p'>::l.copies(), 1); BOOST_TEST_EQ(t<'p'>::l.evals(), 1);
    BOOST_TEST_EQ(t<'q'>::l.copies(), 1); BOOST_TEST_EQ(t<'q'>::l.evals(), 1);
    BOOST_TEST_EQ(t<'e'>::l.copies(), 1); BOOST_TEST_EQ(t<'e'>::l.evals(), 1);

    return boost::report_errors();
}

