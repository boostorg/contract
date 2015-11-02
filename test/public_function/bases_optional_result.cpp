
// Test base and derived classes mixing boost::optional result types.

#include "../aux_/oteststream.hpp"
#include <boost/contract/base_types.hpp>
#include <boost/contract/public_function.hpp>
#include <boost/contract/override.hpp>
#include <boost/contract/guard.hpp>
#include <boost/contract/assert.hpp>
#include <boost/optional.hpp>
#include <boost/detail/lightweight_test.hpp>
#include <cassert>

boost::contract::aux::test::oteststream out;

struct b {
    virtual int b::f(int x, boost::contract::virtual_* v) {
        int result = -1;
        boost::contract::guard c = boost::contract::public_function(
                v, result, this)
            .precondition([&] { out << "b::f::pre" << std::endl; })
            .old([&] { out << "b::f::old" << std::endl; })
            .postcondition([&] (int const& result) {
                out << "b::f::post " << result << std::endl;
                BOOST_CONTRACT_ASSERT(result == x);
            })
        ;

        out << "b::f::body" << std::endl;
        return result = x;
    }
};

struct a
    #define BASES public b
    : BASES
{
    typedef BOOST_CONTRACT_BASE_TYPES(BASES) base_types;
    #undef BASES

    virtual int f(int x, boost::contract::virtual_* v = 0) /* override */ {
        boost::optional<int> result;
        boost::contract::guard c = boost::contract::public_function<override_f>(
                v, result, &a::f, this, x)
            .precondition([&] { out << "a::f::pre" << std::endl; })
            .old([&] { out << "a::f::old" << std::endl; })
            .postcondition([&] (boost::optional<int> const& result) {
                out << "a::f::post " << *result << std::endl;
                BOOST_CONTRACT_ASSERT(*result == x);
            })
        ;

        out << "a::f::body" << std::endl;
        return *(result = x);
    }
    BOOST_CONTRACT_OVERRIDE(f)
};

int main() {
    a aa;
    aa.f(123);
    return boost::report_errors();
}

