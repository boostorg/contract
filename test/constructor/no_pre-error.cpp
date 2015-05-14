
#include <boost/contract/scoped.hpp>
#include <boost/contract/constructor.hpp>

struct a {
    a() {
        boost::contract::scoped contract = boost::contract::constructor(this)
            .precondition([] {}) // Error (must use constructor_precondition).
        ;
    }
};

int main() {
    a aa;
    return 0;
}

