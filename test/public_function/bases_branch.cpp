
// Test public function subcontracting from middle branch of inheritance tree.

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
        #if BOOST_CONTRACT_ENTRY_INVARIANTS
            << "d::static_inv" << std::endl
            << "d::inv" << std::endl
            << "e::static_inv" << std::endl
            << "e::inv" << std::endl
            << "c::static_inv" << std::endl
            << "c::inv" << std::endl
        #endif
        #if BOOST_CONTRACT_PRECONDITIONS
            << "d::f::pre" << std::endl
            << "e::f::pre" << std::endl
            << "c::f::pre" << std::endl
        #endif
        #if BOOST_CONTRACT_POSTCONDITIONS
            << "d::f::old" << std::endl
            << "e::f::old" << std::endl
            << "c::f::old" << std::endl
        #endif
        << "c::f::body" << std::endl
        #if BOOST_CONTRACT_EXIT_INVARIANTS
            << "d::static_inv" << std::endl
            << "d::inv" << std::endl
            << "e::static_inv" << std::endl
            << "e::inv" << std::endl
            << "c::static_inv" << std::endl
            << "c::inv" << std::endl
        #endif
        #if BOOST_CONTRACT_POSTCONDITIONS
            << "d::f::old" << std::endl
            << "d::f::post" << std::endl
            << "e::f::old" << std::endl
            << "e::f::post" << std::endl
            // No old call here because not a base object.
            << "c::f::post" << std::endl
        #endif
    ;
    BOOST_TEST(out.eq(ok.str()));
    
    BOOST_TEST_EQ(r.value, "C");
    BOOST_TEST_EQ(s.value, "cde");
    BOOST_TEST_EQ(s.copies(),
            BOOST_PP_IIF(BOOST_CONTRACT_POSTCONDITIONS, 3, 0));
    BOOST_TEST_EQ(s.evals(),
            BOOST_PP_IIF(BOOST_CONTRACT_POSTCONDITIONS, 3, 0));
    BOOST_TEST_EQ(s.ctors(), s.dtors());

    BOOST_TEST_EQ(cc.y.value, "cC");
    BOOST_TEST_EQ(cc.y.copies(),
            BOOST_PP_IIF(BOOST_CONTRACT_POSTCONDITIONS, 1, 0));
    BOOST_TEST_EQ(cc.y.evals(),
            BOOST_PP_IIF(BOOST_CONTRACT_POSTCONDITIONS, 1, 0));
    BOOST_TEST_EQ(cc.y.ctors(), cc.y.dtors());
    
    BOOST_TEST_EQ(cc.t<'d'>::z.value, "dC");
    BOOST_TEST_EQ(cc.t<'d'>::z.copies(),
            BOOST_PP_IIF(BOOST_CONTRACT_POSTCONDITIONS, 1, 0));
    BOOST_TEST_EQ(cc.t<'d'>::z.evals(),
            BOOST_PP_IIF(BOOST_CONTRACT_POSTCONDITIONS, 1, 0));
    BOOST_TEST_EQ(cc.t<'d'>.ctors(), cc.t<'d'>.dtors());

    BOOST_TEST_EQ(cc.t<'e'>::z.value, "eC");
    BOOST_TEST_EQ(cc.t<'e'>::z.copies(),
            BOOST_PP_IIF(BOOST_CONTRACT_POSTCONDITIONS, 1, 0));
    BOOST_TEST_EQ(cc.t<'e'>::z.evals(),
            BOOST_PP_IIF(BOOST_CONTRACT_POSTCONDITIONS, 1, 0));
    BOOST_TEST_EQ(cc.t<'e'>.ctors(), cc.t<'e'>.dtors());

    return boost::report_errors();
}

