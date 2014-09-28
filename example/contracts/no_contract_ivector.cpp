
// Copyright (C) 2008-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://sourceforge.net/projects/contractpp

#include <vector>

//[no_contract_ivector
class ivector
{
    // invariant:   empty() == (size() == 0)
    //              size() <= capacity()
    //              capacity() <= max_size()
    //              std::distance(begin(), end()) == int(size())

    public: typedef std::vector<int>::size_type size_type;

    public: explicit ivector ( size_type count )
        // precondition:    count >= 0
        // postcondition:   size() == count
        //                  boost::algorithm::all_of_equal(begin(), end(), 0)
        : vector_(count)
    {}

    public: virtual ~ivector ( void ) {}

    public: void push_back ( int const value )
        // precondition:    size() < max_size()
        // postcondition:   size() == oldof size() + 1
        //                  capacity() >= oldof capacity()
        //                  back() == value
    {
        vector_.push_back(value);
    }
    
    private: std::vector<int> vector_;
};
//]

int main ( void )
{
    ivector v(1);
    v.push_back(123);
    return 0;
}

