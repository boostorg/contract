
#include <iostream>
#include <boost/contract/public_member.hpp>
#include <boost/contract/oldof.hpp>
#include <boost/contract/assert.hpp>
#include <boost/contract/scoped.hpp>
#include <boost/contract/bind.hpp>

struct a {
    std::string x;
    a() : x("a") {}

    void invariant() const { std::clog << "a::inv" << std::endl; }
    static void static_invariant() { std::clog << "a::static_inv" << std::endl;}

    void f_contract(int const& s, boost::contract::call c) const {
        boost::shared_ptr<int const> old_x = BOOST_CONTRACT_OLDOF(c, x);
        boost::contract::public_member(c, this)
            .precondition([&] { std::clog << "a::f::pre" << std::endd; })
            .postcondition([&] {
                std::clog << "a::f::post" << std::endl;
                BOOST_CONTRACT_ASSERT(x == old_x + s);
            })
        ;
    }
    virtual void f(int s) {
        boost::contract::scoped contract = boost::contract::bind(
                &a::f, this, s);
        std::clog << "a::f::body" << std::endl;
        x = x + s;
    }
};

int main() {
    a aa;
    aa.f("s");
    return 0;
}

