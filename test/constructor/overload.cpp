
// Test constructor overloads.

#include "../aux_/oteststream.hpp"
#include "../aux_/cpcnt.hpp"
#include <boost/contract/constructor.hpp>
#include <boost/contract/base_types.hpp>
#include <boost/contract/assert.hpp>
#include <boost/contract/oldof.hpp>
#include <boost/contract/var.hpp>
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

    explicit a() : // Test overload with no argument.
        // Test overload with no preconditions.
        i_(-1)
    {
        boost::shared_ptr<n_cnt const> old_n =
                BOOST_CONTRACT_OLDOF(n_cnt::eval(n));
        boost::contract::var contract = boost::contract::constructor(this)
            .postcondition([&] {
                out << "a::ctor()::post" << std::endl;
                BOOST_CONTRACT_ASSERT(i_ == -1);
                BOOST_CONTRACT_ASSERT(n.value == old_n->value + 1);
            })
        ;
        ++n.value;
    }

    explicit a(int i) : // Test overload with int.
        boost::contract::constructor_precondition<a>([&] {
            out << "a::ctor(int)::pre" << std::endl;
            BOOST_CONTRACT_ASSERT(i > 0);
        }),
        i_(i)
    {
        boost::shared_ptr<n_cnt const> old_n =
                BOOST_CONTRACT_OLDOF(n_cnt::eval(n));
        boost::contract::var contract = boost::contract::constructor(this)
            .postcondition([&] {
                out << "a::ctor(int)::post" << std::endl;
                BOOST_CONTRACT_ASSERT(i_ == i);
                BOOST_CONTRACT_ASSERT(n.value == old_n->value + 1);
            })
        ;
        ++n.value;
    }

    explicit a(char h) : // Test overload with char.
        boost::contract::constructor_precondition<a>([&] {
            out << "a::ctor(char)::pre" << std::endl;
            BOOST_CONTRACT_ASSERT(h != '\0');
        }),
        i_(h)
    {
        boost::shared_ptr<n_cnt const> old_n =
                BOOST_CONTRACT_OLDOF(n_cnt::eval(n));
        boost::contract::var contract = boost::contract::constructor(this)
            .postcondition([&] {
                out << "a::ctor(char)::post" << std::endl;
                BOOST_CONTRACT_ASSERT(i_ == h);
                BOOST_CONTRACT_ASSERT(n.value == old_n->value + 1);
            })
        ;
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

