// Copyright (C) 2009-2010 Lorenzo Caminiti.
// Use, modification, and distribution is subject to the
// Contract++ Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt.)

#if !BOOST_PP_IS_ITERATING
#   // Include guards (but only if not iter).
#   ifndef CONTRACT_CONSTRUCTOR_HPP_
#       define CONTRACT_CONSTRUCTOR_HPP_
#       include "config.hpp"
#       include "nonstatic_member_function.hpp"
#       include <boost/mpl/assert.hpp>
#       include <boost/preprocessor.hpp>
#       include "aux_/function/local_macros_define.hpp" // #undef below.

namespace contract {

// Should never be used directly (use only the specializations).
template<typename F
        // No base contracts as constructors do not directly
        // subcontract (C++ construction calls bases automatically).
        >
class constructor {
    BOOST_MPL_ASSERT_MSG(0, CONTRACT_ERROR_specified_invalid_function_type_template_parameter_F, ());
};

} // namespace

// Self-iterate this file over arity.
#       define BOOST_PP_ITERATION_PARAMS_1 (3, \
            (0, CONTRACT_CONFIG_MAX_FUNCTION_ARITY, \
            CONTRACT_CONFIG_CONSTRUCTOR_HPP_FILE_PATH_))
#       include BOOST_PP_ITERATE() // Iter over arity.
#       include "aux_/function/local_macros_undef.hpp" // #define above.
#   endif // #include guard
# // 1st self-iteration over function-arity.
#elif BOOST_PP_ITERATION_DEPTH() == 1
#   // Define local macros directly depending on iteration.
#   define CONTRACT_arity \
        BOOST_PP_SUB(BOOST_PP_FRAME_FINISH(1), BOOST_PP_FRAME_ITERATION(1))
#   define CONTRACT_is_not_void 0 // Construcotr always void.
#   define CONTRACT_is_member 1 // Always a member.

namespace contract {

template<class ClassType
        // , ArgumentType0 ...
        BOOST_PP_ENUM_TRAILING(CONTRACT_arity,
                CONTRACT_tparam_ArgumentType, ~)
        // No bases.
        >
class constructor<CONTRACT_f(1 /* always member */)>:
        public nonstatic_member_function<CONTRACT_f(1 /* member */)> {
    // Constructor class cannot be copyable because there was no
    // object before body (so there is no old object).
    BOOST_MPL_ASSERT_MSG(
            boost::mpl::not_< aux::is_copyable<ClassType> >::value,
            CONTRACT_ERROR_class_type_cannot_be_copyable_for_constructors, (ClassType));
    BOOST_MPL_ASSERT_MSG(
            boost::mpl::not_< boost::is_const<ClassType> >::value,
            CONTRACT_ERROR_class_type_cannot_be_const_for_constructors, (ClassType));
    
private:
    // Type manipulations (see nonstatic_member_function<>).
    CONTRACT_typedef_maybecv_class_type
    CONTRACT_typedef_class_type // No direct constr subcontract so private.
    CONTRACT_typedef_maybecv_class_ptr
    CONTRACT_typedef_arg_class_ptr;
    CONTRACT_typedef_old_class_type
    CONTRACT_typedef_arg_old_class_ptr
    typedef void ResultType;
    CONTRACT_typedef_arg_result_type
    BOOST_PP_REPEAT(CONTRACT_arity, CONTRACT_typedef_argument_type, ~)
    BOOST_PP_REPEAT(CONTRACT_arity, CONTRACT_typedef_argument_ref, ~)
    BOOST_PP_REPEAT(CONTRACT_arity,
            CONTRACT_typedef_arg_argument_type, ~)
    BOOST_PP_REPEAT(CONTRACT_arity,
            CONTRACT_typedef_old_argument_type, ~)
    BOOST_PP_REPEAT(CONTRACT_arity,
            CONTRACT_typedef_arg_old_argument_type, ~)

    CONTRACT_typedef_static_precondition_function_ptr
    CONTRACT_typedef_postcondition_function_ptr
    CONTRACT_typedef_body_function_ptr(CONTRACT_is_member)

#if CONTRACT_CONFIG_DEBUG_
    private: typedef class_type debug_type;
#endif // debug
        
public:
    constructor(body_function_ptr body_function
#if defined CONTRACT_CHECK_PRECONDITION
            , static_precondition_function_ptr precondition_function
#endif // check precondition
#if defined CONTRACT_CHECK_POSTCONDITION
            , postcondition_function_ptr postcondition_function
#endif // check postcondition
            ): nonstatic_member_function<
                    CONTRACT_f(1 /* always member */)>(
                    body_function
#if defined CONTRACT_CHECK_PRECONDITION
                    , 0 // Pre call made by call_pre() below.
#endif // check precondition
#if defined CONTRACT_CHECK_POSTCONDITION
                    , postcondition_function
#endif // check postcondition
            )
#if defined CONTRACT_CHECK_PRECONDITION
            , STATIC_PRECONDITION_FUNCTION_(precondition_function)
#endif // check precondition
            {}

    inline ResultType call(
            maybecv_class_ptr object
            // , argument_type0 argument0, ...
            BOOST_PP_ENUM_TRAILING(CONTRACT_arity,
                    CONTRACT_noncopyable_argument, ~)
            ) {
        CONTRACT_AUX_DEBUGT(debug_type, dbg
                << "Called constructor contract");
        return exec(
                object
                // , argument0, ...
                BOOST_PP_ENUM_TRAILING(CONTRACT_arity,
                        CONTRACT_argument, ~)
                , false // Never check invariant in precondition.
                , true // Precondition check.
                , true // Post-invariant check.
                , true // Postcondition check.
                );
    }

private:
    inline from here() const { return FROM_CONSTRUCTOR; }

#if defined CONTRACT_CHECK_PRECONDITION
    inline void call_precondition(
            arg_class_ptr object
            // , arg_argument_type0 argument0, ...
            BOOST_PP_ENUM_TRAILING(CONTRACT_arity,
                    CONTRACT_arg_argument, ~)
            ) {
        // Drop object and call static member precondition.
        STATIC_PRECONDITION_FUNCTION_(
                // argument0, ...
                BOOST_PP_ENUM(CONTRACT_arity,
                        CONTRACT_argument, ~)
                );
    }
            
    static_precondition_function_ptr const STATIC_PRECONDITION_FUNCTION_;
#endif // check precondition

}; // class
} // namespace

#   // Undef ALL local macros directly depending on iteration.
#   undef CONTRACT_arity
#   undef CONTRACT_is_not_void
#   undef CONTRACT_is_member
#else // Self-iteration out-of-range (should never happen...).
#   error "Preprocessor iteration depth out-of-range (internal error)"

#endif // BOOST_PP_IS_ITERATING

