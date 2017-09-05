
// Copyright (C) 2008-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://sourceforge.net/projects/contractpp

#if !BOOST_PP_IS_ITERATING
#   ifndef CONTRACT_AUX_SUBCONTRACT_CLASS_INVARIANT_HPP_
#       define CONTRACT_AUX_SUBCONTRACT_CLASS_INVARIANT_HPP_

#include <contract/config.hpp>
#include <contract/aux_/subcontract/from.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/repetition/repeat.hpp>
#include <boost/preprocessor/iteration/iterate.hpp>

#define CONTRACT_class_Base(z, n, unused) \
    , class BOOST_PP_CAT(Base, n)
#define CONTRACT_comma_base_params(z, n, unused) \
    , BOOST_PP_CAT(Base, n) const CONTRACT_iteration_volatile* const \
            BOOST_PP_CAT(base, n) \
    , void (BOOST_PP_CAT(Base, n)::* const \
            BOOST_PP_CAT(sub_class_inv, n)) ( ) \
            const CONTRACT_iteration_volatile

#define CONTRACT_base_class_inv_check(z, n, unused) \
    if(is_subcontracted_from< Class, BOOST_PP_CAT(Base, n) >::value) { \
        (BOOST_PP_CAT(base, n)->*BOOST_PP_CAT(sub_class_inv, n))(); \
    }

#       define BOOST_PP_ITERATION_PARAMS_1 (3, (0, 1, \
                "contract/aux_/subcontract/class_invariant.hpp"))
#       include BOOST_PP_ITERATE() // Iterate over volatile or not.
#       undef CONTRACT_class_Base
#       undef CONTRACT_comma_base_params
#       undef CONTRACT_base_class_inv_check
#   endif // #include guard
#elif BOOST_PP_ITERATION_DEPTH() == 1
#   if BOOST_PP_FRAME_ITERATION(1) == 0
#       define CONTRACT_iteration_volatile /* empty */
#   elif BOOST_PP_FRAME_ITERATION(1) == 1
#       define CONTRACT_iteration_volatile volatile
#   else
#       error "INTERNAL ERROR: iteration index out-of-range"
#   endif

namespace contract { namespace aux {

template<
    class Class
    BOOST_PP_REPEAT(CONTRACT_CONFIG_INHERITANCE_MAX, CONTRACT_class_Base, ~)
>
void subcontract_class_invariant(
    // NOTE: Even if the class inv func name is known a priori, func must be
    // passed by ptr to avoid error in accessing a private func.
      Class const CONTRACT_iteration_volatile* const obj
    , void (Class::* const this_class_inv) ( ) const CONTRACT_iteration_volatile
    BOOST_PP_REPEAT(CONTRACT_CONFIG_INHERITANCE_MAX,
            CONTRACT_comma_base_params, ~)
) {
    // Check all class invs in short-circuit AND (1st throw stops check).
    BOOST_PP_REPEAT(CONTRACT_CONFIG_INHERITANCE_MAX,
            CONTRACT_base_class_inv_check, ~)
    (obj->*this_class_inv)();
}

}} // namespace contract::aux

#   undef CONTRACT_iteration_volatile
#else // iteration
#   error "INTERNAL ERROR: iteration index out-of-range"
#endif // iteration

