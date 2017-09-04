/**
 * @file
 * Support for class invariant.
 * @author Copyright (C) 2009 Lorenzo Caminiti.
 *  Distributed under DBC++ Software License v1.0 (see file LICENSE_1_0.txt).
 */

#ifndef DBC_INVARIANT_HPP_
#define DBC_INVARIANT_HPP_

#include "detail/pp/defines.hpp" // Must be 1st include.
#include "config.hpp"

#if defined DBC_DOC

#define DBC_INVARIANT(full_class_type, invariants) \
    DBC_CONFIG_DOC_INVARIANT(full_class_type, invariants)

#elif !defined DBC

#undef DBC_INVARIANT_FUN
#define DBC_INVARIANT(full_class_type, invariants)

#else // DBC

#include "object.hpp"
#include <boost/type_traits.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/preprocessor.hpp>

/** User might use this to code the invariant check function directly bypassing
 * the macro below -- but not recommended. */
#define DBC_INVARIANT_FUN dbc_invariant_

/**
 * @param full_class_type Must include class's namespace and template params.
 */
#define DBC_INVARIANT(full_class_type, invariants) \
    /* statically assert "class is derived from dbc::object<>" */ \
    /* asserted here instead of in fun<> so user gets error in single spot */ \
    BOOST_MPL_ASSERT_MSG((::boost::is_base_of< ::dbc::object< \
            full_class_type >, full_class_type >::value), \
            DBC_ERROR_class_must_privately_inherit_from_dbc_object_, \
            (/* don't specify class_type here as it could be abstract */)); \
    /* class invariant impl (as non-member friend) */ \
    BOOST_PP_EXPR_IF(DBC_CHECK_INVARIANT, \
            friend inline void DBC_INVARIANT_FUN(const full_class_type& self) \
                invariants)

#endif // DBC

#endif // DBC_INVARIANT_HPP_

