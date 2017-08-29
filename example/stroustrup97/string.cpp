
// Copyright (C) 2008-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://sourceforge.net/projects/contractpp

//[stroustrup97_string
// File: string.cpp
#include "string.hpp"

CONTRACT_CONSTRUCTOR_BODY(string, string) ( const char* chars )
    { init(chars); }

CONTRACT_CONSTRUCTOR_BODY(string, string) ( const string& other )
    { init(other.chars_); }

CONTRACT_DESTRUCTOR_BODY(string, ~string) ( void )
    { delete[] chars_; }

char& CONTRACT_MEMBER_BODY(string, operator([])(at)) ( int index )
    { return chars_[index]; }

int CONTRACT_MEMBER_BODY(string, size) ( void ) const { return size_; }

void CONTRACT_MEMBER_BODY(string, init) ( const char* chars ) {
    size_ = strlen(chars);
    chars_ = new char[size_ + 1];
    for(int i = 0; i < size_; ++i) chars_[i] = chars[i];
    chars_[size_] = '\0';
}
//]

