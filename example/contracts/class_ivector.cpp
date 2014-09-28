
// Copyright (C) 2008-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://sourceforge.net/projects/contractpp

#include <contract.hpp>
#include <boost/algorithm/cxx11/all_of.hpp>
#include <boost/detail/lightweight_test.hpp>
#include <iterator>
#include <vector>

//[class_ivector_classinv
CONTRACT_CLASS( // Declare the class.
    class (ivector)
) {
    CONTRACT_CLASS_INVARIANT( // Specify the class invariants.
        empty() == (size() == 0),
        size() <= capacity(),
        capacity() <= max_size(),
        std::distance(begin(), end()) == int(size())
    )

    public: typedef std::vector<int>::size_type size_type;
    // ...
//]
    public: typedef std::vector<int>::const_reference const_reference;
    public: typedef std::vector<int>::const_iterator const_iterator;
    

    //[class_ivector_constructor
    CONTRACT_CONSTRUCTOR( // Declare the constructor and its contract.
        public explicit (ivector) ( (size_type) count )
            precondition( count >= 0 )
            postcondition(
                size() == count,
                boost::algorithm::all_of_equal(begin(), end(), 0)
            )
            initialize( vector_(count) )
    ) {}
    //]

    //[class_ivector_destructor
    CONTRACT_DESTRUCTOR( // Declare the destructor (so it checks invariants).
        public virtual (~ivector) ( void )
    ) {}
    //]

    //[class_ivector_member
    CONTRACT_FUNCTION( // Declare the member function with its contract.
        public void (push_back) ( int const value )
            precondition( size() < max_size() )
            postcondition(
                auto old_size = CONTRACT_OLDOF size(),
                auto old_capacity = CONTRACT_OLDOF capacity(),
                size() == old_size + 1,
                capacity() >= old_capacity,
                back() == value
            )
    ) {
        vector_.push_back(value);
    }
    //]
    
    public: bool empty ( void ) const { return vector_.empty(); }
    public: size_type size ( void ) const { return vector_.size(); }
    public: size_type max_size ( void ) const { return vector_.max_size(); }
    public: size_type capacity ( void ) const { return vector_.capacity(); }
    public: const_reference back ( void ) const { return vector_.back(); }
    public: const_iterator begin ( void ) const { return vector_.begin(); }
    public: const_iterator end ( void ) const { return vector_.end(); }

    private: std::vector<int> vector_;
};

int main ( void )
{
    ivector v(1);
    BOOST_TEST(v.size() == 1);
    BOOST_TEST(v.back() == 0);
    
    v.push_back(123);
    BOOST_TEST(v.size() == 2);
    BOOST_TEST(v.back() == 123);

    return boost::report_errors();
}

