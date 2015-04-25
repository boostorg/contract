
#include "../aux_/oteststream.hpp"
#include <boost/contract/free_function.hpp>
#include <boost/contract/type.hpp>
#include <boost/detail/lightweight_test.hpp>
#include <sstream>

boost::contract::aux::test::oteststream out;

// Test free-function with neither pre nor post set.
void nothing() {
    boost::contract::type c = boost::contract::free_function();
    out << "body" << std::endl;
}

// Test free-function with only pre set.
void pre_only() {
    boost::contract::type c = boost::contract::free_function()
        .precondition([&] { out << "pre" << std::endl; })
    ;
    out << "body" << std::endl;
}

// Test free-function with only post set.
void post_only() {
    boost::contract::type c = boost::contract::free_function()
        .postcondition([&] { out << "post" << std::endl; })
    ;
    out << "body" << std::endl;
}

// Test free-function with pre set before post.
void pre_post() {
    boost::contract::type c = boost::contract::free_function()
        .precondition([&] { out << "pre" << std::endl; })
        .postcondition([&] { out << "post" << std::endl; })
    ;
    out << "body" << std::endl;
}

// Test free-function with post set before pre.
void post_pre() {
    boost::contract::type c = boost::contract::free_function()
        .postcondition([&] { out << "post" << std::endl; })
        .precondition([&] { out << "pre" << std::endl; })
    ;
    out << "body" << std::endl;
}

int main() {
    std::ostringstream ok;
    
    out.str("");
    nothing();
    ok.str(""); ok << "body" << std::endl;
    BOOST_TEST(out.check(ok.str()));
    
    out.str("");
    pre_only();
    ok.str(""); ok << "pre" << std::endl << "body" << std::endl;
    BOOST_TEST(out.check(ok.str()));
    
    out.str("");
    post_only();
    ok.str(""); ok << "body" << std::endl << "post" << std::endl;
    BOOST_TEST(out.check(ok.str()));

    ok.str(""); ok << "pre" << std::endl << "body" << std::endl << "post" <<
            std::endl;
    
    out.str("");
    pre_post();
    BOOST_TEST(out.check(ok.str()));
    
    out.str("");
    post_pre();
    BOOST_TEST(out.check(ok.str()));

    return boost::report_errors();
}

