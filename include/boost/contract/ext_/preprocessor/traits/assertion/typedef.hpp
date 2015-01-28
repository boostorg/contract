
#ifndef BOOST_CONTRACT_EXT_PP_TYPEDEF_ASSERTION_TRAITS_HPP_
#define BOOST_CONTRACT_EXT_PP_TYPEDEF_ASSERTION_TRAITS_HPP_

#include <boost/contract/ext_/preprocessor/traits/assertion/typedef/new_name.hpp>
#include <boost/contract/ext_/preprocessor/traits/assertion/typedef/name.hpp>
#include <boost/contract/ext_/preprocessor/traits/assertion/kind.hpp>

/* PRIVATE */

#define BOOST_CONTRACT_EXT_PP_TYPEDEF_ASSERTION_TRAITS_DONE_(decl_traits) \
    ( \
        BOOST_PP_TUPLE_ELEM(2, 0, decl_traits), \
        BOOST_CONTRACT_EXT_PP_TRAITS_DONE( \
                BOOST_PP_TUPLE_ELEM(2, 1, decl_traits)) \
    )

/* PUBLIC */

// TODO: I cannot keep repeating this DONE macro everywhere... in
// utility/adt.hpp (rename it back to that from traits.hpp) provide INIT and
// DONE macros that do not alter decl but INIT and DONE traits:
// #define DECL_TRAITS_INIT(decl) (decl, TRAITS_INIT)
// #define DECL_TRAITS_DONE(decl_traits) (decl, TRAITS_DONE(traits))
// Then ideally, I'd remove TRAITS_INIT/DONE and always force the user to use
// DECL_TRAITS_INIT/DONE... but can I do this?

// Precondition: decl = `typedef wrapped-type new-name`.
#define BOOST_CONTRACT_EXT_PP_TYPEDEF_ASSERTION_TRAITS_PARSE_D(d, decl) \
    BOOST_CONTRACT_EXT_PP_TYPEDEF_ASSERTION_TRAITS_DONE_( \
    BOOST_CONTRACT_EXT_PP_TYPEDEF_ASSERTION_TRAITS_NEW_NAME_PARSE( \
    BOOST_CONTRACT_EXT_PP_TYPEDEF_ASSERTION_TRAITS_NAME_PARSE_D(d, \
    BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_SET_KIND_PARSE(typedef, \
        (decl BOOST_PP_NIL, BOOST_CONTRACT_EXT_PP_TRAITS_INIT) \
    ))))

// ASSERTION_TRAITS_KIND(traits) expands to `typedef` for this assertion.

#endif // #include guard

