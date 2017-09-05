// Copyright (C) 2009-2010 Lorenzo Caminiti.
// Use, modification, and distribution is subject to the
// Contract++ Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt.)

#ifndef CONTRACT_AUX_ARG_HPP_
#define CONTRACT_AUX_ARG_HPP_

#include <boost/type_traits.hpp>

namespace contract {

class noold; // Farward declaration.

namespace aux {

// To ensure CONSTANT-CORRECTNESS:
// 1) Arguments are usually passed by cont& -- this makes sure that
//    the referenced object is const and cannot be modified but the
//    reference could be modified. This is the way C++ usually uses 
//    reference for const because eventual modifications to the
//    reference will have local scope plus they are usually not
//    possible because copy operators and constructors operatorate on
//    const&. (The reference could be made const& const to absolutely
//    avoid any modification also to the reference itself...)
// 2) Pointers are passed as const* -- this makes sure that the
//    pointed object is const and cannot be modified but the pointer 
//    itself can still be modified. This is the way C++ usually uses
//    pointers for const because eventual modification to the pointer
//    only have local scope so do not violate const correctness. (The
//    pointer could be passed as const* const to also prevent
//    modification to the pointer itself...)
// 3) noold is passed by value (this does not affect
//    constant-correctness because noold has no member so it cannot 
//    be used to do anything.

template<typename T>
struct arg {
    typedef typename boost::add_reference<typename
            boost::add_const<T>::type>::type type; // T const&
};

template<typename T>
struct arg<T*> {
    typedef typename boost::add_pointer<typename
            boost::add_const<T>::type>::type type; // T const*
};

// Keep outer const for ptr if specified by user (but do not add it).
template<typename T>
struct arg<T* const> {
    typedef typename boost::add_pointer<typename
            boost::add_const<T>::type>::type const type; // T const* const
};

// Avoid adding a reference to a reference (which gives an error).
template<typename T>
struct arg<T&> {
    typedef typename boost::add_reference<typename
            boost::add_const<T>::type>::type type; // T const&
};

template<>
struct arg<contract::noold> {
    typedef noold type; // noold (passed by value)
};

}} // namespace

#endif // #include guard

