
// Copyright (C) 2008-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://sourceforge.net/projects/contractpp

//[mitchell02_simple_queue
// File: simple_queue.cpp
#include <contract.hpp>
#include <boost/detail/lightweight_test.hpp>
#include <vector>

// Assertion requirements used to model assertion computational complexity.
#define O_1 0   // O(1) constant (default)
#define O_N 1   // O(n) linear
#define COMPLEXITY_MAX O_1

CONTRACT_CLASS(
    template( typename T )
    class (simple_queue)
) {
    CONTRACT_CLASS_INVARIANT( count() >= 0 ) // non-negative count

    // Creation.

    CONTRACT_CONSTRUCTOR_TPL( // Create empty queue.
        public explicit (simple_queue) ( int const the_capacity )
            precondition( the_capacity > 0 ) // positive capacity
            postcondition(
                capacity() == the_capacity, // capacity set
                is_empty() // empty
            )
    ) {
        items_.reserve(the_capacity);
    }

    CONTRACT_DESTRUCTOR_TPL( // Destroy queue.
        public virtual (~simple_queue) ( void )
    ) {}

    // Basic queries.

    CONTRACT_FUNCTION_TPL( // Items in the queue (in their order).
        public (std::vector<T> const&) (items) ( void ) const
    ) {
        return items_;
    }

    CONTRACT_FUNCTION_TPL( // Max number of items queue can hold.
        public int (capacity) ( void ) const
    ) {
        return items_.capacity();
    }

    // Derived queries.

    CONTRACT_FUNCTION_TPL( // Number of items.
        public int (count) ( void ) const
            postcondition(
                auto result = return,
                result == int(items().size()) // return items count
            )
    ) {
        return items_.size();
    }

    CONTRACT_FUNCTION_TPL( // Item at head.
        public (T const&) (head) ( void ) const
            precondition( not is_empty() )
            postcondition(
                auto result = return,
                result == items().at(0) // return item on top
            )
    ) {
        return items_.at(0);
    }

    CONTRACT_FUNCTION_TPL( // If queue contains no item.
        public bool (is_empty) ( void ) const
            postcondition(
                auto result = return,
                result == (count() == 0) // consistent with count
            )
    ) {
        return items_.size() == 0;
    }

    CONTRACT_FUNCTION_TPL( // If queue has no room for another item.
        public bool (is_full) ( void ) const
            postcondition(
                auto result = return,
                // consistent with size and capacity
                result == (capacity() == int(items().size()))
            )
    ) {
        return items_.size() == items_.capacity();
    }

    // Commands.

    CONTRACT_FUNCTION_TPL( // Remove head item and shift all other items.
        public void (remove) ( void )
            precondition( not is_empty() )
            postcondition(
                auto old_count = CONTRACT_OLDOF count(),
                auto old_items = CONTRACT_OLDOF items(),
                count() == old_count - 1, // count decreased
                // Expensive assertion to check so marked with its complexity.
                all_equal(items(), old_items, 1 /* shifted */),
                        requires O_N <= COMPLEXITY_MAX
            )
    ) {
        items_.erase(items_.begin());
    }

    CONTRACT_FUNCTION_TPL( // Add item to tail.
        public void (put) ( (T const&) item )
            precondition( count() < capacity() )
            postcondition(
                auto old_count = CONTRACT_OLDOF count(),
                auto old_items = CONTRACT_OLDOF items(),
                count() == old_count + 1, // count increased
                items().at(count() - 1) == item, // second last item
                if(count() >= 2) (
                    // Computationally expensive assertion to check.
                    all_equal(items(), old_items),
                            requires O_N <= COMPLEXITY_MAX
                )
            )
    ) {
        items_.push_back(item);
    }

    CONTRACT_FUNCTION_TPL( // Contract helper.
        private static bool (all_equal) (
                (std::vector<T> const&) left,
                (std::vector<T> const&) right,
                size_t offset, default 0 
            )
            precondition(
                right.size() == left.size() + offset // correct offset
            )
    ) {
        for(size_t i = offset; i < right.size(); ++i)
            if(left.at(i - offset) != right.at(i)) return false;
        return true;
    }

    private: std::vector<T> items_;
};

int main ( void )
{
    simple_queue<int> q(10);
    q.put(123);
    q.put(456);
    std::vector<int> const& items = q.items();
    BOOST_TEST(items[0] == 123);
    BOOST_TEST(items[1] == 456);
    BOOST_TEST(q.capacity() == 10);
    BOOST_TEST(q.head() == 123);
    BOOST_TEST(not q.is_empty());
    BOOST_TEST(not q.is_full());
    q.remove();
    BOOST_TEST(q.count() == 1);
    return boost::report_errors();
}
//]

