
#ifndef BOOST_CONTRACT_EXT_PP_USING_ASSERTION_NAME_HPP_
#define BOOST_CONTRACT_EXT_PP_USING_ASSERTION_NAME_HPP_

/* PRIVATE */

// Precondition: name = `name | (name)`.
#define BOOST_CONTRACT_EXT_PP_USING_ASSERTION_TRAITS_NAME_(\
        name, traits) \
    ( \
        BOOST_PP_NIL, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK(traits, \
            BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_HAS_PAREN(name), \
                name \
            , \
                (name) \
            ) \
        ) \
    )

// Precondition: decl = `name NIL`.
#define BOOST_CONTRACT_EXT_PP_USING_ASSERTION_TRAITS_NAME_PARSE_ARGS_(\
        decl, traits) \
    BOOST_CONTRACT_EXT_PP_USING_ASSERTION_TRAITS_NAME_( \
            BOOST_CONTRACT_EXT_PP_NIL_REMOVE_BACK(decl), traits)

/* PUBLIC */

#define BOOST_CONTRACT_EXT_PP_USING_ASSERTION_TRAITS_NAME_PARSE( \
        decl_traits) \
    BOOST_PP_EXPAND( \
        BOOST_CONTRACT_EXT_PP_USING_ASSERTION_TRAITS_NAME_PARSE_ARGS_ \
        decl_traits \
    )
    
// Expand to `(name,,,)` (this name is wrapped within parenthesis because in
// general it can contain commas, for example for template aliases).
#define BOOST_CONTRACT_EXT_PP_USING_ASSERTION_TRAITS_NAME(traits) \
    BOOST_CONTRACT_EXT_PP_TRAITS_ELEM( \
        BOOST_CONTRACT_EXT_PP_USING_ASSERTION_TRAITS_AUX_NAME_INDEX, \
        traits \
    )

#endif // #include guard    

