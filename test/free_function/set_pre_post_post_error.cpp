
#include <boost/contract/free_function.hpp>
#include <boost/contract/type.hpp>

int main() {
    boost::contract::type c = boost::contract::free_function()
        .precondition([&] {})
        .postcondition([&] {})
        .postcondition([&] {})
    ;
    return 0;
}

