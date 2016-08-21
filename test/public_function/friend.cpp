
#include <boost/contract.hpp>
#include <cassert>
#include <iostream>

class y;
class z;

class x {
public:
    void invariant() const {
        std::cout << "x::inv" << std::endl;
        BOOST_CONTRACT_ASSERT(get() >= 0);
    }

    x() : value_(0) {}
    int get() const { return value_; }
    friend void set_all(x&, y&, int value);

private:
    int value_;
};

class y {
public:
    void invariant() const {
        std::cout << "y::inv" << std::endl;
        BOOST_CONTRACT_ASSERT(get() >= 0);
    }

    y() : value_(0) {}
    int get() const { return value_; }
    friend void set_all(x&, y&, int value);

private:
    int value_;
};

void set_all(x& a, y& b, int value) {
    boost::contract::check post = boost::contract::function()
        .postcondition([&] {
            std::cout << "f::post" << std::endl;
            BOOST_CONTRACT_ASSERT(a.get() == value);
            BOOST_CONTRACT_ASSERT(b.get() == value);
        })
    ;
    boost::contract::check inv_b = boost::contract::public_function(&b);
    boost::contract::check inv_a = boost::contract::public_function(&a);
    boost::contract::check pre = boost::contract::function()
        .precondition([&] {
            std::cout << "f::pre" << std::endl;
            BOOST_CONTRACT_ASSERT(value > 0);
        })
    ;

    std::cout << "f::body" << std::endl;
    a.value_ = b.value_ = value;
}

int main() {
    x a;
    y b;
    set_all(a, b, 123); 
    assert(a.get() == 123);
    assert(b.get() == 123);
    return 1;
}

