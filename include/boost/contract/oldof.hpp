
#ifndef BOOST_CONTRACT_OLDOF_HPP_
#define BOOST_CONTRACT_OLDOF_HPP_

#include <boost/contract/virtual_body.hpp>
#include <boost/contract/config.hpp>
#include <boost/contract/aux_/oldof.hpp>
#include <boost/contract/aux_/virtual_call.hpp>
#include <boost/type_traits/remove_reference.hpp>
#include <boost/optional.hpp>
#include <boost/preprocessor/config/config.hpp>
#include <boost/config.hpp>

// TODO: There is a problem with old-of of virtual body functions for which
// old-of of the base function are evaluated *after* the derived virtual
// function body is executed (so invalidating old-of values)... Can I fix this?
// Maybe passing a (mutable) pointer v and implementing a "stack" (like a map
// of boost::any indexed by old-of #) inside the mutable object pointed by v...

// IMPORTANT: Following old-of templates and macros ensure that:
//  1.  Old-value expressions are evaluated only once and only when old-of
//      should not be skipped.
//  2.  Old-values are copied only once (using old-value type copy constructor)
//      and only when old-of should not be skipped.
// Old-of are skipped if either postconditions are disabled all together (see
// also CONFIG_NO_POSTCONDITONS), or if virtual-body functions are called to
// not check postconditions (as controlled by the "v" extra parameter).

#if !BOOST_PP_VARIADICS

#define BOOST_CONTRACT_OLDOF BOOST_CONTRACT_ERROR_variadic_macros_required_by_BOOST_CONTRACT_OLDOF_otherwise_manually_program_old_values

#else

#include <boost/preprocessor/facilities/overload.hpp>
#include <boost/preprocessor/cat.hpp>

/* PUBLIC */

#define BOOST_CONTRACT_OLDOF(...) \
    BOOST_PP_CAT(BOOST_PP_OVERLOAD( /* CAT(... EMPTY()) workaround for MSVC */ \
BOOST_CONTRACT_ERROR_macro_BOOST_CONTRACT_OLDOF_invalid_number_of_arguments_, \
            __VA_ARGS__)(__VA_ARGS__), BOOST_PP_EMPTY())

/* PRIVATE */

// NOTE: Following are not local macros, do NOT #undef them. These macro names
// are use so all variadic macro argument numbers > 2 will generate appropriate
// ERROR symbols.

#define \
BOOST_CONTRACT_ERROR_macro_BOOST_CONTRACT_OLDOF_invalid_number_of_arguments_1( \
        value) \
    (boost::contract::oldof BOOST_CONTRACT_OLDOF_TYPEOF_(value) ( \
        boost::contract::copy_oldof() ? value : boost::contract::oldof() \
    ))

#define \
BOOST_CONTRACT_ERROR_macro_BOOST_CONTRACT_OLDOF_invalid_number_of_arguments_2( \
        v, value) \
    (boost::contract::oldof BOOST_CONTRACT_OLDOF_TYPEOF_(value) ( \
        v, boost::contract::copy_oldof(v) ? value : boost::contract::oldof() \
    ))

#ifdef BOOST_NO_CXX11_AUTO_DECLARATIONS
#   define BOOST_CONTRACT_OLDOF_TYPEOF_(value) /* nothing */
#else
#   include <boost/typeof/typeof.hpp>
#   define BOOST_CONTRACT_OLDOF_TYPEOF_(value) <BOOST_TYPEOF(value)>
#endif

#endif // VARIADICS

/* CODE */

namespace boost { namespace contract {

bool copy_oldof(boost::contract::virtual_body v = 0) {
#ifdef BOOST_CONTRACT_CONFIG_NO_POSTCONDITIONS
    return false; // Never check post, so old-of never copied.
#else
    // Copy if user call (also !v) or virtual contract call for copy.
    return !v || v->action == boost::contract::aux::virtual_call::user_call ||
            v->action == boost::contract::aux::virtual_call::copy_oldof;
#endif
}

boost::contract::aux::oldof oldof() { return boost::contract::aux::oldof(); }

// Un-erasure via explicit type T so to allow to use C++11 auto decl.
template<typename T>
boost::shared_ptr<typename boost::remove_reference<T>::type const>
oldof(boost::contract::virtual_body v,
        boost::contract::aux::oldof const& old) {
    return boost::contract::aux::oldof(v, old);
}

// Un-erasure will be done based on explicit decl type (no auto allowed).
boost::contract::aux::oldof oldof(boost::contract::virtual_body const v,
        boost::contract::aux::oldof const& old) {
    return boost::contract::aux::oldof(v, old);
}

// Un-erasure via explicit type T so to allow to use C++11 auto decl.
template<typename T>
boost::shared_ptr<typename boost::remove_reference<T>::type const> oldof(
        boost::contract::aux::oldof const& old) {
    return boost::contract::aux::oldof(0, old);
}

// Un-erasure will be done based on explicit decl type (no auto allowed).
boost::contract::aux::oldof oldof(boost::contract::aux::oldof const& old) {
    return boost::contract::aux::oldof(0, old);
}

} } // namespace

#endif // #include guard

