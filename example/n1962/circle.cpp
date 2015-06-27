
#include <boost/contract.hpp>
#include <boost/detail/lightweight_test.hpp>
#include <cassert>

class shape {
public:
    virtual ~shape() {}

    virtual int compute_area(boost::contract::virtual_* v = 0) const = 0;
};

int shape::compute_area(boost::contract::virtual_* v) const {
    int result;
    auto c = boost::contract::public_function(v, result, this)
        .postcondition([&] (int const& result) {
            BOOST_CONTRACT_ASSERT(result > 0);
        })
    ;
    assert(false); return result = -1; // Never gets here.
}

class circle
    #define BASES public shape
    : BASES
{
public:
    typedef BOOST_CONTRACT_BASE_TYPES(BASES) base_types;
    #undef BASES

    int radius; // Make sure to set this...
    static int const pi = 3; // Truncated to int from 3.14...

    virtual int compute_area(boost::contract::virtual_* v = 0)
            const /* override */ {
        int result;
        auto c = boost::contract::public_function<override_compute_area>(
                v, result, &circle::compute_area, this)
            .postcondition([&] (int const& result) {
                BOOST_CONTRACT_ASSERT(result == pi * radius * radius);
            })
        ;
        
        return result = pi * radius * radius;
    }
    BOOST_CONTRACT_OVERRIDE(compute_area);
};

int main() {
    circle c;
    c.radius = 2;
    BOOST_TEST_EQ(c.compute_area(), 12);
    return boost::report_errors();
}

