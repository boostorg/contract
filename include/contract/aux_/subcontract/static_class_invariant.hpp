
// Copyright (C) 2008-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://sourceforge.net/projects/contractpp

#ifndef CONTRACT_AUX_SUBCONTRACT_STATIC_CLASS_INVARIANT_HPP_
#define CONTRACT_AUX_SUBCONTRACT_STATIC_CLASS_INVARIANT_HPP_

#include <contract/config.hpp>
#include <contract/aux_/subcontract/from.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/repetition/repeat.hpp>

#define CONTRACT_comma_class_Base(z, n, unused) \
    , class BOOST_PP_CAT(Base, n)
#define CONTRACT_comma_base_param(z, n, unused) \
    , void (* BOOST_PP_CAT(sub_static_class_inv, n)) ( )
#define CONTRACT_base_static_class_inv_check(z, n, unused) \
    if(is_subcontracted_from< Class, BOOST_PP_CAT(Base, n) >::value) { \
        (*BOOST_PP_CAT(sub_static_class_inv, n))(); \
    }

namespace contract { namespace aux {

template<
    class Class
    BOOST_PP_REPEAT(CONTRACT_CONFIG_INHERITANCE_MAX,
            CONTRACT_comma_class_Base, ~)
>
void subcontract_static_class_invariant(
    // NOTE: Even if the class inv func name is known a priori, func must be
    // passed by ptr to avoid error in accessing a private func.
      void (* this_static_class_inv) ( )
    BOOST_PP_REPEAT(CONTRACT_CONFIG_INHERITANCE_MAX,
            CONTRACT_comma_base_param, ~)
) {
    // Check all static class inv in short-circuit AND (1st throw stops check).
    BOOST_PP_REPEAT(CONTRACT_CONFIG_INHERITANCE_MAX,
            CONTRACT_base_static_class_inv_check, ~)
    (*this_static_class_inv)();
}

}} // namespace contract::aux

#undef CONTRACT_comma_class_Base
#undef CONTRACT_comma_base_param
#undef CONTRACT_base_static_class_inv_check

#endif // #include guard

