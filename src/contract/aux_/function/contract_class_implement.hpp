// Copyright (C) 2009-2010 Lorenzo Caminiti.
// Use, modification, and distribution is subject to the
// Contract++ Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt.)

// IMPORTANT: This code is grouped here because common between
//            non-static member and non-member functions and it
//            is #included to implement those.
// * Do not use #include guards here.
// See context #including this file.

// These local macros must be #defined before #including this file.
#ifndef CONTRACT_arity
#   error "Must define CONTRACT_arity before #inclusion (internal error)"
#endif
#ifndef CONTRACT_is_not_void
#   error "Must define CONTRACT_is_not_void before #inclusion (internal error)"
#endif
#ifndef CONTRACT_is_member
#   error "Must define CONTRACT_is_member before #inclusion (internal error)"
#endif
    
// Start of class declaration here.

#if CONTRACT_is_member
private:
    CONTRACT_typedef_maybecv_class_type;
public: // Must be public for subcontracting (but only class_type).
    // C -- for function types.
    CONTRACT_typedef_class_type
private:
    // C [+ const] + ptr -- used by object this type.
    CONTRACT_typedef_maybecv_class_ptr
    // arg<C [+ const] + ptr> -- used by this arg passing.
    CONTRACT_typedef_arg_class_ptr;
    // old<C [+ const] [+ copyable]> -- used by old this variables.
    CONTRACT_typedef_old_class_type
    // arg< old<C [+ const] + ptr [+ copyable]> > -- used by old
    // this arg passing.
    CONTRACT_typedef_arg_old_class_ptr
#endif // is_member

private:
    // typedef void ResultType; (needed to compile).
    BOOST_PP_EXPR_IF(BOOST_PP_NOT(CONTRACT_is_not_void),
            typedef void ResultType;)

    // arg<R> -- used by result argument passing.
    CONTRACT_typedef_arg_result_type
    
    // A -- used by function types.
    // typedef remove_copyable<ArgumentType0> argument_type0; ...
    BOOST_PP_REPEAT(CONTRACT_arity, CONTRACT_typedef_argument_type, ~)
    
    // A + ref -- used by call() argument passing.
    // typedef add_reference<argument_type0> argument_ref0; ...
    BOOST_PP_REPEAT(CONTRACT_arity, CONTRACT_typedef_argument_ref, ~)
    
    // arg<A> -- used by argrument passing.
    // typedef arg<argument_type0> arg_argument_type0; ...
    BOOST_PP_REPEAT(CONTRACT_arity,
            CONTRACT_typedef_arg_argument_type, ~)
    
    // old<A>  -- used by old argument variables.
    // typedef old<argument_type0> old_argument_type0; ...
    BOOST_PP_REPEAT(CONTRACT_arity,
            CONTRACT_typedef_old_argument_type, ~)
    
    // arg< old<A> > -- used by old argrument passing.
    // typedef arg< old<argument_type0> > arg_old_argument_type0; ...
    BOOST_PP_REPEAT(CONTRACT_arity,
            CONTRACT_typedef_arg_old_argument_type, ~)

    // typedef void (class_type::* precondition_function_ptr)(
    // arg_argument_type0, ...) const;
    CONTRACT_typedef_precondition_function_ptr

    // typedef void (class_type::* precondition_function_ptr)(
    // arg_old_class_ptr, arg_argument_type0, arg_old_argument0, ...
    // , arg_result_type) const;
    CONTRACT_typedef_postcondition_function_ptr

    // typedef ResultType (class_type::* body_function_ptr)(
    //  argument_type0, ...) const;
    CONTRACT_typedef_body_function_ptr(CONTRACT_is_member)

#if CONTRACT_CONFIG_DEBUG_
    private:
        typedef BOOST_PP_IF(CONTRACT_is_member,
                class_type, body_function_ptr) debug_type;
#endif // debug

public:
    // Constructor arguments take body first so pre and post can 
    // always add leading comma (needed to facilitate code-based API).
    BOOST_PP_IF(CONTRACT_is_member // Constructor function name.
        , nonstatic_member_function
        , nonmember_function
    )(body_function_ptr body_function
#if defined CONTRACT_CHECK_PRECONDITION
            , precondition_function_ptr precondition_function
#endif // check precondition
#if defined CONTRACT_CHECK_POSTCONDITION
            , postcondition_function_ptr postcondition_function
#endif // check postcondition
            ): BODY_FUNCTION_(body_function)
#if defined CONTRACT_CHECK_PRECONDITION
            , PRECONDITION_FUNCTION_(precondition_function)
#endif // check precondition
#if defined CONTRACT_CHECK_POSTCONDITION
            , POSTCONDITION_FUNCTION_(postcondition_function)
#endif // check postcondition
#if CONTRACT_is_member
            BOOST_PP_ENUM_TRAILING(
                    CONTRACT_CONFIG_MAX_MULTIPLE_INHERITANCE,
                    CONTRACT_init_base_contract, ~)
#endif // is_member
            {
#if CONTRACT_is_member
        BOOST_PP_EXPR_IF(CONTRACT_is_member,
            // if (BaseContractClass0 != void_base_contract<F>)
            //  base_contract0_ = new BaseContractClass0(); ...
            BOOST_PP_REPEAT(CONTRACT_CONFIG_MAX_MULTIPLE_INHERITANCE,
                    CONTRACT_alloc_base_contract, ~)
        )
#endif // is_member
    }
    
    virtual // Compliers warn if no virtual destr but virt func.
    BOOST_PP_IF(CONTRACT_is_member // Constructor function name.
        , ~nonstatic_member_function
        , ~nonmember_function
    )() {
#if CONTRACT_is_member
        // if (base_contract0_) delete base_contract0_; ...
        BOOST_PP_REPEAT(CONTRACT_CONFIG_MAX_MULTIPLE_INHERITANCE,
                CONTRACT_dealloc_base_contract, ~)
#endif // is member (else, default destructor)
    }

    // Body function is passed at run-time to avoid errors for
    // overloaded functions (compiler gets confused with overloaded
    // constructors if body are passed as static function pointer in
    // template arguments -- I got error "using unqualified id as
    // template parameters"). Pre/post conditions function pointers
    // instead MUST be passed as template parameters because they
    // must be part of the base contract type for subcontrating.
    virtual ResultType call(
#if CONTRACT_is_member
            maybecv_class_ptr object
#endif // is member
            BOOST_PP_COMMA_IF(BOOST_PP_AND(CONTRACT_arity,
                    CONTRACT_is_member))
            // argument_type0 argument0, ...
            BOOST_PP_ENUM(CONTRACT_arity, 
                    CONTRACT_noncopyable_argument, ~)
            ) {
        CONTRACT_AUX_DEBUGT(debug_type, dbg << "Called "
                << (CONTRACT_is_member ?
                "member" : "non-member") << " function contract");
        return exec(
#if CONTRACT_is_member
                object
#endif // is member
                BOOST_PP_COMMA_IF(BOOST_PP_AND(CONTRACT_arity,
                        CONTRACT_is_member))
                // argument0, ...
                BOOST_PP_ENUM(CONTRACT_arity, CONTRACT_argument, ~)
#if CONTRACT_is_member
                , true // Pre-invariant check.
#endif // is member
                BOOST_PP_COMMA_IF(BOOST_PP_OR(CONTRACT_arity,
                        CONTRACT_is_member))
                true // Precondition check.
#if CONTRACT_is_member
                , true // Post-invariant check.
#endif // is member
                , true // Postcondition check.
                );
    }

    // For non-static members, check_xyz() must be pub (no prot/priv)
    // for subcontracting, otherwise they can be private.
#if !CONTRACT_is_member
private:
#endif // is member
    
    // check_xyz() must throw for proper subcontracting (of
    // preconditions) -- xyz_failed() must be called by exec().

#if defined CONTRACT_CHECK_CLASS_INVARIANT
#if CONTRACT_is_member
    void check_invariant(arg_class_ptr object,
            const bool& dynamic_invariant_check) {
        try {
            aux::globally_checking_contract = true;
            // POLICY: First, check in AND all base
            // invariants (following inheritance oreder
            // of BaseContractClass template params), AND
            // then check this class invariants.
            
            // And, all base invariants (subcontracting).
            // if (base_contract0_) {
            //     typename BaseContractClass0::class_type
            //             const* base_object = 0;
            //     state::to_base_(object, base_object);
            //     base_contract0_->check_invariant(
            //             base_object, dynamic_invariant_check);
            // } ...
            BOOST_PP_REPEAT(
                    CONTRACT_CONFIG_MAX_MULTIPLE_INHERITANCE,
                    CONTRACT_check_base_invariant, ~)
            
            // AND, this class invariants.
            CONTRACT_AUX_DEBUGT(debug_type, dbg
                        << "Checking static invariants");
            state::call_static_invariant_<class_type>();
            // POLICTY: Static invariant checking is never disabled.
            // Dynamic invariant checking instead is disabled in
            // nested calls, constructors entry, destructor exit,
            // etc (decided by this function caller).
            if (dynamic_invariant_check) { 
                CONTRACT_AUX_DEBUGT(debug_type, dbg
                        << "Checking invariants");
                state::call_invariant_(object);
            }
            
            aux::globally_checking_contract = false;
        } catch (...) {
            aux::globally_checking_contract = false;
            throw;
        }
    }
#else // is member
    // Do nothing for non-members but static members will override to
    // check static invariants.
    virtual void check_invariant() {}
#endif // is member
#endif // check invariant

#if defined CONTRACT_CHECK_PRECONDITION
    void check_precondition(
#if CONTRACT_is_member
            arg_class_ptr object
            BOOST_PP_COMMA_IF(CONTRACT_arity)
#endif // is member
            // arg_argument_type0 argument0, ...
            BOOST_PP_ENUM(CONTRACT_arity, CONTRACT_arg_argument, ~)
            ) {
        try {
            aux::globally_checking_contract = true;
            bool failed = true;

#if CONTRACT_is_member
            // POLICY: First, check in OR all base
            // preconditions (following inheritance oreder
            // of BaseContractClass template params), OR else
            // check this class preconditions at the end.

            // Check in OR all base postconditions (subcontracting).
            // if (failed && base_contract0_) {
            //     try {
            //         typename BaseContractClass0::class_type 
            //                 const* base_object = 0;
            //         state::to_base_(object, base_object);
            //         base_contract0_->check_precondition(
            //                 base_object
            //                 BOOST_PP_ENUM_TRAILING(
            //                         CONTRACT_arity,
            //                         CONTRACT_argument, ~)
            //                 );
            //         failed = false; // Passed, done.
            //     } catch (...) {} // Keep checking.
            // } ...
            BOOST_PP_REPEAT(
                    CONTRACT_CONFIG_MAX_MULTIPLE_INHERITANCE,
                    CONTRACT_check_base_precondition, ~)
#endif // is member
            
            // OR, this class preconditions.
            if (failed) {
                // All base preconditions failed. Then we check
                // this class preconditions. If they pass, no
                // exception is thrown. If they fail, they throw
                // a failure expection that is handeled by our
                // caller exec() by invoking
                // precondition_failed() with the thrown error.
                // Therefore, precondition_failed() CANNOT be
                // called from within here!
                CONTRACT_AUX_DEBUGT(debug_type, dbg
                        << "Checking preconditions");
#if CONTRACT_is_member
                call_precondition(object
                        // , argument0, ...
                        BOOST_PP_ENUM_TRAILING(CONTRACT_arity,
                                CONTRACT_argument, ~)
                        );
#else // is member
                PRECONDITION_FUNCTION_(
                        // argument0, ...
                        BOOST_PP_ENUM(CONTRACT_arity,
                                CONTRACT_argument, ~)
                        );
#endif // is member
            }
            
            aux::globally_checking_contract = false;
        } catch (...) {
            aux::globally_checking_contract = false;
            throw;
        }
    }
#endif // check precondition

#if defined CONTRACT_CHECK_POSTCONDITION
    void check_postcondition(
#if CONTRACT_is_member
            arg_class_ptr object
            , arg_old_class_ptr old_object
            BOOST_PP_COMMA_IF(CONTRACT_arity)
#endif // is member
            // arg_argument_type0 argument0
            // , arg_old_argument_type0 old_argument0, ...
            BOOST_PP_ENUM(CONTRACT_arity,
                    CONTRACT_arg_now_and_old_argument, ~)
            // , arg_result_type result (if not void)
#if CONTRACT_is_member || CONTRACT_arity
            BOOST_PP_COMMA_IF(CONTRACT_is_not_void)
#endif // is member or arity != 0
            BOOST_PP_EXPR_IF(CONTRACT_is_not_void,
                    arg_result_type result)
            ) {
        try {
            aux::globally_checking_contract = true;

#if CONTRACT_is_member
            // POLICY: First, check in AND all base
            // postconditions (following inheritance oreder
            // of BaseContractClass template params), AND
            // then check this class postconditions.

            // Check all base postconditions (subcontracting).
            // if (base_contract0_) {
            //     typename BaseContractClass0::class_type 
            //             const* base_object = 0;
            //     state::to_base_(object, base_object);
            //     base_contract0_->check_postcondition(
            //             base_object
            //             , old_object
            //             // , argument0, old_argument0, ...
            //             BOOST_PP_ENUM_TRAILING(
            //                     CONTRACT_arity,
            //         CONTRACT_now_and_old_argument, ~)
            //             // , result (if non-void)
            //             BOOST_PP_COMMA_IF(
            //                     CONTRACT_is_not_void)
            //             BOOST_PP_EXPR_IF(
            //                     CONTRACT_is_not_void,
            //                     result)
            //             );
            // } ...
            BOOST_PP_REPEAT(
                    CONTRACT_CONFIG_MAX_MULTIPLE_INHERITANCE,
                    CONTRACT_check_base_postcondition, ~)
#endif // is member

            // AND, this class postconditions.
            CONTRACT_AUX_DEBUGT(debug_type, dbg
                    << "Checking postconditions");
            (
#if CONTRACT_is_member
                    object->*
#endif // is member
                    POSTCONDITION_FUNCTION_
                    )(
#if CONTRACT_is_member
                    old_object
                    BOOST_PP_COMMA_IF(CONTRACT_arity)
#endif // is member
                    // argument0, old_argument0, ...
                    BOOST_PP_ENUM(CONTRACT_arity,
                            CONTRACT_now_and_old_argument, ~)
                    // , result (if not void)
#if CONTRACT_is_member || CONTRACT_arity
                    BOOST_PP_COMMA_IF(CONTRACT_is_not_void)
#endif // is member || arity != 0
                    BOOST_PP_EXPR_IF(CONTRACT_is_not_void,
                            result)
                    );
            
            aux::globally_checking_contract = false;
        } catch (...) {
            aux::globally_checking_contract = false;
            throw;
        }
    }
#endif // check postcondition

protected:
    // Redefined for constructor, destructor, etc.
    virtual from here() const {
#if CONTRACT_is_member
        return FROM_NONSTATIC_MEMBER_FUNCTION;
#else // is member
        return FROM_NONMEMBER_FUNCTION;
#endif // is member
    }

    // Virtual wrapper to call precondition so contructor can overide
    // it to drop object and static member, etc.
#if defined CONTRACT_CHECK_PRECONDITION && CONTRACT_is_member
    virtual void call_precondition(
            arg_class_ptr object
            // , arg_argument_type0 argument0, ...
            BOOST_PP_ENUM_TRAILING(CONTRACT_arity,
                    CONTRACT_arg_argument, ~)
            ) {
        (object->*PRECONDITION_FUNCTION_)(
                // argument0, ...
                BOOST_PP_ENUM(CONTRACT_arity,
                        CONTRACT_argument, ~)
                );
    }
#endif // check precondition && is member

    // Protected because accessed by derived constructor, etc (but
    // no virtual because cannot be overridden).
    inline ResultType exec(
#if CONTRACT_is_member
            maybecv_class_ptr object
#endif // is member
            BOOST_PP_COMMA_IF(BOOST_PP_AND(CONTRACT_arity,
                    CONTRACT_is_member))
            // argument_type0 argument0, ...
            BOOST_PP_ENUM(CONTRACT_arity,
                    CONTRACT_noncopyable_argument, ~)
#if CONTRACT_is_member
            , const bool& preinvariant_check
#endif // is member
            BOOST_PP_COMMA_IF(BOOST_PP_OR(CONTRACT_arity,
                    CONTRACT_is_member))
            const bool& precondition_check
#if CONTRACT_is_member
            , const bool& postinvariant_check
#endif // is member
            , const bool& postcondition_check
            ) {
        // This code should be optimized as much as possible to limit
        // contract calling and checking overhead.

        // Note on const-correctness: Arguments are const here
        // because they were passed using arg<>. Object instaed
        // is const only for const-members but object is always
        // used in const context but when body is called.

#if !defined CONTRACT_CHECK_CLASS_INVARIANT && \
    !defined CONTRACT_CHECK_PRECONDITION && \
    !defined CONTRACT_CHECK_POSTCONDITION
        // For optimization, just call body when contracts off.
        // If user contract programmed correctly, when contracts 
        // off this function will not even be called and the body
        // is called directly (but this functions handles the
        // contracts off case also to be more robust).
        CONTRACT_AUX_DEBUGT(debug_type, dbg
                << "Entering, executing body, and returning "
                << "because contracts turned off at "
                << "compile-time");
        return (
#if CONTRACT_is_member
                object->*
#endif // is member
                BODY_FUNCTION_
                )(
                // argument0, ...
                BOOST_PP_ENUM(CONTRACT_arity, CONTRACT_argument, ~)
                );
#else // check no contract

        // POLICY: Assertions disabled within assertions.
        if (aux::globally_checking_contract) {
            CONTRACT_AUX_DEBUGT(debug_type, dbg
                    << "Entering, executing body, and returning "
                    << "because assertions disabled within "
                    << "assertion checking");
            return (
#if CONTRACT_is_member
                    object->*
#endif // is member
                    BODY_FUNCTION_
                    )(
                    // argument0, ...
                    BOOST_PP_ENUM(CONTRACT_arity,
                            CONTRACT_argument, ~)
                    );
        }
        CONTRACT_AUX_DEBUGT(debug_type, dbg << "Entering");

#if CONTRACT_is_member
#if defined CONTRACT_CHECK_CLASS_INVARIANT
        bool invariant_disabled = true;
        if (preinvariant_check || postinvariant_check) {
            // POLICY: Invariant checking disabled in object
            // nested calls to avoid infinite recursion. In
            // nested calls, object state will be already
            // checking contracts.
            invariant_disabled = state::get_state_(
                    object).object_checking_contract_;
            if (invariant_disabled) {
                // Follwing code will not check dyn. invariant.
                CONTRACT_AUX_DEBUGT(debug_type, dbg
                        << "Dynamic invariant checking disabled in "
                        << "nested call");
            }
        }
#endif // check invariant
        state::get_state_(object).object_checking_contract_ = true;
#endif // is member

#if defined CONTRACT_CHECK_CLASS_INVARIANT
        // Only used when invariant checking turned on (so must wrap
        // declaration with #ifdef to avoid unsused variable error).
        bool calling_body = false;
#endif // check invariant
        try {

            // Invariants are checked *before* pre/post-
            // conditions so pre/post assertions can assume
            // invariants are true (e.g., if inv assert a
            // pointer is not NULL, pre/post can dereference it
            // safely). However, invariant checking might be
            // disabled in nested calls...
            
#if defined CONTRACT_CHECK_CLASS_INVARIANT
            try {
                check_invariant(
#if CONTRACT_is_member
                    object, !invariant_disabled && preinvariant_check
#endif // is member
                );
            } catch (...) { class_invariant_failed(here()); }
#endif // check invariant

#if defined CONTRACT_CHECK_PRECONDITION
            if (precondition_check) {
                try {
                    check_precondition(
#if CONTRACT_is_member
                            object
                            BOOST_PP_COMMA_IF(CONTRACT_arity)
#endif // is member
                            // argument0, ...
                            BOOST_PP_ENUM(CONTRACT_arity,
                                    CONTRACT_argument, ~)
                            );
                } catch (...) { precondition_failed(here()); }
            }
#endif // check precondition

#if defined CONTRACT_CHECK_POSTCONDITION
            // Ideally, the oldof variables should be declared
            // only if postcondition_check is true but then they
            // will be local to the if-statement code
            // complicating this code structure quite a bit. For
            // now, the only time postcondition_check is false is
            // for destructors which have no arguments and
            // non-copyable self so the oldof declarations do not
            // make any copy and this code does not negatively
            // affect performances even if postcondition_check is
            // false.
            // The oldof variables are declaraed only after
            // pre-invariant and preconditions checking so to
            // save their eventual copy operation in case of
            // precondition failure [Crowl2006].

            // Old variables (eventual copies).
#if CONTRACT_is_member
            copy<old_class_type> oldcopy_object(*object);
#endif // is member
            // copy<old_argument_type0> old_argument0(argument0);
            // ...
            BOOST_PP_REPEAT(CONTRACT_arity,
                    CONTRACT_copy_old_argument, ~)
#endif // check postcondition

            // For non-void functions, the following code will
            // copy result. This introduces overhead but it is
            // necessary even when post-invariants and
            // postconditions are not checked because
            // object_checking_contract_ must be updated to flase
            // *after* body execution.

            // Execute body.
            CONTRACT_AUX_DEBUGT(debug_type, dbg << "Executing body");
#if defined CONTRACT_CHECK_CLASS_INVARIANT
            calling_body = true;
#endif // check invariant
            // If void: (object->*BODY_FUNCTION_)(argument0, ...);
            // else:    ResultType result(
            //              (object->*body)(argument0, ...) );
            BOOST_PP_EXPR_IF(CONTRACT_is_not_void,
                    ResultType result)
                BOOST_PP_LPAREN_IF(CONTRACT_is_not_void)
                (
#if CONTRACT_is_member
                        object->*
#endif // is member
                        BODY_FUNCTION_
                        )(
                        // argument0, ...
                        BOOST_PP_ENUM(CONTRACT_arity,
                                CONTRACT_argument, ~)
                        )
                BOOST_PP_RPAREN_IF(CONTRACT_is_not_void)
            ;
#if defined CONTRACT_CHECK_CLASS_INVARIANT
            calling_body = false;
#endif // check invariant

#if defined CONTRACT_CHECK_CLASS_INVARIANT
            try {
                check_invariant(
#if CONTRACT_is_member
                    object, !invariant_disabled && postinvariant_check
#endif // is member
                );
            } catch (...) { class_invariant_failed(here()); }
#endif // check invariant

#if defined CONTRACT_CHECK_POSTCONDITION
            if (postcondition_check) {
                try {
                    check_postcondition(
#if CONTRACT_is_member
                            object
                            , &(oldcopy_object.value) // Pass pointer.
                            BOOST_PP_COMMA_IF(CONTRACT_arity)
#endif // is member
                            // argument0, , old_argument0, ...
                            BOOST_PP_ENUM(CONTRACT_arity,
                                CONTRACT_now_and_oldcopy_argument,
                                ~)
                            // , result (if non-void)
#if CONTRACT_is_member || CONTRACT_arity
                            BOOST_PP_COMMA_IF(
                                    CONTRACT_is_not_void)
#endif // is member || arity != 0
                            BOOST_PP_EXPR_IF(CONTRACT_is_not_void,
                                    result)
                            );
                } catch (...) { postcondition_failed(here()); }
            }
#endif // check postcondition

#if CONTRACT_is_member
            state::get_state_(
                    object).object_checking_contract_ = false;
#endif // is member
            
            CONTRACT_AUX_DEBUGT(debug_type, dbg
                    << "Returning normally");
            // If void 'return;', else 'return result;'.
            return BOOST_PP_EXPR_IF(CONTRACT_is_not_void, result);

        } catch (...) {
            CONTRACT_AUX_DEBUGT(debug_type, dbg
                    << "Returning because of an exception");
            
#if defined CONTRACT_CHECK_CLASS_INVARIANT
            // POLICY: Invariants (but not postconditions)
            // checked also when body exited abnormally for
            // exception safety guarantees [Crowl2006].
            
            if (calling_body) { // Exception thrown by body.
                calling_body = false;
                try {
#if defined CONTRACT_CHECK_CLASS_INVARIANT
                    try {
                        check_invariant(
#if CONTRACT_is_member
                            object, !invariant_disabled &&
                                    postinvariant_check
#endif // is member
                        );
                    } catch (...) { class_invariant_failed(here()); }
#endif // check invariant

                } catch (...) {
#if CONTRACT_is_member
                    // Make sure to clear contract state even if
                    // class_invariant_failed() throws.
                    state::get_state_(
                            object).object_checking_contract_ = false;
#endif // is member
                    throw; // Re-throw invariant exception.
                }
                
                // If invariant passed (no throw, no exit, etc).
                throw; // Re-throw body exception.
            }
#endif // check invariant
            
#if CONTRACT_is_member
            state::get_state_(
                    object).object_checking_contract_ = false;
#endif // is member
            throw;
        }
#endif // check contract
    }

private:
    // Pointers to body, pre, post, and bases (they could be 0).

    body_function_ptr const BODY_FUNCTION_;
#if defined CONTRACT_CHECK_PRECONDITION
    precondition_function_ptr const PRECONDITION_FUNCTION_;
#endif // check precondition
#if defined CONTRACT_CHECK_POSTCONDITION
    postcondition_function_ptr const POSTCONDITION_FUNCTION_;
#endif // check postcondition

#if CONTRACT_is_member
    // BaseContractClass0* base_contract_class0_; ...
    BOOST_PP_REPEAT(CONTRACT_CONFIG_MAX_MULTIPLE_INHERITANCE,
            CONTRACT_declare_base_contract, ~)
#endif // is_member

// End of class declaration here.

