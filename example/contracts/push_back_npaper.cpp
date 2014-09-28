
// Copyright (C) 2008-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://sourceforge.net/projects/contractpp

//[push_back_npaper
// Extra spaces, newlines, etc used to align text with this library code.
#include <concept>
#include <vector>
#include "pushable.hpp" // Some base class.


template< typename T > requires CopyConstructible<T> // Concepts.
class vector : public pushable<T> // Subcontracting.
{
    invariant {
        empty() == (size() == 0); // More class invariants here...
    }

    public: typedef typename std::vector<T>::size_type size_type;
    public: typedef typename std::vector<T>::const_reference const_reference;

        
    public: void push_back ( T const& value ) override
        precondition {
            size() < max_size(); // More preconditions here...
        }
        postcondition {
            // Old-of values use `oldof` operator.
            size() == oldof size() + 1; // More postconditions here...
        }
    {
        vector_.push_back(value); // Original function body.
    }
    
    // Rest of class here (with possibly more contracts)...
    public: bool empty ( void ) const { return vector_.empty(); }
    public: size_type size ( void ) const { return vector_.size(); }
    public: size_type max_size ( void ) const { return vector_.max_size(); }
    public: const_reference back ( void ) const { return vector_.back(); }

    private: std::vector<T> vector_;
};
//]

