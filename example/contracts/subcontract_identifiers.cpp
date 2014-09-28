
// Copyright (C) 2008-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://sourceforge.net/projects/contractpp

#include <contract.hpp>
#include <boost/detail/lightweight_test.hpp>
#include <vector>
#include <algorithm>

//[subcontract_identifiers_unique
CONTRACT_CLASS(
    class (unique_identifiers)
) {
    CONTRACT_CLASS_INVARIANT( size() >= 0 )

    CONTRACT_CONSTRUCTOR(
        public (unique_identifiers) ( void )
            postcondition( size() == 0 )
    ) {}

    CONTRACT_DESTRUCTOR(
        public virtual (~unique_identifiers) ( void )
    ) {}

    CONTRACT_FUNCTION(
        public virtual void (add) ( int id )
            precondition(
                // Id not already present.
                std::find(begin(), end(), id) == end()
            )
            postcondition(
                auto old_size = CONTRACT_OLDOF size(),
                auto old_found = CONTRACT_OLDOF
                        std::find(begin(), end(), id) != end(),
                // If id was not already present, it was added now...
                old_found ? true : std::find(begin(), end(), id) != end(),
                // ...and size was increased of 1.
                old_found ? true : size() == old_size + 1
            )
    ) {
        identifiers_.push_back(id);
    }
    
    // ...
//]

    public: typedef std::vector<int>::const_iterator const_iterator;

    // Should contract these members too...
    public: int size ( void ) const { return identifiers_.size(); }
    public: const_iterator begin ( void ) const { return identifiers_.begin(); }
    public: const_iterator end ( void ) const { return identifiers_.end(); }

    protected: std::vector<int> identifiers_;
};

//[subcontract_identifiers_duplicate
CONTRACT_CLASS(
    class (duplicate_identifiers)
        extends( public unique_identifiers ) // Automatically subcontract.
) {
    CONTRACT_CLASS_INVARIANT(
        size() >= 1 // Strengthened inherited class invariants (in `and`).
    )

    CONTRACT_CONSTRUCTOR(
        public (duplicate_identifiers) ( int id )
            postcondition( size() == 1 )
    ) {
        // As usual, constructor should not call virtual member `add`.
        identifiers_.push_back(id);
    }

    CONTRACT_DESTRUCTOR(
        public virtual (~duplicate_identifiers) ( void )
    ) {}

    CONTRACT_FUNCTION(
        public virtual void (add) ( int id )
            precondition( // Wakened inherited preconditions (in `or`).
                // OK even if id is already present.
                std::find(begin(), end(), id) != end()
            )
            postcondition( // Strengthened inherited postconditions (in `and`).
                auto old_size = CONTRACT_OLDOF size(),
                auto old_found = CONTRACT_OLDOF
                        std::find(begin(), end(), id) != end(),
                // Inherited postconditions not checked because of
                // select assertions, plus size unchanged if already present.
                old_found ? size() == old_size : true
            )
    ) {
        if(std::find(begin(), end(), id) == end()) { // Not already present.
            // Unfortunately, must invoke base function via `BODY` macro.
            unique_identifiers::CONTRACT_MEMBER_BODY(add)(id);
        }
    }
};
//]

int main ( void )
{
    //[subcontract_identifiers_duplicate_add
    duplicate_identifiers ids(123);
    ids.add(123);
    //]
    BOOST_TEST(ids.size() == 1); // Not 2 because `add(123)` has no effect.
    ids.add(456);
    BOOST_TEST(ids.size() == 2);
    return boost::report_errors();
}

