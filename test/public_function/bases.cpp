
#include "bases.hpp"
#include <boost/detail/lightweight_test.hpp>
#include <sstream>

int main() {
    std::ostringstream ok;
    
    a aa; // Test call to derived out-most leaf.
    s_type s; s.value = "A";
    out.str("");
    result_type& r = aa.f(s);

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
        
        << "d::f::old" << std::endl
        << "e::f::old" << std::endl
        << "c::f::old" << std::endl
        << "a::f::old" << std::endl

        << "a::f::body" << std::endl
        
        << "d::static_inv" << std::endl
        << "d::inv" << std::endl
        << "e::static_inv" << std::endl
        << "e::inv" << std::endl
        << "c::static_inv" << std::endl
        << "c::inv" << std::endl
        << "a::static_inv" << std::endl
        << "a::inv" << std::endl
        
        << "d::f::old" << std::endl
        << "d::f::post" << std::endl
        << "e::f::old" << std::endl
        << "e::f::post" << std::endl
        << "c::f::old" << std::endl
        << "c::f::post" << std::endl
        // No old call here because not a base object.
        << "a::f::post" << std::endl
    ;
    BOOST_TEST(out.eq(ok.str()));
    
    BOOST_TEST_EQ(r.value, "A");
    BOOST_TEST_EQ(s.value, "acde");
    BOOST_TEST_EQ(s.copies(), 4);
    BOOST_TEST_EQ(s.evals(), 4);

    BOOST_TEST_EQ(aa.x.value, "aA");
    BOOST_TEST_EQ(aa.x.copies(), 1);
    BOOST_TEST_EQ(aa.x.evals(), 1);

    BOOST_TEST_EQ(aa.y.value, "cA");
    BOOST_TEST_EQ(aa.y.copies(), 1);
    BOOST_TEST_EQ(aa.y.evals(), 1);
    
    BOOST_TEST_EQ(aa.t<'d'>::z.value, "dA");
    BOOST_TEST_EQ(aa.t<'d'>::z.copies(), 1);
    BOOST_TEST_EQ(aa.t<'d'>::z.evals(), 1);

    BOOST_TEST_EQ(aa.t<'e'>::z.value, "eA");
    BOOST_TEST_EQ(aa.t<'e'>::z.copies(), 1);
    BOOST_TEST_EQ(aa.t<'e'>::z.evals(), 1);

    return boost::report_errors();
}

