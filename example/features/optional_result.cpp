
#include <boost/contract.hpp>
#include <boost/optional.hpp>

//[optional_result
struct surface {
    // No default constructor.
    explicit surface(int area) : area_(area) {}
    int area() const { return area_; }
private:
    int area_;
};

surface square_area(int edge) {
    boost::optional<surface> result; // No default constructor so use optional.
    auto c = boost::contract::function()
        .precondition([&] {
            BOOST_CONTRACT_ASSERT(edge > 0);
        })
        .postcondition([&] {
            BOOST_CONTRACT_ASSERT(result->area() == edge * edge);
        })
    ;

    return *(result = surface(edge * edge)); // Function body.
}
//]

