// Copyright (C) 2009-2010 Lorenzo Caminiti.
// Use, modification, and distribution is subject to the
// Contract++ Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt.)

// Main documentation example that illustrates most library uses.

#ifndef MYVECTOR_HPP_
#define MYVECTOR_HPP_

//[ myvector_cpp

// Base classes for subcontracting.
#include "pushable.hpp"
#include "boundable.hpp"
#include "basic_begin.hpp"
#include <contract.hpp> // This library.
#include <boost/utility.hpp> // For `boost::prior()`.
#include <vector> // STL vector.
    
// Wrapper that adds simple (not complete) contracts to C++ STL illustrating
// most library usages. For simplicity, assume T is comparable and copyable.
template<typename T>
class myvector: public pushable<T>,
        public boundable<typename std::vector<T>::const_iterator>,
        private basic_begin<typename std::vector<T>::const_iterator> {

    // Class invariants (checked by any function with a contract).
    CONTRACT_INVARIANT(
    (static)({ // Static invariants (optional).
        // Static class invariants `(static)({ ... })` are optional and they
        // could have been omitted since they assert nothing in this example.
        // When present, they can only access static members.
    }) ({ // Non-static invariants (can access object).
        CONTRACT_ASSERT( (size() == 0) == empty() );
        // More invariants here...
    }) )

public:
    typedef typename std::vector<T>::size_type size_type;
    typedef typename std::vector<T>::iterator iterator;
    typedef typename std::vector<T>::const_iterator const_iterator;
    typedef typename std::vector<T>::const_reference const_reference;

    // Contract for constructor.
    explicit myvector(size_type count): vector_(count)
    CONTRACT_CONSTRUCTOR( // Constructor contract macro.
            (class) (myvector) // Constructor signature.
            (public) (explicit) (myvector)( (size_type)(count) )
    // Never object `this` in constructor preconditions.
    (postcondition) ({
        // Never `CONTRACT_OLDOF(this)` in constructor postconditions.
        CONTRACT_ASSERT( size() == count );
    })
    (body) ({
        // Do nothing in this case.
    }) )

    // Contractor for overloaded member (resolved by argumnet name).
    myvector(const myvector& right)
    CONTRACT_CONSTRUCTOR( (class) (myvector)
            (public) (myvector)( (const myvector&)(right) )
    (postcondition) ({
        CONTRACT_ASSERT( vector_ == right.vector_ );
    })
    (body) (;) ) // Deferres body definition.

    // Contract for destructor.
    virtual ~myvector(void)
    CONTRACT_DESTRUCTOR( // Destructor contract macro.
            (class) (myvector) // Destructor signature.
            // Must use `(void)` for no arguments.
            (public) (virtual) (myvector)( (void) )
    // No preconditions allowed (no arguments).
    // No postconditions allowed (no object after destructor).
    (body) (;) )

    // Contract for member function.
    void insert(iterator where, size_type count, const T& element)
    CONTRACT_FUNCTION( // Function contract macro.
            (class) (copyable)(myvector) // Function signature.
            // Old values for object `this` and argument `where`.
            (public) (void) (insert)( (copyable)(iterator)(where)
                    (size_type)(count) (const T&)(element) )
    (precondition) ({ // Function preconditions (optional).
        CONTRACT_ASSERT( (size() + count) <= max_size() );
        // More preconditions here...
    })
    (postcondition) ({ // Function postconditions (optional).
        // Any C++ code allowed in contracts (but keep it simple).
        // Old values of types tagged copyable via `CONTRACT_OLDOF()`.
        if (capacity() == CONTRACT_OLDOF(this)->capacity()) {
            CONTRACT_ASSERT( all_equals(
                    boost::prior(CONTRACT_OLDOF(where)),
                    boost::prior(CONTRACT_OLDOF(where)) + count,
                    element) );
        }
        // More postconditions here...
    })
    (body) ({ // Function body (mandatory).
        vector_.insert(where, count, element);
    }) )

    // Contract for constant member.
    const_iterator begin(void) const
    CONTRACT_FUNCTION( (class) (myvector)
            // Subcontracting for multiple inheritance.
            (inherit)(boundable<const_iterator>)
            (inherit)(basic_begin<const_iterator>)
            (public) (const_iterator) // Non-void result type.
            (begin)( (void) ) (const) // Constant.
    (postcondition) (result) ({ // Named result value.
        if (empty()) CONTRACT_ASSERT( result == end() );
    })
    (body) ({
        return vector_.begin();
    }) )
    
    // Contract for overloaded member (resolved because not const).
    iterator begin(void)
    CONTRACT_FUNCTION( (class) (myvector) (public)
            (iterator) (begin)( (void) )
    (postcondition) (result) ({
        if (empty()) CONTRACT_ASSERT( result == end() );
    })
    (body) (
        ;
    ) )
    
    // Contract for operator.
    const_reference operator[](size_type index) const
    CONTRACT_FUNCTION( (class) (myvector)
            // Must spell operator name also in words).
            (public) (const_reference) (operator([], at))(
                    (size_type)(index) ) (const)
    (precondition) ({
        CONTRACT_ASSERT( index < size() );
    })
    (body) (;) )

    // Main function example used in documentation.
    void push_back(const T& element)
    CONTRACT_FUNCTION(
            (class) (copyable)(myvector) (inherit)(pushable<T>)
            (public) (void) (push_back)( (const T&)(element) )
    (precondition) ({
        CONTRACT_ASSERT( size() < max_size() );
    })
    (postcondition) ({
        CONTRACT_ASSERT( size() == (CONTRACT_OLDOF(this)->size() + 1) );
    })
    (body) ({
        vector_.push_back(element);
    }) )
    
    // Contract for template plus static member function.
    template<class Iter>
    static bool all_equals(Iter first, Iter last, const T& element)
    CONTRACT_FUNCTION( (class) (myvector)
            (public) (template)( (class)(Iter) ) // Function template.
            (static) (bool) (all_equals)( // Static member.
                    (Iter)(first) (Iter)(last) (const T&)(element) )
    (precondition) ({
        CONTRACT_ASSERT( first < last );
    })
    (body) ({
        // For simplicity, let's assume T can be compared.
        for (Iter i = first; i < last; ++i) {
            if (*i != element) return false;
        }
        return true;
    }) )

    // Similarly, complete contracts sketched here and add contracts
    // for all other functions (see [Crowl2006] vector example).
    bool empty(void) const { return vector_.empty(); }
    size_type size(void) const { return vector_.size(); }
    size_type max_size(void) const { return vector_.max_size(); }
    size_type capacity(void) const { return vector_.capacity(); }
    iterator end(void) { return vector_.end(); }
    const_iterator end(void) const { return vector_.end(); }
    const_reference back(void) const { return vector_.back(); }

private:
    std::vector<T> vector_;
};

// Deferred constructor body definition.
template<typename T>
CONTRACT_CONSTRUCTOR_BODY(myvector<T>, myvector)(
        const myvector& right) {
    vector_ = right.vector_;
}

// Deferred destructor body definition.
template<typename T>
CONTRACT_DESTRUCTOR_BODY(myvector<T>, myvector)(void) {
    // Do nothing in this case.
}

// Deferred member function definition.
template<typename T>
typename myvector<T>::iterator myvector<T>::CONTRACT_BODY(begin)(
        void) {
    return vector_.begin();
}

// Deferred member operator definition.
template<typename T>
typename myvector<T>::const_reference myvector<T>::
        CONTRACT_BODY(operator([], at))(
        size_type index) const {
    return vector_[index];
}

// Contract for non-member function.
double abs_total(const myvector<double>& vector)
CONTRACT_FUNCTION(
        (double) (abs_total)( (const myvector<double>&)(vector) )
(postcondition) (total) ({ // Result value named `total`.
    CONTRACT_ASSERT( total >= 0.0 );
})
(body) ({
    double total = 0.0;
    // Block invariants can appear anywhere in code block.
    CONTRACT_ASSERT_BLOCK_INVARIANT( total == 0.0 );

    { // Variant initialized locally to its loop.
        CONTRACT_INIT_LOOP_VARIANT;
        for (size_t i = 0; i < vector.size(); ++i) {
            // Block invariants used to assert loop invariants.
            CONTRACT_ASSERT_BLOCK_INVARIANT( i < vector.size() );
            // Loop variant (can only appear in loops).
            CONTRACT_ASSERT_LOOP_VARIANT( vector.size() - i );

            total += vector[i];
        }
    }
    return total < 0.0 ? -total : total;
}) )

//]

#endif // #include guard

