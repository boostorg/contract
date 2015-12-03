
// Test missing contract guard gives run-time error.

struct err {};

#define BOOST_CONTRACT_CONFIG_ON_MISSING_GUARD throw err();
#include <boost/contract/function.hpp>
#include <boost/contract/guard.hpp>

int main() {
    boost::contract::guard c = boost::contract::function() // Test this is OK.
        .precondition([] {})
        .old([] {})
        .postcondition([] {})
    ;

    try {
        boost::contract::function() // Test no `guard c = ...` errors.
            .precondition([] {})
            .old([] {})
            .postcondition([] {})
        ;
        return 1;
    } catch(err const&) { return 0; } // Test missing guard threw.
    catch(...) { return 2; }
    return 3;
}

