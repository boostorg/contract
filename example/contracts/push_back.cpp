
// Copyright (C) 2008-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://sourceforge.net/projects/contractpp

#include <boost/detail/lightweight_test.hpp>

//[push_back
#include <bppst/contract.hpp> // This library.
#include <vector>
#include "pushable.hpp" // Some base class.

BOOST_CONTRACT_CLASS(
    template( typename T )
    class (vector) extends( public pushable<T> ) // Subcontracting.
        invariant(
            empty() == (size() == 0) // More class invariants here...
        )
) {
public:
    typedef typename std::vector<T>::size_type size_type;
    typedef typename std::vector<T>::const_reference const_reference;

    BOOST_CONTRACT_FUNCTION_TPL(
        void (push_back) ( (T const&) value )
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
    bool empty ( ) const { return vector_.empty(); }
    size_type size ( ) const { return vector_.size(); }
    size_type max_size ( ) const { return vector_.max_size(); }
    const_reference back ( ) const { return vector_.back(); }

private:
    std::vector<T> vector_;
};
//]

int main ( ) {
    vector<int> v;
    v.push_back(123);
    BOOST_TEST(v.size() == 1);
    return boost::report_errors();
}

