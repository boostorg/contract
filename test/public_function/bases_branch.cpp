
#include "bases.hpp"
#include <boost/detail/lightweight_test.hpp>
#include <sstream>

int main() {
    std::ostringstream ok;
    
    c cc; // Test call to class at mid- inheritance tree (a base with bases).
    s_type s; s.value = "C";
    out.str("");
    result_type& r = cc.f(s);

    ok.str(""); ok
        << "d::static_inv" << std::endl
        << "d::inv" << std::endl
        << "e::static_inv" << std::endl
        << "e::inv" << std::endl
        << "c::static_inv" << std::endl
        << "c::inv" << std::endl

        << "d::f::pre" << std::endl
        << "e::f::pre" << std::endl
        << "c::f::pre" << std::endl

        << "d::f::old" << std::endl
        << "e::f::old" << std::endl
        << "c::f::old" << std::endl

        << "c::f::body" << std::endl
        
        << "d::static_inv" << std::endl
        << "d::inv" << std::endl
        << "e::static_inv" << std::endl
        << "e::inv" << std::endl
        << "c::static_inv" << std::endl
        << "c::inv" << std::endl
        
        << "d::f::old" << std::endl
        << "d::f::post" << std::endl
        << "e::f::old" << std::endl
        << "e::f::post" << std::endl
        // No old call here because not a base object.
        << "c::f::post" << std::endl
    ;
    BOOST_TEST(out.eq(ok.str()));
    
    BOOST_TEST_EQ(r.value, "C");
    BOOST_TEST_EQ(s.value, "cde");
    BOOST_TEST_EQ(s.copies(), 3);
    BOOST_TEST_EQ(s.evals(), 3);

    BOOST_TEST_EQ(cc.y.value, "cC");
    BOOST_TEST_EQ(cc.y.copies(), 1);
    BOOST_TEST_EQ(cc.y.evals(), 1);
    
    BOOST_TEST_EQ(cc.t<'d'>::z.value, "dC");
    BOOST_TEST_EQ(cc.t<'d'>::z.copies(), 1);
    BOOST_TEST_EQ(cc.t<'d'>::z.evals(), 1);

    BOOST_TEST_EQ(cc.t<'e'>::z.value, "eC");
    BOOST_TEST_EQ(cc.t<'e'>::z.copies(), 1);
    BOOST_TEST_EQ(cc.t<'e'>::z.evals(), 1);

    return boost::report_errors();
}

