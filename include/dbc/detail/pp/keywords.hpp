/**
 * @file
 * @author Copyright (C) 2009 Lorenzo Caminiti.
 *  Distributed under DBC++ Software License (see file LICENSE_1_0.txt).
 */

#ifndef DBC_PP_FUN_KEYWORDS_HPP_
#define DBC_PP_FUN_KEYWORDS_HPP_

#include <boost/preprocessor.hpp>
// [LC] From the Boost mailing list, P. Mensonides mentioned that
// BOOST_PP_IS_UNARY is in detail/ bacause it does not work with older versions
// of the Borland C++ compiler. Thecnically, this is part of the _private_ API
// for Boost.Preprocessor (and it should not be used) but also P. Mensonides
// suggests to use this macro if its functionality were needed (as the macro
// is defined to be work on different compilers as much as possible) keeping in
// mind that it might not work on some compilers, like older Borland, that do
// not fully implement the C++ preprocessor standard.
#include <boost/preprocessor/detail/is_unary.hpp>

// Do NOT #undef these macros! They are mixed capital because their postfix
// match the keyword but they are NOT local macros.
// [LC] The "1" can be any token. It is needed otherwise some compilers (MSVC)
// will generate a warning like "not enough params for BOOST_PP_IS_UNARY" (but
// on other compiler (GCC) these macros can be defined simply as "()").
#define DBC_PP_PRIVATE_private          (1)
#define DBC_PP_PROTECTED_protected      (1)
#define DBC_PP_PUBLIC_public            (1)
#define DBC_PP_VIRTUAL_virtual          (1)
#define DBC_PP_VOID_void                (1)
#define DBC_PP_TEMPLATE_template        (1)
#define DBC_PP_CONST_const              (1)
// Postfix must match symbol prefixed by DBC_BASE() macro.
#define DBC_PP_BASE_dbc_base_           (1)
// Postfix must match symbol prefixed by DBC_COPYABLE() macro.
#define DBC_PP_COPYABLE_dbc_copyable_   (1)

#define DBC_PP_IS_FUN_KEYWORD_(keyword_prefix, token) \
    BOOST_PP_IS_UNARY(BOOST_PP_CAT(keyword_prefix, token))

#define DBC_PP_IS_PRIVATE_(token) \
    DBC_PP_IS_FUN_KEYWORD_(DBC_PP_PRIVATE_, token)

#define DBC_PP_IS_PROTECTED_(token) \
    DBC_PP_IS_FUN_KEYWORD_(DBC_PP_PROTECTED_, token)

#define DBC_PP_IS_PUBLIC_(token) \
    DBC_PP_IS_FUN_KEYWORD_(DBC_PP_PUBLIC_, token)

#define DBC_PP_IS_VIRTUAL_(token) \
    DBC_PP_IS_FUN_KEYWORD_(DBC_PP_VIRTUAL_, token)

#define DBC_PP_IS_VOID_(token) \
    DBC_PP_IS_FUN_KEYWORD_(DBC_PP_VOID_, token)

#define DBC_PP_IS_TEMPLATE_(token) \
    DBC_PP_IS_FUN_KEYWORD_(DBC_PP_TEMPLATE_, token)

#define DBC_PP_IS_CONST_(token) \
    DBC_PP_IS_FUN_KEYWORD_(DBC_PP_CONST_, token)

#define DBC_PP_IS_BASE_(token) \
    DBC_PP_IS_FUN_KEYWORD_(DBC_PP_BASE_, token)

#define DBC_PP_IS_COPYABLE_(token) \
    DBC_PP_IS_FUN_KEYWORD_(DBC_PP_COPYABLE_, token)

#endif // DBC_PP_FUN_KEYWORDS_HPP_

