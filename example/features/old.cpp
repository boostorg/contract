
#include <boost/contract.hpp>
#include <string>
#include <cstddef>

//[old
char replace(std::string& s, std::size_t index, char c) {
    char result;
    boost::shared_ptr<char const> old_c; // But old values copied later...
    auto c = boost::contract::function()
        .precondition([&] {
            BOOST_CONTRACT_ASSERT(index < s.size());
        })
        .old([&] { // ...here, after preconditions (and invariants) checked.
            old_c = BOOST_CONTRACT_OLDOF(s[index]);
        })
        .postcondition([&] {
            BOOST_CONTRACT_ASSERT(s[index] == c);
            BOOST_CONTRACT_ASSERT(result == *old_c);
        })
    ;

    // Function body.
    result = s[index];
    s[index] = c;
    return result;
}
//]

