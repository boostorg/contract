/**
 * @file
 * @author Copyright (C) 2009 Lorenzo Caminiti.
 *  Distributed under DBC++ Software License (see file LICENSE_1_0.txt).
 */

#ifndef DBC_TYPE_TRAITS_HPP_
#define DBC_TYPE_TRAITS_HPP_

#define DBC_ADD_CONST_REF_(typename_keyword, the_type) \
    typename_keyword ::dbc::add_const_ref_< the_type >::type
//    const typename_keyword ::dbc::remove_const_<
//    typename_keyword ::dbc::remove_ref_< the_type >::type>::type&

// Implement metafunctions similar (but much simpler) to Boost.TypeTraits to 
// work-around some Boost compiler specific bugs (gcc bugs: #23771, #23691).

namespace dbc {

template<typename T> struct add_const_ref_ { typedef const T& type; };
template<typename T> struct add_const_ref_<T&> { typedef const T& type; };
template<typename T> struct add_const_ref_<const T&> { typedef const T& type; };
template<typename T> struct add_const_ref_<T*> { typedef const T* type; };
template<typename T> struct add_const_ref_<const T*> { typedef const T* type; };

// Remove const //

/** Primary template, remove nothing. */
template<typename T> struct remove_const_ { typedef T type; };

/** Specialization to remove const. */
template<typename T> struct remove_const_<const T> { typedef T type; };

/** Specialization to remove const from pointers. */
template<typename T> struct remove_const_<const T*> { typedef T* type; };

// Remove & //

/** Primary template, remove nothing. */
template<typename T> struct remove_ref_ { typedef T type; };

/** Specialization to remove only reference. */
template<typename T> struct remove_ref_<T&> { typedef T type; };

} // namespace dbc

#endif // DBC_TYPE_TRAITS_HPP_

