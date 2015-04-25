
#include <boost/contract/constructor.hpp>
#include <boost/contract/type.hpp>

// Test pre error (must use constructor_precondition instead).

struct a {
    explicit a() {
        boost::contract::type c = boost::contract::constructor(this)
            .precondition([&] {})
        ;
    }
};

int main() {
    a aa;
    return 0;
}

