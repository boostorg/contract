
// Copyright (C) 2008-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://sourceforge.net/projects/contractpp

#include <contract.hpp>
#include <boost/detail/lightweight_test.hpp>

//[exception_array
CONTRACT_CLASS(
    template( typename T )
    class (array)
) {
    CONTRACT_CLASS_INVARIANT_TPL( size() >= 0 )

    public: struct out_of_memory {};
    public: struct error {};

    CONTRACT_CONSTRUCTOR_TPL(
        public explicit (array) ( size_t count )
            precondition( count >= 0 )
            postcondition( size() == count )
            // Function try-blocks are programmed within the macros only for
            // constructors with member initializers otherwise they are
            // programmed with the body definitions and outside the macros.
            try initialize( // Try block for constructor initializers and body.
                data_(new T[count]),
                size_(count)
            // Use `BOOST_IDENTITY_TYPE` if the exception type has unwrapped
            // commas or leading symbols.
            ) catch(std::bad_alloc&) (
                throw out_of_memory();
            ) catch(...) (
                throw error();
            )
    ) {}

    CONTRACT_DESTRUCTOR_TPL(
        public virtual (~array) ( void ) throw( void ) // Throw nothing.
    ) {
        delete[] data_;
    }

    // ...
//]

    CONTRACT_FUNCTION_TPL(
        public size_t (size) ( void ) const
    ) {
        return size_;
    }

    CONTRACT_FUNCTION_TPL(
        public (T&) operator([])(at) ( size_t index )
            precondition( index >= 0, index < size() )
    ) {
        return data_[index];
    }

    private: T* data_;
    private: size_t size_;
};

int main ( void )
{
    array<int> a(3);
    BOOST_TEST(a.size() == 3);
    a[0] = 1; BOOST_TEST(a[0] == 1);
    a[1] = 2; BOOST_TEST(a[1] == 2);
    a[2] = 3; BOOST_TEST(a[2] == 3);
    return boost::report_errors();
}

