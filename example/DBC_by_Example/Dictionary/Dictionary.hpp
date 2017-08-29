/**
 * @file
 * @author Copyright (C) 2009 Lorenzo Caminiti.
 *  Distributed under DBC++ Software License (see file LICENSE_1_0.txt).
 */
/* $Id$ */

#ifndef DICTIONARY_HPP_
#define DICTIONARY_HPP_

#include <dbc.hpp>
#include <map>

/** Simple dictionary. */
template<typename Key, typename Value>
class Dictionary DBC_INHERIT_OBJECT(DBC_MPARAM(2, (Dictionary<Key, Value>))) {
public:
    // Creation //

    /** Create an empty dictionary. */
    Dictionary()
    DBC_CONSTRUCTOR( (public) (template)(Dictionary)(), {
    }, {
        DBC_ASSERT(0 == self.now.count(), "is empty");
    }, {})

    virtual ~Dictionary()
    DBC_DESTRUCTOR( (public) (virtual) (template)(Dictionary)(), {})

    // Basic Queries //

    /** Number of keys in dictionary. */
    int count() const 
    DBC_MEM_FUN( (public) (int) (template)(Dictionary) (count)() (const), {
    }, {
        DBC_ASSERT(result >= 0, "returning non-negative");
    }, { 
        return items_.size(); 
    })

    /** If the dictionary contain specified key. */
    bool has(const Key& key) const
    DBC_MEM_FUN( (public) (bool) (template)(Dictionary) 
            (has)( (const Key&)(key) ) (const), {
    }, {
        if (0 == self.now.count()) DBC_ASSERT(!result, "if empty, has no key");
    }, {
        return items_.end() != items_.find(key);
    })

    /** Value associated with specified key. */
    const Value& valueFor(const Key& key) const
    DBC_MEM_FUN( (public) (const Value&) (template)(Dictionary) 
            (valueFor)( (const Key&)(key) ) (const), {
        DBC_ASSERT(self.has(key), "key in dictionary");
    }, {
    }, {
        return items_.find(key)->second;
    })

    // Commands //

    /** Put specified key into dictionary with specified value. */
    void put(const Key& key, const Value& value)
    DBC_MEM_FUN( (public) (void) (template)DBC_COPYABLE(Dictionary)
            (put)( (const Key&)(key) (const Value&)(value) ), {
        DBC_ASSERT(!self.has(key), "key not in dictionary");
    }, {
        DBC_ASSERT_STREAM(self.now.count() == (self.old.count() + 1),
                "one more value",
                err << "count " << self.now.count() << " not increased from "
                << self.old.count());
        DBC_ASSERT(self.now.has(key.now), "key in dictionary");
        DBC_ASSERT(self.now.valueFor(key.now) == value.now, 
                "set value for key");
    }, {
        items_[key] = value;
    })

    /** Remove specified key and its value from dictionary. */
    void remove(const Key& key)
    DBC_MEM_FUN( (public) (void) (template)DBC_COPYABLE(Dictionary)
            (remove)( (const Key&)(key) ), {
        DBC_ASSERT(self.has(key), "key in dictionary");
    }, {
        DBC_ASSERT(self.now.count() == (self.old.count() - 1), 
                "count decreased");
        DBC_ASSERT(!self.now.has(key.now), "key not in dictionary");
    }, {
        items_.erase(key);
    })

private:
    std::map<Key, Value> items_;
    
    DBC_INVARIANT(Dictionary, {
        DBC_ASSERT_STREAM(self.count() >= 0, "never negative",
                err << "count " << self.count() << " is negative");
    })
};

#endif // DICTIONARY_HPP_

