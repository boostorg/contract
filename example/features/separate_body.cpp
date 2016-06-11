
// Copyright (C) 2008-2016 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0 (see accompanying
// file LICENSE_1_0.txt or a copy at http://www.boost.org/LICENSE_1_0.txt).
// See: http://www.boost.org/doc/libs/release/libs/contract/doc/html/index.html

#include "separate_body.hpp"
#include <cassert>

//[separate_body_cpp
template<typename T, unsigned MaxSize>
void array<T, MaxSize>::constructor_body(unsigned count) {
    for(unsigned i = 0; i < count; ++i) values_[i] = T();
    size_ = count;
}

template<typename T, unsigned MaxSize>
void array<T, MaxSize>::destructor_body() { delete[] values_; }

template<typename T, unsigned MaxSize>
void array<T, MaxSize>::push_back_body(T const& value) {
    values_[size_++] = value;
}

/* ... */
//]

template<typename T, unsigned MaxSize>
unsigned array<T, MaxSize>::size_body() const { return size_; }

int main() {
    array<char, 3> a(2);
    assert(a.size() == 2);
    a.push_back('x');
    assert(a.size() == 3);
    return 0;
}

