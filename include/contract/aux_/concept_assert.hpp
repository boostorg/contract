
// Copyright (C) 2008-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://sourceforge.net/projects/contractpp

#ifndef CONTRACT_AUX_CONCEPT_ASSERT_HPP_
#define CONTRACT_AUX_CONCEPT_ASSERT_HPP_

#include <boost/concept/requires.hpp>
#include <boost/preprocessor/cat.hpp>

// PRIVATE //

// Add support for more compilers copying Boost.ConceptCheck implementation.
#if BOOST_MSVC
#   if BOOST_WORKAROUND(BOOST_MSVC, == 1310)
#       define CONTRACT_AUX_CONCEPT_ASSERT_FN_(model_fn_ptr, id) \
            enum { \
                BOOST_PP_CAT(boost_concept_bheck, id) = \
                        sizeof(::boost::concepts::require< model_fn_ptr >) \
            }
#   else // Not vc-7.1
#       define CONTRACT_AUX_CONCEPT_ASSERT_FN_(model_fn_ptr, id) \
            enum { \
                BOOST_PP_CAT(boost_concept_check, id) = \
                        sizeof(::boost::concepts::require_((model_fn_ptr)0)) \
            }
#   endif
#else
#   define CONTRACT_AUX_CONCEPT_ASSERT_FN_(model_fn_ptr, id) \
        typedef ::boost::concepts::detail::instantiate< \
                &::boost::concepts::requirement_< model_fn_ptr >::failed > \
                BOOST_PP_CAT(boost_concept_check, id)
#endif

// PUBLIC //

// Same as `BOOST_CONCEPT_ASSERT` but with id (for same line macro expansion).
#define CONTRACT_AUX_CONCEPT_ASSERT(paren_model, id) \
    CONTRACT_AUX_CONCEPT_ASSERT_FN_(void (*) paren_model, id)

#endif // #include guard

