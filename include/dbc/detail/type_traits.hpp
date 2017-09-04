
#ifndef DBC_TYPE_TRAITS_HPP_
#define DBC_TYPE_TRAITS_HPP_

#include "../copyable.hpp"

#define DBC_ADD_CONST_REF_(typename_keyword, the_type) \
    const typename_keyword ::dbc::remove_const_ref_< the_type >::type&

// Implement metafunctions similar (but much simpler) to Boost.TypeTraits to 
// work-around some Boost compiler specific (gcc) bugs (bugs: #23771, #23691).

namespace dbc {

// Remove const& //

/** Primary template, remove nothing. */
template<typename T> struct remove_const_ref_ { typedef T type; };

/** Specialization to remove only const. */
template<typename T> struct remove_const_ref_<const T> { typedef T type; };
 
/** Specialization to remove only reference. */
template<typename T> struct remove_const_ref_<T&> { typedef T type; };

/** Specialization to remove both reference and const. */
template<typename T> struct remove_const_ref_<const T&> { typedef T type; };

// Copyable //

/** Primary template, remove nothing. */
template<typename T> struct remove_copyable_ { typedef T type; };

/** Specialization to remove copyable. */
template<typename T> struct remove_copyable_<copyable<T> > { typedef T type; };

} // namespace dbc

#endif // DBC_TYPE_TRAITS_HPP_

