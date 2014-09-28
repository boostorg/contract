
// Copyright (C) 2008-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://sourceforge.net/projects/contractpp

#include <contract.hpp>
#include <boost/detail/lightweight_test.hpp>
#include <string>
#include <vector>
#include <new>

//[member_operator_string
CONTRACT_CLASS(
    class (string)
) {
    CONTRACT_CLASS_INVARIANT(
        static class( pointers >= 0, arrays >= 0 )
    )

    public: static int pointers;
    public: static int arrays;

    CONTRACT_CONSTRUCTOR(
        public explicit (string) ( (char const*) c_str, default("") )
            initialize( string_(c_str) )
    ) {}

    CONTRACT_DESTRUCTOR(
        public (~string) ( void )
    ) {}

    CONTRACT_FUNCTION( // Symbolic operators: `(==)(equal)`, `(())(call)`, etc.
        public bool operator(==)(equal) ( (string const&) right ) const
    ) {
        return string_ == right.string_;
    }

    CONTRACT_FUNCTION( // Implicit type conversion operator (keyword type).
        public operator char const ( void ) const
    ) {
        return string_[0];
    }
    
    CONTRACT_FUNCTION( // Implicit type conversion operator (symbolic type).
        public operator(char const*)(char_const_ptr) ( void ) const
    ) {
        return string_.c_str();
    }

    CONTRACT_FUNCTION( // Implicit type conversion operator (type with commas).
        public template( typename T, class Allocator )
        operator(std::vector<T, Allocator>)(std_vector) ( void ) const
    ) {
        std::vector<T, Allocator> v(string_.size());
        for(size_t i = 0; i < string_.size(); ++i) v[i] = string_[i];
        return v;
    }

    CONTRACT_FUNCTION( // Comma operator (use `comma` to diff. from above).
        public (string&) operator comma ( (string const&) right )
    ) {
        string_ += right.string_;
        return *this;
    }

    // All memory operators (new, delete, new[], and delete[]) must be
    // explicitly `static` (because pp can't inspect new[] and delete[] that
    // could be any symbolic operator like ==, +, etc).

    CONTRACT_FUNCTION(
        public static (void*) operator new ( size_t size )
    ) {
        void* p = malloc(size);
        if(p == 0) throw std::bad_alloc();
        pointers++;
        return p;
    }

    CONTRACT_FUNCTION(
        public static void operator delete ( (void*) pointer )
    ) {
        if(pointer) {
            free(pointer);
            pointers--;
        }
    }
 
    CONTRACT_FUNCTION(
        public static (void*) operator(new[])(new_array) ( size_t size )
    ) {
        void* a = malloc(size);
        if(a == 0) throw std::bad_alloc();
        arrays++;
        return a;
    }

    CONTRACT_FUNCTION(
        public static void operator(delete[])(delete_array) ( (void*) array )
    ) {
        if(array) {
            free(array);
            arrays--;
        }
    }

    private: std::string string_;
};

int string::pointers = 0;
int string::arrays = 0;
//]
    
int main ( void )
{
    string const xyz("xyz");
    
    string s("abc"); BOOST_TEST(s == string("abc"));
    BOOST_TEST((s, xyz) == string("abcxyz"));

    char x = xyz; BOOST_TEST(x == 'x');
    char const* c_xyz = xyz; BOOST_TEST(string(c_xyz) == xyz);

    std::vector<char, std::allocator<char> > v = xyz;
    BOOST_TEST(v[0] == 'x' && v[1] == 'y' && v[2] == 'z'); 

    string* p = new string; BOOST_TEST(string::pointers == 1);
    delete p; BOOST_TEST(string::pointers == 0);
    
    string* a = new string[5]; BOOST_TEST(string::arrays == 1);
    delete[] a; BOOST_TEST(string::arrays == 0);

    return boost::report_errors();
}

