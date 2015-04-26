
#include "../aux_/oteststream.hpp"
#include <boost/contract/free_function.hpp>
#include <boost/detail/lightweight_test.hpp>
#include <sstream>

// Test pre and post, or nothing combinations that can be set for free functions
// (member functions use same setter objects, so no need to test those too).

boost::contract::aux::test::oteststream out;

void nothing() {
    auto c = boost::contract::free_function();
    out << "body" << std::endl;
}

void pre_only() {
    auto c = boost::contract::free_function()
        .precondition([&] { out << "pre" << std::endl; })
    ;
    out << "body" << std::endl;
}

void post_only() {
    auto c = boost::contract::free_function()
        .postcondition([&] { out << "post" << std::endl; })
    ;
    out << "body" << std::endl;
}

void pre_post() {
    auto c = boost::contract::free_function()
        .precondition([&] { out << "pre" << std::endl; })
        .postcondition([&] { out << "post" << std::endl; })
    ;
    out << "body" << std::endl;
}

void post_pre() {
    auto c = boost::contract::free_function()
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

