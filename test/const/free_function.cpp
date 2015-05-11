
#include <iostream>
#include <boost/contract/oldof.hpp>
#include <boost/contract/free_function.hpp>
#include <boost/contract/assert.hpp>
#include <boost/contract/scoped.hpp>
#include <boost/contract/bind.hpp>
#include <boost/shared_ptr.hpp>

void inv1_contract(int const& x, int const& result, boost::contract::call c) {
    boost::shared_ptr<int const> old_x = BOOST_CONTRACT_OLDOF(c, x);
    boost::contract::free_function(c)
        .precondition([&] {
            std::clog << "inv1::pre" << std::endl;
            BOOST_CONTRACT_ASSERT(x >= 0);
        })
        .postcondition([&] {
            std::clog << "inv1::post" << std::endl;
            BOOST_CONTRACT_ASSERT(-x == *old_x);
            BOOST_CONTRACT_ASSERT(result == *old_x);
        })
    ;
}
int inv1(int& x) {
    std::clog << "inv1" << std::endl;
    int result;
    boost::contract::scoped contract = boost::contract::bind(
            &inv1_contract, x, result);
    
    std::clog << "inv1::body" << std::endl;
    result = x;
    x = -x;
    return result;
}

int inv2(int& x) {
    int result;
    boost::shared_ptr<int const> old_x = BOOST_CONTRACT_OLDOF(x);
    boost::contract::scoped contract = boost::contract::free_function()
        .precondition([&] {
            std::clog << "inv2::pre" << std::endl;
            BOOST_CONTRACT_ASSERT(x >= 0);
        })
        .postcondition([&] {
            std::clog << "inv2::post" << std::endl;
            BOOST_CONTRACT_ASSERT(-x == *old_x);
            BOOST_CONTRACT_ASSERT(result == *old_x);
        })
    ;
    
    std::clog << "inv2::body" << std::endl;
    result = x;
    x = -x;
    return result;
}

int main() {
    int x = 123;
    inv1(x);
    std::clog << std::endl;

    x = 456;
    inv2(x);
    return 0;
}

