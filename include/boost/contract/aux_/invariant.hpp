
#ifndef BOOST_CONTRACT_INVARIANT_HPP_
#define BOOST_CONTRACT_INVARIANT_HPP_

#include <boost/contract/config.hpp>
#include <boost/contract/ext_/sfinae.hpp>
#include <boost/preprocessor/facilities/empty.hpp>

/* PRIVATE */

#define BOOST_CONTRACT_INVARIANT_HAS_(has_name, cv_qualifiers) \
    namespace invariant_ { \
        struct has_name { \
            template< typename C > \
            static boost::contract::ext::sfinae::yes& apply ( \
                boost::contract::ext::sfinae::function_exists< \
                    void (C::* ) ( ) cv_qualifiers, \
                    &C::BOOST_CONTRACT_CONFIG_INVARIANT \
                >* \
            ); \
        }; \
    }

/* CODE */

namespace boost { namespace contract { namespace aux {

BOOST_CONTRACT_INVARIANT_HAS_(has_const, const)
BOOST_CONTRACT_INVARIANT_HAS_(has_mutable, BOOST_PP_EMPTY())

template< class C >
struct has_invariant :
        boost::contract::ext::sfinae::check<C, invariant_::has_const> {};

template< class C >
struct has_mutable_invariant :
        boost::contract::ext::sfinae::check<C, invariant_::has_mutable> {};

} } } // namespace

#endif // #include guard

