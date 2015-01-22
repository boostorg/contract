
#ifndef BOOST_CONTRACT_EXT_PP_ALIASES_TRAITS_HPP_
#define BOOST_CONTRACT_EXT_PP_ALIASES_TRAITS_HPP_

#include <boost/contract/ext_/preprocessor/traits/alias.hpp>
#include <boost/contract/ext_/preprocessor/traits/adt.hpp>
#include <boost/contract/ext_/preprocessor/functional/invoke.hpp>
#include <boost/contract/ext_/preprocessor/utility/empty.hpp>
#include <boost/contract/ext_/preprocessor/utility/expand.hpp>
#include <boost/preprocessor/seq/seq.hpp>
#include <boost/preprocessor/tuple/elem.hpp>
#include <boost/preprocessor/control/while.hpp>
#include <boost/preprocessor/control/iif.hpp>
#include <boost/preprocessor/facilities/empty.hpp>

/* PRIVATE */
        
#define BOOST_CONTRACT_EXT_PP_ALIASES_TRAITS_PUSH_BACK_( \
        decl_seq, traits, alias) \
    ( \
        1, \
        BOOST_PP_SEQ_TAIL(decl_seq), \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK(traits, alias) \
    )

#define BOOST_CONTRACT_EXT_PP_ALIASES_TRAITS_DONE_(decl_seq, traits, unused) \
    (0, decl_seq, traits) 
    
#define BOOST_CONTRACT_EXT_PP_ALIASES_TRAITS_OP_ARGS_( \
        d, continue_, decl_seq, traits, alias) \
    BOOST_CONTRACT_EXT_PP_EXPAND_ONCE( \
        BOOST_CONTRACT_EXT_PP_INVOKE3 \
        BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_IS_EMPTY(alias), \
            (BOOST_CONTRACT_EXT_PP_ALIASES_TRAITS_DONE_, decl_seq, traits, ~) \
        , \
            (BOOST_CONTRACT_EXT_PP_ALIASES_TRAITS_PUSH_BACK_, decl_seq, \
            traits, alias) \
        ) \
    )

#define BOOST_CONTRACT_EXT_PP_ALIASES_TRAITS_OP_(d, continue_decl_traits) \
    BOOST_CONTRACT_EXT_PP_ALIASES_TRAITS_OP_ARGS_( \
        d, \
        BOOST_PP_TUPLE_ELEM(3, 0, continue_decl_traits), \
        BOOST_PP_TUPLE_ELEM(3, 1, continue_decl_traits), \
        BOOST_PP_TUPLE_ELEM(3, 2, continue_decl_traits), \
        BOOST_CONTRACT_EXT_PP_ALIAS_TRAITS_D(d, BOOST_PP_SEQ_HEAD( \
                BOOST_PP_TUPLE_ELEM(3, 1, continue_decl_traits))) \
    )
        
#define BOOST_CONTRACT_EXT_PP_ALIASES_TRAITS_PRED_(d, continue_decl_traits) \
    BOOST_PP_TUPLE_ELEM(3, 0, continue_decl_traits)

// Implementation: SEQ_POP_BACK removes trailing NIL just added below.
#define BOOST_CONTRACT_EXT_PP_ALIASES_TRAITS_RETURN_(continue_decl_traits) \
    ( \
        BOOST_PP_SEQ_POP_BACK( \
                BOOST_PP_TUPLE_ELEM(3, 1, continue_decl_traits)), \
        BOOST_CONTRACT_EXT_PP_TRAITS_DONE(BOOST_PP_TUPLE_ELEM(3, 2, \
                continue_decl_traits)) \
    )

#define BOOST_CONTRACT_EXT_PP_ALIASES_TRAITS_(d, decl_seq) \
    BOOST_CONTRACT_EXT_PP_ALIASES_TRAITS_RETURN_( \
        BOOST_PP_WHILE_ ## d( \
            BOOST_CONTRACT_EXT_PP_ALIASES_TRAITS_PRED_, \
            BOOST_CONTRACT_EXT_PP_ALIASES_TRAITS_OP_, \
            ( \
                1, \
                decl_seq (BOOST_PP_NIL), \
                BOOST_CONTRACT_EXT_PP_TRAITS_INIT \
            ) \
        ), \
    )

/* PUBLIC */

// Precondition: decl is a pp-seq starting with aliases (but it can contain
// other declarations after the aliases), no trait parsed if pp-seq is EMPTY().
#define BOOST_CONTRACT_EXT_PP_ALIASES_TRAITS_PARSE_D(d, decl_seq) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_IS_EMPTY(decl_seq), \
        (decl_seq, BOOST_PP_EMPTY()) BOOST_PP_TUPLE_EAT(2) \
    , \
        BOOST_CONTRACT_EXT_PP_ALIASES_TRAITS_ \
    )(d, decl_seq)

#endif // #include guard

