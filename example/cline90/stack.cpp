
// Copyright (C) 2008-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://sourceforge.net/projects/contractpp

//[cline90_stack
// File: stack.cpp
#include <contract.hpp>
#include <boost/config.hpp>
#include <boost/utility/identity_type.hpp>
#include <boost/detail/lightweight_test.hpp>
#include <exception>
#include <new>
#include <utility>
#include <iostream>

CONTRACT_CLASS(
    template( typename T )
    class (stack)
) {
    // NOTE: Incomplete set of assertions addressing only `empty` and `full`.

    CONTRACT_CLASS_INVARIANT( void )

    public: struct out_of_memory {};
    public: struct error {};

    CONTRACT_CONSTRUCTOR_TPL(
        public explicit (stack) ( int capacity )
            precondition( capacity >= 0 )
            postcondition(
                empty(),
                full() == (capacity == 0)
            )
            // Function-Try blocks are programmed within the macros only for
            // constructors with member initializers otherwise they are
            // programmed with the body definition and outside the macros.
            try initialize( // Try-block for constructor initializers and body.
                data_(new T[capacity]),
                capacity_(capacity),
                size_(0)
            ) catch(std::bad_alloc& e) (
                std::cerr << "out of memory for " << capacity << "-stack: " <<
                        e.what() << std::endl;
                throw out_of_memory();
            // Unfortunately, cannot wrap exception type commas with extra
            // parenthesis (because symbol `...` used to catch-all) but
            // `BOOST_IDENTITY_TYPE` can be used.
            ) catch(BOOST_IDENTITY_TYPE((std::pair<int, char const*>&)) e) (
                std::cerr << "error number " << e.first << " for " <<
                        capacity << "-stack: " << e.second << std::endl;
                throw error();
            ) catch(...) (
                std::cerr << "unknown error for " << capacity << "-stack" <<
                        std::endl;
                throw; // Re-throw exception.
            )
    ) {
        for(int i = 0; i < capacity_; ++i) data_[i] = T();
    }

    CONTRACT_DESTRUCTOR_TPL(
        public virtual (~stack) ( void )
    )
#if !defined(BOOST_MSVC) // MSVC supports only constructor-try blocks.
    try { // Function-try block (outside the macro).
        delete[] data_;
    } catch(...) {
        std::cerr << "error for stack destruction, terminating" << std::endl;
        std::terminate(); // Destructor should never throw.
    }
#else // MSVC
    {
        delete[] data_;
    }
#endif // MSVC

    CONTRACT_FUNCTION_TPL(
        public bool (empty) ( void ) const
    ) {
        return size_ == 0;
    }

    CONTRACT_FUNCTION_TPL(
        public bool (full) ( void ) const
    ) {
        return size_ == capacity_;
    }

    CONTRACT_FUNCTION_TPL(
        public void (push) ( (T) value ) 
#if !defined(BOOST_MSVC) // MSVC only supports throw( void ) exception spec.
            throw( std::exception, error ) // Ex spec.
#endif // MSVC
            precondition( not full() )
            postcondition( not empty() )
    )
#if !defined(BOOST_MSVC) // MSVC supports only constructor-try blocks.
    try
#endif // MSVC
    { // Function-Try block (outside the macro).
        data_[size_++] = value; 
    } 
#if !defined(BOOST_MSVC) // MSVC supports only constructor-try blocks.
    catch(std::exception& e) {
        std::cerr << "error for " << capacity_ << "-stack: " << e.what() <<
                std::endl;
        throw; // Re-throw STL exception.
    } catch(...) {
        std::cerr << "unknown error for " << capacity_ << "-stack" <<
                std::endl;
        throw error();
    }
#endif // MSVC

    CONTRACT_FUNCTION_TPL(
        public (T) (pop) ( void )
            precondition( not empty() )
            postcondition( not full() )
    ) {
        return data_[--size_];
    }

    private: T* data_;
    private: int capacity_;
    private: int size_;
};

int main ( void )
{
    stack<int> s(3);
    s.push(123);
    BOOST_TEST(s.pop() == 123);
    return boost::report_errors();
}
//]

