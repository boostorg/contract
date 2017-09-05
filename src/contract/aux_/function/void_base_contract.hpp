// Copyright (C) 2009-2010 Lorenzo Caminiti.
// Use, modification, and distribution is subject to the
// Contract++ Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt.)

#if !BOOST_PP_IS_ITERATING
#   // #include guard (but only if not iter).
#   ifndef CONTRACT_AUX_VOID_BASE_CONTRACT_HPP_
#       define CONTRACT_AUX_VOID_BASE_CONTRACT_HPP_
#       include "../../config.hpp"
#       include "../../old.hpp"
#       include "../old.hpp"
#       include "../arg.hpp"
#       include "../check01.hpp"
#       include <boost/type_traits.hpp>
#       include <boost/mpl/assert.hpp>
#       include <boost/preprocessor.hpp>
#       include <boost/utility.hpp>

namespace contract { namespace aux {

template<typename F>
class void_base_contract {
    BOOST_MPL_ASSERT_MSG(0, CONTRACT_ERROR_only_void_base_contract_template_specializations_should_be_used, ());
};

}} // namespace

// Self-iterate this file over arity, void, and const (no iteration
// over non-member because base contracts do not apply to non member).
#       define BOOST_PP_ITERATION_PARAMS_1 \
                (3, (0, CONTRACT_CONFIG_MAX_FUNCTION_ARITY, \
        CONTRACT_CONFIG_AUX_VOID_BASE_CONTRACT_HPP_FILE_PATH_))
#       include BOOST_PP_ITERATE() // Iter over function arity.
#   endif // #include guard
# // 1st self-iteration over function-arity.
#elif BOOST_PP_ITERATION_DEPTH() == 1
#   define BOOST_PP_ITERATION_PARAMS_2 (3, (0, 1, \
        CONTRACT_CONFIG_AUX_VOID_BASE_CONTRACT_HPP_FILE_PATH_))
#   include BOOST_PP_ITERATE() // Iter over 0 void, 1 non-void func.
# // 2nd self-iteration over void/non-void function.
#elif BOOST_PP_ITERATION_DEPTH() == 2
#   // Define local macros directly depending on iteration.
#   define CONTRACT_rest_arity BOOST_PP_FRAME_ITERATION(1)
#   define CONTRACT_arity \
        BOOST_PP_SUB(BOOST_PP_FRAME_FINISH(1), CONTRACT_rest_arity)
#   define CONTRACT_is_void BOOST_PP_FRAME_ITERATION(2)
#   define CONTRACT_is_not_void BOOST_PP_NOT(CONTRACT_is_void)
#   // Base contracts only for members (so member is always 1 here).
#   define CONTRACT_is_member 1
#   define CONTRACT_is_not_member BOOST_PP_NOT(CONTRACT_is_member)
#   include "local_macros_define.hpp"

namespace contract { namespace aux {

template<class ClassType
        // , ResultType (if not void)
        BOOST_PP_COMMA_IF(CONTRACT_is_not_void)
        BOOST_PP_EXPR_IF(CONTRACT_is_not_void, typename ResultType)
        // , ArgumentType0 ...
        BOOST_PP_ENUM_TRAILING(CONTRACT_arity,
                CONTRACT_tparam_ArgumentType, ~)
        >
class void_base_contract<CONTRACT_f(CONTRACT_is_member)> {
private:
    CONTRACT_typedef_maybecv_class_type;
public:
    CONTRACT_typedef_class_type // Must be public for subcontracting.
private:
    CONTRACT_typedef_maybecv_class_ptr
    CONTRACT_typedef_arg_class_ptr;
    CONTRACT_typedef_old_class_type
    CONTRACT_typedef_arg_old_class_ptr
    BOOST_PP_EXPR_IF(CONTRACT_is_void, typedef void ResultType;)
    CONTRACT_typedef_arg_result_type
    BOOST_PP_REPEAT(CONTRACT_arity, CONTRACT_typedef_argument_type, ~)
    BOOST_PP_REPEAT(CONTRACT_arity, CONTRACT_typedef_argument_ref, ~)
    BOOST_PP_REPEAT(CONTRACT_arity, CONTRACT_typedef_arg_argument_type, ~)
    BOOST_PP_REPEAT(CONTRACT_arity, CONTRACT_typedef_old_argument_type, ~)
    BOOST_PP_REPEAT(CONTRACT_arity, CONTRACT_typedef_arg_old_argument_type, ~)

public: // Empty check_xyz() implementation "{}" needed to compile.
#if CONTRACT_AUX_CHECK_CLASS_INVARIANT_01
    void check_invariant(arg_class_ptr object,
            const bool& dynamic_invariant_check) {}
#endif // check invariant

#if CONTRACT_AUX_CHECK_PRECONDITION_01
    void check_precondition(arg_class_ptr object
            // , arg_argument_type0 argument0, ...
            BOOST_PP_ENUM_TRAILING(CONTRACT_arity,
                    CONTRACT_arg_argument, ~)
            ) {}
#endif // check precondition

#if CONTRACT_AUX_CHECK_POSTCONDITION_01
    void check_postcondition(arg_class_ptr object
            , arg_old_class_ptr old_object
            // , arg_argument_type0 argument0
            // , arg_old_argument_type0 old_argument0, ...
            BOOST_PP_ENUM_TRAILING(CONTRACT_arity,
                    CONTRACT_arg_now_and_old_argument, ~)
            // , arg_result_type result (if not void)
            BOOST_PP_COMMA_IF(CONTRACT_is_not_void)
            BOOST_PP_EXPR_IF(CONTRACT_is_not_void,
                    arg_result_type result)
            ) {}
#endif // check postcondition
};

}} // namespace

#   // Undef ALL local macros directly depending on iteration.
#   undef CONTRACT_rest_arity
#   undef CONTRACT_arity
#   undef CONTRACT_is_void
#   undef CONTRACT_is_not_void
#   undef CONTRACT_is_const
#   undef CONTRACT_is_not_const
#   undef CONTRACT_is_member
#   undef CONTRACT_is_not_member
#   include "local_macros_undef.hpp"
#else // Self-iteration out-of-range (should never happen...).
#   error "Preprocessor iteration depth out-of-range (internal error)"
#endif // BOOST_PP_IS_ITERATING

