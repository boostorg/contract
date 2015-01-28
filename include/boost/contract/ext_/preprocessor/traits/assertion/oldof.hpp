
#ifndef BOOST_CONTRACT_EXT_PP_OLDOF_ASSERTION_TRAITS_HPP_
#define BOOST_CONTRACT_EXT_PP_OLDOF_ASSERTION_TRAITS_HPP_

#include <boost/contract/ext_/preprocessor/traits/oldof.hpp>
#include <boost/contract/ext_/preprocessor/traits/assertion/oldof/assign.hpp>
#include <boost/contract/ext_/preprocessor/traits/assertion/oldof/type.hpp>
#include <boost/contract/ext_/preprocessor/traits/assertion/oldof/expr.hpp>
#include <boost/contract/ext_/preprocessor/traits/assertion/bool/expr.hpp>

/* PRIVATE */

#define BOOST_CONTRACT_EXT_PP_OLDOF_ASSERTION_TRAITS_DONE_(decl_traits) \
    ( \
        BOOST_PP_TUPLE_ELEM(2, 0, decl_traits), \
        BOOST_CONTRACT_EXT_PP_TRAITS_DONE( \
                BOOST_PP_TUPLE_ELEM(2, 1, decl_traits)) \
    )

/* PUBLIC */

// Precondition: oldofdecl_booltraits =
// `(OLDOF expr, (bool) (auto-wrapped-type assign =)` (which is here transformed
// to the parsalbe decl = `(OLDOF expr) auto-wrapped-type assign =`).
#define BOOST_CONTRACT_EXT_PP_OLDOF_ASSERTION_TRAITS_REPLACE_PARSE_D( \
        d, oldofdecl_booltraits) \
    BOOST_CONTRACT_EXT_PP_OLDOF_ASSERTION_TRAITS_DONE_( \
    BOOST_CONTRACT_EXT_PP_OLDOF_ASSERTION_TRAITS_ASSIGN_PARSE( \
    BOOST_CONTRACT_EXT_PP_OLDOF_ASSERTION_TRAITS_TYPE_PARSE_D(d, \
    BOOST_CONTRACT_EXT_PP_OLDOF_ASSERTION_TRAITS_EXPR_PARSE( \
    BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_SET_KIND_PARSE( \
        BOOST_CONTRACT_EXT_PP_TRAITS_OLDOF, \
        ( \
            (BOOST_PP_TUPLE_ELEM(2, 0, oldofdecl_booltraits)) \
            BOOST_CONTRACT_EXT_PP_BOOL_ASSERTION_TRAITS_EXPR( \
                    BOOST_PP_TUPLE_ELEM(2, 1, oldofdecl_booltraits)) \
            BOOST_PP_NIL, \
            BOOST_CONTRACT_EXT_PP_TRAITS_INIT \
        ) \
    )))))

#endif // #include guard

