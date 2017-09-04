/**
 * @file
 * @author Copyright (C) 2009 Lorenzo Caminiti.
 *  Distributed under DBC++ Software License (see file LICENSE_1_0.txt).
 */

#ifndef DBC_VECTOR_HPP_
#define DBC_VECTOR_HPP_

#include <dbc.hpp> // The DBC++ library.
#include <vector>

namespace dbc {

template<class Iter, typename T>
bool all_equals(Iter first, Iter last, const T& val) {
    // For simplicity, let's assume T can be compared.
    for (Iter i = first; i != last; ++i) {
        if (*i != val) { return false; }
    }
    return true;
}

/**
 * Wrapper with contracts for STL vector.
 * Contracts taken from an example in "Proposal to add Contract Programming to
 * C++ (rev 4)", L. Crowl and T. Ottosen, C++ Standard Committee N1962, 2006.
 */
template<typename T, class Alloc = std::allocator<T> >
class vector
        /** @todo DBC_INHERIT_OBJECT() will probably be removed soon. */
        DBC_INHERIT_OBJECT(DBC_MPARAM(2, (vector<T, Alloc>))) {
private:
    typedef std::vector<T, Alloc> std_vector_type;

    DBC_INVARIANT(vector, {
        // Invariants.
        DBC_ASSERT((self.size() == 0) == self.empty(), "empty iff size 0");
        DBC_ASSERT(int(self.size()) == std::distance(self.begin(), self.end()),
                "size counts from begin to end");
        DBC_ASSERT(int(self.size()) == std::distance(self.rbegin(),
                self.rend()), "size reversely counts from begin to end");
        DBC_ASSERT(self.size() <= self.capacity(),
                "size not greater than capacity");
        DBC_ASSERT(self.capacity() <= self.max_size(),
                "capacity not greater than max size");
    })

public:
    // Types //

    typedef typename std_vector_type::size_type size_type;
    typedef typename std_vector_type::iterator iterator;
    typedef typename std_vector_type::const_iterator const_iterator;
    typedef typename std_vector_type::reverse_iterator reverse_iterator;
    typedef typename std_vector_type::const_reverse_iterator
            const_reverse_iterator;
    typedef typename std_vector_type::reference reference;
    typedef typename std_vector_type::const_reference const_reference;

    // Creation //

    vector(void): v_()
    DBC_CONSTRUCTOR( (public) (template)(vector)( (void) ), { // Signature.
        // Preconditions.
    }, {
        // Postconditions.
        DBC_ASSERT(self.now.empty(), "empty");
    }, {
        // Body.
    })

    explicit vector(const Alloc& al): v_(al)
    DBC_CONSTRUCTOR( (public) (template)(vector)( (const Alloc&)(al) ), {
    }, {
        DBC_ASSERT(self.now.empty(), "empty");
        DBC_ASSERT(al.now == self.now.get_allocator(), "allocator set");
    }, {
    })

    explicit vector(size_type count): v_(count)
    DBC_CONSTRUCTOR( (public) (template)(vector)( (size_type)(count) ), {
    }, {
        DBC_ASSERT(self.now.size() == count.now, "size set to count");
        DBC_ASSERT(all_equals(self.now.begin(), self.now.end(), T()),
                "all elements set to default");
    }, {
    })

    vector(size_type count, const T& val): v_(count, val)
    DBC_CONSTRUCTOR( (public) (template)(vector)( (size_type)(count)
            (const T&)(val) ), {
    }, {
        DBC_ASSERT(self.now.size() == count.now, "size set to count");
        DBC_ASSERT(all_equals(self.now.begin(), self.now.end(), val.now),
                "all elements set to value");
    }, {
    })
    
    vector(size_type count, const T& val, const Alloc& al): v_(count, val, al)
    DBC_CONSTRUCTOR( (public) (template)(vector)( (size_type)(count)
            (const T&)(val) (const Alloc&)(al) ), {
    }, {
        DBC_ASSERT(self.now.size() == count.now, "size set to count");
        DBC_ASSERT(all_equals(self.now.begin(), self.now.end(), val.now),
                "all elements set to value");
        DBC_ASSERT(al.now == self.now.get_allocator(), "allocator set");
    }, {
    })

    vector(const vector& right): v_(right.v_)
    DBC_CONSTRUCTOR( (public) (template)(vector)( (const vector&)(right) ), {
    }, {
        DBC_ASSERT(right.now == self.now, "vector copied");
    }, {
    })

    template<class InIt>
    vector(InIt first, InIt last): v_(first, last)
    /** @todo This library is currently being extended to support templated
     * member function as indicated below:
    DBC_CONSTRUCTOR( (public) (template)(<class InIt>) (template)(vector) (
            (InIt)(first) (InIt)(last) ), {
    }, {
        DBC_ASSERT(equal_distance(first.now, last.now, self.now.size),
                "size set from first to last");
    }, {
    })*/
    {}
    
    template<class InIt>
    vector(InIt first, InIt last, const Alloc& al): v_(first, last, al)
    /** @todo This library is currently being extended to support templated
     * member function as indicated below:
    DBC_CONSTRUCTOR( (public) (template)(<class InIt>) (template)(vector) (
            (InIt)(first) (InIt)(last) ), {
    }, {
        DBC_ASSERT(equal_distance(first.now, last.now, self.now.size),
                "size set from first to last");
        DBC_ASSERT(al.now == self.now.get_allocator(), "allocator set");
    }, {
    })*/
    {}

    // Capacity //

    void reserve(size_type count)
    DBC_MEM_FUN( (public) (void) (template)(vector) (reserve)(
            (size_type)(count) ), {
        DBC_ASSERT(count < self.max_size(), "count smaller than max size");
    }, {
        DBC_ASSERT(self.now.capacity() >= count.now,
                "capacity not smaller than count");
    }, {
        v_.reserve(count);
    })

    size_type capacity(void) const
    DBC_MEM_FUN( (public) (size_type) (template)(vector)
            (capacity)( (void) ) (const), {
    }, {
        DBC_ASSERT(result >= self.now.size(),
                "returning capacity not smaller than size");
    }, {
        return v_.capacity();
    })

    // Iterators //

    iterator begin(void)
    DBC_MEM_FUN( (public) (iterator) (template)(vector) (begin)( (void) ), {
    }, {
        if (self.now.empty()) DBC_ASSERT(result == self.now.end(),
                "if empty, result at end");
    }, {
        return v_.begin();
    })
    
    const_iterator begin(void) const
    DBC_MEM_FUN( (public) (const_iterator) (template)(vector)
            (begin)( (void) ) (const), {
    }, {
        if (self.now.empty()) DBC_ASSERT(result == self.now.end(),
                "if empty, result at end");
    }, {
        return v_.begin();
    })

    
    iterator end(void)
    // Contract specified also if no pre/post condition so to check invariants.
    DBC_MEM_FUN( (public) (iterator) (template)(vector) (end)( (void) ), {
    }, {
    }, {
        return v_.end();
    })
    
    const_iterator end(void) const
    DBC_MEM_FUN( (public) (const_iterator) (template)(vector)
            (end)( (void) ) (const), {
    }, {
    }, {
        return v_.end();
    })
    
    // Reverse Iterators //

    reverse_iterator rbegin(void)
    DBC_MEM_FUN( (public) (reverse_iterator) (template)(vector)
            (rbegin)( (void) ), {
    }, {
        if (self.now.empty()) DBC_ASSERT(result == self.now.rend(),
                "if empty, result at reverse end");
    }, {
        return v_.rbegin();
    })
    
    const_reverse_iterator rbegin(void) const
    DBC_MEM_FUN( (public) (const_reverse_iterator) (template)(vector)
            (rbegin)( (void) ) (const), {
    }, {
        if (self.now.empty()) DBC_ASSERT(result == self.now.rend(),
                "if empty, result at reverse end");
    }, {
        return v_.rbegin();
    })

    reverse_iterator rend(void)
    DBC_MEM_FUN( (public) (reverse_iterator) (template)(vector)
            (rend)( (void) ), {
    }, {
    }, {
        return v_.rend();
    })
    
    const_reverse_iterator rend(void) const
    DBC_MEM_FUN( (public) (const_reverse_iterator) (template)(vector)
            (rend)( (void) ) (const), {
    }, {
    }, {
        return v_.rend();
    })

    // Size //

    void resize(size_type newsize)
    DBC_MEM_FUN( (public) (void) (template)DBC_COPYABLE(vector) (resize)(
            (size_type)(newsize) ), {
    }, {
        DBC_ASSERT(self.now.size() == newsize.now, "new size set");
        if (newsize.now > self.old.size()) DBC_ASSERT(all_equals(
                self.now.begin() + self.old.size(), self.now.end(), T()),
                "all elements set to default");
    }, {
        v_.resize(newsize);
    })
    
    void resize(size_type newsize, T val)
    DBC_MEM_FUN( (public) (void) (template)DBC_COPYABLE(vector) (resize)(
            (size_type)(newsize) (T)(val) ), {
    }, {
        DBC_ASSERT(self.now.size() == newsize.now, "new size set");
        DBC_ASSERT((newsize.now > self.old.size()) ? all_equals(
                self.now.begin() + self.old.size(), self.now.end(), val.now) :
                true, "all elements set to value");
    }, {
        v_.resize(newsize, val);
    })
    
    size_type size(void) const
    DBC_MEM_FUN( (public) (size_type) (template)(vector)
            (size)( (void) ) (const), {
    }, {
        DBC_ASSERT(result <= self.now.capacity(),
                "returning size no greater than capacity");
    }, {
        return v_.size();
    })
    
    size_type max_size(void) const
    DBC_MEM_FUN( (public) (size_type) (template)(vector)
            (max_size)( (void) ) (const), {
    }, {
        DBC_ASSERT(result >= self.now.capacity(),
                "returning max size no smaller than capacity");
    }, {
        return v_.max_size();
    })
    
    bool empty(void) const
    DBC_MEM_FUN( (public) (bool) (template)(vector)
            (empty)( (void) ) (const), {
    }, {
        DBC_ASSERT(result == (self.now.size() == 0),
                "returning empty consistent with size");
    }, {
        return v_.empty();
    })

    // Access //

    reference at(size_type off)
    DBC_MEM_FUN( (public) (reference) (template)(vector) (at)(
            (size_type)(off) ), {
        DBC_ASSERT(off < self.size(), "off within size");
    }, {
    }, {
        return v_.at(off);
    })
    
    const_reference at(size_type off) const
    DBC_MEM_FUN( (public) (const_reference) (template)(vector) (at)(
            (size_type)(off) ) (const), {
        DBC_ASSERT(off < self.size(), "off within size");
    }, {
    }, {
        return v_.at(off);
    })
    
    reference operator[](size_type off)
    DBC_MEM_FUN( (public) (reference) (template)(vector) (operator_at)(
            (size_type)(off) ), {
        DBC_ASSERT(off < self.size(), "off within size");
    }, {
    }, {
        return v_[off];
    })
    
    const_reference operator[](size_type off) const
    DBC_MEM_FUN( (public) (const_reference) (template)(vector) (operator_at)(
            (size_type)(off) ) (const), {
        DBC_ASSERT(off < self.size(), "off within size");
    }, {
    }, {
        return v_[off];
    })

    reference front(void)
    DBC_MEM_FUN( (public) (reference) (template)(vector) (front)( (void) ), {
        DBC_ASSERT(!self.empty(), "not empty");
    }, {
    }, {
        return v_.front();
    })
    
    const_reference front(void) const
    DBC_MEM_FUN( (public) (const_reference) (template)(vector)
            (front)( (void) ) (const), {
        DBC_ASSERT(!self.empty(), "not empty");
    }, {
    }, {
        return v_.front();
    })
    
    reference back(void)
    DBC_MEM_FUN( (public) (reference) (template)(vector) (back)( (void) ), {
        DBC_ASSERT(!self.empty(), "not empty");
    }, {
    }, {
        return v_.back();
    })
    
    const_reference back(void) const
    DBC_MEM_FUN( (public) (const_reference) (template)(vector)
            (back)( (void) ) (const), {
        DBC_ASSERT(!self.empty(), "not empty");
    }, {
    }, {
        return v_.back();
    })

    void push_back(const T& val)
    DBC_MEM_FUN( (public) (void) (template)DBC_COPYABLE(vector) (push_back)(
            (const T&)(val) ), {
        DBC_ASSERT(self.size() < self.max_size(),
                "size smaller than max size");
    }, {
        DBC_ASSERT(self.now.back() == val.now, "back set to value");
        DBC_ASSERT(self.now.size() == (self.old.size() + 1),
                "size increased by 1");
        DBC_ASSERT(self.now.capacity() >= self.old.capacity(),
                "capacity increased");
    }, {
        v_.push_back(val);
    })
    
    void pop_back(void)
    DBC_MEM_FUN( (public) (void) (template)DBC_COPYABLE(vector)
            (pop_back)( (void) ), {
        DBC_ASSERT(!self.empty(), "not empty");
    }, {
        DBC_ASSERT(self.now.size() == (self.old.size() - 1),
                "size decreased by 1");
    }, {
        v_.pop_back();
    })

    template<class InIt>
    void assign(InIt first, InIt last)
    /** @todo This library is currently being extended to support templated
     * member function as indicated below:
    DBC_MEM_FUN( (public) (template)(<class InIt>) (void) (template)(vector)
            (assign)( (InIt)(first) (InIt)(last) ), {
        @pre The range [first, last) is not a sub-range of [begin(), end())
    }, {
        DBC_ASSERT(equal_distance(self.now.first, self.now.last,
                self.now.size()), "size set from first to last");
    }, {
        v_.assign(first, last);
    })*/
    { v_.assign(first, last); }

    void assign(size_type count, const T& val)
    DBC_MEM_FUN( (public) (void) (template)(vector)
            (assign)( (size_type)(count) (const T&)(val) ), {
        DBC_ASSERT(count <= self.max_size(), "count within max size");
    }, {
        DBC_ASSERT(all_equals(self.now.begin(), self.now.end(), val),
                "elements set to value from begin to end");
    }, {
        v_.assign(count, val);
    })

    iterator insert(iterator where, const T& val)
    DBC_MEM_FUN( (public) (iterator) (template)DBC_COPYABLE(vector)
            (insert)( (iterator)(where) (const T&)(val) ), {
        DBC_ASSERT(self.size() < self.max_size(), "size within max size");
    }, {
        DBC_ASSERT(*result == val, "returning value iterator");
        DBC_ASSERT(self.now.size() == (self.old.size() + 1),
                "size increased by 1");
        DBC_ASSERT(self.now.capacity() >= self.old.capacity(),
                "capacity increased");
        /** @post
         *  if (self.now.capacity() > self.old.capacity())
         *      All iterators have been invalidated
         *  else
         *      All the iterators in range [where, end()) have been invalidated
         */
    }, {
        return v_.insert(where, val);
    })
    
    void insert(iterator where, size_type count, const T& val)
    DBC_MEM_FUN( (public) (void) (template)DBC_COPYABLE(vector) (insert)(
            DBC_COPYABLE(iterator)(where) (size_type)(count)
            (const T&)(val) ), {
        DBC_ASSERT((self.size() + count) < self.max_size(),
                "size plus count within max size");
    }, {
        DBC_ASSERT(self.now.size() == (self.old.size() + count.now),
                "size increased by count");
        DBC_ASSERT(self.now.capacity() >= self.old.capacity(),
                "capacity increased");
        // I am not sure if prior() is part of STL or some other library...
        // if (self.now.capacity() == self.old.capacity()) DBC_ASSERT(
        //         all_equals(prior(where.old), prior(where.old) + 
        //         count.now, val), "count elements after where set to value");
        /** @post
         *  if (self.now.capacity() > self.old.capacity())
         *      All iterators have been invalidated
         *  else
         *      All the iterators in range [where, end()) have been invalidated
         */
    }, {
        v_.insert(where, count, val);
    })

    template<class InIt>
    void insert(iterator where, InIt first, InIt last)
    /** @todo This library is currently being extended to support templated
     * member function as indicated below:
    DBC_MEM_FUN( (public) (template)(<class InIt>) (void) (template)(vector)
            (insert)( (iterator)(where) (InIt)(first) (InIt)(last) ), {
        @pre The range [first, last) is not a sub-range of [begin(), end())
        DBC_ASSERT(self.size() + count <= self.max_size(),
                "size plus count within max size");
    }, {
        DBC_ASSERT(self.now.size() == (self.old.size() + count.now),
                "size increased by count");
        DBC_ASSERT(self.now.capacity() >= self.old.capacity(),
                "capacity increased");
        // I am not sure if prior() is part of STL or some other library...
        // if (self.now.capacity() == self.old.capacity()) DBC_ASSERT(
        //         all_equals(prior(where.old), prior(where.old) + 
        //         count.now, val), "count elements after where set to value");
        /// @post
        //  if (self.now.capacity() > self.old.capacity())
        //      All iterators have been invalidated
        //  else
        //      All the iterators in range [where, end()) have been invalidated
        //
    }, {
        v_.insert(where, first, last);
    })*/
    { v_.insert(where, first, last); }

    iterator erase(iterator where)
    DBC_MEM_FUN( (public) (iterator) (template)DBC_COPYABLE(vector)
            (erase)( (iterator)(where) ), {
        DBC_ASSERT(!self.empty(), "not empty");
        DBC_ASSERT(where != self.end(), "where not at end");
    }, {
        DBC_ASSERT(self.now.size() == (self.old.size() - 1),
                "size decreased by 1");
        if (self.empty()) DBC_ASSERT(result == self.now.end(),
                "if empty, returning end");
        /** @post All iterators in [where, end()) have been invalidated */
    }, {
        return v_.erase(where);
    })
    
    iterator erase(iterator first, iterator last)
    DBC_MEM_FUN( (public) (iterator) (template)DBC_COPYABLE(vector)
            (erase)( (iterator)(first) (iterator)(last) ), {
        DBC_ASSERT(self.size() >= std::distance(first, last),
                "size not smaller than count from first to last");
    }, {
        DBC_ASSERT(self.now.size() == (self.old.size() - 
                std::distance(first.now, last.now)),
                "size decreased of count from first to last");
        if (self.empty()) DBC_ASSERT(result == self.now.end(),
                "if empty, returning end");
        /** @post All iterators in [first, end()) have been invalidated */
    }, {
        return v_.erase(first, last);
    })
    
    void clear(void)
    DBC_MEM_FUN( (public) (void) (template)(vector) (clear)( (void) ), {
    }, {
        DBC_ASSERT(self.now.empty(), "empty");
    }, {
        v_.clear();
    })

    // Others //
    
    bool operator==(const vector& right) const
    DBC_MEM_FUN( (public) (bool) (template)(vector) (operator_equal)(
            (const vector&)(right) ) (const), {
    }, {
    }, {
        return v_ == right.v_;
    })
    
    void swap(vector& right)
    DBC_MEM_FUN( (public) (void) (template)DBC_COPYABLE(vector) (swap)(
            DBC_COPYABLE(vector&)(right) ), {
    }, {
        DBC_ASSERT(self.old == right.now, "right equals old object");
        DBC_ASSERT(right.old == self.now, "self equals old right")
    }, {
        v_.swap(right);
    })
    
    Alloc get_allocator(void) const
    DBC_MEM_FUN( (public) (Alloc) (template)(vector)
            (get_allocator)( (void) ) (const), {
    }, {
    }, {
        return v_.get_allocator();
    })

private:
    std_vector_type v_;
};

} // namespace dbc

#endif // DBC_VECTOR_HPP_

