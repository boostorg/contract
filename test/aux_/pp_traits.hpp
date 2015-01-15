
#ifndef BOOST_CONTRACT_TEST_AUX_PP_TRAITS_HPP_
#define BOOST_CONTRACT_TEST_AUX_PP_TRAITS_HPP_

#include <boost/contract/ext_/preprocessor/traits/adt.hpp>
#include <boost/contract/ext_/preprocessor/stringize.hpp>
#include <boost/preprocessor/stringize.hpp>
#include <boost/detail/lightweight_test.hpp>
#include <string>
#include <locale>

/* PRIVATE */

namespace boost { namespace contract { namespace test { namespace aux {
        namespace pp_traits_ {

// Remove spaces not separating words, etc.
std::string trim ( std::string const& source ) {
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

// Indirections for proper expansion of BOOST_TEST generated error message.
#define BOOST_CONTRACT_TEST_AUX_PP_TRAITS_TEST_2ND_(pred) BOOST_TEST(pred);
#define BOOST_CONTRACT_TEST_AUX_PP_TRAITS_TEST_(pred) \
    BOOST_CONTRACT_TEST_AUX_PP_TRAITS_TEST_2ND_(pred)

#define BOOST_CONTRACT_TEST_AUX_PP_TRAITS_EQUAL_(left, right) \
    BOOST_CONTRACT_TEST_AUX_PP_TRAITS_TEST_( \
        boost::contract::test::aux::pp_traits_::trim( \
            BOOST_CONTRACT_EXT_PP_STRINGIZE(left BOOST_PP_EMPTY()) \
        ) \
        == \
        boost::contract::test::aux::pp_traits_::trim( \
            BOOST_CONTRACT_EXT_PP_STRINGIZE(right BOOST_PP_EMPTY()) \
        ) \
    )

#define BOOST_CONTRACT_TEST_AUX_PP_TRAITS_( \
        decl_traits, traits_elem_macro, parsed_trait, decl_after_trait) \
    BOOST_CONTRACT_TEST_AUX_PP_TRAITS_EQUAL_( \
        traits_elem_macro( \
                BOOST_CONTRACT_EXT_PP_DECL_TRAITS_DONE(decl_traits)), \
        parsed_trait \
    ) \
    BOOST_CONTRACT_TEST_AUX_PP_TRAITS_EQUAL_( \
        BOOST_CONTRACT_EXT_PP_DECL_TRAITS_FIRST(decl_traits), \
        decl_after_trait \
    )

/* PUBLIC */

// Precondition: #define BOOST_CONTRACT_EXT_PP_..._TRAITS_TEST_AT_ to the INDEX
// of the trait that needs to be tested.
#ifndef DEBUG
#   define BOOST_CONTRACT_TEST_AUX_PP_TRAITS( \
        traits_elem_macro, \
        traits_parse_macro, \
        decl_before_trait, \
        decl_at_trait, \
        decl_after_trait, \
        parsed_trait \
    ) \
        BOOST_CONTRACT_TEST_AUX_PP_TRAITS_( \
            traits_parse_macro( \
                    decl_before_trait decl_at_trait decl_after_trait), \
            traits_elem_macro, \
            parsed_trait, \
            decl_after_trait \
        )
#else
// To #define DEBUG is useful when looking at pre-processed output (the NIL
// leading parsed_traits will be remove by non-debug invocation of DONE).
#   define BOOST_CONTRACT_TEST_AUX_PP_TRAITS( \
        traits_elem_macro, \
        traits_parse_macro, \
        decl_before_trait, \
        decl_at_trait, \
        decl_after_trait, \
        parsed_trait \
    ) \
        "NOTE: #undefine DEBUG macro (e.g., `bjam cxxflags=-UDEBUG ...`) to see fully generated C++ code" \
        decl = decl_before_trait decl_at_trait decl_after_trait \
        --> \
        (remaining_decl, BOOST_PP_NIL parsed_traits) = traits_parse_macro( \
                decl_before_trait decl_at_trait decl_after_trait)
#endif

#define BOOST_CONTRACT_TEST_AUX_PP_TRAITS_REPORT_ERRORS \
    boost::report_errors()

#endif // #include guard

