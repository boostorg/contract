
#include <boost/preprocessor/config/config.hpp>
#if !BOOST_PP_VARIADICS
#   error "this compiler does not support variadic macros"
#else

#include <boost/contract/ext_/preprocessor/traits/aux_/index/class.hpp>
#define BOOST_CONTRACT_EXT_PP_CLASS_TRAITS_AUX_INDEX_TEST \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_INDEX_CLASS_BASES

#include "../aux_/pp_traits.hpp"
#include "../aux_/pp_1tuple_rem.hpp"
#include <boost/contract/ext_/preprocessor/traits/class.hpp>
#include <boost/contract/ext_/preprocessor/utility/empty.hpp>
#include <boost/preprocessor/seq/for_each_i.hpp>
#include <boost/preprocessor/tuple/eat.hpp>
#include <boost/preprocessor/punctuation/comma_if.hpp>
#include <boost/preprocessor/control/iif.hpp>
#include <boost/preprocessor/facilities/empty.hpp>
        
#define BOOST_CONTRACT_TEST_BASE_(r, unused, i, base_traits) \
    BOOST_PP_COMMA_IF(i) \
    BOOST_CONTRACT_EXT_PP_BASE_TRAITS_ACCESS(base_traits) \
    BOOST_CONTRACT_EXT_PP_BASE_TRAITS_VIRTUAL(base_traits) \
    BOOST_CONTRACT_TEST_AUX_PP_1TUPLE_REM( \
            BOOST_CONTRACT_EXT_PP_BASE_TRAITS_TYPE(base_traits))

#define BOOST_CONTRACT_TEST_BASES_YES_(class_traits) \
    extends( \
        BOOST_PP_SEQ_FOR_EACH_I(BOOST_CONTRACT_TEST_BASE_, ~, \
                BOOST_CONTRACT_EXT_PP_CLASS_TRAITS_BASES(class_traits)) \
    )

#define BOOST_CONTRACT_TEST_BASES_(class_traits) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_IS_EMPTY( \
            BOOST_CONTRACT_EXT_PP_CLASS_TRAITS_BASES(class_traits)), \
        BOOST_PP_TUPLE_EAT(1) \
    , \
        BOOST_CONTRACT_TEST_BASES_YES_ \
    )(class_traits)

#define BOOST_CONTRACT_TEST_EQUAL_(extends, parsed_extends) \
    BOOST_CONTRACT_TEST_AUX_PP_TRAITS( \
        BOOST_CONTRACT_TEST_BASES_, \
        BOOST_CONTRACT_EXT_PP_CLASS_TRAITS_PARSE_D, \
        template( typename T, (std::map<int, char>::value_type) V ) \
        class (a), \
        extends, \
        BOOST_PP_EMPTY(), \
        parsed_extends \
    )

#define BOOST_CONTRACT_TEST_(extends) \
    BOOST_CONTRACT_TEST_EQUAL_(extends, extends)

int main ( ) {
    BOOST_CONTRACT_TEST_( BOOST_PP_EMPTY() )

    BOOST_CONTRACT_TEST_( extends( b ) )
    BOOST_CONTRACT_TEST_( extends( virtual b ) )
    
    BOOST_CONTRACT_TEST_( extends( public b ) )
    BOOST_CONTRACT_TEST_( extends( public virtual b ) )
    BOOST_CONTRACT_TEST_EQUAL_(
        extends( virtual public b ),
        extends( public virtual b )
    )
    
    BOOST_CONTRACT_TEST_( extends( protected b ) )
    BOOST_CONTRACT_TEST_( extends( protected virtual b ) )
    BOOST_CONTRACT_TEST_EQUAL_(
        extends( virtual protected b ),
        extends( protected virtual b )
    )
    
    BOOST_CONTRACT_TEST_( extends( private b ) )
    BOOST_CONTRACT_TEST_( extends( private virtual b ) )
    BOOST_CONTRACT_TEST_EQUAL_(
        extends( virtual private b ),
        extends( private virtual b )
    )
    
    // Test base type with commas.
    BOOST_CONTRACT_TEST_( extends( (std::map<int, char>) ) )
    BOOST_CONTRACT_TEST_( extends( public virtual (std::map<int, char>) ) )

    // Test multiple inheritance (and a bit of everything together).
    BOOST_CONTRACT_TEST_EQUAL_(
        extends(
            b,
            virtual c,
            public d,
            protected virtual d,
            virtual private (std::map<T, U>::value_type)
        ),
        extends(
            b,
            virtual c,
            public d,
            protected virtual d,
            private virtual (std::map<T, U>::value_type)
        )
    )
    
    return BOOST_CONTRACT_TEST_AUX_PP_TRAITS_REPORT_ERRORS;
}

#endif // variadics

