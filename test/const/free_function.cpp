
#include "../aux_/oteststream.hpp"
#include <boost/contract/free_function.hpp>
#include <boost/detail/lightweight_test.hpp>
#include <sstream>

// Test free-function.

boost::contract::aux::test::oteststream out;

void inv1_contract(int const& x, int const& result,
        boost::contract::decl c = 0) {
    boost::shared_ptr<int const> old_x = BOOST_CONTRACT_OLDOF(c, x);
    boost::contract::free_function(c)
        .precondition([&] { BOOST_CONTRACT_ASSERT(x >= 0); })
        .postcondition([&] {
            BOOST_CONTRACT_ASSERT(-x == *old_x);
            BOOST_CONTRACT_ASSERT(result == *old_x);
        })
    ;
}
int inv1(int& x) {
    int result;
    boost::contract::var contract(inv1_contract, x, result);
    result = x;
    x = -x;
    return result;
}

int inv2(int& x) {
    int result;
    boost::shared_ptr<int const> old_x = BOOST_CONTRACT_OLDOF(x);
    boost::contract::var contract = boost::contract::free_function()
        .precondition([&] { BOOST_CONTRACT_ASSERT(x >= 0); })
        .postcondition([&] {
            BOOST_CONTRACT_ASSERT(-x == *old_x);
            BOOST_CONTRACT_ASSERT(result == *old_x);
        })
    ;
    result = x;
    x = -x;
    return result;
}


int main() {
    std::ostringstream ok;

    out.str("");
    f();
    ok.str("");
    ok
        << "f::pre" << std::endl
        << "f::body" << std::endl
        << "f::post" << std::endl
    ;
    BOOST_TEST(out.check(ok.str()));

    return boost::report_errors();
}

