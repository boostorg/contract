
// Test constructor overloads using bind.

#include "../aux_/oteststream.hpp"
#include "../aux_/cpcnt.hpp"
#include <boost/contract/constructor.hpp>
#include <boost/contract/base_types.hpp>
#include <boost/contract/assert.hpp>
#include <boost/contract/oldof.hpp>
#include <boost/contract/var.hpp>
#include <boost/contract/decl_function.hpp>
#include <boost/bind.hpp>
#include <boost/detail/lightweight_test.hpp>
#include <sstream>

boost::contract::aux::test::oteststream out;

struct a
    #define BASES private boost::contract::constructor_precondition<a>
    : BASES
{
    typedef BOOST_CONTRACT_BASE_TYPES(BASES) base_types;
    #undef BASES

    void invariant() const {
        out << "a::inv" << std::endl;
        BOOST_CONTRACT_ASSERT(i_ == -1 || i_ > 0);
    }
    static void static_invariant() {
        out << "a::static_inv" << std::endl;
        BOOST_CONTRACT_ASSERT(n.value >= 0);
    }

    struct n_tag; typedef boost::contract::aux::test::cpcnt<n_tag, int> n_cnt;
    static n_cnt n;

    void constructor(boost::contract::decl c) const {
        boost::shared_ptr<n_cnt const> old_n =
                BOOST_CONTRACT_OLDOF(c, n_cnt::eval(n));
        boost::contract::constructor(c, this)
            .postcondition([&] {
                out << "a::ctor()::post" << std::endl;
                BOOST_CONTRACT_ASSERT(i_ == -1);
                BOOST_CONTRACT_ASSERT(n.value == old_n->value + 1);
            })
        ;
    }
    explicit a() : // Test overload with no argument.
        // Test overload with no preconditions.
        i_(-1)
    {
        boost::contract::var contract = boost::contract::decl_function(
                this, &a::constructor);
        ++n.value;
    }

    struct i_tag; typedef boost::contract::aux::test::cpcnt<i_tag, int> i_cnt;

    static void constructor_precondition(int const i) {
        out << "a::ctor(int)::pre" << std::endl;
        BOOST_CONTRACT_ASSERT(i > 0);
    }
    void constructor(i_cnt const& i, boost::contract::decl c) const {
        boost::shared_ptr<n_cnt const> old_n =
                BOOST_CONTRACT_OLDOF(c, n_cnt::eval(n));
        boost::contract::constructor(c, this)
            .postcondition([&] {
                out << "a::ctor(int)::post" << std::endl;
                BOOST_CONTRACT_ASSERT(i_ == i.value);
                BOOST_CONTRACT_ASSERT(n.value == old_n->value + 1);
            })
        ;
    }
    explicit a(int i) : // Test overload with int.
        boost::contract::constructor_precondition<a>(boost::bind(static_cast<
                void (*)(int const)>(&a::constructor_precondition), i)),
        i_(i)
    {
        i_cnt i_arg; i_arg.value = i;
        boost::contract::var contract = boost::contract::decl_function(
                this, i_arg, &a::constructor);
        BOOST_TEST_EQ(i_arg.copies(), 0); // Test bind args never copied.
        ++n.value;
    }
        
    struct h_tag; typedef boost::contract::aux::test::cpcnt<h_tag, char> h_cnt;

    static void constructor_precondition(char const h) {
        out << "a::ctor(char)::pre" << std::endl;
        BOOST_CONTRACT_ASSERT(h != '\0');
    }
    void constructor(h_cnt const& h, boost::contract::decl c) const {
        boost::shared_ptr<n_cnt const> old_n =
                BOOST_CONTRACT_OLDOF(c, n_cnt::eval(n));
        boost::contract::constructor(c, this)
            .postcondition([&] {
                out << "a::ctor(char)::post" << std::endl;
                BOOST_CONTRACT_ASSERT(i_ == h.value);
                BOOST_CONTRACT_ASSERT(n.value == old_n->value + 1);
            })
        ;
    }
    explicit a(char h) : // Test overload with char.
        boost::contract::constructor_precondition<a>(boost::bind(static_cast<
                void (*)(char const)>(&a::constructor_precondition), h)),
        i_(h)
    {
        h_cnt h_arg; h_arg.value = h;
        boost::contract::var contract = boost::contract::decl_function(
                this, h_arg, &a::constructor);
        BOOST_TEST_EQ(h_arg.copies(), 0); // Test bind args never copied.
        ++n.value;
    }

    ~a() { --n.value; }

private:
    int i_;
};
a::n_cnt a::n;

int main() {
    std::ostringstream ok;

    out.str("");
    a aa;
    ok.str("");
    ok
        // No preconditions.
        << "a::static_inv" << std::endl
        << "a::static_inv" << std::endl
        << "a::inv" << std::endl
        << "a::ctor()::post" << std::endl
    ;
    BOOST_TEST(out.eq(ok.str()));
    BOOST_TEST_EQ(a::n.copies(), 1);
    BOOST_TEST_EQ(a::n.evals(), 1);
    out << std::endl;

    out.str("");
    a ai(123);
    ok.str("");
    ok
        << "a::ctor(int)::pre" << std::endl
        << "a::static_inv" << std::endl
        << "a::static_inv" << std::endl
        << "a::inv" << std::endl
        << "a::ctor(int)::post" << std::endl
    ;
    BOOST_TEST(out.eq(ok.str()));
    BOOST_TEST_EQ(a::n.copies(), 2);
    BOOST_TEST_EQ(a::n.evals(), 2);
    out << std::endl;
    
    out.str("");
    a ac('x');
    ok.str("");
    ok
        << "a::ctor(char)::pre" << std::endl
        << "a::static_inv" << std::endl
        << "a::static_inv" << std::endl
        << "a::inv" << std::endl
        << "a::ctor(char)::post" << std::endl
    ;
    BOOST_TEST(out.eq(ok.str()));
    BOOST_TEST_EQ(a::n.copies(), 3);
    BOOST_TEST_EQ(a::n.evals(), 3);
    out << std::endl;

    return boost::report_errors();
}

