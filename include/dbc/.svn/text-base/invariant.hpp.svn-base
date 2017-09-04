
#ifndef DBC_INVARIANT_HPP_
#define DBC_INVARIANT_HPP_

#include "config.hpp"

#if defined DBC_DOC

#define DBC_INVARIANT(full_class_type, invariant_code) \
    DBC_CONFIG_DOC_INVARIANT(full_class_type, invariant_code)

#elif !defined DBC

#define DBC_INVARIANT(full_class_type, invariant_code)

#else // DBC

#include "object.hpp"
#include <boost/type_traits.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/preprocessor.hpp>

/**
 * @param full_class_type Must include class's namespace and template params.
 */
#define DBC_INVARIANT(full_class_type, invariant_code) \
    /* statically assert "class is derived from dbc::object<>" */ \
    /* asserted here instead of in fun<> so user gets error in single spot */ \
    BOOST_MPL_ASSERT_MSG((::boost::is_base_of< ::dbc::object< \
            full_class_type >, full_class_type >::value), \
            DBC_ERROR_class_must_privately_inherit_from_dbc_object_, \
            (/* don't specify class_type here as it could be abstract */)); \
    /* class invariant impl (as non-member friend) */ \
    BOOST_PP_EXPR_IF(DBC_CHECK_INVARIANT, \
            friend inline void dbc_invariant_(const full_class_type& self) \
                invariant_code)

#endif // DBC

#endif // DBC_INVARIANT_HPP_

