
//[n1962_circle
#include <boost/contract.hpp>
#include <cassert>

class shape {
public:
    virtual ~shape() {}

    virtual unsigned compute_area(boost::contract::virtual_* v = 0) const = 0;
};

unsigned shape::compute_area(boost::contract::virtual_* v) const {
    unsigned result;
    boost::contract::guard c = boost::contract::public_function(v, result, this)
        .postcondition([&] (int const& result) {
            BOOST_CONTRACT_ASSERT(result > 0);
        })
    ;
    assert(false);
    return result = 0;
}

class circle
    #define BASES public shape
    : BASES
{
    friend class boost::contract::access;
    typedef BOOST_CONTRACT_BASE_TYPES(BASES) base_types;
    #undef BASES
    BOOST_CONTRACT_OVERRIDE(compute_area);

public:
    static int const pi = 3; // Truncated to int from 3.14...

    explicit circle(unsigned a_radius) : radius_(a_radius) {
        boost::contract::guard c = boost::contract::constructor(this)
            .postcondition([&] {
                BOOST_CONTRACT_ASSERT(radius() == a_radius);
            })
        ;
    }

    virtual unsigned compute_area(boost::contract::virtual_* v = 0) const
            /* override */ {
        unsigned result;
        boost::contract::guard c = boost::contract::public_function<
                override_compute_area>(v, result, &circle::compute_area, this)
            .postcondition([&] (unsigned const& result) {
                BOOST_CONTRACT_ASSERT(result == pi * radius() * radius());
            })
        ;
        
        return result = pi * radius() * radius();
    }

    unsigned radius() const {
        boost::contract::guard c = boost::contract::public_function(this);
        return radius_;
    }

private:
    unsigned radius_;
};

int main() {
    circle c(2);
    assert(c.radius() == 2);
    assert(c.compute_area() == 12);
    return 0;
}
//]

