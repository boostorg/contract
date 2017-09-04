/**
 * @file
 * @author Copyright (C) 2009 Lorenzo Caminiti.
 *  Distributed under DBC++ Software License (see file LICENSE_1_0.txt).
 */

#ifndef DBC_MFUN_HPP_
#define DBC_MFUN_HPP_

#include "detail/pp/defines.hpp" // Must be 1st include.
#include "config.hpp"

#if defined DBC_DOC

#define DBC_MEM_FUN(signature, require_code, ensure_code, body_code) \
    DBC_CONFIG_DOC_REQUIRE(require_code) \
    DBC_CONFIG_DOC_ENSURE(ensure_code) \
    body_code
#define DBC_CONSTRUCTOR(signature, require_code, ensure_code, body_code) \
    DBC_CONFIG_DOC_REQUIRE(require_code) \
    DBC_CONFIG_DOC_ENSURE(ensure_code) \
    body_code
#define DBC_DESTRUCTOR(signature, body_code) \
    /* destructor has no pre/post conditions */ \
    body_code

#elif !defined DBC || \
        (!DBC_CHECK_REQUIRE && !DBC_CHECK_ENSURE && !DBC_CHECK_INVARIANT)

#define DBC_BASE(base_class_type) (base_class_type)

#define DBC_MEM_FUN(signature, require_code, ensure_code, body_code) \
    body_code
#define DBC_CONSTRUCTOR(signature, require_code, ensure_code, body_code) \
    body_code
#define DBC_DESTRUCTOR(signature, body_code) \
    body_code

#else // DBC

#include "detail/pp/fun.hpp"
#include "detail/pp/fun_traits.hpp"
#include "detail/fun_macro_traits.hpp"
#include "body.hpp"
#include <boost/preprocessor.hpp>
#include <boost/mpl/assert.hpp>

// Public //

// Prefix must match symbol postfix of DBC_PP_BASE_dbc_base_ macro name.
#define DBC_BASE(base_class_type) (dbc_base_)(base_class_type)

#define DBC_MEM_FUN(signature, require_code, ensure_code, body_code) \
    DBC_MEM_FUN_FROM_TRAITS_(DBC_PP_MEM_FUN_(signature), \
            DBC_CONTRACT_KIND_MEM_FUN_, \
            require_code, ensure_code, body_code)

/** Constructors don't check inv w/ precond -- no obj before body exec. */
#define DBC_CONSTRUCTOR(signature, require_code, ensure_code, body_code) \
    DBC_MEM_FUN_FROM_TRAITS_(DBC_PP_CONSTRUCTOR_(signature), \
            DBC_CONTRACT_KIND_CONSTR_, \
            require_code, ensure_code, body_code)

/** Destructors have no pre/post conditions -- they only check inv at entry. */
#define DBC_DESTRUCTOR(signature, body_code) \
    DBC_MEM_FUN_FROM_TRAITS_(DBC_PP_DESTRUCTOR_(signature), \
            DBC_CONTRACT_KIND_DESTR_, \
            {/* no preconditions */}, {/* no postconditions */}, body_code)

// Private //

/** @todo[LC] This should read "if __MSVC__ don't use class, otherwise always
 * use class" but MSVC does not define __MSVC__?? Is there a better way to do
 * this? What symbol does Boost use for MSVC specific code? */
// [LC] Compiler specifi code is best avoided. It is needed here to handle
// friendship syntax for templates for MVSC.
#ifdef __GNUC__
#   define DBC_MEM_FUN_FRIEND_TEMPLATED_CLASS_ friend class
#else // __GNUC__
#   define DBC_MEM_FUN_FRIEND_TEMPLATED_CLASS_ friend // No 'class' for MSVC.
#endif // __GNUC__

/** Expand to code. */
#define DBC_MEM_FUN_CODE_(err, f, kind, \
        require_code, ensure_code, body_code) /**/ \
    /* fun invoking contract (this line follows user's fun declaration) */ \
    { \
        DBC_PP_FUN_GET_RETURN_(f) DBC_FUN_GET_CONTRACT_NAME_(f) \
                (/* invoke contract constructor */).call( \
                *this, &DBC_PP_FUN_GET_CLASS_TYPE_(f) \
                ::DBC_BODY(DBC_PP_FUN_GET_NAME_(f)) \
                DBC_FUN_GET_TRAILING_ARG_NAMES_(f), \
                BOOST_PP_STRINGIZE(DBC_PP_FUN_GET_NAME_(f))); \
    } \
    /* contract */ \
protected: \
/** @todo[LC] This friend causes a bunch of issues: (1) double friend; (2) incompatiblities between GCC and MSVC (but only when using templates). Why is this friend really needed? This is needed when subcontracting -- e.g., see example/DBC_by_Example/Counter example. But, is there a way to avoid it?? */ \
    DBC_MEM_FUN_FRIEND_TEMPLATED_CLASS_ \
            DBC_FUN_GET_MEM_CONTRACT_TYPE_(f, DBC_GET_CONTRACT_TYPE_(kind)); \
    BOOST_PP_EXPR_IF(DBC_PP_FUN_IS_DERIVED_(f), friend class \
            ::dbc::post< DBC_FUN_GET_MEM_BASE_CONTRACT_TYPE_(f) >;) \
    /* mem class "friend" as for C++ std (but not all compilers check it) */ \
    friend class DBC_FUN_GET_CONTRACT_NAME_(f); \
    class DBC_FUN_GET_CONTRACT_NAME_(f): \
            public DBC_FUN_GET_MEM_CONTRACT_TYPE_(f, \
            DBC_GET_CONTRACT_TYPE_(kind)) { \
        BOOST_PP_EXPR_IF(DBC_CHECK_REQUIRE, /* preconditions */ \
            void require(DBC_FUN_GET_MEM_REQUIRE_ARGS_(kind, f)) require_code \
        ) /* end if */ \
        BOOST_PP_EXPR_IF(DBC_CHECK_ENSURE, /* postconditions */ \
            void ensure(DBC_FUN_GET_MEM_ENSURE_ARGS_(kind, f)) ensure_code \
        ) /* end if */ \
    }; \
    /* body */ \
    DBC_PP_FUN_GET_VIRTUAL_(f) DBC_PP_FUN_GET_RESULT_TYPE_(f) \
            DBC_BODY(DBC_PP_FUN_GET_NAME_(f))( \
            DBC_FUN_GET_BODY_ARGS_(f)) DBC_PP_FUN_GET_CONST_(f) body_code \
    /* restore original access level */ \
DBC_PP_FUN_GET_ACCESS_(f): \
    /**/

/** Expand to pre-processor error. */
#define DBC_MEM_FUN_ERROR_(err, f, kind, \
        require_code, ensure_code, body_code) \
    /* Boost.Preprocessor errors BOOST_PP_ASSERT() and/or BOOST_PP_ASSERT_MSG() are best avoided here as they will not provide meaningfull error message (message will be visible only in preprocessed code if compiling with -E but complier error will not, in general, contain the error message. Boost.MPL static assertion allow instead to produce meaning error message at compile time. */ \
    ; /* closes previous statement (and no effect if no prev statement) */ \
    BOOST_MPL_ASSERT_MSG(0, BOOST_PP_TUPLE_ELEM(2, 1, err), ());

/** Make sure DBC_PP_FUN_() expands only once (does expensive parsing). */
#define DBC_MEM_FUN_FROM_TRAITS_(sign_traits_err, kind, \
        require_code, ensure_code, body_code) \
    BOOST_PP_IF(BOOST_PP_TUPLE_ELEM(2, 0, BOOST_PP_TUPLE_ELEM( \
            3, 2, sign_traits_err)), /* expand to error */ \
        DBC_MEM_FUN_ERROR_ \
    , /* else (no error, expand to code) */ \
        DBC_MEM_FUN_CODE_ \
    ) /* endif (expand selected macro)*/ \
    (BOOST_PP_TUPLE_ELEM(3, 2, sign_traits_err), \
            BOOST_PP_TUPLE_ELEM(3, 1, sign_traits_err), kind, \
            require_code, ensure_code, body_code) \

#endif // DBC

#endif // DBC_MFUN_HPP_

