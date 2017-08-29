// Copyright (C) 2009-2010 Lorenzo Caminiti.
// Use, modification, and distribution is subject to the
// Contract++ Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt.)

#if !BOOST_PP_IS_ITERATING
#   // Include guards (but only if not iter).
#   ifndef CONTRACT_STATIC_MEMBER_FUNCTION_HPP_
#       define CONTRACT_STATIC_MEMBER_FUNCTION_HPP_
#       include "nonmember_function.hpp"
#       include <boost/mpl/assert.hpp>
#       include <boost/preprocessor.hpp>
#       include "aux_/function/local_macros_define.hpp" // #undef below.

namespace contract {

// Should never be used directly (use only the specializations).
template<typename F
        // No bases (static have no object instance).
        >
class static_member_function {
    BOOST_MPL_ASSERT_MSG(0, CONTRACT_ERROR_specified_invalid_function_type_template_parameter_F, ());
};

} // namespace

// Self-iterate this file over arity, void, and const.
#       define BOOST_PP_ITERATION_PARAMS_1 (3, \
            (0, CONTRACT_CONFIG_MAX_FUNCTION_ARITY, \
            CONTRACT_CONFIG_STATIC_MEMBER_FUNCTION_HPP_FILE_PATH_))
#       include BOOST_PP_ITERATE() // Iter over arity.
#       include "aux_/function/local_macros_undef.hpp" // #define above.
#   endif // #include guard
# // 1st self-iteration over function-arity.
#elif BOOST_PP_ITERATION_DEPTH() == 1
#   define BOOST_PP_ITERATION_PARAMS_2 (3, (0, 1, \
            CONTRACT_CONFIG_STATIC_MEMBER_FUNCTION_HPP_FILE_PATH_))
#   include BOOST_PP_ITERATE() // Iter over 0 void, 1 non-void func.
# // 2nd self-iteration over void/non-void function.
#elif BOOST_PP_ITERATION_DEPTH() == 2
#   // Define local macros directly depending on iteration.
#   define CONTRACT_arity \
        BOOST_PP_SUB(BOOST_PP_FRAME_FINISH(1), BOOST_PP_FRAME_ITERATION(1))
#   define CONTRACT_is_not_void BOOST_PP_NOT(BOOST_PP_FRAME_ITERATION(2))
#   define CONTRACT_is_member 1 // Always a member function.

namespace contract {

template<class ClassType // Always class type (it's a member).
        // , ResultType (if not void)
        BOOST_PP_COMMA_IF(CONTRACT_is_not_void)
        BOOST_PP_EXPR_IF(CONTRACT_is_not_void, typename ResultType)
        // , ArgumentType0 ...
        BOOST_PP_ENUM_TRAILING(CONTRACT_arity,
                CONTRACT_tparam_ArgumentType, ~)
        // No bases.
        >
class static_member_function<CONTRACT_f(1 /* memeber */)>:
        // Static pre/post are like if not a member so inherit
        // from non-member but override to check static inv.
        public nonmember_function<
                CONTRACT_f(0 /* static so as if non-member */)> {
    BOOST_MPL_ASSERT_MSG(
            boost::mpl::not_< aux::is_copyable<ClassType> >::value,
            CONTRACT_ERROR_class_type_cannot_be_copyable_for_static_member_functions, (ClassType));
    BOOST_MPL_ASSERT_MSG(
            boost::mpl::not_< boost::is_const<ClassType> >::value,
            CONTRACT_ERROR_class_type_cannot_be_const_for_static_member_functions, (ClassType));

private:
    // Type manipulations (see nonmember_function<>).
    CONTRACT_typedef_maybeconst_class_type
    CONTRACT_typedef_class_type // No static subcontract so private.
    CONTRACT_typedef_maybeconst_class_ptr
    CONTRACT_typedef_arg_class_ptr;
    CONTRACT_typedef_old_class_type
    CONTRACT_typedef_arg_old_class_ptr
    BOOST_PP_EXPR_IF(BOOST_PP_NOT(CONTRACT_is_not_void),
            typedef void ResultType;)
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
    CONTRACT_typedef_static_postcondition_function_ptr
    CONTRACT_typedef_body_function_ptr(0 /* static body */)

#if CONTRACT_CONFIG_DEBUG_
    // Use body type (not class) for consistency with non-member.
private: typedef body_function_ptr debug_type;
#endif // debug

public:
    static_member_function(body_function_ptr body_function
        // Static pre/post condition function types (no object).
#if defined CONTRACT_CHECK_PRECONDITION
            , static_precondition_function_ptr precondition_function
#endif // check precondition
#if defined CONTRACT_CHECK_POSTCONDITION
            , static_postcondition_function_ptr postcondition_function
#endif // check postcondition
            ): nonmember_function<
                    CONTRACT_f(0 /* static as if non-member */)>(
                    body_function
#if defined CONTRACT_CHECK_PRECONDITION
                    , precondition_function
#endif // check precondition
#if defined CONTRACT_CHECK_POSTCONDITION
                    , postcondition_function
#endif // check postcondition
            ) {}

private:
    inline from here() const { return FROM_STATIC_MEMBER_FUNCTION; }

#if defined CONTRACT_CHECK_CLASS_INVARIANT
    // Override to check static invariants.
    inline void check_invariant() {
        try {
            aux::globally_checking_contract = true;
            // POLICTY: For static member, only check static
            // invariants (never disabled).
            
            // Log using static body sign (not class_type).
            CONTRACT_AUX_DEBUGT(debug_type, dbg
                    << "Checking static invariants");
            state::call_static_invariant_<class_type>();
            
            aux::globally_checking_contract = false;
        } catch (...) {
            aux::globally_checking_contract = false;
            throw;
        }
    }
#endif // check invariant

}; // class

} // namespace

#   // Undef ALL local macros directly depending on iteration.
#   undef CONTRACT_arity
#   undef CONTRACT_is_not_void
#   undef CONTRACT_is_member
#else // Self-iteration out-of-range (should never happen...).
#   error "Preprocessor iteration depth out-of-range (internal error)"

#endif // BOOST_PP_IS_ITERATING

