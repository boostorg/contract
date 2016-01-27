
// Test free function contracts.

#include "../aux_/oteststream.hpp"
#include "../aux_/counter.hpp"
#include <boost/contract/function.hpp>
#include <boost/contract/old.hpp>
#include <boost/contract/assert.hpp>
#include <boost/contract/guard.hpp>
#include <boost/preprocessor/control/iif.hpp>
#include <boost/detail/lightweight_test.hpp>
#include <sstream>

boost::contract::test::aux::oteststream out;

struct x_tag; typedef boost::contract::test::aux::counter<x_tag, int> x_type;
struct y_tag; typedef boost::contract::test::aux::counter<y_tag, int> y_type;

bool swap(x_type& x, y_type& y) {
    bool result;
    boost::contract::old_ptr<x_type> old_x =
            BOOST_CONTRACT_OLDOF(x_type::eval(x));
    boost::contract::old_ptr<y_type> old_y;
    boost::contract::guard c = boost::contract::function()
        .precondition([&] {
            out << "swap::pre" << std::endl;
            BOOST_CONTRACT_ASSERT(x.value != y.value);
        })
        .old([&] {
            out << "swap::old" << std::endl;
            old_y = BOOST_CONTRACT_OLDOF(y_type::eval(y));
        })
        .postcondition([&] {
            out << "swap::post" << std::endl;
            BOOST_CONTRACT_ASSERT(x.value == old_y->value);
            BOOST_CONTRACT_ASSERT(y.value == old_x->value);
            BOOST_CONTRACT_ASSERT(result == (old_x->value != old_y->value));
        })
    ;

    out << "swap::body" << std::endl;
    if(x.value == y.value) return result = false;
    int save_x = x.value;
    x.value = y.value;
    y.value = save_x;
    return result = true;
}

int main() {
    std::ostringstream ok;

    {
        x_type x; x.value = 123;
        y_type y; y.value = 456;

        out.str("");
        bool r = swap(x, y);
        ok.str(""); ok
            #if BOOST_CONTRACT_PRECONDITIONS
                << "swap::pre" << std::endl
            #endif
            #if BOOST_CONTRACT_POSTCONDITIONS
                << "swap::old" << std::endl
            #endif
            << "swap::body" << std::endl
            #if BOOST_CONTRACT_POSTCONDITIONS
                << "swap::post" << std::endl
            #endif
        ;
        BOOST_TEST(out.eq(ok.str()));
        
        BOOST_TEST(r);
        BOOST_TEST_EQ(x.value, 456);
        BOOST_TEST_EQ(y.value, 123);
    }

    BOOST_TEST_EQ(x_type::copies(),
            BOOST_PP_IIF(BOOST_CONTRACT_POSTCONDITIONS, 1, 0));
    BOOST_TEST_EQ(x_type::evals(),
            BOOST_PP_IIF(BOOST_CONTRACT_POSTCONDITIONS, 1, 0));
    BOOST_TEST_EQ(x_type::ctors(), x_type::dtors()); // No leak.
    
    BOOST_TEST_EQ(y_type::copies(),
        BOOST_PP_IIF(BOOST_CONTRACT_POSTCONDITIONS, 1, 0));
    BOOST_TEST_EQ(y_type::evals(),
        BOOST_PP_IIF(BOOST_CONTRACT_POSTCONDITIONS, 1, 0));
    BOOST_TEST_EQ(y_type::ctors(), y_type::dtors()); // No leak.

    return boost::report_errors();
}

