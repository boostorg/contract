
// Copyright (C) 2008-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://sourceforge.net/projects/contractpp

#include "pushable.hpp"
#include <vector>
#include <iostream>

//[template_specializations_vector
CONTRACT_CLASS( // Not even necessary to contract this template.
    template( typename T, class Allocator, default std::allocator<T> )
    class (vector) extends( public pushable<T> )
) {
    // ...
//]
    CONTRACT_CLASS_INVARIANT_TPL( empty() == (size() == 0) )

    public: typedef typename std::vector<T, Allocator>::size_type size_type;
    public: typedef typename std::vector<T, Allocator>::const_reference
            const_reference;

    CONTRACT_FUNCTION_TPL(
        public void (push_back) ( (T const&) value )
            precondition( size() < max_size() )
            postcondition(
                auto old_size = CONTRACT_OLDOF size(),
                size() == old_size + 1
            )
    ) {
        std::cout << "T, Allocator" << std::endl;
        vector_.push_back(value);
    }

    public: bool empty ( void ) const { return vector_.empty(); }
    public: size_type size ( void ) const { return vector_.size(); }
    public: size_type max_size ( void ) const { return vector_.max_size(); }
    public: const_reference back ( void ) const { return vector_.back(); }

    private: std::vector<T, Allocator> vector_;
};

//[template_specializations_vector_bool
CONTRACT_CLASS( // Template specialization (no template parameter).
    template( void )
    class (vector) ( bool ) extends( public pushable<bool> )
) {
    // ...
//]
    CONTRACT_CLASS_INVARIANT( empty() == (size() == 0) )

    public: typedef std::vector<bool>::size_type size_type;
    public: typedef std::vector<bool>::const_reference
            const_reference;

    CONTRACT_FUNCTION(
        public void (push_back) ( (bool const&) value )
            precondition( size() < max_size() )
            postcondition(
                auto old_size = CONTRACT_OLDOF size(),
                size() == old_size + 1
            )
    ) {
        std::cout << "bool" << std::endl;
        vector_.push_back(value);
    }

    public: bool empty ( void ) const { return vector_.empty(); }
    public: size_type size ( void ) const { return vector_.size(); }
    public: size_type max_size ( void ) const { return vector_.max_size(); }
    public: const_reference back ( void ) const { return vector_.back(); }

    private: std::vector<bool> vector_;
};

//[template_specializations_vector_bool_allocator
CONTRACT_CLASS( // Template specialization (one template parameter).
    template( class Allocator )
    class (vector) ( bool, Allocator ) extends( public pushable<bool> )
) {
    // ...
//]
    CONTRACT_CLASS_INVARIANT_TPL( empty() == (size() == 0) )

    public: typedef typename std::vector<bool, Allocator>::size_type size_type;
    public: typedef typename std::vector<bool, Allocator>::const_reference
            const_reference;

    CONTRACT_FUNCTION_TPL(
        public void (push_back) ( (bool const&) value )
            precondition( size() < max_size() )
            postcondition(
                auto old_size = CONTRACT_OLDOF size(),
                size() == old_size + 1
            )
    ) {
        std::cout << "bool, Allocator" << std::endl;
        vector_.push_back(value);
    }

    public: bool empty ( void ) const { return vector_.empty(); }
    public: size_type size ( void ) const { return vector_.size(); }
    public: size_type max_size ( void ) const { return vector_.max_size(); }
    public: const_reference back ( void ) const { return vector_.back(); }

    private: std::vector<bool, Allocator> vector_;
};

int main ( void )
{
    vector<int> v;
    v.push_back(123);
    std::cout << v.size() << std::endl;
    
    vector<bool> b;
    b.push_back(true);
    std::cout << b.size() << std::endl;
   
    vector<bool, std::allocator<char> > bc;
    bc.push_back(true);
    std::cout << bc.size() << std::endl;
  
    return 0;
}


