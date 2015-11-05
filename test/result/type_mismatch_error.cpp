
// Test override public function error on result type mismatch.

#include <boost/contract/public_function.hpp>
#include <boost/contract/override.hpp>
#include <boost/contract/base_types.hpp>
#include <boost/contract/guard.hpp>

struct b {
    virtual int f(boost::contract::virtual_* v = 0) {
        // Unfortunately, this cannot be made to error at compile-time because
        // in this case public_function does not that &b::f as param (but this
        // will error at run-time on a virtual call via a derived class).
        char result;
        boost::contract::guard c = boost::contract::public_function(
                v, result, this);
        return result;
    }
};

struct a
    #define BASES public b
    : BASES
{
    typedef BOOST_CONTRACT_BASE_TYPES(BASES) base_types;
    #undef BASES

    virtual int f(boost::contract::virtual_* v = 0) /* override */ {
        char result;
        boost::contract::guard c = boost::contract::public_function<override_f>(
                v, result, &a::f, this); // Error (result time mismatch).
        return result;
    }
    BOOST_CONTRACT_OVERRIDE(f)
};

int main() {
    a aa;
    aa.f();
    return 0;
}

