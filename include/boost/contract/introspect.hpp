
#ifndef BOOST_CONTRACT_INTROSPECT_HPP_
#define BOOST_CONTRACT_INTROSPECT_HPP_

#include <boost/contract/aux_/name.hpp>
#include <boost/contract/ext_/sfinae.hpp>
#include <boost/mpl/push_front.hpp>
#include <boost/preprocessor/cat.hpp>

/* PUBLIC */

#define BOOST_CONTRACT_INTROSPECT(function_name) \
    BOOST_CONTRACT_NAMED_INTROSPECT(BOOST_PP_CAT(introspect_, function_name), \
            function_name)

#define BOOST_CONTRACT_NAMED_INTROSPECT(introspect_name, function_name) \
    class introspect_name { \
        template< \
            typename BOOST_CONTRACT_AUX_NAME1(R), \
            class BOOST_CONTRACT_AUX_NAME1(P) \
        > \
        struct BOOST_CONTRACT_AUX_NAME1(has) { \
            template< typename BOOST_CONTRACT_AUX_NAME1(C) > \
            static boost::contract::ext::sfinae::yes& apply ( \
                boost::contract::ext::sfinae::function_exists< \
                    typename boost::function_types::member_function_pointer< \
                        typename boost::mpl::push_front< \
                            typename boost::mpl::push_front< \
                                BOOST_CONTRACT_AUX_NAME1(P), \
                                BOOST_CONTRACT_AUX_NAME1(C) \
                            >::type, \
                            BOOST_CONTRACT_AUX_NAME1(R) \
                        >::type \
                    >::type, \
                    &BOOST_CONTRACT_AUX_NAME1(C)::function_name \
                >* \
            ); \
        }; \
    \
    public:\
        template< \
            class BOOST_CONTRACT_AUX_NAME1(C), \
            typename BOOST_CONTRACT_AUX_NAME1(R), \
            class BOOST_CONTRACT_AUX_NAME1(P) \
        > \
        struct has_member_function : boost::contract::ext::sfinae::check< \
            BOOST_CONTRACT_AUX_NAME1(C), \
            BOOST_CONTRACT_AUX_NAME1(has)<BOOST_CONTRACT_AUX_NAME1(R), \
                    BOOST_CONTRACT_AUX_NAME1(P)> \
        > {}; \
    \
        template< class BOOST_CONTRACT_AUX_NAME1(C), \
                typename BOOST_CONTRACT_AUX_NAME1(F) > \
        static BOOST_CONTRACT_AUX_NAME1(F) member_function_address ( ) { \
            return &BOOST_CONTRACT_AUX_NAME1(C)::function_name; \
        } \
    };

#endif // #include guard

