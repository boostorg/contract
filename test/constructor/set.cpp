
#include "../aux_/oteststream.hpp"
#include <boost/contract/constructor.hpp>
#include <boost/contract/type.hpp>
#include <boost/detail/lightweight_test.hpp>
#include <sstream>

// Test all possible orders in which pre/post can be set.

boost::contract::aux::test::oteststream out;

struct nothing {
    void invariant() const { out << "inv" << std::endl; }
    static void static_invariant() { out << "static_inv" << std::endl; }

    explicit nothing() {
        boost::contract::type c = boost::contract::constructor(this);
        out << "body" << std::endl;
    }
};

struct pre_only : private boost::contract::constructor_precondition<pre_only> {
    void invariant() const { out << "inv" << std::endl; }
    static void static_invariant() { out << "static_inv" << std::endl; }

    explicit pre_only() :
        boost::contract::constructor_precondition<pre_only>([&] {
            out << "pre" << std::endl;
        })
    {
        boost::contract::type c = boost::contract::constructor(this);
        out << "body" << std::endl;
    }
};

struct post_only {
    void invariant() const { out << "inv" << std::endl; }
    static void static_invariant() { out << "static_inv" << std::endl; }

    explicit post_only() {
        boost::contract::type c = boost::contract::constructor(this)
            .postcondition([&] { out << "post" << std::endl; })
        ;
        out << "body" << std::endl;
    }
};

struct pre_post : private boost::contract::constructor_precondition<pre_post> {
    void invariant() const { out << "inv" << std::endl; }
    static void static_invariant() { out << "static_inv" << std::endl; }

    explicit pre_post() :
        boost::contract::constructor_precondition<pre_post>([&] {
            out << "pre" << std::endl;
        })
    {
        boost::contract::type c = boost::contract::constructor(this)
            .postcondition([&] { out << "post" << std::endl; })
        ;
        out << "body" << std::endl;
    }
};

int main() {
    std::ostringstream ok;
    
    out.str("");
    nothing n;
    ok.str(""); ok << "static_inv" << std::endl << "body" << std::endl <<
            "static_inv" << std::endl << "inv" << std::endl;
    BOOST_TEST(out.check(ok.str()));
    
    out.str("");
    pre_only e;
    ok.str(""); ok << "pre" << std::endl << "static_inv" << std::endl << "body"
            << std::endl << "static_inv" << std::endl << "inv" << std::endl;
    BOOST_TEST(out.check(ok.str()));
    
    out.str("");
    post_only o;
    ok.str(""); ok << "static_inv" << std::endl << "body" << std::endl <<
            "static_inv" << std::endl << "inv" << std::endl << "post" <<
            std::endl;
    BOOST_TEST(out.check(ok.str()));

    out.str("");
    pre_post pp;
    ok.str(""); ok << "pre" << std::endl << "static_inv" << std::endl << "body"
            << std::endl << "static_inv" << std::endl << "inv" << std::endl <<
            "post" << std::endl;
    BOOST_TEST(out.check(ok.str()));

    return boost::report_errors();
}

