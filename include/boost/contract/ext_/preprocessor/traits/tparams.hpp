
#ifndef BOOST_CONTRACT_EXT_PP_TPARAMS_TRAITS_HPP_
#define BOOST_CONTRACT_EXT_PP_TPARAMS_TRAITS_HPP_

#include <boost/contract/ext_/preprocessor/traits/tparam/kind.hpp>
#include <boost/contract/ext_/preprocessor/traits/tparam/name.hpp>
#include <boost/contract/ext_/preprocessor/traits/tparam/default.hpp>
#include <boost/contract/ext_/preprocessor/traits/aux_/params.hpp>

// PRIVATE //

// When first parsed, a parameter is assumed to have no default value.
#define BOOST_CONTRACT_EXT_PP_TPARAMS_TRAITS_TPARAM_PARSE_D_S_( \
        d, s, sign_traits) \
    BOOST_CONTRACT_EXT_PP_TPARAM_TRAITS_DEFAULT_PARSE_EMPTY( \
    BOOST_CONTRACT_EXT_PP_TPARAM_TRAITS_NAME_PARSE( \
    BOOST_CONTRACT_EXT_PP_TPARAM_TRAITS_KIND_PARSE( \
        sign_traits \
    )))

// PUBLIC //

#define BOOST_CONTRACT_EXT_PP_TPARAMS_TRAITS_D_S(d, s, sign) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_PARAMS_D_S(d, s, \
        sign, \
        BOOST_CONTRACT_EXT_PP_TPARAMS_TRAITS_TPARAM_PARSE_D_S_, \
        BOOST_CONTRACT_EXT_PP_TPARAM_TRAITS_DEFAULT_PARSE_REPLACE_D_S \
    )

// Expand specified pp-tuple with template parameters signature into pp-list
// of template parameter traits to inspect using TPARAM_TRAITS macros.
#define BOOST_CONTRACT_EXT_PP_TPARAMS_TRAITS(sign) \
    BOOST_CONTRACT_EXT_PP_TPARAM_TRAITS_D_S(1, 1, sign)

#endif // #include guard

