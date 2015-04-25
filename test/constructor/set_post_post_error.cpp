
#include <boost/contract/constructor.hpp>
#include <boost/contract/type.hpp>

// Test double post error.

struct a {
    explicit a() {
        boost::contract::type c = boost::contract::constructor(this)
            .postcondition([&] {})
            .postcondition([&] {})
        ;
    }
};

int main() {
    a aa;
    return 0;
}

