/**
 * @file
 * Support for "old" (for copyable types) in postconditions.
 * @author Copyright (C) 2009 Lorenzo Caminiti.
 *  Distributed under DBC++ Software License v1.0 (see file LICENSE_1_0.txt).
 */

#ifndef DBC_POST_HPP_
#define DBC_POST_HPP_

#include "detail/pp/defines.hpp"

#ifndef DBC

#define DBC_COPYABLE(type) (type)

#else // DBC

#include "detail/logging.hpp"
#include "detail/type_traits.hpp"
#include <boost/type_traits.hpp>
#include <boost/mpl/assert.hpp>

// Prefix must match symbol postfix of DBC_PP_BASE_dbc_copyable_ macro name.
#define DBC_COPYABLE(type) (dbc_copyable_)(type)

#define DBC_ADD_POST_(typename_keyword, the_type) \
    ::dbc::post<typename_keyword ::dbc::remove_const_< \
    typename_keyword ::dbc::remove_ref_< the_type >::type>::type>

#define DBC_ADD_POST_CONST_REF_(typename_keyword, the_type) \
    const DBC_ADD_POST_(typename_keyword, the_type)&

namespace dbc {

// Copyable //

/** Tag specified type as copyable. */
template<typename T> struct copyable { typedef T type; };

template<typename T>
struct is_not_copyable_ { static const bool value = true; };

template<typename T>
struct is_not_copyable_<copyable<T> > { static const bool value = false; };

/** Primary template, remove nothing. */
template<typename T> struct remove_copyable_ { typedef T type; };

/** Specialization to remove copyable. */
template<typename T> struct remove_copyable_<copyable<T> > { typedef T type; };

// Post //

/** Primary template, does not assume T is copyable (old unavailable). */
template<typename T>
class post {
public:
    // A ref (no obj copy).
    const typename remove_const_<typename remove_ref_<T>::type>::type& now;

    explicit post(const typename remove_const_<typename 
            remove_ref_<T>::type>::type& orig): now(orig) {}

    /** @tparam D Type derived from T. */
    template<typename D>
    explicit post(const post<D>& derived): now(derived.now) {
        BOOST_MPL_ASSERT_MSG((boost::is_base_of<T, D>::value),
                DBC_ERROR_D_must_derive_from_T_, ());
    }
};

/** Primary template, does not assume T is copyable (old unavailable). */
template<typename T>
class post<T*> {
public:
    // A ref (no obj copy).
    const typename remove_const_<T>::type* now;

    explicit post(const typename remove_const_<T>::type* orig): now(orig) {}

    /** @tparam D Type derived from T. */
    template<typename D>
    explicit post(const post<D>& derived): now(derived.now) {
        BOOST_MPL_ASSERT_MSG((boost::is_base_of<T, D>::value),
                DBC_ERROR_D_must_derive_from_T_, ());
    }
};

/** Specialization for bare or reference to copyable T (old is available). */
template<typename T>
class post<copyable<T> > {
public:
    // Not a ref, will copy obj.
    const typename remove_const_<typename remove_ref_<T>::type>::type old;
    // A ref (no obj copy).
    const typename remove_const_<typename remove_ref_<T>::type>::type& now;

    explicit post(const typename remove_const_<typename 
            remove_ref_<T>::type>::type& orig): old(orig), now(orig) {
        DBC_LOG_DEBUG_(log << "post<" << typeid(T).name() 
                << ">: copied from original object");
    }

    /** @tparam D Type derived from T. */
    template<typename D>
    explicit post(const post<copyable<D> >& derived): 
            old(derived.old), now(derived.now) {
        BOOST_MPL_ASSERT_MSG((boost::is_base_of<T, D>::value),
                DBC_ERROR_D_must_derive_from_T_, ());
        DBC_LOG_DEBUG_(log << "post< " << typeid(T).name() 
                << ">: copied from derived object of type " 
                << typeid(D).name());
    }
};

/** Specialization for pointer to copyable T (old is available). */
template<typename T>
class post<copyable<T*> > {
public:
    // Owned ptr, will copy obj (must be deallocated).
    const typename remove_const_<T>::type* old;
    // Not owned ptr (no obj copy).
    const typename remove_const_<T>::type* now;

    explicit post(const typename remove_const_<T>::type* orig): 
            old(new typename remove_const_<T>::type(*orig)), now(orig) {
        DBC_LOG_DEBUG_(log << "post<" << typeid(T*).name() 
                << ">: copied from original object");
    }

    /** @tparam D Type derived from T. */
    template<typename D>
    explicit post(const post<copyable<D*> >& derived): old(new typename 
            remove_const_<T>::type(*(derived.old))), now(derived.now) {
        BOOST_MPL_ASSERT_MSG((boost::is_base_of<T, D>::value),
                DBC_ERROR_D_must_derive_from_T_, ());
        DBC_LOG_DEBUG_(log << "post< " << typeid(T*).name() 
                << ">: copied from derived object of type " 
                << typeid(D*).name());
    }

    ~post() { delete old; /* old != 0 always after constr */ }
};

} // namespace dbc

#endif // DBC

#endif // DBC_POST_HPP_

