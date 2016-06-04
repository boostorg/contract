
// Test assertions skipped when operations to check them missing (e.g., `==`).

#include <boost/contract/function.hpp>
#include <boost/contract/guard.hpp>
#include <boost/contract/assert.hpp>
#include <boost/contract/call_if.hpp>
#include <boost/bind.hpp>
#include <boost/type_traits/has_equal_to.hpp>
#include <boost/detail/lightweight_test.hpp>
#include <functional>
#include <vector>

unsigned equal_skips;

template<typename T>
void push_back(std::vector<T>& vect, T const& val) {
    boost::contract::guard c = boost::contract::function()
        .postcondition([&] {
            BOOST_CONTRACT_ASSERT(
                boost::contract::call_if<boost::has_equal_to<T> >(
                    boost::bind(std::equal_to<T>(), boost::cref(vect.back()),
                            boost::cref(val))
                ).else_([] { ++equal_skips; return true; })
            );
        })
    ;
    vect.push_back(val);
}

struct j { // Type without operator==.
    explicit j(int i) : j_(i) {}
private:
    int j_;
};

int main() {
    std::vector<int> vi;
    equal_skips = 0;
    push_back(vi, 123);
    BOOST_TEST_EQ(equal_skips, 0);
        
    unsigned const cnt =
        #ifndef BOOST_CONTRACT_NO_POSTCONDITIONS
            1
        #else
            0
        #endif
    ;

    j jj(456);
    std::vector<j> vj;
    equal_skips = 0;
    push_back(vj, jj);
    BOOST_TEST_EQ(equal_skips, cnt);

    return boost::report_errors();
}

