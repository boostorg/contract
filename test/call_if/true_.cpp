
// Test call_if with true condition and non-void result type.

#include "../aux_/oteststream.hpp"
#include <boost/contract/call_if.hpp>
#include <boost/bind.hpp>
#include <boost/type_traits/has_equal_to.hpp>
#include <boost/detail/lightweight_test.hpp>
#include <sstream>

boost::contract::aux::test::oteststream out;

struct equal {
    typedef bool result_type; // Test non-void result type.

    template<typename L, typename R>
    result_type operator()(L left, R right) const {
        return left == right; // Requires operator==.
    }
};

struct x {}; // Doest not have operator==.

int main() {
    std::ostringstream ok;
    x x1, x2;;
    
    out.str("");
    out <<
        boost::contract::call_if<boost::has_equal_to<int> >(
            boost::bind(equal(), 123, 456) // False.
        ) // Test no else (not called).
    << std::endl;
    ok.str(""); ok << false << std::endl;
    BOOST_TEST(out.eq(ok.str()));

    out.str("");
    out <<
        boost::contract::call_if<boost::has_equal_to<int> >(
            boost::bind(equal(), 123, 123) // True.
        ).else_([] { return false; }) // Test else not called.
    << std::endl;
    ok.str(""); ok << true << std::endl;
    BOOST_TEST(out.eq(ok.str()));
    
    out.str("");
    out << // Test "..._c".
        boost::contract::call_if_c<boost::has_equal_to<int>::value>(
            boost::bind(equal(), 123, 123) // True.
        ).else_( // Test else not called.
            boost::bind(equal(), x1, x2) // Compiler-error... but not called.
        )
    << std::endl;
    ok.str(""); ok << true << std::endl;
    BOOST_TEST(out.eq(ok.str()));

    return boost::report_errors();
}

