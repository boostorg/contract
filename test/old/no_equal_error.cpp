
// Test old value error when operations to check them missing (e.g., `==`).

#include <boost/contract/function.hpp>
#include <boost/contract/guard.hpp>
#include <boost/contract/old.hpp>
#include <boost/contract/assert.hpp>
#include <vector>

template<typename T>
void push_back(std::vector<T>& vect, T const& val) {
    boost::contract::guard c = boost::contract::function()
        .postcondition([&] {
            BOOST_CONTRACT_ASSERT(vect.back() == val); // Error (j has no ==).
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
    push_back(vi, 123);

    j jj(456);
    std::vector<j> vj;
    push_back(vj, jj);

    return 0;
}

