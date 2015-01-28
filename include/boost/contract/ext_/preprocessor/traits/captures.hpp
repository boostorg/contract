
#ifndef BOOST_CONTRACT_EXT_PP_CAPTURES_TRAITS_HPP_
#define BOOST_CONTRACT_EXT_PP_CAPTURES_TRAITS_HPP_

#include <boost/contract/ext_/preprocessor/traits/capture.hpp>

// TODO: It should be possible to commonize this with params, tparams,
// assertions, etc. (but make default also optional in the params alg with an
// additional allow_default arg). Also after that commonization, some of these
// params.hpp, assertions.hpp, captures.hpp files might became pointless and
// do essentially nothing so they could be removed (it'd make sense to leave
// instead param.hpp as entry of param/*, etc like func.hpp is the entry of
// func/*, just the param*S*.hpp can be remove, but func/params.hpp will also be
// kept).

/* PUBLIC */

#define BOOST_CONTRACT_EXT_PP_CAPTURES_TRAITS_PARSE_D(d, decl_seq) \
    BOOST_CONTRACT_EXT_PP_PARAMS_TRAITS_PARSE_(d, 0, decl_seq, \
        BOOST_CONTRACT_EXT_PP_CAPTURE_TRAITS_PARSE_D, \
        todo_remove_this_param_from_params_parse_alg \
    )

#endif // #include guard

