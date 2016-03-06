
// no #include guard

// Test error if non-static inv declared mutable (unless PERMISSIVE #defined).

#include <boost/contract/public_function.hpp>
#include <boost/contract/guard.hpp>

struct a {
    void invariant() {}

    void f() {
        // Same for ctor and dtor (because they all use check_pre_post_inv).
        boost::contract::guard c = boost::contract::public_function(this);
    }
};

int main() {
    a aa;
    aa.f();
    return 0;
};

