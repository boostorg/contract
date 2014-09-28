
// Copyright (C) 2008-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://sourceforge.net/projects/contractpp

//[n1962_vector
// File: vector.hpp
#include <contract.hpp>
#include <boost/utility.hpp>
#include <boost/type_traits/has_equal_to.hpp>
#include <boost/algorithm/cxx11/all_of.hpp>
#include <boost/concept_check.hpp>
#include <iterator>
#include <vector>

CONTRACT_CLASS( // Vector wrapper with contracts.
    template( class T, class Allocator, default std::allocator<T> )
    class (vector) // No base classes so no subcontracting for this example.
) {
    CONTRACT_CLASS_INVARIANT_TPL( // At very beginning of the class declaration.
        empty() == (size() == 0),
        std::distance(begin(), end()) == int(size()),
        std::distance(rbegin(), rend()) == int(size()),
        size() <= capacity(),
        capacity() <= max_size()
    ) // No static or volatile class invariants for this example.

    public: typedef typename std::vector<T, Allocator>::allocator_type
            allocator_type;
    public: typedef typename std::vector<T, Allocator>::pointer pointer;
    public: typedef typename std::vector<T, Allocator>::const_pointer
            const_pointer;
    public: typedef typename std::vector<T, Allocator>::reference reference;
    public: typedef typename std::vector<T, Allocator>::const_reference
            const_reference;
    public: typedef typename std::vector<T, Allocator>::value_type value_type;
    public: typedef typename std::vector<T, Allocator>::iterator iterator;
    public: typedef typename std::vector<T, Allocator>::const_iterator
            const_iterator;
    public: typedef typename std::vector<T, Allocator>::size_type size_type;
    public: typedef typename std::vector<T, Allocator>::difference_type
            difference_type;
    public: typedef typename std::vector<T, Allocator>::reverse_iterator
            reverse_iterator;
    public: typedef typename std::vector<T, Allocator>::const_reverse_iterator
            const_reverse_iterator;

    CONTRACT_CONSTRUCTOR_TPL(
        public (vector) ( void ) // Always specify access level `public`, etc.
            postcondition( not empty() )
            initialize( vector_() ) // Member initializers.
    ) {}

    CONTRACT_CONSTRUCTOR_TPL(
        public explicit (vector) ( (const Allocator&) allocator )
            postcondition(
                empty(),
                allocator == get_allocator()
            )
            initialize( vector_(allocator) )
    ) {}

    CONTRACT_CONSTRUCTOR_TPL(
        public explicit (vector) ( (size_type) count )
            postcondition(
                size() == count,
                boost::algorithm::all_of_equal(begin(), end(), T()),
                        requires boost::has_equal_to<T>::value // Requirements.
            )
            initialize( vector_(count) )
    ) {}

    CONTRACT_CONSTRUCTOR_TPL(
        public (vector) ( (size_type) count, (const T&) value )
            postcondition(
                size() == count,
                boost::algorithm::all_of_equal(begin(), end(), value),
                        requires boost::has_equal_to<T>::value
            )
            initialize( vector_(count, value) )
    ) {}

    CONTRACT_CONSTRUCTOR_TPL(
        public (vector) ( (size_type) count, (const T&) value,
                (const Allocator&) allocator )
            postcondition(
                size() == count,
                boost::algorithm::all_of_equal(begin(), end(), value),
                        requires boost::has_equal_to<T>::value,
                allocator == get_allocator()
            )
            initialize( vector_(count, value, allocator) )
    ) {}

    CONTRACT_CONSTRUCTOR_TPL( // Contract with concepts.
        public template( class Iterator )
            requires( boost::InputIterator<Iterator> )
        (vector) ( (Iterator) first, (Iterator) last )
            postcondition( std::distance(first, last) == int(size()) )
            initialize( vector_(first, last) )
    ) {}

    CONTRACT_CONSTRUCTOR_TPL(
        public template( class Iterator )
                requires( boost::InputIterator<Iterator> )
        (vector) ( (Iterator) first, (Iterator) last,
                (const Allocator&) allocator )
            postcondition(
                std::distance(first, last) == int(size()),
                allocator == get_allocator()
            )
            initialize( vector_(first, last, allocator) )
    ) {}

    CONTRACT_CONSTRUCTOR_TPL(
        public (vector) ( (const vector&) right )
            postcondition(
                right == *this, requires boost::has_equal_to<T>::value
            )
            initialize( vector_(right.vector_) )
    ) {}

    CONTRACT_FUNCTION_TPL( // Operator symbol and (arbitrary) name `copy`.
        public (vector&) operator(=)(copy) ( (const vector&) right )
            postcondition(
                auto result = return, // Return value.
                result == *this, requires boost::has_equal_to<T>::value,
                result == right, requires boost::has_equal_to<T>::value
            )
    ) {
        return vector_ = right.vector_;
    }

    CONTRACT_DESTRUCTOR_TPL( // Destruct contract (check class invariant).
        public virtual (~vector) ( void )
    ) {}

    CONTRACT_FUNCTION_TPL(
        // Wrapping parenthesis optional for keyword types `void`, `bool`, etc.
        public void (reserve) ( (size_type) count )
            precondition( count < max_size() )
            postcondition( capacity() >= count )
    ) {
        vector_.reserve(count);
    }

    CONTRACT_FUNCTION_TPL(
        public (size_type) (capacity) ( void ) const // Constant member.
            postcondition( auto result = return, result >= size() )
    ) {
        return vector_.capacity();
    }

    CONTRACT_FUNCTION_TPL(
        public (iterator) (begin) ( void )
            postcondition(
                auto result = return,
                if(empty()) ( // Select assertions `if(...) ( ...)`.
                    result == end()
                ) // Omitted optional `else( ... )`.
            )
    ) {
        return vector_.begin();
    }

    CONTRACT_FUNCTION_TPL( // Contract overloaded function (see above).
        public (const_iterator) (begin) ( void ) const
            postcondition(
                auto result = return,
                if(empty()) ( result == end() )
            )
    ) {
        return vector_.begin();
    }

    CONTRACT_FUNCTION_TPL( // Contract with no pre/post checks class invariants.
        public (iterator) (end) ( void )
    ) {
        return vector_.end();
    }

    CONTRACT_FUNCTION_TPL(
        public (const_iterator) (end) ( void ) const
    ) {
        return vector_.end();
    }

    CONTRACT_FUNCTION_TPL(
        public (reverse_iterator) (rbegin) ( void )
            postcondition(
                auto result = return,
                if(empty()) ( result == rend() )
            )
    ) {
        return vector_.rbegin();
    }

    CONTRACT_FUNCTION_TPL(
        public (const_reverse_iterator) (rbegin) ( void ) const
            postcondition(
                auto result = return,
                if(empty()) ( result == rend() )
            )
    ) {
        return vector_.rbegin();
    }

    CONTRACT_FUNCTION_TPL(
        public (reverse_iterator) (rend) ( void )
    ) {
        return vector_.rend();
    }

    CONTRACT_FUNCTION_TPL(
        public (const_reverse_iterator) (rend) ( void ) const
    ) {
        return vector_.rend();
    }

    CONTRACT_FUNCTION_TPL(
        public void (resize) ( (size_type) count )
            postcondition(
                auto old_size = CONTRACT_OLDOF size(), // Old value (at entry).
                size() == count,
                if(count > old_size) (
                    boost::algorithm::all_of_equal(begin() + old_size, end(),
                            T()), requires boost::has_equal_to<T>::value
                )
            )
    ) {
        vector_.resize(count);
    }

    CONTRACT_FUNCTION_TPL(
        public void (resize) ( (size_type) count, (T) value )
            postcondition(
                (size_type) old_size = CONTRACT_OLDOF size(), // With old type.
                size() == count,
                count > old_size ? // Ternary operator.
                    boost::algorithm::all_of_equal(begin() + old_size, end(),
                            value)
                :
                    true
                , requires boost::has_equal_to<T>::value
            )
    ) {
        vector_.resize(count, value);
    }

    CONTRACT_FUNCTION_TPL(
        public (size_type) (size) ( void ) const
            postcondition( auto result = return, result <= capacity() )
    ) {
        return vector_.size();
    }

    CONTRACT_FUNCTION_TPL(
        public (size_type) (max_size) ( void ) const
            postcondition( auto result = return, result >= capacity() )
    ) {
        return vector_.max_size();
    }

    CONTRACT_FUNCTION_TPL(
        public bool (empty) ( void ) const
            postcondition(
                auto result = return,
                result == (size() == 0)
            )
    ) {
        return vector_.empty();
    }

    CONTRACT_FUNCTION_TPL(
        public (Allocator) (get_allocator) ( void ) const
    ) {
        return vector_.get_allocator();
    }

    CONTRACT_FUNCTION_TPL(
        public (reference) (at) ( (size_type) index )
            precondition( index < size() )
    ) {
        return vector_.at(index);
    }

    CONTRACT_FUNCTION_TPL(
        public (const_reference) (at) ( (size_type) index ) const
            precondition( index < size() )
    ) {
        return vector_.at(index);
    }

    CONTRACT_FUNCTION_TPL(
        public (reference) operator([])(at) ( (size_type) index )
            precondition( index < size() )
    ) {
        return vector_[index];
    }

    CONTRACT_FUNCTION_TPL(
        public (const_reference) operator([])(at) ( (size_type) index ) const
            precondition( index < size() )
    ) {
        return vector_[index];
    }

    CONTRACT_FUNCTION_TPL(
        public (reference) (front) ( void )
            precondition( not empty() ) // `not` instead of symbol `!`.
    ) {
        return vector_.front();
    }

    CONTRACT_FUNCTION_TPL(
        public (const_reference) (front) ( void ) const
            precondition( bool(!empty()) ) // Or, `bool` to wrap symbol `!`.
    ) {
        return vector_.front();
    }

    CONTRACT_FUNCTION_TPL(
        public (reference) (back) ( void )
            precondition( not empty() )
    ) {
        return vector_.back();
    }

    CONTRACT_FUNCTION_TPL(
        public (const_reference) (back) ( void ) const
            precondition( not empty() )
    ) {
        return vector_.back();
    }

    CONTRACT_FUNCTION_TPL(
        public void (push_back) ( (const T&) value )
            precondition( size() < max_size() )
            postcondition(
                auto old_size = CONTRACT_OLDOF size(),
                auto old_capacity = CONTRACT_OLDOF capacity(),
                back() == value, requires boost::has_equal_to<T>::value,
                size() == old_size + 1,
                capacity() >= old_capacity
            )
    ) {
        vector_.push_back(value);
    }

    CONTRACT_FUNCTION_TPL(
        public void (pop_back) ( void )
            precondition( not empty() )
            postcondition(
                auto old_size = CONTRACT_OLDOF size(),
                size() == old_size - 1
            )
    ) {
        vector_.pop_back();
    }

    CONTRACT_FUNCTION_TPL(
        public template( class Iterator )
            requires( boost::InputIterator<Iterator> )
        void (assign) ( (Iterator) first, (Iterator) last )
            // precondition: [begin(), end()) does not contain [first, last)
            postcondition( std::distance(first, last) == int(size()) )
    ) {
        vector_.assign(first, last);
    }

    CONTRACT_FUNCTION_TPL(
        public void (assign) ( (size_type) count, (const T&) value )
            precondition( count <= max_size() )
            postcondition(
                boost::algorithm::all_of_equal(begin(), end(), value),
                        requires boost::has_equal_to<T>::value
            )
    ) {
        vector_.assign(count, value);
    }

    CONTRACT_FUNCTION_TPL(
        public (iterator) (insert) ( (iterator) where, (const T&) value )
            precondition( size() < max_size() )
            postcondition(
                auto result = return,
                auto old_size = CONTRACT_OLDOF size(),
                value == *result, requires boost::has_equal_to<T>::value,
                size() == old_size + 1
                //  if(capacity() > oldof capacity())
                //     [begin(), end()) is invalid
                //  else
                //     [where, end()) is invalid
            )
    ) {
        return vector_.insert(where, value);
    }

    CONTRACT_FUNCTION_TPL(
        public void (insert) ( (iterator) where, (size_type) count,
                (const T&) value )
            precondition( size() + count < max_size() )
            postcondition(
                using boost::prior,
                auto old_size = CONTRACT_OLDOF size(),
                auto old_capacity = CONTRACT_OLDOF capacity(),
                auto old_where = CONTRACT_OLDOF where,
                size() == old_size + count,
                capacity() >= old_capacity,
                if(capacity() == old_capacity) (
                    boost::algorithm::all_of_equal(prior(old_where),
                            prior(old_where) + count, value),
                            requires boost::has_equal_to<T>::value
                    // [where, end()) is invalid
                ) // else [begin(), end()) is invalid
            )
    ) {
        vector_.insert(where, count, value);
    }

    CONTRACT_FUNCTION_TPL(
        public template( class Iterator )
            requires( boost::InputIterator<Iterator> )
        void (insert) ( (iterator) where, (Iterator) first, (Iterator) last )
            precondition(
                // [first, last) is not contained in [begin(), end())
                size() + std::distance(first, last) < max_size()
            )
            postcondition(
                auto old_size = CONTRACT_OLDOF size(),
                auto old_capacity = CONTRACT_OLDOF capacity(),
                size() == old_size + std::distance(first, last),
                capacity() >= old_capacity
            )
    ) {
        vector_.insert(where, first, last);
    }

    CONTRACT_FUNCTION_TPL(
        public (iterator) (erase) ( (iterator) where )
            precondition(
                not empty(),
                where != end()
            )
            postcondition(
                auto result = return,
                auto old_size = CONTRACT_OLDOF size(),
                size() == old_size - 1,
                if(empty()) ( result == end() )
                // [where, end()) is invalid
            )
    ) {
        return vector_.erase(where);
    }

    CONTRACT_FUNCTION_TPL(
        public (iterator) (erase) ( (iterator) first, (iterator) last )
            precondition( size() >= std::distance(first, last) )
            postcondition(
                auto result = return,
                auto old_size = CONTRACT_OLDOF size(),
                size() == old_size - std::distance(first, last),
                if(empty()) ( result == end() )
                // [first, last) is invalid
            )
    ) {
        return vector_.erase(first, last);
    }

    CONTRACT_FUNCTION_TPL(
        public void (clear) ( void )
            postcondition( empty() )
    ) {
        vector_.clear();
    }

    CONTRACT_FUNCTION_TPL(
        public void (swap) ( (vector&) right )
            postcondition(
                auto old_self = CONTRACT_OLDOF *this,
                auto old_right = CONTRACT_OLDOF right,
                right == old_self, requires boost::has_equal_to<T>::value,
                old_right == *this, requires boost::has_equal_to<T>::value
            )
    ) {
        vector_.swap(right);
    }

    friend bool operator== ( vector const& left, vector const& right )
    {
        return left.vector_ == right.vector_;
    }

    private: std::vector<T, Allocator> vector_;
};
//]

