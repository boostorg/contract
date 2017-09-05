
// Copyright (C) 2008-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://sourceforge.net/projects/contractpp

#undef CONTRACT_AUX_PP_ITERATION_IS_MEMBER
#undef CONTRACT_AUX_PP_ITERATION_MEMBER_CONST
#undef CONTRACT_AUX_PP_ITERATION_MEMBER_VOLATILE

#if BOOST_PP_FRAME_ITERATION(2) == 0 // Free func.
#   define CONTRACT_AUX_PP_ITERATION_IS_MEMBER 0
#   define CONTRACT_AUX_PP_ITERATION_MEMBER_CONST /* empty */
#   define CONTRACT_AUX_PP_ITERATION_MEMBER_VOLATILE /* empty */
#elif BOOST_PP_FRAME_ITERATION(2) == 1 // Member func.
#   define CONTRACT_AUX_PP_ITERATION_IS_MEMBER 1
#   define CONTRACT_AUX_PP_ITERATION_MEMBER_CONST /* empty */
#   define CONTRACT_AUX_PP_ITERATION_MEMBER_VOLATILE /* empty */
#elif BOOST_PP_FRAME_ITERATION(2) == 2 // Const member func.
#   define CONTRACT_AUX_PP_ITERATION_IS_MEMBER 1
#   define CONTRACT_AUX_PP_ITERATION_MEMBER_CONST const
#   define CONTRACT_AUX_PP_ITERATION_MEMBER_VOLATILE /* empty */
#elif BOOST_PP_FRAME_ITERATION(2) == 3 // Volatile member func.
#   define CONTRACT_AUX_PP_ITERATION_IS_MEMBER 1
#   define CONTRACT_AUX_PP_ITERATION_MEMBER_CONST /* empty */
#   define CONTRACT_AUX_PP_ITERATION_MEMBER_VOLATILE volatile
#elif BOOST_PP_FRAME_ITERATION(2) == 4 // Const volatile member func.
#   define CONTRACT_AUX_PP_ITERATION_IS_MEMBER 1
#   define CONTRACT_AUX_PP_ITERATION_MEMBER_CONST const
#   define CONTRACT_AUX_PP_ITERATION_MEMBER_VOLATILE volatile
#else
#   error "INTERNAL ERROR: invalid iteration index (in frame 2)"
#endif

