/**
 * @file
 * @author Copyright (C) 2009 Lorenzo Caminiti.
 *  Distributed under DBC++ Software License (see file LICENSE_1_0.txt).
 */
/* $Id$ */

#ifndef SIMPLE_QUEUE_HPP_
#define SIMPLE_QUEUE_HPP_

#include <dbc.hpp>
#include <vector>

/** Simple queue. */
template<typename T>
class SimpleQueue DBC_INHERIT_OBJECT(SimpleQueue<T>) {
public:
    // Creation //

    /** Create empty queue. */
    SimpleQueue(const int& theCapacity): items_()
    DBC_CONSTRUCTOR( (public) (template)(SimpleQueue)
            ( (const int&)(theCapacity) ), {
        DBC_ASSERT(theCapacity >= 1, "capacity at least 1");
    }, {
        DBC_ASSERT_STREAM(self.now.capacity() == theCapacity.now, 
                "capacity set",
                err << "capacity " << self.now.capacity() << " not set to " 
                << theCapacity.now);
        DBC_ASSERT(self.now.isEmpty(), "is empty");
    }, {
        items_.reserve(theCapacity);
    })

    virtual ~SimpleQueue()
    DBC_DESTRUCTOR( (public) (virtual) (template)(SimpleQueue)(), {})

    // Basic Queries //

    /** Items in queue in their order. */
    const std::vector<T> items() const
    DBC_MEM_FUN( (public) (const std::vector<T>) (template)(SimpleQueue)
            (items)() (const), {
    }, {
    }, { 
        return items_; 
    })

    /** Maximum number of items queue can hold. */
    int capacity() const
    DBC_MEM_FUN( (public) (int) (template)(SimpleQueue) (capacity)() (const), {
    }, {
    }, { 
        return items_.capacity(); 
    })

    // Derived Queries //

    /** Number of items in the queue. */
    int count() const
    DBC_MEM_FUN( (public) (int) (template)(SimpleQueue) (count)() (const), {
    }, {
        DBC_ASSERT(result == int(self.now.items().size()), 
                "result consistent with size");
    }, {
        return items_.size();
    })

    /** Item at the head. */
    const T& head() const
    DBC_MEM_FUN( (public) (const T&) (template)(SimpleQueue) (head)() (const), {
        DBC_ASSERT(!self.isEmpty(), "not empty");
    }, {
        DBC_ASSERT(result == self.now.items().at(0), "result is item's top");
    }, {
        return items_.at(0);
    })

    /** If queue contains no items. */
    bool isEmpty() const
    DBC_MEM_FUN( (public) (bool) (template)(SimpleQueue) (isEmpty)() (const), {
    }, {
        DBC_ASSERT(result == (0 == self.now.count()), 
                "result consistent with count ");
    }, {
        return 0 == items_.size();
    })

    /** If queue has no room for another item. */
    bool isFull() const
    DBC_MEM_FUN( (public) (bool) (template)(SimpleQueue) (isFull)() (const), {
    }, {
        DBC_ASSERT_STREAM(result == (int(self.now.items().size())
                == self.now.capacity()), 
                "result consistent with count and capacity",
                err << "result " << result 
                << " inconsistent with items' count " 
                << self.now.items().size() << " and capacity " 
                << self.now.capacity());
    }, {
        return items_.size() == items_.capacity();
    })

    // Commands //

    /** Remove head item shifting all other items accordingly. */
    void remove()
    DBC_MEM_FUN( (public) (void) (template)DBC_COPYABLE(SimpleQueue) 
            (remove)(), {
        DBC_ASSERT(!self.isEmpty(), "not empty");
    }, {
        DBC_ASSERT(self.now.count() == (self.old.count() - 1), 
                "number of items decreased");

        const std::vector<T>& items = self.now.items();
        const std::vector<T>& oldItems = self.old.items();
        for (size_t i = 1; i < oldItems.size(); ++i) {
            DBC_ASSERT_STREAM(items.at(i - 1) == oldItems.at(i), 
                    "all items shifted",
                    err << "item not shifted from " << i << " to " << (i - 1));
        }
    }, {
        items_.erase(items_.begin());
    })

    /** Add specified item to queue tail. */
    void put(const T& item)
    DBC_MEM_FUN( (public) (void) (template)DBC_COPYABLE(SimpleQueue) 
            (put)( (const T&)(item) ), {
        DBC_ASSERT(self.count() < self.capacity(), 
                "count not filled capacity");
    }, {
        const int& count = self.now.count();
        const int& oldCount = self.old.count();
        DBC_ASSERT(count == (oldCount + 1), "count increased");

        const std::vector<T> items = self.now.items();
        DBC_ASSERT(items.at(count - 1) == item.now, "item at tail");

        // Frame rule.
        const std::vector<T> oldItems = self.old.items();
        if (count >= 2)
            for (int i = 0; i < oldCount; ++i) {
                DBC_ASSERT_STREAM(items.at(i) == oldItems.at(i), 
                        "existing items unchanged",
                        err << "original item at " << i 
                        << " was changed");
            }
    }, {
        items_.push_back(item);
    })

private:
    std::vector<T> items_;
    
    DBC_INVARIANT(SimpleQueue, {
        DBC_ASSERT(self.count() >= 0, "count never negative");
    })
};

#endif // SIMPLE_QUEUE_HPP_

