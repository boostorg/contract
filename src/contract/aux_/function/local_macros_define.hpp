// Copyright (C) 2009-2010 Lorenzo Caminiti.
// Use, modification, and distribution is subject to the
// Contract++ Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt.)

// IMPORTANT:
// *    No #include guard here
// *    Do not #include any other headers here (do it in the file
//      #including this one instead).
// *    These macros are local to the #including file, they all must be #undef
//      by "local_macros_undef.hpp" which must also be #include by the
//      #including file.
// See "local_macros_undef.hpp".

// These #defines are in a separate header only to split the code and
// make it more manageable. The #defines only make sense as part of
// the file that #include this file.

// Result typedefs.
// RestultType := R (R is untagged result type).

#define CONTRACT_typedef_arg_result_type \
    BOOST_PP_EXPR_IF(CONTRACT_is_not_void, \
        typedef typename aux::arg<ResultType>::type arg_result_type; \
    )

// Argument types.

#define CONTRACT_ArgumentType(z, n, data) \
    BOOST_PP_CAT(ArgumentType, n)

#define CONTRACT_argument_type(z, n, data) \
    BOOST_PP_CAT(argument_type, n)

#define CONTRACT_argument_ref(z, n, data) \
    BOOST_PP_CAT(argument_ref, n)

#define CONTRACT_arg_argument_type(z, n, data) \
    BOOST_PP_CAT(arg_argument_type, n)

#define CONTRACT_old_argument_type(z, n, data) \
    BOOST_PP_CAT(old_argument_type, n)

#define CONTRACT_arg_old_argument_type(z, n, data) \
    BOOST_PP_CAT(arg_old_argument_type, n)

// Agument names.

#define CONTRACT_argument(z, n, data) \
    BOOST_PP_CAT(argument, n)

#define CONTRACT_old_argument(z, n, data) \
    BOOST_PP_CAT(old_argument, n)

#define CONTRACT_oldcopy_argument(z, n, data) \
    BOOST_PP_CAT(oldcopy_argument, n)

#define CONTRACT_now_and_old_argument(z, n, data) \
    CONTRACT_argument(z, n, data) \
    BOOST_PP_COMMA() \
    CONTRACT_old_argument(z, n, data)

#define CONTRACT_now_and_oldcopy_argument(z, n, data) \
    CONTRACT_argument(z, n, data) \
    BOOST_PP_COMMA() \
    CONTRACT_oldcopy_argument(z, n, data).value

// Argument typedes.
// ArgumentType := A [+ copyable] (A is untagged argument type).

#define CONTRACT_typedef_argument_type(z, n, data) \
    typedef typename aux::remove_copyable< \
            CONTRACT_ArgumentType(z, n, data)>::type \
            CONTRACT_argument_type(z, n, data);

#define CONTRACT_typedef_argument_ref(z, n, data) \
    typedef typename boost::add_reference< \
            CONTRACT_argument_type(z, n, data)>::type \
            CONTRACT_argument_ref(z, n, data);

#define CONTRACT_typedef_arg_argument_type(z, n, data) \
    typedef typename aux::arg< \
            CONTRACT_argument_type(z, n, data)>::type \
            CONTRACT_arg_argument_type(z, n, data);

#define CONTRACT_typedef_old_argument_type(z, n, data) \
    typedef typename aux::old< \
            /* must keep eventual copyable for old */ \
            CONTRACT_ArgumentType(z, n, data)>::type \
            CONTRACT_old_argument_type(z, n, data);

#define CONTRACT_typedef_arg_old_argument_type(z, n, data) \
    typedef typename aux::arg< \
            CONTRACT_old_argument_type(z, n, data)>::type \
            CONTRACT_arg_old_argument_type(z, n, data);

// Now and old arguments.

#define CONTRACT_noncopyable_argument(z, n, data) \
    CONTRACT_argument_type(z, n, data) \
    CONTRACT_argument(z, n, data) 

#define CONTRACT_arg_argument(z, n, data) \
    CONTRACT_arg_argument_type(z, n, data) \
    CONTRACT_argument(z, n, data) 

#define CONTRACT_arg_now_and_old_argument(z, n, data) \
    CONTRACT_arg_argument(z, n, data) /* now type and name */ \
    BOOST_PP_COMMA() \
    CONTRACT_arg_old_argument_type(z, n, data) \
    CONTRACT_old_argument(z, n, data)

#define CONTRACT_copy_old_argument(z, n, data) \
    copy<CONTRACT_old_argument_type(z, n, data)> \
    CONTRACT_oldcopy_argument(z, n, data)( \
            CONTRACT_argument(z, n, data));

// Class types.
// ClassType := C [+ const ] [+ volatile] [+ copyable]
// (C is untagged class type).
    
#define CONTRACT_typedef_maybecv_class_type \
    typedef typename aux::remove_copyable<ClassType>::type \
            maybecv_class_type;

#define CONTRACT_typedef_class_type \
    typedef typename boost::remove_const<typename \
            boost::remove_volatile<maybecv_class_type>::type>::type \
            class_type;

#define CONTRACT_typedef_maybecv_class_ptr \
    typedef typename boost::add_pointer<maybecv_class_type \
            >::type maybecv_class_ptr;

#define CONTRACT_typedef_arg_class_ptr \
    typedef typename aux::arg<maybecv_class_ptr>::type \
            arg_class_ptr;

#define CONTRACT_typedef_old_class_type \
    typedef typename aux::old<ClassType>::type old_class_type;

#define CONTRACT_typedef_arg_old_class_ptr \
    typedef typename aux::arg<typename aux::old< \
            typename aux::copyable_add_pointer<ClassType \
            >::type>::type>::type arg_old_class_ptr;

// Base contracts.

#define CONTRACT_BaseContractClass(z, n, data) \
    BOOST_PP_CAT(BaseContractClass, n)

#define CONTRACT_base_contract(z, n, data) \
    /* postfixed with '_' because private member variable */ \
    BOOST_PP_CAT(BOOST_PP_CAT(base_contract, n), _)

#define CONTRACT_declare_base_contract(z, n, data) \
    CONTRACT_BaseContractClass(z, n, data)* \
    CONTRACT_base_contract(z, n, data);

#define CONTRACT_init_base_contract(z, n, data) \
    CONTRACT_base_contract(z, n, data)(/* default constructor */)

#define CONTRACT_alloc_base_contract(z, n, data) \
    if (!boost::is_same<CONTRACT_BaseContractClass(z, n, data), \
            aux::void_base_contract<CONTRACT_f(CONTRACT_is_member)> \
            >::value) { \
        CONTRACT_base_contract(z, n, data) = \
                new CONTRACT_BaseContractClass(z, n, data)(); \
    }

#define CONTRACT_dealloc_base_contract(z, n, data) \
    if (CONTRACT_base_contract(z, n, data)) { \
        delete CONTRACT_base_contract(z, n, data); \
    }

#define CONTRACT_check_base_invariant(z, n, data) \
    if (CONTRACT_base_contract(z, n, data)) { \
        typename CONTRACT_BaseContractClass(z, n, data)::class_type \
                const* base_object = 0; \
        state::to_base_(object, base_object); \
        CONTRACT_base_contract(z, n, data)->check_invariant( \
                base_object, dynamic_invariant_check); \
    }

#define CONTRACT_check_base_precondition(z, n, data) \
    if (failed && CONTRACT_base_contract(z, n, data)) { \
        try { \
            typename CONTRACT_BaseContractClass(z, n, data):: \
                    class_type const* base_object = 0; \
            state::to_base_(object, base_object); \
            CONTRACT_base_contract(z, n, data)->check_precondition( \
                    base_object \
                    BOOST_PP_ENUM_TRAILING( \
                            CONTRACT_arity, \
                            CONTRACT_argument, ~) \
                    ); \
            failed = false; /* Passed, done. */ \
        } catch (...) {} /* Keep checking... */ \
    }

#define CONTRACT_check_base_postcondition(z, n, data) \
    if (CONTRACT_base_contract(z, n, data)) { \
        typename CONTRACT_BaseContractClass(z, n, data):: \
                class_type const* base_object = 0; \
        state::to_base_(object, base_object); \
        CONTRACT_base_contract(z, n, data)->check_postcondition(\
                base_object \
                , old_object \
                /* , argument0, old_argument0, ... */ \
                BOOST_PP_ENUM_TRAILING(CONTRACT_arity, \
                        CONTRACT_now_and_old_argument, ~) \
                /* , result (if non-void) */ \
                BOOST_PP_COMMA_IF(CONTRACT_is_not_void) \
                BOOST_PP_EXPR_IF(CONTRACT_is_not_void, result) \
                ); \
    }

// Template parameters.

#define CONTRACT_tparam_ArgumentType(z, n, data) \
    typename CONTRACT_ArgumentType(z, n, data) 

#define CONTRACT_tparam_BaseContractClass(z, n, data) \
    class CONTRACT_BaseContractClass(z, n, data)

#define CONTRACT_tparam_BaseContractClass_default(z, n, data) \
    class CONTRACT_BaseContractClass(z, n, data) = \
            aux::void_base_contract<F>

// Functions pointers.

// F := ResultType (ClassType const*, ArgumentType0, ...).
// Class and argument types are optional, result type can be void.
#define CONTRACT_f(is_member) \
    BOOST_PP_IF(BOOST_PP_NOT(CONTRACT_is_not_void), void, ResultType) \
    ( \
        BOOST_PP_EXPR_IF(is_member, ClassType*) \
        BOOST_PP_COMMA_IF(BOOST_PP_AND(is_member, CONTRACT_arity)) \
        BOOST_PP_ENUM(CONTRACT_arity, CONTRACT_ArgumentType, ~) \
    ) 

#define CONTRACT_typedef_body_member_function_ptr_(unused) \
    /* Use cv-qualified support types for compiler compatibility (MSVC). */ \
    typedef ResultType (class_type::* nonconst_body_function_ptr_)( \
            /* argument_type0, ... */ \
            BOOST_PP_ENUM(CONTRACT_arity, \
                    CONTRACT_argument_type, ~) ) \
            ; \
    typedef ResultType (class_type::* const_body_function_ptr_)( \
            /* argument_type0, ... */ \
            BOOST_PP_ENUM(CONTRACT_arity, \
                    CONTRACT_argument_type, ~) ) \
            const; \
    typedef ResultType (class_type::* volatile_body_function_ptr_)( \
            /* argument_type0, ... */ \
            BOOST_PP_ENUM(CONTRACT_arity, \
                    CONTRACT_argument_type, ~) ) \
            volatile; \
    typedef ResultType (class_type::* cv_body_function_ptr_)( \
            /* argument_type0, ... */ \
            BOOST_PP_ENUM(CONTRACT_arity, \
                    CONTRACT_argument_type, ~) ) \
            const volatile; \
    typedef /* no indentation to better read MPL if_ */ \
typename boost::mpl::if_< \
        boost::mpl::and_< \
              boost::is_const<maybecv_class_type> \
            , boost::is_volatile<maybecv_class_type> \
        > \
    , cv_body_function_ptr_ \
    , typename boost::mpl::if_<boost::is_const<maybecv_class_type> \
        , const_body_function_ptr_ \
        , typename boost::mpl::if_< \
                boost::is_volatile<maybecv_class_type> \
            , volatile_body_function_ptr_ \
            , nonconst_body_function_ptr_ \
        >::type \
    >::type \
>::type body_function_ptr; 
        
#define CONTRACT_typedef_body_nonmember_function_ptr_(unused) \
    typedef ResultType (* body_function_ptr)( \
            /* argument_type0, ... */ \
            BOOST_PP_ENUM(CONTRACT_arity, \
                    CONTRACT_argument_type, ~) ) \
            ; 

#define CONTRACT_typedef_body_function_ptr(is_member) \
    BOOST_PP_IF(is_member, \
        CONTRACT_typedef_body_member_function_ptr_ \
    , /* else */ \
        CONTRACT_typedef_body_nonmember_function_ptr_ \
    )(~) /* delay macro expansion to handle commas in mpl::if_<> */

#define CONTRACT_typedef_precondition_function_ptr_(name) \
    typedef void ( \
            BOOST_PP_EXPR_IF(CONTRACT_is_member, class_type::) \
            * name)( \
            /* arg_argument_type0 argument0, ... */ \
            BOOST_PP_ENUM(CONTRACT_arity, CONTRACT_arg_argument, ~) \
            ) /* user must add trailing `;` */

#define CONTRACT_typedef_precondition_function_ptr_select_(name) \
    typedef typename boost::mpl::if_< \
                    boost::is_volatile<maybecv_class_type> \
                , cv_precondition_function_ptr_ \
                , const_precondition_function_ptr_ \
            >::type name /* user must add trailing `;` */

#define CONTRACT_typedef_precondition_function_ptr \
    BOOST_PP_IF(CONTRACT_is_member, \
        CONTRACT_typedef_precondition_function_ptr_( \
                const_precondition_function_ptr_) const ; \
        CONTRACT_typedef_precondition_function_ptr_( \
                cv_precondition_function_ptr_) const volatile ; \
        CONTRACT_typedef_precondition_function_ptr_select_ \
    , /* else */ \
        CONTRACT_typedef_precondition_function_ptr_ \
    )(precondition_function_ptr) ;

#define CONTRACT_typedef_static_precondition_function_ptr \
    typedef void ( \
            /* never class type (static so no object) */ \
            * static_precondition_function_ptr)( \
            /* arg_argument_type0 argument0, ... */ \
            BOOST_PP_ENUM(CONTRACT_arity, CONTRACT_arg_argument, ~) ) \
            /* never const (static so no object) */ ;

#define CONTRACT_typedef_postcondition_function_ptr_(name) \
    typedef void ( \
            BOOST_PP_EXPR_IF(CONTRACT_is_member, class_type::) \
            * name)( \
            /* arg_old_class_ptr (if memeber) */ \
            BOOST_PP_EXPR_IF(CONTRACT_is_member, arg_old_class_ptr) \
            /* , arg_argument_type0 argument0 */ \
            /* , arg_old_argument_type0 old_argument0, ... */ \
            BOOST_PP_COMMA_IF(BOOST_PP_AND(CONTRACT_arity, \
                    CONTRACT_is_member)) \
            BOOST_PP_ENUM(CONTRACT_arity, \
                    CONTRACT_arg_now_and_old_argument, ~) \
            /* , arg_result_type result (if not void) */ \
            BOOST_PP_COMMA_IF(BOOST_PP_AND(CONTRACT_is_not_void, \
                    BOOST_PP_OR(CONTRACT_arity, CONTRACT_is_member))) \
            BOOST_PP_EXPR_IF(CONTRACT_is_not_void, \
                    arg_result_type result) \
            ) /* user must add trailing `;` */

#define CONTRACT_typedef_postcondition_function_ptr_select_(name) \
    typedef typename boost::mpl::if_< \
                    boost::is_volatile<maybecv_class_type> \
                , cv_postcondition_function_ptr_ \
                , const_postcondition_function_ptr_ \
            >::type name /* user must add trailing `;` */

#define CONTRACT_typedef_postcondition_function_ptr \
    BOOST_PP_IF(CONTRACT_is_member, \
        CONTRACT_typedef_postcondition_function_ptr_( \
                const_postcondition_function_ptr_) const ; \
        CONTRACT_typedef_postcondition_function_ptr_( \
                cv_postcondition_function_ptr_) const volatile ; \
        CONTRACT_typedef_postcondition_function_ptr_select_ \
    , /* else */ \
        CONTRACT_typedef_postcondition_function_ptr_ \
    )(postcondition_function_ptr) ;
            
#define CONTRACT_typedef_static_postcondition_function_ptr \
    typedef void ( \
            /* never class_type (static so no object) */ \
            * static_postcondition_function_ptr)( \
            /* ever old object type (static so no ojbect) */ \
            /* , arg_argument_type0 argument0 */ \
            /* , arg_old_argument_type0 old_argument0, ... */ \
            BOOST_PP_ENUM(CONTRACT_arity, \
                    CONTRACT_arg_now_and_old_argument, ~) \
            /* , arg_result_type result (if not void) */ \
            BOOST_PP_COMMA_IF(BOOST_PP_AND(CONTRACT_is_not_void, \
                    CONTRACT_arity)) \
            BOOST_PP_EXPR_IF(CONTRACT_is_not_void, \
                    arg_result_type result) \
            ) /* never const (static so no ojbect) */ ;

