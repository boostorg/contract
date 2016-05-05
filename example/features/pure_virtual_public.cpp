
#include <boost/contract.hpp>
#include <boost/optional.hpp>
#include <cassert>

//[pure_virtual_public
struct surface {
    int area;
    int perimeter;

    // No default constructor.
    surface(int area, int perimeter) : area(area), perimeter(perimeter) {}
};

class shape {
public:
    virtual surface get_surface(boost::contract::virtual_* v = 0) const = 0;
};

// Pure-virtual function definition (and contract) out-of-line (usual in C++).
surface shape::get_surface(boost::contract::virtual_* v) const {
    boost::optional<surface> result;
    boost::contract::guard c = boost::contract::public_function(v, result, this)
        .postcondition([&] (boost::optional<surface const&> const& result) {
            BOOST_CONTRACT_ASSERT(result->area > 0);
            BOOST_CONTRACT_ASSERT(result->perimeter > 0);
        })
    ;

    assert(false); // Pure function body (never executed by this library).
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

    surface get_surface(boost::contract::virtual_* v = 0) const /* override */ {
        boost::optional<surface> result;
        boost::contract::guard c = boost::contract::public_function<
                override_get_surface>(v, result, &square::get_surface, this)
            .postcondition([&] (boost::optional<surface const&> const& result) {
                BOOST_CONTRACT_ASSERT(result->area == edge() * edge());
                BOOST_CONTRACT_ASSERT(result->perimeter == edge() * 4);
            })
        ;

        return *(result = surface(edge() * edge(), edge() * 4));
    }
    BOOST_CONTRACT_OVERRIDE(get_surface)

    /* ... */
//]
    
    explicit square(int edge) :
        boost::contract::constructor_precondition<square>([&] {
            BOOST_CONTRACT_ASSERT(edge > 0);
        }),
        edge_(edge)
    {
        // Check invariants.
        boost::contract::guard c = boost::contract::constructor(this);
    }

    ~square() {
        // Check invariants.
        boost::contract::guard c = boost::contract::destructor(this);
    }

    int edge() const {
        // Check invariants.
        boost::contract::guard c = boost::contract::public_function(this);
        return edge_;
    }
    
    void invarinat() const {
        BOOST_CONTRACT_ASSERT(edge() > 0);
    }

private:
    int edge_;
};

int main() {
    square sq(10);
    surface s = sq.get_surface();
    assert(s.area == 100);
    assert(s.perimeter == 40);
    return 0;
}

