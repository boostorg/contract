
#ifndef BOOST_CONTRACT_TEST_AUX_PP_TRAITS_HPP_
#define BOOST_CONTRACT_TEST_AUX_PP_TRAITS_HPP_

#include <boost/contract/ext_/preprocessor/traits/parse.hpp>
#include <boost/contract/ext_/preprocessor/stringize.hpp>
#include <boost/preprocessor/stringize.hpp>
#include <boost/detail/lightweight_test.hpp>
#include <string>
#include <locale>

/* PRIVATE */

namespace boost { namespace contract { namespace test { namespace aux {
        namespace pp_traits_ {

std::string remove_non_separation_spaces(std::string const& source) {
    std::locale locale;
    std::string result = "";
    for(std::string::size_type i = 0; i < source.size(); ++i) {
        if(source[i] != ' ') {
            result += source[i]; // Keep non-space char.
        } else if(i == 0) {
            // Skip leading space.
        } else if(i == source.size() - 1) {
            // Skip trailing space.
        } else if(!std::isalpha(source[i - 1], locale) ||
                !std::isalpha(source[i + 1], locale)) {
            // Skip spaces not in between letters.
        } else {
            result += source[i]; // Keep separation space.
        }
    }
    return result;
}

} } } } } // namespace

#define BOOST_CONTRACT_TEST_AUX_PP_TRAITS_EQUAL_(left, right) \
    BOOST_TEST( \
        boost::contract::test::aux::pp_traits_::remove_non_separation_spaces( \
            BOOST_CONTRACT_EXT_PP_STRINGIZE(left BOOST_PP_EMPTY()) \
        ) \
        == \
        boost::contract::test::aux::pp_traits_::remove_non_separation_spaces( \
            BOOST_CONTRACT_EXT_PP_STRINGIZE(right BOOST_PP_EMPTY()) \
        ) \
    );

#define BOOST_CONTRACT_TEST_AUX_PP_TRAITS_( \
        sign_traits, get_trait_macro, parsed_trait, sign_after_trait) \
    BOOST_CONTRACT_TEST_AUX_PP_TRAITS_EQUAL_( \
        get_trait_macro(BOOST_CONTRACT_EXT_PP_TRAITS_PARSE_DONE(sign_traits)), \
        parsed_trait \
    ) \
    BOOST_CONTRACT_TEST_AUX_PP_TRAITS_EQUAL_( \
        BOOST_CONTRACT_EXT_PP_TRAITS_PARSE_REST(sign_traits), \
        sign_after_trait \
    )

/* PUBLIC */

// Precondition: #define BOOST_CONTRACT_EXT_PP_..._TRAITS_TEST_AT_ to the INDEX
// of the trait that needs to be tested.
#define BOOST_CONTRACT_TEST_AUX_PP_TRAITS( \
    get_trait_macro, \
    parse_traits_macro, \
    sign_before_trait, \
    sign_at_trait, \
    sign_after_trait, \
    parsed_trait \
) \
    BOOST_CONTRACT_TEST_AUX_PP_TRAITS_( \
        parse_traits_macro(sign_before_trait sign_at_trait sign_after_trait), \
        get_trait_macro, \
        parsed_trait, \
        sign_after_trait \
    )

#define BOOST_CONTRACT_TEST_AUX_PP_TRAITS_REPORT_ERRORS \
    boost::report_errors()

#endif // #include guard

