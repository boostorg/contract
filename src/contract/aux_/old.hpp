// Copyright (C) 2009-2010 Lorenzo Caminiti.
// Use, modification, and distribution is subject to the
// Contract++ Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt.)

#ifndef CONTRACT_AUX_OLD_HPP_
#define CONTRACT_AUX_OLD_HPP_

#include "../old.hpp"
#include <boost/mpl/bool.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/type_traits.hpp>

namespace contract { namespace aux {

// Old //

template<typename T> struct old { typedef noold type; };
template<typename T> struct old< copyable<T> > { typedef T type; };

// Copyable //

template<typename T> struct remove_copyable { typedef T type; };
template<typename T> struct remove_copyable< copyable<T> >
    { typedef T type; };

template<typename T> struct is_copyable: boost::mpl::false_ {};
template<typename T> struct is_copyable< copyable<T> >:
    boost::mpl::true_ {};

template<typename T> struct copyable_add_pointer
    { typedef typename boost::add_pointer<T>::type type; };
template<typename T> struct copyable_add_pointer< copyable<T> >
    { typedef copyable<typename boost::add_pointer<T>::type> type; };

}} // namespace

#endif // #include guard
