
// WARNING: FILE AUTOMATICALLY GENERATED, DO NOT MODIFY IT!
// Instead, modify and run the related generation script "generate.py".

#ifndef BOOST_CONTRACT_EXT_PP_KEYWORD_THREAD_LOCAL_HPP_
#define BOOST_CONTRACT_EXT_PP_KEYWORD_THREAD_LOCAL_HPP_

#include <boost/contract/ext_/preprocessor/keyword/utility/is.hpp>
#include <boost/contract/ext_/preprocessor/keyword/utility/rem.hpp>

// PRIVATE //

// NOTE: These are not local macros, do NOT #undefine them.
// The following macro must expand to a unary token: `(1)`, etc.
#define BOOST_CONTRACT_EXT_PP_KEYWORD_THREAD_LOCAL_IS_thread_local (1)
// The following macro must expand to nothing.
#define BOOST_CONTRACT_EXT_PP_KEYWORD_THREAD_LOCAL_REM_thread_local

// PUBLIC //

#define BOOST_CONTRACT_EXT_PP_KEYWORD_IS_THREAD_LOCAL(tokens) \
    BOOST_CONTRACT_EXT_PP_KEYWORD_UTILITY_IS(tokens, \
            BOOST_CONTRACT_EXT_PP_KEYWORD_THREAD_LOCAL_IS_)

#define BOOST_CONTRACT_EXT_PP_KEYWORD_THREAD_LOCAL_REM(tokens) \
    BOOST_CONTRACT_EXT_PP_KEYWORD_UTILITY_REM(tokens, \
            BOOST_CONTRACT_EXT_PP_KEYWORD_THREAD_LOCAL_REM_)

#endif // #include guard
        