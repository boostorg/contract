
//[n1962_factorial
#include <boost/contract.hpp>
#include <boost/detail/lightweight_test.hpp>

// Assertion complexity classified relative their function body complexity.
#define O_LESS_THAN_BODY        0
#define O_SAME_AS_BODY          1
#define O_GREATHER_THAN_BODY    2
#define COMPLEXITY_MAX          O_SAME_AS_BODY

int factorial(int n ) {
    int result;
    auto c = boost::contract::function()
        .precondition([&] {
            BOOST_CONTRACT_ASSERT(n >= 0); // Non-negative natural number.
            BOOST_CONTRACT_ASSERT(n <= 12); // Max function input.
        })
        .postcondition([&] {
            BOOST_CONTRACT_ASSERT(result >= 1);
            if(n < 2) { // Select assertion.
                BOOST_CONTRACT_ASSERT(result == 1);
            } else {
                // Following assertion introduce significant run-time overhead
                // (same as the function body) so assertion can be selectively
                // disabled by setting COMPLEXITY_MAX.
                if(O_SAME_AS_BODY <= COMPLEXITY_MAX) {
                    // Assertion automatically disable within other assertions.
                    // Therefore, this postcondition can recursively call the
                    // function without causing infinite recursion.
                    BOOST_CONTRACT_ASSERT(n * factorial(n - 1));
                }
            }
        })
    ;

    return n < 2 ? (result = 1) : (result = n * factorial(n - 1));
}

int main() {
    BOOST_TEST_EQ(factorial(4), 24);
    return boost::report_errors();
}
//]

