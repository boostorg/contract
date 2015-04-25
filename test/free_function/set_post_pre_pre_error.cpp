
#include <boost/contract/free_function.hpp>
#include <boost/contract/type.hpp>

int main() {
    boost::contract::type c = boost::contract::free_function()
        .postcondition([&] {})
        .precondition([&] {})
        .precondition([&] {})
    ;
    return 0;
}

