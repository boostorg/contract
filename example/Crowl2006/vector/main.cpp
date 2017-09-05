// Copyright (C) 2009-2010 Lorenzo Caminiti.
// Use, modification, and distribution is subject to the
// Contract++ Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt.)

// Add complete contracts to STL C++ vector.

#include <contract.hpp>
#include <boost/utility.hpp> // For boost::prior().
#include <vector>

// Tools to write the contracts (for convenience).

template<class Iter, class T>
bool all_equals(Iter first, Iter last, const T& val)
CONTRACT_FUNCTION(
        (template)( (class)(Iter) (class)(T) )
        (bool) (all_equals)(
                (Iter)(first) (Iter)(last) (const T&)(val) )
(body) ({
    // For simplicity, let's assume T can be compared.
    for (Iter i = first; i < last; ++i) {
        if (*i != val) return false;
    }
    return true;
}) )

template<class Iter, class Size>
bool equal_distance(Iter first, Iter last, Size size)
CONTRACT_FUNCTION(
        (template)( (class)(Iter) (class)(Size) )
        (bool) (equal_distance)(
                (Iter)(first) (Iter)(last) (Size)(size) )
(body) ({
    // Could implement internal tagging to support input iterators.
    return int(size) == std::distance(first, last);
}) )

// New vector interface.

template<class T, class Alloc = std::allocator<T> >
class vector {

    CONTRACT_INVARIANT( ({
        CONTRACT_ASSERT( (size() == 0) == empty() );
        CONTRACT_ASSERT( int(size()) == std::distance(begin(), end()) );
        CONTRACT_ASSERT( int(size()) == std::distance(rbegin(), rend()) );
        CONTRACT_ASSERT( size() <= capacity() );
        CONTRACT_ASSERT( capacity() <= max_size() );
    }) )

public:
    typedef typename std::vector<T, Alloc>::size_type size_type;
    typedef typename std::vector<T, Alloc>::iterator iterator;
    typedef typename std::vector<T, Alloc>::const_iterator
            const_iterator;
    typedef typename std::vector<T, Alloc>::reverse_iterator
            reverse_iterator;
    typedef typename std::vector<T, Alloc>::const_reverse_iterator
            const_reverse_iterator;
    typedef typename std::vector<T, Alloc>::reference reference;
    typedef typename std::vector<T, Alloc>::const_reference
            const_reference;

    vector(void): vector_()
    CONTRACT_CONSTRUCTOR( (class) (vector)
            (public) (vector)( (void) )
    (postcondition) ({
        CONTRACT_ASSERT( empty() );
    })
    (body) ({
    }) )

    explicit vector(const Alloc& al): vector_(al)
    CONTRACT_CONSTRUCTOR( (class) (vector)
            (public) (explicit) (vector)( (const Alloc&)(al) )
    (postcondition) ({
        CONTRACT_ASSERT( empty() );
        CONTRACT_ASSERT( al == get_allocator() );
    })
    (body) ({
    }) )

    explicit vector(size_type count): vector_(count)
    CONTRACT_CONSTRUCTOR( (class) (vector)
            (public) (explicit) (vector)( (size_type)(count) )
    (postcondition) ({
        CONTRACT_ASSERT( size() == count );
        CONTRACT_ASSERT( all_equals(begin(), end(), T()) );
    })
    (body) ({
    }) )

    vector(size_type count, const T& val): vector_(count, val)
    CONTRACT_CONSTRUCTOR( (class) (vector)
            (public) (vector)( (size_type)(count) (const T&)(val) )
    (postcondition) ({
        CONTRACT_ASSERT( size() == count );
        CONTRACT_ASSERT( all_equals(begin(), end(), val) );
    })
    (body) ({
    }) )
    
    vector(size_type count, const T& val, const Alloc& al):
            vector_(count, val, al)
    CONTRACT_CONSTRUCTOR( (class) (vector)
            (public) (vector)( (size_type)(count) (const T&)(val) 
                    (const Alloc&)(al) )
    (postcondition) ({
        CONTRACT_ASSERT( size() == count );
        CONTRACT_ASSERT( all_equals(begin(), end(), val) );
        CONTRACT_ASSERT( al == get_allocator() );
    })
    (body) ({
    }) )

    vector(const vector& right): vector_(right.vector_)
    CONTRACT_CONSTRUCTOR( (class) (vector)
            (public) (vector)( (const vector&)(right) )
    (postcondition) ({
        CONTRACT_ASSERT( right == *this );
    })
    (body) ({
    }) )

    template<class InIt>
    vector(InIt first, InIt last): vector_(first, last)
    CONTRACT_CONSTRUCTOR( (class) (vector)
            (public) (template)( (class)(InIt) )
            (vector)( (InIt)(first) (InIt)(last) )
    (postcondition) ({
        CONTRACT_ASSERT( equal_distance(first, last, size()) );
    })
    (body) ({
    }) )
    
    template<class InIt>
    vector(InIt first, InIt last, const Alloc& al):
            vector_(first, last, al)
    CONTRACT_CONSTRUCTOR( (class) (vector)
            (public) (template)( (class)(InIt) )
            (vector)( (InIt)(first) (InIt)(last) (const Alloc&)(al) )
    (postcondition) ({
        CONTRACT_ASSERT( equal_distance(first, last, size()) );
        CONTRACT_ASSERT( al == get_allocator() );
    })
    (body) ({
    }) )

    ~vector(void) // Contracted so destructor checks invariants.
    CONTRACT_DESTRUCTOR( (class) (vector)
            (public) (vector)( (void) )
    (body) ({
    }) )

    void reserve(size_type count)
    CONTRACT_FUNCTION( (class) (vector)
            (public) (void) (reserve)( (size_type)(count) )
    (precondition) ({
        CONTRACT_ASSERT( count < max_size() );
    })
    (postcondition) ({
        CONTRACT_ASSERT( capacity() >= count );
    })
    (body) ({
        vector_.reserve(count);
    }) )

    size_type capacity(void) const
    CONTRACT_FUNCTION( (class) (vector)
            (public) (size_type) (capacity)( (void) ) (const)
    (postcondition) (result) ({
        CONTRACT_ASSERT( result >= size() );
    })
    (body) ({
        return vector_.capacity();
    }) )
    
    iterator begin(void)
    CONTRACT_FUNCTION( (class) (vector)
            (public) (iterator) (begin)( (void) )
    (postcondition) (result) ({
        if (empty()) CONTRACT_ASSERT( result == end() );
    })
    (body) ({
        return vector_.begin();
    }) )

    const_iterator begin(void) const
    CONTRACT_FUNCTION( (class) (vector)
            (public) (const_iterator) (begin)( (void) ) (const)
    (postcondition) (result) ({
        if (empty()) CONTRACT_ASSERT( result == end() );
    })
    (body) ({
        return vector_.begin();
    }) )
    
    iterator end(void)
    CONTRACT_FUNCTION( (class) (vector)
            (public) (iterator) (end)( (void) )
    // Contracted even if no pre/post condition so check invariants.
    (body) ({
        return vector_.end();
    }) )
    
    const_iterator end(void) const
    CONTRACT_FUNCTION( (class) (vector)
            (public) (const_iterator) (end)( (void) ) (const)
    (body) ({
        return vector_.end();
    }) )
    
    reverse_iterator rbegin(void)
    CONTRACT_FUNCTION( (class) (vector)
            (public) (reverse_iterator) (rbegin)( (void) )
    (postcondition) (result) ({
        if (empty()) CONTRACT_ASSERT( result == rend() );
    })
    (body) ({
        return vector_.rbegin();
    }) )

    const_reverse_iterator rbegin(void) const
    CONTRACT_FUNCTION( (class) (vector)
            (public) (const_reverse_iterator) (rbegin)( (void) ) (const)
    (postcondition) (result) ({
        if (empty()) CONTRACT_ASSERT( result == rend() );
    })
    (body) ({
        return vector_.rbegin();
    }) )
    
    reverse_iterator rend(void)
    CONTRACT_FUNCTION( (class) (vector)
            (public) (reverse_iterator) (rend)( (void) )
    (body) ({
        return vector_.rend();
    }) )
    
    const_reverse_iterator rend(void) const
    CONTRACT_FUNCTION( (class) (vector)
            (public) (const_reverse_iterator) (rend)( (void) ) (const)
    (body) ({
        return vector_.rend();
    }) )

    void resize(size_type newsize)
    CONTRACT_FUNCTION( (class) (copyable)(vector)
            (public) (void) (resize)( (size_type)(newsize) )
    (postcondition) ({
        CONTRACT_ASSERT( size() == newsize );
        // Version 1: with an if.
        if (newsize > CONTRACT_OLDOF(this)->size()) CONTRACT_ASSERT(
                all_equals(begin() + CONTRACT_OLDOF(this)->size(),
                end(), T()) );
    })
    (body) ({
        vector_.resize(newsize);
    }) )

    void resize(size_type newsize, T val)
    CONTRACT_FUNCTION( (class) (copyable)(vector)
            (public) (void) (resize)( (size_type)(newsize) (T)(val) )
    (postcondition) ({
        CONTRACT_ASSERT( size() == newsize );
        // Version 2: with a ternary operator.
        CONTRACT_ASSERT( newsize > CONTRACT_OLDOF(this)->size() ? 
                all_equals(begin() + CONTRACT_OLDOF(this)->size(),
                end(), val) : true );
    })
    (body) ({
        vector_.resize(newsize, val);
    }) )
    
    size_type size(void) const
    CONTRACT_FUNCTION( (class) (vector)
            (public) (size_type) (size)( (void) ) (const)
    (postcondition) (result) ({
        CONTRACT_ASSERT( result <= capacity() );
    })
    (body) ({
        return vector_.size();
    }) )
    
    size_type max_size(void) const
    CONTRACT_FUNCTION( (class) (vector)
            (public) (size_type) (max_size)( (void) ) (const)
    (postcondition) (result) ({
        CONTRACT_ASSERT( result >= capacity() );
    })
    (body) ({
        return vector_.max_size();
    }) )

    bool empty(void) const
    CONTRACT_FUNCTION( (class) (vector)
            (public) (bool) (empty)( (void) ) (const)
    (postcondition) (result) ({
        CONTRACT_ASSERT( result == (size() == 0) );
    })
    (body) ({
        return vector_.empty();
    }) )

    Alloc get_allocator(void) const
    CONTRACT_FUNCTION( (class) (vector)
            (public) (Alloc) (get_allocator)( (void) ) (const)
    (body) ({
        return vector_.get_allocator();
    }) )

    reference at(size_type off)
    CONTRACT_FUNCTION( (class) (vector)
            (public) (reference) (at)( (size_type)(off) )
    (precondition) ({
        CONTRACT_ASSERT( off < size() );
    })
    (body) ({
        return at(off);
    }) )
    
    const_reference at(size_type off) const
    CONTRACT_FUNCTION( (class) (vector)
            (public) (const_reference) (at)( (size_type)(off) )
            (const)
    (precondition) ({
        CONTRACT_ASSERT( off < size() );
    })
    (body) ({
        return at(off);
    }) )

    reference operator[](size_type off)
    CONTRACT_FUNCTION( (class) (vector)
            (public) (reference) (operator_at)( (size_type)(off) )
    (precondition) ({
        CONTRACT_ASSERT( off < size() );
    })
    (body) ({
        return operator[](off);
    }) )

    const_reference operator[](size_type off) const
    CONTRACT_FUNCTION( (class) (vector)
            (public) (const_reference) (operator_at)(
                    (size_type)(off) ) (const)
    (precondition) ({
        CONTRACT_ASSERT( off < size() );
    })
    (body) ({
        return operator[](off);
    }) )

    reference front(void)
    CONTRACT_FUNCTION( (class) (vector)
            (public) (reference) (front)( (void) )
    (precondition) ({
        CONTRACT_ASSERT( !empty() );
    })
    (body) ({
        return vector_.front();
    }) )

    const_reference front(void) const
    CONTRACT_FUNCTION( (class) (vector)
            (public) (const_reference) (front)( (void) ) (const)
    (precondition) ({
        CONTRACT_ASSERT( !empty() );
    })
    (body) ({
        return vector_.front();
    }) )

    reference back(void)
    CONTRACT_FUNCTION( (class) (vector)
            (public) (reference) (back)( (void) )
    (precondition) ({
        CONTRACT_ASSERT( !empty() );
    })
    (body) ({
        return vector_.back();
    }) )

    const_reference back(void) const
    CONTRACT_FUNCTION( (class) (vector)
            (public) (const_reference) (back)( (void) ) (const)
    (precondition) ({
        CONTRACT_ASSERT( !empty() );
    })
    (body) ({
        return vector_.back();
    }) )

    void push_back(const T& val)
    CONTRACT_FUNCTION( (class) (copyable)(vector)
            (public) (void) (push_back)( (const T&)(val) )
    (precondition) ({
        CONTRACT_ASSERT( size() < max_size() );
    })
    (postcondition) ({
        CONTRACT_ASSERT( back() == val );
        CONTRACT_ASSERT( size() == (CONTRACT_OLDOF(this)->size() + 1) );
        CONTRACT_ASSERT( capacity() >= CONTRACT_OLDOF(this)->capacity() );
    })
    (body) ({
        vector_.push_back(val);
    }) )

    void pop_back(void)
    CONTRACT_FUNCTION( (class) (copyable)(vector)
            (public) (void) (pop_back)( (void) )
    (precondition) ({
        CONTRACT_ASSERT( !empty() );
    })
    (postcondition) ({
        CONTRACT_ASSERT( size() == (CONTRACT_OLDOF(this)->size() - 1) );
    })
    (body) ({
        vector_.pop_back();
    }) )

    template<class InIt>
    void assign(InIt first, InIt last)
    CONTRACT_FUNCTION( (class) (vector)
            (public) (template)( (class)(InIt) )
            (void) (assign)( (InIt)(first) (InIt)(last) )
    (precondition) ({
        /** @pre [first, last) not sub-range of [begin(), end()). */
    })
    (postcondition) ({
        CONTRACT_ASSERT( equal_distance(first, last, size()) );
    })
    (body) ({
        vector_.assign(first, last);
    }) )

    void assign(size_type count, const T& val)
    CONTRACT_FUNCTION( (class) (vector)
            (public) (void) (assign)(
                    (size_type)(count) (const T&)(val) )
    (precondition) ({
        CONTRACT_ASSERT( count <= max_size() );
    })
    (postcondition) ({
        CONTRACT_ASSERT( all_equals(begin(), end(), val) );
    })
    (body) ({
        vector_.assign(count, val);
    }) )

    iterator insert(iterator where, const T& val)
    CONTRACT_FUNCTION( (class) (copyable)(vector)
            (public) (iterator) (insert)(
                    (iterator)(where) (const T&)(val) )
    (precondition) ({
        CONTRACT_ASSERT( size() < max_size() );
    })
    (postcondition) (result) ({
        CONTRACT_ASSERT( *result == val );
        CONTRACT_ASSERT( size() == (CONTRACT_OLDOF(this)->size() + 1) );
        CONTRACT_ASSERT( capacity() >= CONTRACT_OLDOF(this)->capacity() );
        /** @post
         *  if capacity() > oldof capacity():
         *      all iterators invalidated
         *  else:
         *      all iterators in [where, end()) invalidated
         */
    })
    (body) ({
        return vector_.insert(where, val);
    }) )
    
    void insert(iterator where, size_type count, const T& val)
    CONTRACT_FUNCTION( (class) (copyable)(vector)
            (public) (void) (insert)( (copyable)(iterator)(where)
                    (size_type)(count) (const T&)(val) )
    (precondition) ({
        CONTRACT_ASSERT( (size() + count) < max_size() );
    })
    (postcondition) ({
        CONTRACT_ASSERT( size() ==
                (CONTRACT_OLDOF(this)->size() + count) );
        CONTRACT_ASSERT( capacity() >= CONTRACT_OLDOF(this)->capacity() );
        if (capacity() == CONTRACT_OLDOF(this)->capacity()) {
            CONTRACT_ASSERT( all_equals(
                    boost::prior(CONTRACT_OLDOF(where)),
                    boost::prior(CONTRACT_OLDOF(where)) + count,
                    val) );
            /** @post All iterators in [where, end()) invalidated. */
        }
        else {
            /** @post All iterators invalidated. */
        }
    })
    (body) ({
        vector_.insert(where, val);
    }) )

    template<class InIt>
    void insert(iterator where, InIt first, InIt last)
    CONTRACT_FUNCTION( (class) (copyable)(vector)
            (public) (template)( (class)(InIt) )
            (void) (insert)( (copyable)(iterator)(where)
                    (InIt)(first) (InIt)(last) )
    (precondition) ({
        /** @pre [first, last) not a sub-range or [begin(), end()). */
        int count = std::distance(first, last);
        CONTRACT_ASSERT( (size() + count) < max_size() );
    })
    (postcondition) ({
        int count = std::distance(first, last);
        CONTRACT_ASSERT( size() ==
                (CONTRACT_OLDOF(this)->size() + count) );
        CONTRACT_ASSERT( capacity() >= CONTRACT_OLDOF(this)->capacity() );
    })
    (body) ({
        return vector_.insert(where, first, last);
    }) )

    iterator erase(iterator where)
    CONTRACT_FUNCTION( (class) (copyable)(vector)
            (public) (iterator) (erase)( (iterator)(where) )
    (precondition) ({
        CONTRACT_ASSERT( !empty() );
        CONTRACT_ASSERT( where != end() );
    })
    (postcondition) (result) ({
        CONTRACT_ASSERT( size() == (CONTRACT_OLDOF(this)->size() - 1) );
        if (empty()) CONTRACT_ASSERT( result == end() );
        /** @post Iterators in [where, end()) invalidated. */
    })
    (body) ({
        return vector_.erase(where);
    }) )

    iterator erase(iterator first, iterator last)
    CONTRACT_FUNCTION( (class) (copyable)(vector)
            (public) (iterator) (erase)( (iterator)(first)
                    (iterator)(last) )
    (precondition) ({
        CONTRACT_ASSERT( size() >= std::distance(first, last) );
    })
    (postcondition) (result) ({
        CONTRACT_ASSERT( size() == (CONTRACT_OLDOF(this)->size() -
                std::distance(first, last)) );
        if (empty()) CONTRACT_ASSERT( result == end() );
        /** @post Iterators in [first, end()) invalidated. */
    })
    (body) ({
        return vector_.erase(first, last);
    }) )

    void clear(void)
    CONTRACT_FUNCTION( (class) (vector)
            (public) (void) (clear)( (void) )
    (postcondition) ({
        CONTRACT_ASSERT( empty() );
    })
    (body) ({
        vector_.clear();
    }) )

    void swap(vector& right)
    CONTRACT_FUNCTION( (class) (copyable)(vector)
            (public) (void) (swap)( (copyable)(vector&)(right) )
    (postcondition) ({
        CONTRACT_ASSERT( *CONTRACT_OLDOF(this) == right );
        CONTRACT_ASSERT( CONTRACT_OLDOF(right) == *this );
    })
    (body) ({
        vector_.swap(right);
    }) )

    bool operator==(const vector& right) const
    CONTRACT_FUNCTION( (class) (vector)
            (public) (bool) (operator_equal)(
                    (const vector&)(right) ) (const)
    (body) ({
        return vector_ == right.vector_;
    }) )

private:
    std::vector<T, Alloc> vector_;
};

int main() {
    // Run a few of the operations (could test more of them...).
    std::cout << std::endl << "constructor()" << std::endl;
    vector<double> v(3);
    const vector<double>& cv = v; // A reference, no copy.
    
    std::cout << std::endl << "copy constructor()" << std::endl;
    vector<double> w(v);
    
    std::cout << std::endl << "begin()" << std::endl;
    vector<double>::iterator b = v.begin();
    std::cout << *b << std::endl;
    
    std::cout << std::endl << "begin() const" << std::endl;
    vector<double>::const_iterator cb = cv.begin();
    std::cout << *cb << std::endl;
    
    std::cout << std::endl << "insert()" << std::endl;
    v.insert(b, 2, -3.21);
    
    std::cout << std::endl << "operator[]" << std::endl;
    double v0 = v[0];
    std::cout << v0 << std::endl;
    
    std::cout << std::endl << "push_back()" << std::endl;
    v.push_back(1.23);

    std::cout << std::endl << "destructor()" << std::endl;
    return 0;
}

