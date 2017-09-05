
// Copyright (C) 2008-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://sourceforge.net/projects/contractpp

#ifndef CLASS_MEMBER_CONCEPT_VECTOR_HPP_
#define CLASS_MEMBER_CONCEPT_VECTOR_HPP_

#include <contract.hpp>
#include <vector>

//[class_member_concept_vector_class
#include <boost/concept_check.hpp> // Boost.ConceptCheck predefined concepts.

CONTRACT_CLASS(
    template( typename T )
        requires( boost::CopyConstructible<T> ) // Check concepts.
    class (vector)
) {
    CONTRACT_CLASS_INVARIANT_TPL(
        size() <= capacity(),
        capacity() <= max_size()
    )

    // ...
//]

    public: typedef typename std::vector<T>::size_type size_type;
    public: typedef typename std::vector<T>::iterator iterator;
    public: typedef typename std::vector<T>::const_reference const_reference;

    //[class_member_concept_vector_constructor
    CONTRACT_CONSTRUCTOR_TPL(
        public template( class Iterator )
            requires( boost::InputIterator<Iterator> ) // Check concepts.
        (vector) ( (Iterator) first, (Iterator) last )
            postcondition( std::distance(first, last) == int(size()) )
            initialize( vector_(first, last) )
    ) {}
    //]

    CONTRACT_DESTRUCTOR_TPL(
        public (~vector) ( void )
    ) {}

    //[class_member_concept_vector_member
    CONTRACT_FUNCTION_TPL(
        public template( class Iterator )
            requires( boost::InputIterator<Iterator> ) // Check concepts.
        void (insert) ( (Iterator) where, (Iterator) first, (Iterator) last )
            precondition( size() + std::distance(first, last) < max_size() )
            postcondition(
                auto old_increased_size = CONTRACT_OLDOF
                        size() + std::distance(first, last),
                auto old_capacity = CONTRACT_OLDOF capacity(),
                size() == old_increased_size,
                capacity() >= old_capacity
            )
    ) {
        vector_.insert(where, first, last);
    }
    //]

    public: size_type size ( void ) const { return vector_.size(); }
    public: size_type max_size ( void ) const { return vector_.max_size(); }
    public: size_type capacity ( void ) const { return vector_.capacity(); }
    public: iterator begin ( void ) { return vector_.begin(); }
    public: iterator end ( void ) { return vector_.end(); }
    public: const_reference operator[] ( size_type index ) const
        { return vector_[index]; }

    private: std::vector<T> vector_;
};
//]

#endif // #include guard

