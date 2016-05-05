
#include <boost/contract.hpp>
#include <boost/optional.hpp>
#include <cassert>

//[optional_result
struct surface {
    int area;
    int perimeter;

    // No default constructor.
    surface(int area, int perimeter) : area(area), perimeter(perimeter) {}
};

surface square_surface(int edge) {
    boost::optional<surface> result; // No default constructor so use optional.
    boost::contract::guard c = boost::contract::function()
        .precondition([&] {
            BOOST_CONTRACT_ASSERT(edge > 0);
        })
        .postcondition([&] {
            BOOST_CONTRACT_ASSERT(result->area == edge * edge);
            BOOST_CONTRACT_ASSERT(result->perimeter == edge * 4);
        })
    ;

    return *(result = surface(edge * edge, edge * 4));
}
//]

int main() {
    surface s = square_surface(10);
    assert(s.area == 100);
    assert(s.perimeter == 40);
    return 0;
}

