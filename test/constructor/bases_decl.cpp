
// Test constructor subcontracting and contract declaration functions.

#include "../aux_/oteststream.hpp"
#include "../aux_/cpcnt.hpp"
#include <boost/contract/constructor.hpp>
#include <boost/contract/decl_function.hpp>
#include <boost/contract/base_types.hpp>
#include <boost/contract/assert.hpp>
#include <boost/contract/oldof.hpp>
#include <boost/contract/var.hpp>
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
        BOOST_CONTRACT_ASSERT(i_ < 0);
    }
    static void static_invariant() {
        out << Id << "::static_inv" << std::endl;
        BOOST_CONTRACT_ASSERT(n.value >= 0);
    }

    struct n_tag; typedef boost::contract::aux::test::cpcnt<n_tag, int> n_cnt;
    static n_cnt n;

    struct arg_tag;
    typedef boost::contract::aux::test::cpcnt<arg_tag, int> arg_cnt;

    // MSVC 2010 errors on lambdas in template member initializations...
    static void constructor_precondition(arg_cnt const& arg) {
        out << Id << "::ctor::pre" << std::endl;
        BOOST_CONTRACT_ASSERT(arg.value < 0);
    }
    void constructor(arg_cnt const& arg, boost::contract::decl c) const {
        boost::shared_ptr<arg_cnt const> old_arg =
                BOOST_CONTRACT_OLDOF(c, arg_cnt::eval(arg));
        boost::shared_ptr<n_cnt const> old_n =
                BOOST_CONTRACT_OLDOF(c, n_cnt::eval(n));
        boost::contract::var contract = boost::contract::constructor(c, this)
            .postcondition([&] {
                out << Id << "::ctor::post" << std::endl;
                BOOST_CONTRACT_ASSERT(i_ == old_arg->value);
                BOOST_CONTRACT_ASSERT(arg.value == n.value);
                BOOST_CONTRACT_ASSERT(n.value == old_n->value + 1);
            })
        ;
    }
    explicit t(arg_cnt& arg) :
        boost::contract::constructor_precondition<t<Id> >(boost::bind(
                &t::constructor_precondition, boost::cref(arg)))
    {
        unsigned save_arg_copies = arg.copies();
        boost::contract::var contract = boost::contract::decl_function(
                this, arg, &t::constructor);
        // Test decl_function did not copy (only 1 copy from contract old-of).
        BOOST_TEST_EQ(arg.copies(), save_arg_copies + 1);

        out << Id << "::ctor::body" << std::endl;
        i_ = arg.value;
        arg.value = ++n.value;
    }

    virtual ~t() { --n.value; }

private:
    int i_;
};
template<char Id> typename t<Id>::n_cnt t<Id>::n;

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
        BOOST_CONTRACT_ASSERT(i_ < 0);
    }
    static void static_invariant() {
        out << "c::static_inv" << std::endl;
        BOOST_CONTRACT_ASSERT(n.value >= 0);
    }
    
    struct n_tag; typedef boost::contract::aux::test::cpcnt<n_tag, int> n_cnt;
    static n_cnt n;

    struct arg_tag;
    typedef boost::contract::aux::test::cpcnt<arg_tag, int> arg_cnt;

    static void constructor_precondition(arg_cnt const& arg) {
        out << "c::ctor::pre" << std::endl;
        BOOST_CONTRACT_ASSERT(arg.value < 0);
    }
    void constructor(arg_cnt const& arg, boost::contract::decl c) const {
        boost::shared_ptr<arg_cnt const> old_arg =
                BOOST_CONTRACT_OLDOF(c, arg_cnt::eval(arg));
        boost::shared_ptr<n_cnt const> old_n =
                BOOST_CONTRACT_OLDOF(c, n_cnt::eval(n));
        boost::contract::var contract = boost::contract::constructor(c, this)
            .postcondition([&] {
                out << "c::ctor::post" << std::endl;
                BOOST_CONTRACT_ASSERT(i_ == old_arg->value);
                BOOST_CONTRACT_ASSERT(arg.value == n.value);
                BOOST_CONTRACT_ASSERT(n.value == old_n->value + 1);
            })
        ;
    }
    explicit c(arg_cnt& arg, t<'d'>::arg_cnt& d_arg, t<'e'>::arg_cnt& e_arg,
            t<'f'>::arg_cnt& f_arg) :
        boost::contract::constructor_precondition<c>(boost::bind(
                &constructor_precondition, boost::cref(arg))),
        t<'d'>(d_arg), t<'e'>(e_arg), t<'f'>(f_arg)
    {
        unsigned save_arg_copies = arg.copies();
        boost::contract::var contract = boost::contract::decl_function(
                this, arg, &c::constructor);
        // Test decl_function did not copy (only 1 copy from contract old-of).
        BOOST_TEST_EQ(arg.copies(), save_arg_copies + 1);

        out << "c::ctor::body" << std::endl;
        i_ = arg.value;
        arg.value = ++n.value;
    }

    virtual ~c() { --n.value; }

private:
    int i_;
};
c::n_cnt c::n;

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
        BOOST_CONTRACT_ASSERT(i_ < 0);
    }
    static void static_invariant() {
        out << "a::static_inv" << std::endl;
        BOOST_CONTRACT_ASSERT(n.value >= 0);
    }
    
    struct n_tag; typedef boost::contract::aux::test::cpcnt<n_tag, int> n_cnt;
    static n_cnt n;

    struct arg_tag;
    typedef boost::contract::aux::test::cpcnt<arg_tag, int> arg_cnt;

    static void constructor_precondition(arg_cnt const& arg) {
        out << "a::ctor::pre" << std::endl;
        BOOST_CONTRACT_ASSERT(arg.value < 0);
    }
    void constructor(arg_cnt const& arg, boost::contract::decl c) const {
        boost::shared_ptr<arg_cnt const> old_arg =
                BOOST_CONTRACT_OLDOF(c, arg_cnt::eval(arg));
        boost::shared_ptr<n_cnt const> old_n =
                BOOST_CONTRACT_OLDOF(c, n_cnt::eval(n));
        boost::contract::var contract = boost::contract::constructor(c, this)
            .postcondition([&] {
                out << "a::ctor::post" << std::endl;
                BOOST_CONTRACT_ASSERT(i_ == old_arg->value);
                BOOST_CONTRACT_ASSERT(arg.value == n.value);
                BOOST_CONTRACT_ASSERT(n.value == old_n->value + 1);
            })
        ;
    }
    explicit a(arg_cnt& arg, c::arg_cnt& c_arg, t<'d'>::arg_cnt& d_arg,
            t<'e'>::arg_cnt& e_arg, t<'f'>::arg_cnt& f_arg) :
        boost::contract::constructor_precondition<a>(boost::bind(
                &a::constructor_precondition, boost::cref(arg))),
        b(), c(c_arg, d_arg, e_arg, f_arg)
    {
        unsigned save_arg_copies = arg.copies();
        boost::contract::var contract = boost::contract::decl_function(
                this, arg, &a::constructor);
        // Test decl_function did not copy (only 1 copy from contract old-of).
        BOOST_TEST_EQ(arg.copies(), save_arg_copies + 1);

        out << "a::ctor::body" << std::endl;
        i_ = arg.value;
        arg.value = ++n.value;
    }

    virtual ~a() { --n.value; }

private:
    int i_;
};
a::n_cnt a::n;

int main() {
    std::ostringstream ok;

    t<'f'>::arg_cnt f_arg; f_arg.value = -5;
    t<'e'>::arg_cnt e_arg; e_arg.value = -4;
    t<'d'>::arg_cnt d_arg; d_arg.value = -3;
    c::arg_cnt c_arg; c_arg.value = -2;
    a::arg_cnt a_arg; a_arg.value = -1;

    out.str("");
    a aa(a_arg, c_arg, d_arg, e_arg, f_arg);
    ok.str("");
    ok
        // Test all constructor pre checked first.
        << "a::ctor::pre" << std::endl
        << "c::ctor::pre" << std::endl
        << "d::ctor::pre" << std::endl

        // Test static inv, but not const inv, checked before constructor body.
        << "d::static_inv" << std::endl
        << "d::ctor::body" << std::endl
        << "d::static_inv" << std::endl
        << "d::inv" << std::endl
        << "d::ctor::post" << std::endl

        << "e::ctor::pre" << std::endl
        << "e::static_inv" << std::endl
        << "e::ctor::body" << std::endl
        << "e::static_inv" << std::endl
        << "e::inv" << std::endl
        << "e::ctor::post" << std::endl

        << "f::ctor::pre" << std::endl
        << "f::static_inv" << std::endl
        << "f::ctor::body" << std::endl
        << "f::static_inv" << std::endl
        << "f::inv" << std::endl
        << "f::ctor::post" << std::endl

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

    BOOST_TEST_EQ(a_arg.copies(), 1); BOOST_TEST_EQ(a_arg.evals(), 1);
    BOOST_TEST_EQ(c_arg.copies(), 1); BOOST_TEST_EQ(c_arg.evals(), 1);
    BOOST_TEST_EQ(d_arg.copies(), 1); BOOST_TEST_EQ(d_arg.evals(), 1);
    BOOST_TEST_EQ(e_arg.copies(), 1); BOOST_TEST_EQ(e_arg.evals(), 1);
    BOOST_TEST_EQ(f_arg.copies(), 1); BOOST_TEST_EQ(f_arg.evals(), 1);

    BOOST_TEST_EQ(a::n.copies(), 1); BOOST_TEST_EQ(a::n.evals(), 1);
    BOOST_TEST_EQ(c::n.copies(), 1); BOOST_TEST_EQ(c::n.evals(), 1);
    BOOST_TEST_EQ(t<'d'>::n.copies(), 1); BOOST_TEST_EQ(t<'d'>::n.evals(), 1);
    BOOST_TEST_EQ(t<'e'>::n.copies(), 1); BOOST_TEST_EQ(t<'e'>::n.evals(), 1);
    BOOST_TEST_EQ(t<'f'>::n.copies(), 1); BOOST_TEST_EQ(t<'f'>::n.evals(), 1);

    return boost::report_errors();
}

