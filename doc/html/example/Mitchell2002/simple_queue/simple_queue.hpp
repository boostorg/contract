// Copyright (C) 2009-2010 Lorenzo Caminiti.
// Use, modification, and distribution is subject to the
// Contract++ Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt.)

// Contracts for an Eiffel-like simple queue (ported from Eiffel code).

#ifndef SIMPLE_QUEUE_HPP_
#define SIMPLE_QUEUE_HPP_

#include <contract.hpp>
#include <vector>

/** Simple queue. */
template<typename T>
class simple_queue {

    CONTRACT_INVARIANT( ({
        CONTRACT_ASSERT( count() >= 0 );
    }) )

public:
    // Creation //

    /** Create empty queue. */
    simple_queue(const int& the_capacity): items_()
    CONTRACT_CONSTRUCTOR( (class) (simple_queue)
            (public) (simple_queue)( (const int&)(the_capacity) )
    (precondition) ({
        CONTRACT_ASSERT( the_capacity >= 1 );
    })
    (postcondition) ({
        CONTRACT_ASSERT( capacity() == the_capacity );
        CONTRACT_ASSERT( is_empty() );
    })
    (body) ({
        items_.reserve(the_capacity);
    }) )

    /** Destroy queue. */
    virtual ~simple_queue(void)
    CONTRACT_DESTRUCTOR( (class) (simple_queue)
            (public) (virtual) (simple_queue)( (void) )
    (body) ({
    }) )

    // Basic Queries //

    /** Items in the queue (in their order). */
    const std::vector<T>& items(void) const
    CONTRACT_FUNCTION( (class) (simple_queue)
            (public) (const std::vector<T>&) (items)( (void) ) (const)
    (body) ({
        return items_;
    }) )

    /** Maximum number of items queue can hold. */
    int capacity(void) const
    CONTRACT_FUNCTION( (class) (simple_queue)
            (public) (int) (capacity)( (void) ) (const)
    (body) ({
        return items_.capacity();
    }) )

    // Derived Queries //

    /** Number of items. */
    int count(void) const
    CONTRACT_FUNCTION( (class) (simple_queue)
            (public) (int) (count)( (void) ) (const)
    (postcondition) (result) ({
        CONTRACT_ASSERT( result == int(items().size()) );
    })
    (body) ({
        return items_.size();
    }) )

    /** Item at head. */
    const T& head(void) const
    CONTRACT_FUNCTION( (class) (simple_queue)
            (public) (const T&) (head)( (void) ) (const)
    (precondition) ({
        CONTRACT_ASSERT( !is_empty() );
    })
    (postcondition) (result) ({
        CONTRACT_ASSERT( result == items().at(0) );
    })
    (body) ({
        return items_.at(0);
    }) )

    /** If queue contains no items. */
    bool is_empty(void) const
    CONTRACT_FUNCTION( (class) (simple_queue)
            (public) (bool) (is_empty)( (void) ) (const)
    (postcondition) (result) ({
        CONTRACT_ASSERT( result == (0 == count()) );
    })
    (body) ({
        return 0 == items_.size();
    }) )

    /** If queue has no room for another item. */
    bool is_full(void) const
    CONTRACT_FUNCTION( (class) (simple_queue)
            (public) (bool) (is_full)( (void) ) (const)
    (postcondition) (result) ({
        CONTRACT_ASSERT( result ==
                (int(items().size()) == capacity()) );
    })
    (body) ({
        return items_.size() == items_.capacity();
    }) )

    // Commands //

    /** Remove head item shifting all other items accordingly. */
    void remove(void)
    CONTRACT_FUNCTION( (class) (copyable)(simple_queue)
            (public) (void) (remove)( (void) )
    (precondition) ({
        CONTRACT_ASSERT( !is_empty() );
    })
    (postcondition) ({
        CONTRACT_ASSERT( count() ==
                (CONTRACT_OLDOF(this)->count() - 1) );

        for (size_t i = 1; i < CONTRACT_OLDOF(this)->items().size();
                ++i) 
            CONTRACT_ASSERT( items().at(i - 1) ==
                    CONTRACT_OLDOF(this)->items().at(i) );
    })
    (body) ({
        items_.erase(items_.begin());
    }) )

    /** Add item to tail. */
    void put(const T& item)
    CONTRACT_FUNCTION( (class) (copyable)(simple_queue)
            (public) (void) (put)( (const T&)(item) )
    (precondition) ({
        CONTRACT_ASSERT( count() < capacity() );
    })
    (postcondition) ({
        CONTRACT_ASSERT( count() ==
                (CONTRACT_OLDOF(this)->count() + 1) );
        CONTRACT_ASSERT( items().at(count() - 1) == item );
        if (count() >= 2) {
            for (int i = 0; i < CONTRACT_OLDOF(this)->count(); ++i) {
                CONTRACT_ASSERT( items().at(i) ==
                        CONTRACT_OLDOF(this)->items().at(i) );
            }
        }
    })
    (body) ({
        items_.push_back(item);
    }) )

private:
    std::vector<T> items_;
};

#endif // #include guard

