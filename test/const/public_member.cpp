
#include <iostream>
#include <boost/contract/public_member.hpp>
#include <boost/contract/oldof.hpp>
#include <boost/contract/assert.hpp>
#include <boost/contract/scoped.hpp>
#include <boost/contract/bind.hpp>

struct a {
    int x;

    void invariant() const {
        std::clog << "a::inv" << std::endl;
        BOOST_CONTRACT_ASSERT(x > 0);
    }
    static void static_invariant() {
        std::clog << "a::static_inv" << std::endl;
    }

    void swap_contract(int const& y, boost::contract::call c) const {
        boost::shared_ptr<int const> old_x = BOOST_CONTRACT_OLDOF(c, x);
        boost::shared_ptr<int const> old_y = BOOST_CONTRACT_OLDOF(c, y);
        boost::contract::public_member(c, this)
            .precondition([&] {
                std::clog << "a::swap::pre" << std::endl;
                BOOST_CONTRACT_ASSERT(x != y);
            })
            .postcondition([&] {
                std::clog << "a::swap::post" << std::endl;
                BOOST_CONTRACT_ASSERT(x == *old_y);
                BOOST_CONTRACT_ASSERT(y == *old_x);
            })
        ;
    }
    void swap(int& y) {
        boost::contract::scoped contract = boost::contract::bind(
                &a::swap_contract, this, y);

        std::clog << "a::swap::body" << std::endl;
        int save_x = x;
        x = y;
        y = save_x;
    }
};

int main() {
    a aa;
    aa.x = 10;
    int y = 20;
    aa.swap(y);
    return 0;
}

