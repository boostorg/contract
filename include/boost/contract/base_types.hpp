
#ifndef BOOST_CONTRACT_BASE_TYPES_HPP_
#define BOOST_CONTRACT_BASE_TYPES_HPP_

// Copyright (C) 2008-2016 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0 (see accompanying
// file LICENSE_1_0.txt or a copy at http://www.boost.org/LICENSE_1_0.txt).
// See: http://www.boost.org/doc/libs/release/libs/contract/doc/html/index.html

// TODO: Document the max number of bases is 20 because of Boost.MPL vector limit. If Boost.MPL vector and related alg impl was to change to use variadic templates in the future there will be not limit to max bases (but for now this high limit is better than the extra complexity of reimpl all Boost.MPL vector, etc. within this lib with variadic templates).

/** @file
Facilities to specify base classes so to support subcontracting.
*/

#include <boost/contract/detail/all_core_headers.hpp>
#include <boost/preprocessor/config/config.hpp>

#if !BOOST_PP_VARIADICS
    
#define BOOST_CONTRACT_BASE_TYPES \
BOOST_CONTRACT_ERROR_macro_BASE_TYPES_requires_variadic_macros_otherwise_manually_program_base_types

#elif defined(BOOST_CONTRACT_NO_PUBLIC_FUNCTIONS)

/**
Variadic macro to program base classes @c typedef.
A class that has contracts for one or more overriding public functions must
declare a @c typedef named @RefMacro{BOOST_CONTRACT_BASE_TYPEDEF} using this
macro.
This @c typedef can be programmed manually without this macro on compilers that
do not support variadic macros (see @RefSect{advanced_topics, Advanced Topics}).
@see @RefSect{tutorial, Tutorial}.
@param ...  Comma separated list of base classes with must explicitly list their
            access (@c public, @c protected, or @c private) and @c virtual (if
            present) specifiers.
*/
#define BOOST_CONTRACT_BASE_TYPES(...) void /* dummy type for typedef */

#else // contracts on

#include <boost/mpl/vector.hpp>
#include <boost/contract/detail/preprocessor/keyword/virtual.hpp>
#include <boost/contract/detail/preprocessor/keyword/public.hpp>
#include <boost/contract/detail/preprocessor/keyword/protected.hpp>
#include <boost/contract/detail/preprocessor/keyword/private.hpp>
#include <boost/preprocessor/variadic/to_seq.hpp>
#include <boost/preprocessor/seq/fold_left.hpp>
#include <boost/preprocessor/seq/enum.hpp>
#include <boost/preprocessor/seq/push_back.hpp>
#include <boost/preprocessor/seq/size.hpp>
#include <boost/preprocessor/seq/seq.hpp> // For HEAD, TAIL, etc.
#include <boost/preprocessor/tuple/elem.hpp>
#include <boost/preprocessor/tuple/rem.hpp>
#include <boost/preprocessor/tuple/eat.hpp>
#include <boost/preprocessor/comparison/equal.hpp>
#include <boost/preprocessor/control/iif.hpp>
#include <boost/preprocessor/facilities/expand.hpp>

/* PRIVATE */

#define BOOST_CONTRACT_BASE_TYPES_REMOVE_VIRTUAL_(base) \
    BOOST_PP_EXPAND( \
        BOOST_PP_IIF(BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_VIRTUAL(base), \
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_REMOVE_VIRTUAL \
        , \
            BOOST_PP_TUPLE_REM(1) \
        )(base) \
    )

#define BOOST_CONTRACT_BASE_TYPES_PUSH_BACK_IF_(is_public, types_nilseq, base) \
    ( \
        is_public, \
        BOOST_PP_IIF(is_public, \
            BOOST_PP_SEQ_PUSH_BACK \
        , \
            types_nilseq BOOST_PP_TUPLE_EAT(2) \
        )(types_nilseq, base) \
    )

#define BOOST_CONTRACT_BASE_TYPES_SKIP_NOT_PUBLIC_(is_public, types_nilseq, \
        base) \
    (0, types_nilseq)

// Precondition: base = `public [virtual] ...`.
#define BOOST_CONTRACT_BASE_TYPES_PUSH_BACK_PUBLIC_(is_public, types_nilseq, \
        base) \
    ( \
        1, \
        BOOST_PP_SEQ_PUSH_BACK(types_nilseq, \
            BOOST_CONTRACT_BASE_TYPES_REMOVE_VIRTUAL_( \
                    BOOST_CONTRACT_DETAIL_PP_KEYWORD_REMOVE_PUBLIC(base)) \
        ) \
    )

#define BOOST_CONTRACT_BASE_TYPES_ACCESS_(is_public, types_nilseq, base) \
    BOOST_PP_IIF(BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_PUBLIC(base), \
        BOOST_CONTRACT_BASE_TYPES_PUSH_BACK_PUBLIC_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_PROTECTED(base), \
        BOOST_CONTRACT_BASE_TYPES_SKIP_NOT_PUBLIC_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_PRIVATE(base), \
        BOOST_CONTRACT_BASE_TYPES_SKIP_NOT_PUBLIC_ \
    , \
        BOOST_CONTRACT_BASE_TYPES_PUSH_BACK_IF_ \
    )))(is_public, types_nilseq, base)

#define BOOST_CONTRACT_BASE_TYPES_(s, public_types, base) \
    BOOST_CONTRACT_BASE_TYPES_ACCESS_( \
        BOOST_PP_TUPLE_ELEM(2, 0, public_types), \
        BOOST_PP_TUPLE_ELEM(2, 1, public_types), \
        BOOST_CONTRACT_BASE_TYPES_REMOVE_VIRTUAL_(base) \
    )

#define BOOST_CONTRACT_BASE_TYPES_RETURN_YES_(types_nilseq) \
    BOOST_PP_SEQ_ENUM(BOOST_PP_SEQ_TAIL(types_nilseq))

#define BOOST_CONTRACT_BASE_TYPES_RETURN_(types_nilseq) \
    BOOST_PP_IIF(BOOST_PP_EQUAL(BOOST_PP_SEQ_SIZE(types_nilseq), 1), \
        BOOST_PP_TUPLE_EAT(1) \
    , \
        BOOST_CONTRACT_BASE_TYPES_RETURN_YES_ \
    )(types_nilseq)

#define BOOST_CONTRACT_BASE_TYPES_OK_(base_tuple, bases_seq) \
    boost::mpl::vector< \
        BOOST_CONTRACT_BASE_TYPES_RETURN_(BOOST_PP_TUPLE_ELEM(2, 1, \
            BOOST_PP_SEQ_FOLD_LEFT( \
                BOOST_CONTRACT_BASE_TYPES_, \
                (0, (BOOST_PP_NIL)), \
                bases_seq \
            ) \
        )) \
    >

#define BOOST_CONTRACT_BASE_TYPES_ERR_(bases_tuple, bases_seq) \
    BOOST_CONTRACT_ERROR_all_bases_must_explicitly_specify_public_protected_or_private base_tuple

#define BOOST_CONTRACT_BASE_TYPES_IS_ACCESS_(base) \
    BOOST_PP_IIF(BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_PUBLIC(base), \
        1 \
    , BOOST_PP_IIF(BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_PROTECTED(base), \
        1 \
    , BOOST_PP_IIF(BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_PRIVATE(base), \
        1 \
    , \
        0 \
    )))

// Cannot check that all base types have access specifiers (unless users have to
// specify bases using pp-seq, because user specified base list can have
// unwrapped commas between bases but also within a given base type, when base
// types are templates), but at least check the very first base type explicitly
// specifies access `[virtual] public | protected | private [virtual] ...`.
#define BOOST_CONTRACT_BASE_TYPES_CHECK_(bases_tuple, bases_seq) \
    BOOST_PP_IIF(BOOST_CONTRACT_BASE_TYPES_IS_ACCESS_( \
            BOOST_CONTRACT_BASE_TYPES_REMOVE_VIRTUAL_(BOOST_PP_SEQ_HEAD( \
                    bases_seq))), \
        BOOST_CONTRACT_BASE_TYPES_OK_ \
    , \
        BOOST_CONTRACT_BASE_TYPES_ERR_ \
    )(bases_tuple, bases_seq)

/* PUBLIC */

#define BOOST_CONTRACT_BASE_TYPES(...) \
    BOOST_CONTRACT_BASE_TYPES_CHECK_((__VA_ARGS__), \
            BOOST_PP_VARIADIC_TO_SEQ(__VA_ARGS__))

#endif // contract on/off

#endif // #include guard

