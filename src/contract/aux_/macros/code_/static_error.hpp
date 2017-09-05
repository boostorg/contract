// Copyright (C) 2009-2010 Lorenzo Caminiti.
// Use, modification, and distribution is subject to the
// Contract++ Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt.)

#ifndef CONTRACT_AUX_CODE_STATIC_ERROR_HPP_
#define CONTRACT_AUX_CODE_STATIC_ERROR_HPP_

#include <boost/mpl/assert.hpp>

// @param message A symbol of the form
//  `CONTRACT_ERROR_error_descriotion_here_in_lower_case`. This does
//  not have to be a #define macro or anything else, its just a name.
#define CONTRACT_AUX_CODE_STATIC_ERROR(message) \
    ; /* close eventaul previous staments, otherwise no effect */ \
    BOOST_MPL_ASSERT_MSG(0, message, ())
    ; /* must close ASSERT macro within class scope */ 

#endif // #include guard

