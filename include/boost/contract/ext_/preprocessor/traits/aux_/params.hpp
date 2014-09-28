
#ifndef BOOST_CONTRACT_EXT_PP_TRAITS_AUX_PARAMS_HPP_
#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_PARAMS_HPP_

#include <boost/contract/ext_/preprocessor/keyword/default.hpp>
#include <boost/preprocessor/facilities/empty.hpp>
#include <boost/preprocessor/arithmetic/dec.hpp>
#include <boost/preprocessor/seq/fold_left.hpp>
#include <boost/preprocessor/tuple/to_seq.hpp>
#include <boost/preprocessor/tuple/elem.hpp>
#include <boost/preprocessor/tuple/rem.hpp>
#include <boost/preprocessor/list/append.hpp>
#include <boost/preprocessor/list/size.hpp>
#include <boost/preprocessor/list/at.hpp>
#include <boost/preprocessor/list/first_n.hpp>

// PRIVATE //

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_PARAMS_REPLACE_LAST_DEFAULT_( \
        s, sign, d, param_parse_macro, default_replace_macro, traits, last) \
    BOOST_PP_LIST_APPEND_D(d, \
        BOOST_PP_LIST_FIRST_N_D(d, last, traits), \
        ( \
            BOOST_PP_TUPLE_ELEM(2, 1, \
                default_replace_macro(d, s, \
                    ( \
                        sign, \
                        BOOST_PP_LIST_AT_D(d, traits, last) \
                    ) \
                ) \
            ), \
            BOOST_PP_NIL \
        ) \
    )

// Now parsing `default ...` so replace default value of last parsed parameter.
#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_PARAMS_REPLACE_DEFAULT_( \
        s, sign, d, param_parse_macro, default_replace_macro, traits) \
    ( \
        d, \
        param_parse_macro, \
        default_replace_macro, \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_PARAMS_REPLACE_LAST_DEFAULT_( \
                s, sign, d, param_parse_macro, default_replace_macro, traits, \
                BOOST_PP_DEC(BOOST_PP_LIST_SIZE_D(d, traits))) \
    )

// Now paring parameter declaration (assume default is EMPTY at first).
#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_PARAMS_APPEND_PARAM_( \
        s, sign, d, param_parse_macro, default_replace_macro, traits) \
    ( \
        d, \
        param_parse_macro, \
        default_replace_macro, \
        BOOST_PP_LIST_APPEND_D(d, \
            traits, \
            ( \
                BOOST_PP_TUPLE_ELEM(2, 1, \
                    param_parse_macro(d, s, \
                        ( \
                            sign, \
                            BOOST_PP_EMPTY() \
                        ) \
                    ) \
                ), \
                BOOST_PP_NIL \
            ) \
        ) \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_PARAMS_( \
        s, d_param_default_traits, sign) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_DEFAULT(sign), \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_PARAMS_REPLACE_DEFAULT_ \
    , \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_PARAMS_APPEND_PARAM_ \
    )( \
        s, \
        sign, \
        BOOST_PP_TUPLE_ELEM(4, 0, d_param_default_traits), \
        BOOST_PP_TUPLE_ELEM(4, 1, d_param_default_traits), \
        BOOST_PP_TUPLE_ELEM(4, 2, d_param_default_traits), \
        BOOST_PP_TUPLE_ELEM(4, 3, d_param_default_traits) \
    )

// PUBLIC //

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_PARAMS_D_S( \
        d, s, sign, param_parse_macro, default_replace_macro) \
    BOOST_PP_TUPLE_ELEM(4, 3, \
        BOOST_PP_SEQ_FOLD_LEFT_ ## s( \
            BOOST_CONTRACT_EXT_PP_TRAITS_AUX_PARAMS_, \
            ( \
                d, \
                param_parse_macro, \
                default_replace_macro, \
                BOOST_PP_NIL \
            ), \
            BOOST_PP_TUPLE_TO_SEQ(sign) \
        ) \
    )

// Expand specified pp-tuple of parameters signatures into a pp-list
// of parameters traits (also handles default arguments).
#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_PARAMS(sign) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_PARAMS_D_S(1, 1, sign)

#endif // #include guard

