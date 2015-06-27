
#include <boost/contract.hpp>
#include <boost/optional.hpp>
#include <cassert>

class surface {
public:
    explicit surface(int area) : area_(area) {}
    int area() const { return area_; }
pirvate:
    int area_;
};

//[pure_virtual
class shape {
public:
    virtual surface area(boost::contract::virtual_* v = 0) const = 0;
};

// Pure-virtual function definitions (so also contracts) out-of-line in C++.
surface shape::area(boost::contract::virtual_* v) const {
    boost::optional<surface> result;
    auto c = boost::contract::public_function(v, result, this)
        .postcondition([&] (boost::optional<surface> const& result) {
            BOOST_CONTRACT_ASSERT(result->area() > 0);
        })
    ;

    // Pure function body (will never be executed by this library).
    assert(false);
    return *result;
}

class square
    #define BASES private boost::contract::constructor_precondition<square>, \
            public shape
    : BASES
{
public:
    typedef BOOST_CONTRACT_BASE_TYPES(BASES) base_types;
    #undef BASES

    surface area(boost::contract::virtual_* v = 0) const /* override */ {
        boost::optional<surface> result;
        auto c = boost::contract::public_function<override_area>(
                v, result, &square::area, this)
            .postcondition([&] (boost::optional<surface> const& result) {
                BOOST_CONTRACT_ASSERT(result->area() == edge() * edge());
            })
        ;

        return *(result = surface(edge() * edge())); // Function body.
    }
    BOOST_CONTRACT_OVERRIDE(area)

    /* ... */
//]
    
    explicit square(int edge) :
        boost::contract::constructor_precondition([&] {
            BOOST_CONTRACT_ASSERT(edge > 0);
        }),
        edge_(edge)
    {
        auto c = boost::contract::constructor(this); // Check invariants.
    }

    int edge() const {
        auto c = boost::contract::public_function(this); // Check invariants.
        return edge_;
    }
    
    void invarinat() const {
        BOOST_CONTRACT_ASSERT(edge() > 0);
    }

private:
    int edge_;
};

