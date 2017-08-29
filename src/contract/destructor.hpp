// Copyright (C) 2009-2010 Lorenzo Caminiti.
// Use, modification, and distribution is subject to the
// Contract++ Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt.)

#ifndef CONTRACT_DESTRUCTOR_HPP_
#define CONTRACT_DESTRUCTOR_HPP_

#include "config.hpp"
#include "nonstatic_member_function.hpp"
#include "aux_/debug.hpp"
#include <boost/mpl/assert.hpp>

#define CONTRACT_f void (ClassType*) // Local macros #define.

namespace contract {

// Should never be used directly (use only the specializations).
template<typename F
        // No base contracts as constructors do not directly
        // subcontract (C++ construction calls bases automatically).
        >
class destructor {
    BOOST_MPL_ASSERT_MSG(0, CONTRACT_ERROR_specified_invalid_function_type_template_parameter_F, ());
};

template<class ClassType>
class destructor<CONTRACT_f>:
        public nonstatic_member_function<CONTRACT_f> { 
    // Destructor class cannot be copyable because there is no
    // object after body (so there is no postcondition).
    BOOST_MPL_ASSERT_MSG(
            boost::mpl::not_< aux::is_copyable<ClassType> >::value,
            CONTRACT_ERROR_class_type_cannot_be_copyable_for_destructors, (ClassType));
    BOOST_MPL_ASSERT_MSG(
            boost::mpl::not_< boost::is_const<ClassType> >::value,
            CONTRACT_ERROR_class_type_cannot_be_const_for_destructors, (ClassType));

private:
    // Type names consistent with nonstatic_member_function<>.
    typedef ClassType* maybeconst_class_ptr; // But never const...
    typedef void (ClassType::* body_function_ptr)();

#if CONTRACT_CONFIG_DEBUG_
    private: typedef ClassType debug_type;
#endif // debug

public:
    destructor(body_function_ptr body_function
            ): nonstatic_member_function<CONTRACT_f>(
                    body_function
#if defined CONTRACT_CHECK_PRECONDITION
                    , 0 // Never preconditions.
#endif // check precondition
#if defined CONTRACT_CHECK_POSTCONDITION
                    , 0 // Never postconditions.
#endif // check postcondition
            ) {}

    inline void call(
            maybeconst_class_ptr object
            // No function arguments.
            ) {
        CONTRACT_AUX_DEBUGT(debug_type, dbg
                << "Called destructor contract");
        return exec(
                object
                // No function arguments.
                , true // Only check invariants at entry.
                , false // No precondition check.
                , false // No post-invariant check.
                , false // No postcondition check.
                );
    }

private:
    inline from here() const { return FROM_DESTRUCTOR; }
};

} // namespace

#undef CONTRACT_f // Local macros #undef.

#endif // #include guard

