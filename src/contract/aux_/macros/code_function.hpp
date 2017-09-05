// Copyright (C) 2009-2010 Lorenzo Caminiti.
// Use, modification, and distribution is subject to the
// Contract++ Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt.)

#ifndef CONTRACT_AUX_CODE_FUNCTION_HPP_
#define CONTRACT_AUX_CODE_FUNCTION_HPP_

#include "code_/kind.hpp"
#include "code_/body.hpp"
#include "code_/contract_class.hpp"
#include "code_/postcondition.hpp"
#include "code_/precondition.hpp"
#include "code_/contracted_function.hpp"
#include "code_/static_validate.hpp"
#include "../preprocessor/sign/class.hpp"
#include "../preprocessor/sign/postcondition.hpp"
#include "../preprocessor/sign/body.hpp"
#include "../preprocessor/sign/access.hpp"
#include "../check01.hpp"
#include <boost/preprocessor.hpp>

// WORKAROUND: Commas in Macro Parameters
// This code works around preprocessor limitation of not handling
// commas within macros using the `IF(... TUPLE_EAT(1))(sign)` below.
// Note that all code blocks, contract class definitions, etc can
// contain commas not wrapped within () so the work around is needed.

// WORKAROUND: typename/template Outside Templates
// C++ requires using typname/template to explicitely specify types
// when compiler cannot deduce them in templates but this explicit
// type specification is not allowed outside templates. For example,
// this is the case for `arg<>::type` which must be 
// `typename arg<>::type` in templates, and `function::member<>` which
// must be `function::template member<>` in templates (this could 
// have been avoided by not making `member` a nested type but for
// `arg` typename must be specified). Earlier version of the library
// required the user to specify `(template)` before `(class)` so the
// library knew when to use typename/template specification. In order
// to avoid asking the user to specify the additional `(template)`
// (which is strange because it does not require the actual class
// template parameters...) a workaround has been implemented which
// makes the pre/post condition functions and contract class always
// templates using an artificial `UNUSED` template parameter so the
// typname/template specification can be used regardless of weather
// the contracted class type and/or function are a template or not.
// * All the workaround code is marked by a special comment.
// * Does making the contract class and pre/post condition function
//   always templates affect negatively compile-time performances?

// CANNOT USE STATIC NON-MEMBER
// For non-member functions is NOT possible to make the non-member
// contract functions static to to contraint their use within the
// translation unit because this use of static for non-members is
// obsolete in C++ (i.e., still supported by the language but
// encouraged to not use it -- see [Stroustrup1997]).
// The contract class could instead be defined within the contracted
// non-member function code block so to limit its scope however some
// compilers do not fully support class declarations within code
// blocks.
// The contract class, precondition, postcondition, and body function
// are therefore declared and defined at same scope as the contracted
// function but their names are `contract_..._` so users should not
// use them directly.

#define CONTRACT_AUX_CODE_FUNCTION(kind, sign) \
    /* original function signature here */ \
\
    /* contracted function definition */ \
    BOOST_PP_IF(CONTRACT_AUX_CHECK_CLASS_01, \
        BOOST_PP_IF(CONTRACT_AUX_PP_SIGN_IS_CLASS_MEMBER(sign), \
            CONTRACT_AUX_CODE_CONTRACTED_FUNCTION_MEMBER /* block */ \
        , /* else */ \
            /* non-member deferr definition because of restricted */ \
            /* visibility rules outside class scope */ \
            ; /* deferred definition (see later below) */ \
            BOOST_PP_TUPLE_EAT(2) \
        )(kind, sign) \
        BOOST_PP_TUPLE_EAT(1) \
    , /* else */ \
        /* original body definition if contract off */ \
        CONTRACT_AUX_PP_SIGN_BODY \
    )(sign) \
\
    /* pre/post conditions are private but access level changed */ \
    /* only for members, plus non-members cannot be static func */ \
    /* because func ptr template parameters need external linkage */ \
\
    /* preconditions (but no for destructor) */ \
    BOOST_PP_IF(BOOST_PP_AND(CONTRACT_AUX_CHECK_PRECONDITION_01, \
            BOOST_PP_NOT(BOOST_PP_EQUAL(kind, \
                    CONTRACT_AUX_CODE_KIND_DESTRUCTOR))), \
        BOOST_PP_EXPR_IF(CONTRACT_AUX_PP_SIGN_IS_CLASS_MEMBER(sign), \
            private: \
        ) /* endif */ \
        CONTRACT_AUX_CODE_PRECONDITION /* sign and block */ \
    , /* else */ \
        BOOST_PP_TUPLE_EAT(2) \
    )(kind, sign) \
\
    /* postconditions (but no for destructor) */ \
    BOOST_PP_IF(BOOST_PP_AND(CONTRACT_AUX_CHECK_POSTCONDITION_01, \
            BOOST_PP_NOT(BOOST_PP_EQUAL(kind, \
                    CONTRACT_AUX_CODE_KIND_DESTRUCTOR))), \
        BOOST_PP_EXPR_IF(CONTRACT_AUX_PP_SIGN_IS_CLASS_MEMBER(sign), \
            private: \
        ) /* endif */ \
        CONTRACT_AUX_CODE_POSTCONDITION /* sign and block */ \
    , /* else */ \
        BOOST_PP_TUPLE_EAT(2) \
    )(kind, sign) \
\
    /* body -- must be defined before contract class for */ \
    /* typename/template workaround */ \
    BOOST_PP_IF(CONTRACT_AUX_CHECK_CLASS_01, \
        BOOST_PP_EXPR_IF(CONTRACT_AUX_PP_SIGN_IS_CLASS_MEMBER(sign), \
            protected: /* must be protected for subcontracting */ \
        ) \
        CONTRACT_AUX_CODE_BODY /* sign and block */ \
    , /* else */ \
        BOOST_PP_TUPLE_EAT(2) \
    )(kind, sign) \
\
    /* contract class definition */ \
    BOOST_PP_IF(CONTRACT_AUX_CHECK_CLASS_01, \
        BOOST_PP_EXPR_IF(CONTRACT_AUX_PP_SIGN_IS_CLASS_MEMBER(sign), \
            protected: /* must be protected for subcontracting */ \
        ) \
        CONTRACT_AUX_CODE_CONTRACT_CLASS \
    , /* else */ \
        BOOST_PP_TUPLE_EAT(2) \
    )(kind, sign) \
\
    /* restore original access level (for members only */ \
    BOOST_PP_EXPR_IF(BOOST_PP_AND(CONTRACT_AUX_CHECK_CLASS_01, \
            CONTRACT_AUX_PP_SIGN_IS_CLASS_MEMBER(sign)), \
        CONTRACT_AUX_PP_SIGN_ACCESS(sign): /* `:` for access */ \
    ) \
\
    /* non-member contracted function separated definition */ \
    BOOST_PP_IF(BOOST_PP_AND(CONTRACT_AUX_CHECK_CLASS_01, \
            BOOST_PP_NOT(CONTRACT_AUX_PP_SIGN_IS_CLASS_MEMBER( \
            sign))), \
        /* macro expasion delayed to handle tparams commas */ \
        CONTRACT_AUX_CODE_CONTRACTED_FUNCTION_NON_MEMBER \
    , /* else */ \
        BOOST_PP_TUPLE_EAT(2) \
    )(kind, sign) \
\
    /* compile-time (after preprocessing) signature validation */ \
    BOOST_PP_IF(CONTRACT_AUX_CHECK_CLASS_01, \
        CONTRACT_AUX_CODE_STATIC_VALIDATE \
    , \
        BOOST_PP_TUPLE_EAT(2) \
    )(kind, sign) /* delay expansion because validate can return nothing */ \

#endif // #include guard

