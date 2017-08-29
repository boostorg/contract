
// Copyright (C) 2008-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://sourceforge.net/projects/contractpp

#ifndef CONTRACT_AUX_CODE_NAME_HPP_
#define CONTRACT_AUX_CODE_NAME_HPP_

#include <contract/aux_/symbol.hpp>
#include <contract/detail/preprocessor/traits/func.hpp> // f

// PRIVATE //

// Precondition: name is alphanumeric (so not destructor name `~...`).
#define CONTRACT_AUX_CODE_NAME_OPERATOR_(name) \
    CONTRACT_AUX_SYMBOL( (operator)(name) )

#define CONTRACT_AUX_CODE_NAME_OPERATOR_COMMA_(unused) \
    , /* symbol for for `operator,` */

// Precondition: SIZE(operator_tokens) > 0.
#define CONTRACT_AUX_CODE_NAME_OPERATOR_SYMBOL_(operator_tokens, name) \
    /* operator's name is always alphanumeric so IS_COMMA_FRONT can be used */ \
    /* (name is not alphanumeric only for ~destructor, not an operator) */ \
    BOOST_PP_IIF(CONTRACT_DETAIL_PP_KEYWORD_IS_COMMA_FRONT(name), \
        CONTRACT_AUX_CODE_NAME_OPERATOR_COMMA_ /* comma operator */ \
    , \
        BOOST_PP_ARRAY_ENUM /* operator symbol tokens */ \
    )(operator_tokens)
        
#define CONTRACT_AUX_CODE_NAME_(operator_tokens, name) \
    name

// PUBLIC //

// Expand to either the function name `f` or to the operator symbolic name
// `operator ==`, `operator ,`, `operator new`, `operator int*` etc.
#define CONTRACT_AUX_CODE_NAME(operator_tokens, name) \
    BOOST_PP_IF(BOOST_PP_ARRAY_SIZE(operator_tokens), \
        operator CONTRACT_AUX_CODE_NAME_OPERATOR_SYMBOL_ \
    , \
        CONTRACT_AUX_CODE_NAME_ \
    )(operator_tokens, name)

#define CONTRACT_AUX_CODE_NAME_POSTFIXED(is_constructor01, is_destructor01, \
        operator_tokens, name, postfix_seq) \
    CONTRACT_AUX_SYMBOL( \
        ( \
            BOOST_PP_IIF(is_constructor01, \
                /* contract_aux_... so user can use func named constructor */ \
                CONTRACT_AUX_SYMBOL( (constructor) ) \
                BOOST_PP_TUPLE_EAT(1) \
            , BOOST_PP_IIF(is_destructor01, \
                /* contract_aux_... so user can use func named destructor */ \
                CONTRACT_AUX_SYMBOL( (destructor) ) \
                BOOST_PP_TUPLE_EAT(1) \
            , BOOST_PP_IF(BOOST_PP_ARRAY_SIZE(operator_tokens), \
                CONTRACT_AUX_CODE_NAME_OPERATOR_ \
            , \
                BOOST_PP_TUPLE_REM(1) \
            )))(name) \
        ) \
        postfix_seq \
    )

#endif // #include guard

