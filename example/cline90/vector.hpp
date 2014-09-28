
// Copyright (C) 2008-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://sourceforge.net/projects/contractpp

//[cline90_vector_header
// File: vector.hpp
#ifndef VECTOR_HPP_
#define VECTOR_HPP_

#include <contract.hpp>

CONTRACT_CLASS(
    template( typename T )
    class (vector)
) {
    // NOTE: Incomplete set of assertions addressing only `size`.

    CONTRACT_CLASS_INVARIANT_TPL( size() >= 0 )

    CONTRACT_CONSTRUCTOR_TPL(
        public explicit (vector) ( int count, default 10 )
            precondition( count >= 0 )
            postcondition( size() == count )
            initialize( data_(new T[count]), size_(count) )
    ) {
        for(int i = 0; i < size_; ++i) data_[i] = T();
    }

    CONTRACT_DESTRUCTOR_TPL(
        public virtual (~vector) ( void )
    ) {
        delete[] data_;
    }

    CONTRACT_FUNCTION_TPL(
        public int (size) ( void ) const
            // postcondition: Result non-negative checked by class invariant
    ) {
        return size_;
    }

    CONTRACT_FUNCTION_TPL(
        public void (resize) ( int count )
            precondition( count >= 0 )
            postcondition( size() == count )
    ) {
        T* slice = new T[count];
        for(int i = 0; i < count && i < size_; ++i) slice[i] = data_[i];
        delete[] data_;
        data_ = slice;
        size_ = count;
    }

    CONTRACT_FUNCTION_TPL(
        public (T&) operator([])(at) ( int index )
            precondition(
                index >= 0,
                index < size()
            )
    ) {
        return data_[index];
    }

    private: T* data_;
    private: int size_;
};

#endif // #include guard
//]

