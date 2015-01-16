
#ifndef BOOST_CONTRACT_EXT_PP_TYPEDEF_ASSERTION_TRAITS_HPP_
#define BOOST_CONTRACT_EXT_PP_TYPEDEF_ASSERTION_TRAITS_HPP_
    
/* PRIVATE */

#define BOOST_CONTRACT_EXT_PP_TYPEDEF_ASSERTION_TRAITS_NAME_PARSE_( \
        decl_type, traits) \
    ( \
        BOOST_CONTRACT_EXT_PP_DECL_TRAITS_FIRST(decl_type) \
    , \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK(traits, \
                BOOST_CONTRACT_EXT_PP_DECL_TRAITS_SECOND(decl_type)) \
    )

/* PUBLIC */

// Precondition: decl = `new-name`.
#define BOOST_CONTRACT_EXT_PP_TYPEDEF_ASSERTION_TRAITS_NEW_NAME_PARSE( \
        decl_traits) \
    ( \
        BOOST_PP_NIL \
    , \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            BOOST_CONTRACT_EXT_PP_DECL_TRAITS_SECOND(decl_traits), \
            BOOST_CONTRACT_EXT_PP_DECL_TRAITS_FIRST(decl_traits) \
        ) \
    )
    
// Precondition: decl = `typedef wrapped-type ...`.
#define BOOST_CONTRACT_EXT_PP_TYPEDEF_ASSERTION_TRAITS_NAME_PARSE(decl_traits) \
    BOOST_CONTRACT_EXT_PP_TYPEDEF_ASSERTION_TRAITS_NAME_PARSE_( \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_TYPE( \
            BOOST_CONTRACT_EXT_PP_KEYWORD_TYPEDEF_REMOVE_FRONT( \
                BOOST_CONTRACT_EXT_PP_DECL_TRAITS_FIRST(decl_traits) \
            ) \
        ), \
        BOOST_CONTRACT_EXT_PP_DECL_TRAITS_SECOND(decl_traits) \
    )

// decl = typedef wrapped-type new-name
#define BOOST_CONTRACT_EXT_PP_TYPEDEF_ASSERTION_TRAITS(decl) \
    BOOST_CONTRACT_EXT_PP_DECL_TRAITS_DONE( \
    BOOST_CONTRACT_EXT_PP_TYPEDEF_ASSERTION_TRAITS_NEW_NAME_PARSE( \
    BOOST_CONTRACT_EXT_PP_TYPEDEF_ASSERTION_TRAITS_NAME_PARSE( \
    BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_KIND_SET(typedef, \
    BOOST_CONTRACT_EXT_PP_DECL_TRAITS_INIT( \
        decl \
    )))))

// Index 0 below already used and reserved for ASSERTION_TRAITS_KIND.

// Expand to `(,,,)`.
#define BOOST_CONTRACT_EXT_PP_TYPEDEF_ASSERTION_TRAITS_NAME(traits) \
    BOOST_CONTRACT_EXT_PP_TRAITS_ELEM(1, traits)

// Expand to `token`.
#define BOOST_CONTRACT_EXT_PP_TYPEDEF_ASSERTION_TRAITS_NEW_NAME(traits) \
    BOOST_CONTRACT_EXT_PP_TRAITS_ELEM(2, traits)

#endif // #include guard

