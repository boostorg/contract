
// Test a public function contract cannot override from a protected one.

#include <boost/contract/public_function.hpp>
#include <boost/contract/base_types.hpp>
#include <boost/contract/override.hpp>
#include <boost/contract/guard.hpp>

struct b {
protected:
    virtual void f(boost::contract::virtual_* v = 0) {
        boost::contract::guard c = boost::contract::public_function(v, this);
    }
    
    friend class boost::contract::access; // Test this cannot prevent error.
};
struct a
    #define BASES public b
    : BASES
{
    typedef BOOST_CONTRACT_BASE_TYPES(BASES) base_types;
    #undef BASES

    void f(boost::contract::virtual_* v = 0) /* override */ {
        boost::contract::guard c = boost::contract::public_function<override_f>(
                v, &a::f, this);
    }

    // GCC and CLang cannot correctly even see b::f as part of overloaded bases
    // because it is protected. MSVC at least still fails compilation where
    // override_f below tries to call b::f because it is protected so it cannot
    // be seen from within override_f.
    BOOST_CONTRACT_OVERRIDE(f)
    
    friend class boost::contract::access; // Test this cannot prevent error.
};

int main() {
    a aa;
    aa.f();
    return 0;
}

