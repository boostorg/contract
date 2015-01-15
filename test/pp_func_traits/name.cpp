
#include <boost/preprocessor/config/config.hpp>
#if !BOOST_PP_VARIADICS
#   error "this compiler does not support variadic macros"
#else

#include <boost/contract/ext_/preprocessor/traits/func/aux_/index.hpp>
#define BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_AUX_INDEX_TEST \
    BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_AUX_NAME_INDEX

#include "../aux_/pp_traits.hpp"
#include <boost/contract/ext_/preprocessor/traits/func.hpp>
#include <boost/preprocessor/facilities/empty.hpp>

#define BOOST_CONTRACT_TEST_(before, name, after, \
        parsed_operator_name, parsed_func_name) \
    BOOST_CONTRACT_TEST_AUX_PP_TRAITS( \
        BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_OPERATOR_NAME, \
        BOOST_CONTRACT_EXT_PP_FUNC_TRAITS, \
        before, \
        name, \
        after, \
        parsed_operator_name \
    ) \
    BOOST_CONTRACT_TEST_AUX_PP_TRAITS( \
        BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_NAME, \
        BOOST_CONTRACT_EXT_PP_FUNC_TRAITS, \
        before, \
        name, \
        after, \
        parsed_func_name \
    )

int main ( ) {
    // Test function name.
    BOOST_CONTRACT_TEST_(
        int, (f), ( int ),
        BOOST_PP_EMPTY(), f
    )
    
    // Test constructor and destructor names.
    BOOST_CONTRACT_TEST_(
        explicit, (ctor), ( int n ),
        BOOST_PP_EMPTY(), ctor
    )
    BOOST_CONTRACT_TEST_(
        virtual, (~dtor), ( ),
        BOOST_PP_EMPTY(), ~dtor
    )
    
    // Test a few (non type conversion) operators.
    BOOST_CONTRACT_TEST_(
        template( typename L, typename R )
        auto, operator(+)(add), ( (L) l, (R) r ) return decltype(l + r),
        (+), add
    )
    BOOST_CONTRACT_TEST_(
        long double, operator("" _deg)(deg_literal), ( long double deg ),
        ("" _deg), deg_literal
    )
    BOOST_CONTRACT_TEST_(
        void, operator(())(call), ( int x ),
        (()), call
    )
    BOOST_CONTRACT_TEST_(
        template( typename L, typename R )
        (R), operator(,)(comma), ( (L) l , (R) r ),
        (,), comma
    )
    BOOST_CONTRACT_TEST_(
        (void*), operator(new[])(new_array), ( (std::size_t) size ),
        (new[]), new_array
    )
    BOOST_CONTRACT_TEST_(
        void, operator(delete[])(delete_array), ( (void*) ptr ),
        (delete[]), delete_array
    )

    // Test type conversion operators with and without commas.
    BOOST_CONTRACT_TEST_(
        explicit, operator(int*)(int_ptr), ( ),
        (int*), int_ptr
    )
    BOOST_CONTRACT_TEST_(
        template( typename T )
        , operator(std::map<int, T>)(std_map_int_T), ( ),
        (std::map<int, T>), std_map_int_T
    )

    // Test type conversion operators with and without operator name.
    BOOST_CONTRACT_TEST_(
        explicit, operator unsigned int, ( ) const,
        (unsigned int), unsignedint
    )
    BOOST_CONTRACT_TEST_(
        explicit, operator(unsigned int)(unsigned_int), ( ) const,
        (unsigned int), unsigned_int
    )
    
    // Test new and delete operators with and without operator name.
    BOOST_CONTRACT_TEST_(
        (void*), operator new, ( ),
        (new), new
    )
    BOOST_CONTRACT_TEST_(
        (void*), operator(new)(new_ptr), ( ),
        (new), new_ptr
    )
    BOOST_CONTRACT_TEST_(
        void, operator delete, ( ),
        (delete), delete
    )
    BOOST_CONTRACT_TEST_(
        void, operator(delete)(delete_ptr), ( ),
        (delete), delete_ptr
    )
    
    return BOOST_CONTRACT_TEST_AUX_PP_TRAITS_REPORT_ERRORS;
}

#endif // variadics

