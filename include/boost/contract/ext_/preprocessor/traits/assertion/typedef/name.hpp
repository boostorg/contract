
#ifndef BOOST_CONTRACT_EXT_PP_TYPEDEF_ASSERTION_NAME_HPP_
#define BOOST_CONTRACT_EXT_PP_TYPEDEF_ASSERTION_NAME_HPP_

/* PRIVATE */

#define BOOST_CONTRACT_EXT_PP_TYPEDEF_ASSERTION_TRAITS_NAME_( \
        decl_type, traits) \
    ( \
        BOOST_PP_TUPLE_ELEM(2, 0, decl_type), \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK(traits, \
                BOOST_PP_TUPLE_ELEM(2, 1, decl_type)) \
    )

/* PUBLIC */

// Precondition: decl = `typedef wrapped-type ...`.
#define BOOST_CONTRACT_EXT_PP_TYPEDEF_ASSERTION_TRAITS_NAME_PARSE_D(d, \
        decl_traits) \
    BOOST_CONTRACT_EXT_PP_TYPEDEF_ASSERTION_TRAITS_NAME_( \
        BOOST_CONTRACT_EXT_PP_TYPE_TRAITS_PARSE_D(d, \
            BOOST_CONTRACT_EXT_PP_KEYWORD_TYPEDEF_REMOVE_FRONT( \
                BOOST_PP_TUPLE_ELEM(2, 0, decl_traits) \
            ) \
        ), \
        BOOST_PP_TUPLE_ELEM(2, 1, decl_traits) \
    )
    
// Expand to `(type,,,)`.
#define BOOST_CONTRACT_EXT_PP_TYPEDEF_ASSERTION_TRAITS_NAME(traits) \
    BOOST_CONTRACT_EXT_PP_TRAITS_ELEM( \
        BOOST_CONTRACT_EXT_PP_TYPEDEF_ASSERTION_TRAITS_AUX_NAME_INDEX, \
        traits \
    )

#endif // #include guard    

