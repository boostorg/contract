
#ifndef BOOST_CONTRACT_INVARIANT_HPP_
#define BOOST_CONTRACT_INVARIANT_HPP_

#include <boost/contract/config.hpp>
#include <boost/contract/ext_/sfinae.hpp>
#include <boost/preprocessor/facilities/empty.hpp>

/* PRIVATE */

#define BOOST_CONTRACT_INVARIANT_HAS_(name, tparam, func_member, cv, func_name)\
    struct name { \
        template<typename tparam> \
        static boost::contract::ext::sfinae::yes& apply( \
            boost::contract::ext::sfinae::function_exists< \
                void func_member () cv, \
                &tparam::func_name \
            >* \
        ); \
    };

/* CODE */

namespace boost { namespace contract { namespace aux {
    
namespace invariant_ {
    BOOST_CONTRACT_INVARIANT_HAS_(has_const, T, (T::*), const,
            BOOST_CONTRACT_CONFIG_INVARIANT)

    BOOST_CONTRACT_INVARIANT_HAS_(has_mutable, T, (T::*), BOOST_PP_EMPTY(),
            BOOST_CONTRACT_CONFIG_INVARIANT)

    BOOST_CONTRACT_INVARIANT_HAS_(has_static, T, (*),
            BOOST_PP_EMPTY(), BOOST_CONTRACT_CONFIG_STATIC_INVARIANT)
}

template<class Class>
struct has_const_invariant :
        boost::contract::ext::sfinae::check<Class, invariant_::has_const> {};

template<class Class>
struct has_mutable_invariant :
        boost::contract::ext::sfinae::check<Class, invariant_::has_mutable> {};

template<class Class>
struct has_static_invariant :
        boost::contract::ext::sfinae::check<Class, invariant_::has_static> {};

} } } // namespace

#endif // #include guard

