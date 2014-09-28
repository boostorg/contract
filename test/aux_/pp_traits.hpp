
#ifndef BOOST_CONTRACT_TEST_AUX_PP_TRAITS_HPP_
#define BOOST_CONTRACT_TEST_AUX_PP_TRAITS_HPP_

#include <boost/preprocessor/stringize.hpp>
#include <boost/detail/lightweight_test.hpp>

#ifndef BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_DEBUG_AT_
#   define BOOST_CONTRACT_TEST_AUX_PP_TRAITS_CHECK_EQUAL( \
            traits_macro, trait_macro, sign, trait) \
        BOOST_TEST(BOOST_PP_STRINGIZE(trait_macro(traits_macro(sign))) == \
                BOOST_PP_STRINGIZE(trait));
#else
#   define BOOST_CONTRACT_TEST_AUX_PP_TRAITS_CHECK_EQUAL( \
            traits_macro, trait_macro, sign, trait) \
        sign ==> traits_macro(sign) ==> trait
#endif

#endif // #include guard

