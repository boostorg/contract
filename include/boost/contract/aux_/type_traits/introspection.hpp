
#ifndef BOOST_CONTRACT_AUX_INTROSPECTION_HPP_
#define BOOST_CONTRACT_AUX_INTROSPECTION_HPP_

#include <boost/contract/aux_/name.hpp>
/** @cond */
#include <boost/function_types/member_function_pointer.hpp>
#include <boost/function_types/function_pointer.hpp>
#include <boost/function_types/property_tags.hpp>
#include <boost/mpl/push_front.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/preprocessor/tuple/eat.hpp>
#include <boost/preprocessor/tuple/rem.hpp>
#include <boost/preprocessor/control/iif.hpp>
/** @endcond */

// NOTE: Unfortunately, it is not possible to use Boost.TTI because it not
// always works on MSVC (e.g., when the introspecting meta-function is invoked
// multiple times, MSVC 2010 gives an internal compiler error). This is a
// simpler introspecting implementation that seem to work better with MSVC.

/* PUBLIC */

#define BOOST_CONTRACT_AUX_INTROSPECTION_HAS_TYPE(trait, type_name)\
    template<typename BOOST_CONTRACT_AUX_NAME1(T)> \
    class trait { \
        template<class BOOST_CONTRACT_AUX_NAME1(C)> \
        static boost::contract::aux::introspection::yes& check( \
                typename BOOST_CONTRACT_AUX_NAME1(C)::type_name*); \
        BOOST_CONTRACT_AUX_INTROSPECTION_END_(BOOST_CONTRACT_AUX_NAME1(T)) \
    };

#define BOOST_CONTRACT_AUX_INTROSPECTION_HAS_MEMBER_FUNCTION( \
        trait, func_name) \
    BOOST_CONTRACT_AUX_INTROSPECTION_HAS_MEMBER_FUNCTION_(/* is_static = */ 0, \
            trait, func_name)

#define BOOST_CONTRACT_AUX_INTROSPECTION_HAS_STATIC_MEMBER_FUNCTION(trait, \
        func_name) \
    BOOST_CONTRACT_AUX_INTROSPECTION_HAS_MEMBER_FUNCTION_(/* is_static = */ 1, \
            trait, func_name)
        
/* PRIVATE */

#define BOOST_CONTRACT_AUX_INTROSPECTION_HAS_MEMBER_FUNCTION_(is_static, \
        trait, func_name) \
    template< \
        typename BOOST_CONTRACT_AUX_NAME1(T), \
        typename BOOST_CONTRACT_AUX_NAME1(R), \
        class BOOST_CONTRACT_AUX_NAME1(P), \
        class BOOST_CONTRACT_AUX_NAME1(G) = boost::function_types::null_tag \
    > \
    class trait { \
        template<class BOOST_CONTRACT_AUX_NAME1(C)> \
        static boost::contract::aux::introspection::yes& check( \
            boost::contract::aux::introspection::check_function< \
                typename \
                    BOOST_PP_IIF(is_static, \
                        boost::function_types::function_pointer \
                    , \
                        boost::function_types::member_function_pointer \
                    ) \
                < \
                    typename boost::mpl::push_front< \
                        BOOST_PP_IIF(is_static, \
                            BOOST_CONTRACT_AUX_NAME1(P) \
                            BOOST_PP_TUPLE_EAT(2) \
                        , \
                            BOOST_PP_TUPLE_REM(2) \
                        )( \
                            typename boost::mpl::push_front< \
                                BOOST_CONTRACT_AUX_NAME1(P), \
                                BOOST_CONTRACT_AUX_NAME1(C) \
                            >::type \
                        ) \
                        , BOOST_CONTRACT_AUX_NAME1(R) \
                    >::type, \
                    BOOST_CONTRACT_AUX_NAME1(G) \
                >::type, \
                &BOOST_CONTRACT_AUX_NAME1(C)::func_name \
            >* \
        ); \
        BOOST_CONTRACT_AUX_INTROSPECTION_END_(BOOST_CONTRACT_AUX_NAME1(T)) \
    };

#define BOOST_CONTRACT_AUX_INTROSPECTION_END_(tparam) \
        template<typename> \
        static boost::contract::aux::introspection::no& check(...); \
    public: \
        static bool const value = sizeof(check<tparam>(0)) == \
                sizeof(boost::contract::aux::introspection::yes); \
        typedef boost::mpl::bool_<value> type;

/* CODE */

namespace boost { namespace contract { namespace aux { namespace introspection {

typedef struct {} yes;
typedef yes no[2];

template<typename F, F> struct check_function;

} } } } // namespace

#endif // #include guard

