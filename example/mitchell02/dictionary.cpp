
// Copyright (C) 2008-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://sourceforge.net/projects/contractpp

//[mitchell02_dictionary
// File: dictionary.cpp
#include <contract.hpp>
#include <boost/detail/lightweight_test.hpp>
#include <utility>
#include <map>

CONTRACT_CLASS( // Simple dictionary.
    template( typename Key, typename Value )
    class (dictionary)
) {
    CONTRACT_CLASS_INVARIANT_TPL( count() >= 0 ) // non-negative count

    // Creation.

    CONTRACT_CONSTRUCTOR_TPL( // Create empty dictionary.
        public (dictionary) ( void )
            postcondition( count() == 0 ) // empty
    ) {}

    CONTRACT_DESTRUCTOR_TPL( // Destroy dictionary.
        public virtual (~dictionary) ( void )
    ) {}

    // Basic queries.

    CONTRACT_FUNCTION_TPL( // Number of key entires.
        public int (count) ( void ) const
            // postcondition: non-negative count asserted by class invariants
    ) {
        return items_.size();
    }

    CONTRACT_FUNCTION_TPL( // Has entry for key?
        public bool (has) ( (Key const&) key ) const
            postcondition(
                auto result = return,
                if(count() == 0) ( not result ) // empty has no key
            )
    ) {
        return items_.find(key) != items_.end();
    }

    CONTRACT_FUNCTION_TPL( // Value for given key.
        public (Value const&) (value_for) ( (Key const&) key ) const
            precondition( has(key) ) // has key
    ) {
        return items_.find(key)->second;
    }

    // Commands.

    CONTRACT_FUNCTION_TPL( // Put value for given key.
        public void (put) ( (Key const&) key, (Value const&) value )
            postcondition(
                auto old_count = CONTRACT_OLDOF count(),
                count() == old_count + 1, // count increased
                has(key), // has key
                value_for(key) == value // value for key set
            )
    ) {
        items_.insert(std::make_pair(key, value));
    }

    CONTRACT_FUNCTION_TPL( // Remove value for given key.
        public void (remove) ( (Key const&) key )
            precondition( has(key) ) // has key
            postcondition(
                auto old_count = CONTRACT_OLDOF count(),
                count() == old_count - 1, // count decreased
                not has(key) // does not have key
            )
    ) {
        items_.erase(key);
    }

    private: std::map<Key, Value> items_;
};

int main ( void )
{
    dictionary<std::string, int> ages;
    BOOST_TEST(not ages.has("john"));
    ages.put("john", 23);
    BOOST_TEST(ages.value_for("john") == 23);
    ages.remove("john");
    BOOST_TEST(ages.count() == 0);
    return boost::report_errors();
}
//]

