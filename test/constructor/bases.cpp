
#include "../aux_/oteststream.hpp"
#include "../aux_/old.hpp"
#include <boost/contract/constructor.hpp>
#include <boost/contract/base_types.hpp>
#include <boost/contract/assert.hpp>
#include <boost/contract/oldof.hpp>
#include <boost/contract/scoped.hpp>
#include <boost/bind.hpp>
#include <boost/ref.hpp>
#include <boost/detail/lightweight_test.hpp>
#include <sstream>

// Test constructor subcontracting.

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
        BOOST_CONTRACT_ASSERT(x_ < 0);
    }
    static void static_invariant() {
        out << Id << "::static_inv" << std::endl;
        BOOST_CONTRACT_ASSERT(i_ >= 0);
    }

    struct arg_tag;
    typedef boost::contract::aux::test::old<arg_tag, int> arg_type;

    // MSVC 2010 errors on lambdas in template member initializations...
    static void t_precondition(arg_type const& arg) {
        out << Id << "::ctor::pre" << std::endl;
        BOOST_CONTRACT_ASSERT(arg.value < 0);
    }
    explicit t(arg_type& arg) :
        boost::contract::constructor_precondition<t<Id> >(
                boost::bind(&t::t_precondition, boost::cref(arg)))
    {
        boost::shared_ptr<arg_type const> old_arg =
                BOOST_CONTRACT_OLDOF(arg_type::eval(arg));
        boost::contract::scoped contract = boost::contract::constructor(this)
            .postcondition([&] {
                out << Id << "::ctor::post" << std::endl;
                BOOST_CONTRACT_ASSERT(x_ == old_arg->value);
                BOOST_CONTRACT_ASSERT(arg.value == i_);
            })
        ;
        out << Id << "::ctor::body" << std::endl;
        x_ = arg.value;
        arg.value = ++i_;
    }

    virtual ~t() { --i_; }

private:
    static int i_;
    int x_;
};
template<char Id> int t<Id>::i_ = 0;

// Test deep inheritance (2 vertical levels), multiple inheritance (4
// horizontal levels), and that all public/protected/private part of
// subcontracting for constructors (not just public, because all access levels
// are part of C++ object construction mechanism).
struct c
    #define BASES private boost::contract::constructor_precondition<c>, \
            public t<'d'>, protected t<'e'>, private t<'f'>
    : BASES
{
    typedef BOOST_CONTRACT_BASE_TYPES(BASES) base_types;
    #undef BASES

    void invariant() const {
        out << "c::inv" << std::endl;
        BOOST_CONTRACT_ASSERT(x_ < 0);
    }
    static void static_invariant() {
        out << "c::static_inv" << std::endl;
        BOOST_CONTRACT_ASSERT(i_ >= 0);
    }

    struct arg_tag;
    typedef boost::contract::aux::test::old<arg_tag, int> arg_type;

    explicit c(arg_type& arg, t<'d'>::arg_type& d_arg, t<'e'>::arg_type& e_arg,
            t<'f'>::arg_type& f_arg) :
        boost::contract::constructor_precondition<c>([&] {
            out << "c::ctor::pre" << std::endl;
            BOOST_CONTRACT_ASSERT(arg.value < 0);
        }),
        t<'d'>(d_arg), t<'e'>(e_arg), t<'f'>(f_arg)
    {
        boost::shared_ptr<arg_type const> old_arg =
                BOOST_CONTRACT_OLDOF(arg_type::eval(arg));
        boost::contract::scoped contract = boost::contract::constructor(this)
            .postcondition([&] {
                out << "c::ctor::post" << std::endl;
                BOOST_CONTRACT_ASSERT(x_ == old_arg->value);
                BOOST_CONTRACT_ASSERT(arg.value == i_);
            })
        ;
        out << "c::ctor::body" << std::endl;
        x_ = arg.value;
        arg.value = ++i_;
    }

    virtual ~c() { --i_; }

private:
    static int i_;
    int x_;
};
int c::i_ = 0;

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

// Test both non-contracted and contracted bases.
struct a
    #define BASES private boost::contract::constructor_precondition<a>, \
            public b, public c
    : BASES
{
    typedef BOOST_CONTRACT_BASE_TYPES(BASES) base_types;
    #undef BASES

    void invariant() const {
        out << "a::inv" << std::endl;
        BOOST_CONTRACT_ASSERT(x_ < 0);
    }
    static void static_invariant() {
        out << "a::static_inv" << std::endl;
        BOOST_CONTRACT_ASSERT(i_ >= 0);
    }

    struct arg_tag;
    typedef boost::contract::aux::test::old<arg_tag, int> arg_type;

    explicit a(arg_type& arg, c::arg_type& c_arg, t<'d'>::arg_type& d_arg,
            t<'e'>::arg_type& e_arg, t<'f'>::arg_type& f_arg) :
        boost::contract::constructor_precondition<a>([&] {
            out << "a::ctor::pre" << std::endl;
            BOOST_CONTRACT_ASSERT(arg.value < 0);
        }),
        b(),
        c(c_arg, d_arg, e_arg, f_arg)
    {
        boost::shared_ptr<arg_type const> old_arg =
                BOOST_CONTRACT_OLDOF(arg_type::eval(arg));
        boost::contract::scoped contract = boost::contract::constructor(this)
            .postcondition([&] {
                out << "a::ctor::post" << std::endl;
                BOOST_CONTRACT_ASSERT(x_ == old_arg->value);
                BOOST_CONTRACT_ASSERT(arg.value == i_);
            })
        ;
        out << "a::ctor::body" << std::endl;
        x_ = arg.value;
        arg.value = ++i_;
    }

    virtual ~a() { --i_; }

private:
    static int i_;
    int x_;
};
int a::i_ = 0;

int main() {
    std::ostringstream ok;

    t<'f'>::arg_type f_arg; f_arg.value = -5;
    t<'e'>::arg_type e_arg; e_arg.value = -4;
    t<'d'>::arg_type d_arg; d_arg.value = -3;
    c::arg_type c_arg;      c_arg.value = -2;
    a::arg_type a_arg;      a_arg.value = -1;

    out.str("");
    a aa(a_arg, c_arg, d_arg, e_arg, f_arg);
    ok <<
        // Test all constructor pre checked first.
        "a::ctor::pre" << std::endl <<
        "c::ctor::pre" << std::endl <<
        "d::ctor::pre" << std::endl <<

        // Test static inv, but not const inv, checked before constructor body.
        "d::static_inv" << std::endl <<
        "d::ctor::body" << std::endl <<
        "d::static_inv" << std::endl <<
        "d::inv" << std::endl <<
        "d::ctor::post" << std::endl <<
        
        "e::ctor::pre" << std::endl <<
        "e::static_inv" << std::endl <<
        "e::ctor::body" << std::endl <<
        "e::static_inv" << std::endl <<
        "e::inv" << std::endl <<
        "e::ctor::post" << std::endl <<
        
        "f::ctor::pre" << std::endl <<
        "f::static_inv" << std::endl <<
        "f::ctor::body" << std::endl <<
        "f::static_inv" << std::endl <<
        "f::inv" << std::endl <<
        "f::ctor::post" << std::endl <<
        
        "c::static_inv" << std::endl <<
        "c::ctor::body" << std::endl <<
        "c::static_inv" << std::endl <<
        "c::inv" << std::endl <<
        "c::ctor::post" << std::endl <<
        
        "a::static_inv" << std::endl <<
        "a::ctor::body" << std::endl <<
        "a::static_inv" << std::endl <<
        "a::inv" << std::endl <<
        "a::ctor::post" << std::endl
    ;
    BOOST_TEST(out.check(ok.str()));

    BOOST_TEST_EQ(a_arg.copies(), 1); BOOST_TEST_EQ(a_arg.evals(), 1);
    BOOST_TEST_EQ(c_arg.copies(), 1); BOOST_TEST_EQ(c_arg.evals(), 1);
    BOOST_TEST_EQ(d_arg.copies(), 1); BOOST_TEST_EQ(d_arg.evals(), 1);
    BOOST_TEST_EQ(e_arg.copies(), 1); BOOST_TEST_EQ(e_arg.evals(), 1);
    BOOST_TEST_EQ(f_arg.copies(), 1); BOOST_TEST_EQ(f_arg.evals(), 1);

    return boost::report_errors();
}

