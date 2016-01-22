
#ifndef BOOST_CONTRACT_PUBLIC_FUNCTION_HPP_
#define BOOST_CONTRACT_PUBLIC_FUNCTION_HPP_

// TODO: Check all #includes for all files... and make sure that #include not of this library are within @cond ... @endcond. Also disable #include when not needed based on BOOST_CONTRACT_PRECONDITIONS, etc.

#include <boost/contract/core/config.hpp>
#include <boost/contract/core/access.hpp>
#include <boost/contract/core/set_precondition_old_postcondition.hpp>
#include <boost/contract/core/virtual.hpp>
#include <boost/contract/aux_/operation/public_function.hpp>
#include <boost/contract/aux_/operation/public_static_function.hpp>
#include <boost/contract/aux_/decl.hpp>
#include <boost/contract/aux_/tvariadic.hpp>
#include <boost/contract/aux_/none.hpp>
#include <boost/optional.hpp>
#include <boost/function_types/result_type.hpp>
#include <boost/function_types/function_arity.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/type_traits/remove_reference.hpp>
#include <boost/static_assert.hpp>
#include <boost/preprocessor/logical/or.hpp>
#include <boost/preprocessor/logical/compl.hpp>
#include <boost/preprocessor/control/iif.hpp>
#include <boost/preprocessor/control/if.hpp>
#include <boost/preprocessor/punctuation/comma_if.hpp>
#include <boost/config.hpp>
    
/* PRIVATE */

#if BOOST_CONTRACT_PUBLIC_FUNCTIONS
    // This check is not strictly necessary because compilation will fail
    // anyways, but it helps limiting cryptic compiler's errors.
    #define BOOST_CONTRACT_PUBLIC_FUNCTION_ASSERT_ARITY_(F, arity) \
        BOOST_STATIC_ASSERT_MSG( \
            /* -2 for both `this` and `virtual_*` extra parameters */ \
            boost::function_types::function_arity<F>::value - 2 == arity, \
            "missing one or more arguments for specified function" \
        );

    // Always enforce this so base contracts can always specify postconditions
    // with result, without need to change derived contracts.
    #define BOOST_CONTRACT_PUBLIC_FUNCTION_ASSERT_NO_RESULT_(F) \
        BOOST_STATIC_ASSERT_MSG( \
            boost::is_same< \
                typename boost::function_types::result_type<F>::type, \
                void \
            >::value, \
            "missing 'result' argument for non-void function" \
        );

    #define BOOST_CONTRACT_PUBLIC_FUNCTION_ASSERT_RESULT_(F, R) \
        BOOST_STATIC_ASSERT_MSG( \
            boost::is_same< \
                typename boost::remove_reference<typename \
                        boost::function_types::result_type<F>::type>::type, \
                typename boost::contract::public_function_:: \
                        remove_optional_ref<R>::type \
            >::value, \
            "mismatching result type for specified function" \
        );

    // Always enforce this so this lib can check and enforce override.
    #define BOOST_CONTRACT_PUBLIC_FUNCTION_ASSERT_BASE_TYPES_(C) \
        BOOST_STATIC_ASSERT_MSG( \
            boost::contract::access::has_base_types<C>::value, \
            "enclosing class missing 'base-types' typedef" \
        );
#endif

/* CODE */

namespace boost { namespace contract {

#if BOOST_CONTRACT_PUBLIC_FUNCTIONS
    namespace public_function_ {
        template<typename R>
        struct remove_optional_ref { typedef R type; };

        template<typename R>
        struct remove_optional_ref<boost::optional<R> > {
            typedef typename boost::remove_reference<R>::type type;
        };
    }
#endif

// NOTE: O and (optionally) R allowed only when v is present because:
// * An overriding func must override a base func declared virtual so with
//   v extra param, thus the overriding func must also always have v (i.e., O
//   might be present only if v is also present).
//   However, the first appearing virtual func (e.g., in root class) will not
//   override any previously declared virtual func so does not need O (i.e., O
//   always optional).
//   Furthermore, F needs to be specified only together with O.
// * R is only used for virtual functions (i.e., R might be present only if v
//   is also present).
//   However, R is never specified, not even for virtual functions, when the
//   return type is void (i.e., R always optional).

// For static public member functions.
template<class C>
set_precondition_old_postcondition<> public_function() {
    #if BOOST_CONTRACT_PUBLIC_FUNCTIONS
        return set_precondition_old_postcondition<>(
            new boost::contract::aux::public_static_function<C>());
    #else
        return set_precondition_old_postcondition<>();
    #endif
}

// For non-static, non-virtual, and non-overriding public member functions.
template<class C>
set_precondition_old_postcondition<> public_function(C* obj) {
    #if BOOST_CONTRACT_PUBLIC_FUNCTIONS
        return set_precondition_old_postcondition<>(
            new boost::contract::aux::public_function<
                boost::contract::aux::none,
                boost::contract::aux::none,
                boost::contract::aux::none,
                C
                BOOST_CONTRACT_AUX_NO_TVARIADIC_COMMA(
                        BOOST_CONTRACT_CONFIG_MAX_ARGS)
                BOOST_CONTRACT_AUX_NO_TVARIADIC_ENUM_Z(1,
                    BOOST_CONTRACT_CONFIG_MAX_ARGS,
                    boost::contract::aux::none
                )
            >(
                static_cast<boost::contract::virtual_*>(0),
                obj,
                boost::contract::aux::none::value()
                BOOST_CONTRACT_AUX_NO_TVARIADIC_COMMA(
                        BOOST_CONTRACT_CONFIG_MAX_ARGS)
                BOOST_CONTRACT_AUX_NO_TVARIADIC_ENUM_Z(1,
                    BOOST_CONTRACT_CONFIG_MAX_ARGS,
                    boost::contract::aux::none::value()
                )
            )
        );
    #else
        return set_precondition_old_postcondition<>();
    #endif
}

// For non-static, virtual, and non-overriding public member functions.
#define BOOST_CONTRACT_PUBLIC_FUNCTION_VIRTUAL_NOOVERRIDE_(has_result) \
    template< \
        BOOST_PP_EXPR_IIF(has_result, typename R) \
        BOOST_PP_COMMA_IF(has_result) \
        class C \
    > \
    set_precondition_old_postcondition<BOOST_PP_EXPR_IIF(has_result, R)> \
    public_function( \
        virtual_* v \
        BOOST_PP_COMMA_IF(has_result) \
        BOOST_PP_EXPR_IIF(has_result, R& r) \
        , C* obj \
    ) { \
        BOOST_PP_IIF(BOOST_CONTRACT_PUBLIC_FUNCTIONS, \
            /* NOTE: No F so cannot enforce contracted f ret R (up to user) */ \
            return (set_precondition_old_postcondition< \
                    BOOST_PP_EXPR_IIF(has_result, R)>( \
                new boost::contract::aux::public_function< \
                    boost::contract::aux::none, \
                    BOOST_PP_IIF(has_result, R, boost::contract::aux::none), \
                    boost::contract::aux::none, \
                    C \
                    BOOST_CONTRACT_AUX_NO_TVARIADIC_COMMA( \
                            BOOST_CONTRACT_CONFIG_MAX_ARGS) \
                    BOOST_CONTRACT_AUX_NO_TVARIADIC_ENUM_Z(1, \
                        BOOST_CONTRACT_CONFIG_MAX_ARGS, \
                        boost::contract::aux::none \
                    ) \
                >( \
                    v, \
                    obj, \
                    BOOST_PP_IIF(has_result, \
                        r \
                    , \
                        boost::contract::aux::none::value() \
                    ) \
                    BOOST_CONTRACT_AUX_NO_TVARIADIC_COMMA( \
                            BOOST_CONTRACT_CONFIG_MAX_ARGS) \
                    BOOST_CONTRACT_AUX_NO_TVARIADIC_ENUM_Z(1, \
                        BOOST_CONTRACT_CONFIG_MAX_ARGS, \
                        boost::contract::aux::none::value() \
                    ) \
                ) \
            )); \
        , \
            return set_precondition_old_postcondition< \
                    BOOST_PP_EXPR_IIF(has_result, R)>(); \
        ) \
    }

BOOST_CONTRACT_PUBLIC_FUNCTION_VIRTUAL_NOOVERRIDE_(/* has_result = */ 0)
BOOST_CONTRACT_PUBLIC_FUNCTION_VIRTUAL_NOOVERRIDE_(/* has_result = */ 1)

// For non-static, virtual, and overriding public member functions.
#define BOOST_CONTRACT_PUBLIC_FUNCTION_VIRTUAL_OVERRIDE_Z_( \
        z, arity, arity_compl, has_result) \
    BOOST_CONTRACT_AUX_DECL_OVERRIDING_PUBLIC_FUNCTION_Z(z, \
        arity, /* is_friend = */ 0, has_result, \
        O, R, F, C, Args, \
        v, r, f, obj, args \
    ) { \
        BOOST_PP_IIF(BOOST_CONTRACT_PUBLIC_FUNCTIONS, \
            BOOST_CONTRACT_PUBLIC_FUNCTION_ASSERT_ARITY_(F, \
                    BOOST_CONTRACT_AUX_TVARIADIC_SIZEOF(arity, Args)) \
            BOOST_PP_IIF(has_result, \
                BOOST_CONTRACT_PUBLIC_FUNCTION_ASSERT_RESULT_ \
            , \
                BOOST_PP_TUPLE_EAT(2) \
            )(F, R) \
            BOOST_CONTRACT_PUBLIC_FUNCTION_ASSERT_BASE_TYPES_(C) \
            return (set_precondition_old_postcondition< \
                    BOOST_PP_EXPR_IIF(has_result, R)>( \
                new boost::contract::aux::public_function< \
                    O, \
                    BOOST_PP_IIF(has_result, R, boost::contract::aux::none), \
                    F, \
                    C \
                    BOOST_CONTRACT_AUX_TVARIADIC_COMMA(arity) \
                    BOOST_CONTRACT_AUX_TVARIADIC_ARGS_Z(z, arity, Args) \
                    BOOST_CONTRACT_AUX_NO_TVARIADIC_COMMA(arity_compl) \
                    BOOST_CONTRACT_AUX_NO_TVARIADIC_ENUM_Z(z, arity_compl, \
                            boost::contract::aux::none) \
                >( \
                    v, \
                    obj, \
                    BOOST_PP_IIF(has_result, \
                        r \
                    , \
                        boost::contract::aux::none::value() \
                    ) \
                    BOOST_CONTRACT_AUX_TVARIADIC_COMMA(arity) \
                    BOOST_CONTRACT_AUX_TVARIADIC_ARGS_Z(z, arity, args) \
                    BOOST_CONTRACT_AUX_NO_TVARIADIC_COMMA(arity_compl) \
                    BOOST_CONTRACT_AUX_NO_TVARIADIC_ENUM_Z(z, arity_compl, \
                            boost::contract::aux::none::value()) \
                ) \
            )); \
        , \
            return set_precondition_old_postcondition< \
                    BOOST_PP_EXPR_IIF(has_result, R)>(); \
        ) \
    }

#if BOOST_CONTRACT_AUX_TVARIADIC
    BOOST_CONTRACT_PUBLIC_FUNCTION_VIRTUAL_OVERRIDE_Z_(1,
            /* arity = */ ~, /* arity_compl = */ ~, /* has_result = */ 0)
    BOOST_CONTRACT_PUBLIC_FUNCTION_VIRTUAL_OVERRIDE_Z_(1,
            /* arity = */ ~, /* arity_compl = */ ~, /* has_result = */ 1)
#else
    #define BOOST_CONTRACT_PUBLIC_FUNCTION_VIRTUAL_OVERRIDE_ARITY_( \
            z, arity, unused) \
        BOOST_CONTRACT_PUBLIC_FUNCTION_VIRTUAL_OVERRIDES_(z, arity, \
                BOOST_PP_SUB(BOOST_CONTRACT_CONFIG_MAX_ARGS, arity), ~)
    
    #define BOOST_CONTRACT_PUBLIC_FUNCTION_VIRTUAL_OVERRIDES_(z, \
            arity, arity_compl, unused) \
        BOOST_CONTRACT_PUBLIC_FUNCTION_VIRTUAL_OVERRIDE_Z_(z, \
                arity, arity_compl, /* has_result = */ 0) \
        BOOST_CONTRACT_PUBLIC_FUNCTION_VIRTUAL_OVERRIDE_Z_(z, \
                arity, arity_compl, /* has_result = */ 1)
    
    BOOST_PP_REPEAT(BOOST_PP_INC(BOOST_CONTRACT_CONFIG_MAX_ARGS),
            BOOST_CONTRACT_PUBLIC_FUNCTION_VIRTUAL_OVERRIDE_ARITY_, ~)
#endif

} } // namespace

#endif // #include guard

