
// Test error if override func does not actually override (unless PERMISSIVE).

#include <boost/contract/public_function.hpp>
#include <boost/contract/base_types.hpp>
#include <boost/contract/override.hpp>
#include <boost/contract/guard.hpp>

struct b {
    virtual void g(boost::contract::virtual_* v = 0) {
        boost::contract::guard c = boost::contract::public_function(v, this);
    }
};

struct a
    #define BASES public b
    : BASES
{
    typedef BOOST_CONTRACT_BASE_TYPES(BASES) base_types;
    #undef BASES

    virtual void f(boost::contract::virtual_* v = 0) /* override */ {
        boost::contract::guard c = boost::contract::public_function<
                override_f>(v, &a::f, this);
    }
    BOOST_CONTRACT_OVERRIDE(f)
};

int main() {
    a aa;
    aa.f();
    return 0;
}

