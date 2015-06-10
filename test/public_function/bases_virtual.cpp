
#include "bases.hpp"
#include <boost/detail/lightweight_test.hpp>
#include <sstream>

int main() {
    std::ostringstream ok;
    
    a aa;
    c& ca = aa; // Test polymorphic virtual call (via reference to base c).
    s_type s; s.value = "A";
    out.str("");
    result_type& r = ca.f(s);

    ok.str(""); ok
        << "d::static_inv" << std::endl
        << "d::inv" << std::endl
        << "e::static_inv" << std::endl
        << "e::inv" << std::endl
        << "c::static_inv" << std::endl
        << "c::inv" << std::endl
        << "a::static_inv" << std::endl
        << "a::inv" << std::endl

        << "d::f::pre" << std::endl
        << "e::f::pre" << std::endl
        << "c::f::pre" << std::endl
        << "a::f::pre" << std::endl

        << "a::f::body" << std::endl
        
        << "d::static_inv" << std::endl
        << "d::inv" << std::endl
        << "e::static_inv" << std::endl
        << "e::inv" << std::endl
        << "c::static_inv" << std::endl
        << "c::inv" << std::endl
        << "a::static_inv" << std::endl
        << "a::inv" << std::endl
        
        << "d::f::post" << std::endl
        << "e::f::post" << std::endl
        << "c::f::post" << std::endl
        << "a::f::post" << std::endl
    ;
    BOOST_TEST(out.eq(ok.str()));
    
    BOOST_TEST_EQ(r.value, "A");
    BOOST_TEST_EQ(s.value, "acde");
    BOOST_TEST_EQ(s.copies(), 4);
    BOOST_TEST_EQ(s.evals(), 4);

    // Cannot access x via ca, but only via aa.
    BOOST_TEST_EQ(aa.x.value, "aA");
    BOOST_TEST_EQ(aa.x.copies(), 1);
    BOOST_TEST_EQ(aa.x.evals(), 1);

    BOOST_TEST_EQ(ca.y.value, "cA");
    BOOST_TEST_EQ(ca.y.copies(), 1);
    BOOST_TEST_EQ(ca.y.evals(), 1);
    
    BOOST_TEST_EQ(ca.t<'d'>::z.value, "dA");
    BOOST_TEST_EQ(ca.t<'d'>::z.copies(), 1);
    BOOST_TEST_EQ(ca.t<'d'>::z.evals(), 1);

    BOOST_TEST_EQ(ca.t<'e'>::z.value, "eA");
    BOOST_TEST_EQ(ca.t<'e'>::z.copies(), 1);
    BOOST_TEST_EQ(ca.t<'e'>::z.evals(), 1);

    return boost::report_errors();
}

