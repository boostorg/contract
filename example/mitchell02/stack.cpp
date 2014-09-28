
// Copyright (C) 2008-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://sourceforge.net/projects/contractpp

//[mitchell02_stack
// File: stack.cpp
#include <contract.hpp>
#include <boost/detail/lightweight_test.hpp>
#include <vector>

CONTRACT_CLASS( // Simple stack.
    template( typename T )
    class (stack)
) {
    CONTRACT_CLASS_INVARIANT_TPL( count() >= 0 ) // non-negative count

    // Creation.

    CONTRACT_CONSTRUCTOR_TPL( // Create empty stack.
        public (stack) ( void )
            postcondition( count() == 0 ) // empty
    ) {}

    CONTRACT_DESTRUCTOR_TPL( // Destroy stack.
        public virtual (~stack) ( void )
    ) {}

    // Basic queries.

    CONTRACT_FUNCTION_TPL( // Number of items.
        public int (count) ( void ) const
    ) {
        return items_.size();
    }

    CONTRACT_FUNCTION_TPL( // Item at index in [1, count()] (as in Eiffel).
        public (T const&) (item_at) ( int const index ) const
            precondition(
                index > 0, // positive index
                index <= count() // index within count
            )
    ) {
        return items_.at(index - 1);
    }

    // Derived queries.

    CONTRACT_FUNCTION_TPL( // If no items.
        public bool (is_empty) ( void ) const
            postcondition(
                auto result = return,
                result == (count() == 0) // consistent with count
            )
    ) {
        return count() == 0;
    }

    CONTRACT_FUNCTION_TPL( // Top item.
        public (T const&) (item) ( void ) const
            precondition( count() > 0 ) // not empty
            postcondition(
                auto result = return,
                result == item_at(count()) // item on top
            )
    ) {
        return item_at(count());
    }

    // Commands.

    CONTRACT_FUNCTION_TPL( // Push item to the top.
        public void (put) ( (T const&) new_item )
            postcondition(
                auto old_count = CONTRACT_OLDOF count(),
                count() == old_count + 1, // count increased
                item() == new_item // item set
            )
    ) {
        items_.push_back(new_item);
    }

    CONTRACT_FUNCTION_TPL( // Pop top item.
        public void (remove) ( void )
            precondition( count() > 0 ) // not empty
            postcondition(
                auto old_count = CONTRACT_OLDOF count(),
                count() == old_count - 1 // count decreased
            )
    ) {
        items_.resize(items_.size() - 1);
    }

    private: std::vector<T> items_;
};

int main ( void )
{
    stack<int> s;
    BOOST_TEST(s.count() == 0);
    s.put(123);
    BOOST_TEST(s.item_at(1) == 123);
    s.remove();
    BOOST_TEST(s.is_empty());
    return boost::report_errors();
}
//]

