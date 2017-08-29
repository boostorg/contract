/**
 * @file
 * @author Copyright (C) 2009 Lorenzo Caminiti.
 *  Distributed under Eiffel for C++ Software License.
 */

#ifndef DBC_SEPARATING_TYPE_TRAITS_HPP_
#define DBC_SEPARATING_TYPE_TRAITS_HPP_

#include <boost/mpl/if.hpp>
#include <boost/mpl/find_if.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/mpl/or.hpp>
#include <boost/mpl/and.hpp>
#include <boost/mpl/not.hpp>
#include <boost/type_traits.hpp>
#include <iostream>

namespace dbc {
/** @todo[LC] Once finalized, merge this stuff into dbc/details/type_traits.hpp
 * -- that is why this is left out of the 'separating' namespace. */

// Const (boost::is_const is only for top-level const) //

template<typename T> struct is_const: boost::false_type {};
template<typename T> struct is_const<const T>: boost::true_type {};
template<typename T> struct is_const<const T*>: boost::true_type {};
template<typename T> struct is_const<const T&>: boost::true_type {};

// In/Out Args //

template<typename T> struct is_inout:
    boost::mpl::and_<
        boost::mpl::not_<is_const<T> >
        , boost::mpl::or_<boost::is_reference<T>, boost::is_pointer<T> >
    >::type {};

template<typename T> struct is_in: boost::mpl::not_<is_inout<T> >::type {};

// Command/Query Functions //

/** @future These templates would be better if they operate on a single tparam
 * "F" like Boost.FunctionTypes. However, Boost.FunctionTypes is not part of
 * Boost 1.34.1 (current on Ubuntu) so "F" cannot be implemented yet. */

template<typename R, typename Args> struct is_command:
    boost::mpl::and_<
        boost::is_void<R>
        , boost::is_same<
            typename boost::mpl::find_if<Args, is_inout<boost::mpl::_> >::type
            , typename boost::mpl::end<Args>::type
        >
    >::type {};

template<typename R, typename Args> struct is_query:
    boost::mpl::not_<is_command<R, Args> >::type {};

} // namespace dbc

#endif // DBC_SEPARATING_TYPE_TRAITS_HPP_

