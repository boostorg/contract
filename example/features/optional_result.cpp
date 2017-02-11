
// Copyright (C) 2008-2016 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0 (see accompanying
// file LICENSE_1_0.txt or a copy at http://www.boost.org/LICENSE_1_0.txt).
// See: http://www.boost.org/doc/libs/release/libs/contract/doc/html/index.html

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

surface squared_surface(int edge) {
    boost::optional<surface> result; // No default constructor so use optional.
    boost::contract::check c = boost::contract::function()
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
    surface s = squared_surface(10);
    assert(s.area == 100);
    assert(s.perimeter == 40);
    return 0;
}

