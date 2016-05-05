
#include <boost/contract.hpp>
#include <string>
#include <cstddef>
#include <cassert>

//[old
char replace(std::string& s, std::size_t index, char x) {
    char result;
    boost::contract::old_ptr<char> old_y; // But old value copied later...
    boost::contract::guard c = boost::contract::function()
        .precondition([&] {
            BOOST_CONTRACT_ASSERT(index < s.size());
        })
        .old([&] { // ...after preconditions (and invariants) checked.
            old_y = BOOST_CONTRACT_OLDOF(s[index]);
        })
        .postcondition([&] {
            BOOST_CONTRACT_ASSERT(s[index] == x);
            BOOST_CONTRACT_ASSERT(result == *old_y);
        })
    ;

    result = s[index];
    s[index] = x;
    return result;
}
//]

int main() {
    std::string s = "abc";
    char r = replace(s, 1, '_');
    assert(s == "a_c");
    assert(r == 'b');
    return 0;
}

