
#ifndef DBC_PP_FUN_KEYWORDS_HPP_
#define DBC_PP_FUN_KEYWORDS_HPP_

#include <boost/preprocessor.hpp>
#include <boost/preprocessor/detail/is_unary.hpp>

// Do NOT #undef these macros! They are mixed capital because their postfix
// must be the keyword to match but they are NOT local macros.
#define DBC_PP_PRIVATE_private          ()
#define DBC_PP_PROTECTED_protected      ()
#define DBC_PP_PUBLIC_public            ()
#define DBC_PP_VIRTUAL_virtual          ()
#define DBC_PP_VOID_void                ()
#define DBC_PP_TEMPLATE_template        ()
#define DBC_PP_CONST_const              ()
// Postfix must match symbol prefixed by DBC_BASE() macro.
#define DBC_PP_BASE_dbc_base_           ()
// Postfix must match symbol prefixed by DBC_COPYABLE() macro.
#define DBC_PP_COPYABLE_dbc_copyable_   ()

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

