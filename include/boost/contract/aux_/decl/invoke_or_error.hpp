
#ifndef BOOST_CONTRACT_AUX_CODE_INVOKE_OR_ERROR_HPP_
#define BOOST_CONTRACT_AUX_CODE_INVOKE_OR_ERROR_HPP_

#include <boost/contract/ext_/preprocessor/utility/nil.hpp>
#include <boost/static_assert.hpp>
#include <boost/preprocessor/tuple/elem.hpp>
#include <boost/preprocessor/control/iif.hpp>
#include <boost/preprocessor/stringize.hpp>

/* PUBLIC */

// Expand to `op_macro(d, id, traits)` if parsed decl is NIL (i.e., no trait
// parsing error), otherwise expand to a static assertion error messaging the
// decl that remained unparsed.
#define BOOST_CONTRACT_AUX_INVOKE_OR_ERROR(d, r, id, tpl, orig_decl, \
        parsed_decltraits, macro) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_IS_NIL_FRONT(BOOST_PP_TUPLE_ELEM(2, 0, \
            parsed_decltraits)), \
        BOOST_CONTRACT_AUX_INVOKE_OR_ERROR_NO_ \
    , \
        BOOST_CONTRACT_AUX_INVOKE_OR_ERROR_YES_ \
    )(d, r, id, tpl, orig_decl, parsed_decltraits, macro)

/* PRIVATE */

#define BOOST_CONTRACT_AUX_INVOKE_OR_ERROR_NO_(d, r, id, tpl, orig_decl, \
        parsed_decltraits, macro) \
    macro(d, r, id, tpl, BOOST_PP_TUPLE_ELEM(2, 1, parsed_decltraits))

// Static assertion must be used because there is portable way to report an
// error with a description message using a preprocessor macro expansion
// (because macros cannot expand and therefore use #error).
#define BOOST_CONTRACT_AUX_INVOKE_OR_ERROR_YES_(d, r, id, tpl, orig_decl, \
        parsed_decltraits, macro) \
    BOOST_STATIC_ASSERT_MSG( \
        false, \
        "unable to complete parsing of declaration '" \
        BOOST_PP_STRINGIZE(orig_decl) "', parsed only up until '" \
        BOOST_PP_STRINGIZE(BOOST_PP_TUPLE_ELEM(2, 0, parsed_decltraits)) "'" \
    )

#endif // #include guard

