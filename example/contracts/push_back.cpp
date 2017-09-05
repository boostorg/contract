
// Copyright (C) 2008-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://sourceforge.net/projects/contractpp

#include <boost/detail/lightweight_test.hpp>

//[push_back
#include <contract.hpp> // This library.
#include <boost/concept_check.hpp>
#include <vector>
#include "pushable.hpp" // Some base class.

CONTRACT_CLASS(
    template( typename T ) requires( boost::CopyConstructible<T> ) // Concepts.
    class (vector) extends( public pushable<T> ) // Subcontracting.
) {
    CONTRACT_CLASS_INVARIANT_TPL(
        empty() == (size() == 0) // More class invariants here...
    )

    public: typedef typename std::vector<T>::size_type size_type;
    public: typedef typename std::vector<T>::const_reference const_reference;

    CONTRACT_FUNCTION_TPL(
        public void (push_back) ( (T const&) value ) override
            precondition(
                size() < max_size() // More preconditions here...
            )
            postcondition(
                auto old_size = CONTRACT_OLDOF size(), // Old-of values.
                size() == old_size + 1 // More postconditions here...
            )
    ) {
        vector_.push_back(value); // Original function body.
    }
    
    // Rest of class here (possibly with more contracts)...
    public: bool empty ( void ) const { return vector_.empty(); }
    public: size_type size ( void ) const { return vector_.size(); }
    public: size_type max_size ( void ) const { return vector_.max_size(); }
    public: const_reference back ( void ) const { return vector_.back(); }

    private: std::vector<T> vector_;
};
//]

int main ( void )
{
    vector<int> v;
    v.push_back(123);
    BOOST_TEST(v.size() == 1);
    return boost::report_errors();
}

