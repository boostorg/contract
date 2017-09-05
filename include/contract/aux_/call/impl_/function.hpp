
// Copyright (C) 2008-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://sourceforge.net/projects/contractpp

#ifndef CONTRACT_AUX_CALL_ARITY
#   error "INTERNAL ERROR: must define CONTRACT_AUX_CALL_ARITY"
#endif
#ifndef CONTRACT_AUX_CALL_IS_MEMBER
#   error "INTERNAL ERROR: must define CONTRACT_AUX_CALL_IS_MEMBER"
#endif
#ifndef CONTRACT_AUX_CALL_IS_STATIC
#   error "INTERNAL ERROR: must define CONTRACT_AUX_CALL_IS_STATIC"
#endif
#ifndef CONTRACT_AUX_CALL_IS_DESTRUCTOR
#   error "INTERNAL ERROR: must define CONTRACT_AUX_CALL_IS_DESTRUCTOR"
#endif
#ifndef CONTRACT_AUX_CALL_IS_CONSTRUCTOR_ENTRY
#   error "INTERNAL ERROR: must define CONTRACT_AUX_CALL_IS_CONSTRUCTOR_ENTRY"
#endif
#ifndef CONTRACT_AUX_CALL_IS_CONSTRUCTOR_EXIT
#   error "INTERNAL ERROR: must define CONTRACT_AUX_CALL_IS_CONSTRUCTOR_EXIT"
#endif

// The following code is fairly complex and hard to read due to the amount of
// preprocessor metaprogramming that is used. This code was programmed this
// way so this one piece of code can generate *all* the call functions in order
// to *completely* avoid any code duplication in their implementations.
// Previous revisions or this code used to duplicate code among different call
// functions implementations but while these older revisions were more
// readable, they were very difficult to maintain because bug fixes and changes
// needed to be propagated among different part of the code. Therefore, all the
// call code was incorporated into this one metaprogram (and it should be kept
// this way).
//
// The following code in general follows the conventions that #if-directives
// are used to turn on/off contract code blocks (via CONFIG macros) while
// PP-macros are used to pp-metaprogram the function code (this distinction was
// found to make this code a bit more readable).
//
// See also: include_.hpp, define_.hpp, undef_.hpp

template< class SignTraits >
BOOST_PP_EXPR_IIF(BOOST_PP_COMPL(CONTRACT_AUX_CALL_IS_CONSTRUCTOR_ENTRY),
    // This generates a cons for constructor entry so no result allowed.
    typename SignTraits::result_type
)
CONTRACT_func
(
#if CONTRACT_AUX_CONFIG_DEBUG_01
    char const* file, unsigned long const& line, // Trailing comma `,`.
#endif
    BOOST_PP_IIF(CONTRACT_AUX_CALL_IS_CONSTRUCTOR_ENTRY,
        // NOTE: Need to deduce this param because ISO C++ does not allow to
        // specify tparams for const (because invoked without a name).
        SignTraits
    ,
        typename SignTraits::body_type const body
    )
    BOOST_PP_REPEAT(CONTRACT_AUX_CALL_ARITY, CONTRACT_comma_arg_param, ~)
    BOOST_PP_COMMA_IF(BOOST_PP_BITAND(CONTRACT_AUX_CALL_IS_MEMBER,
            BOOST_PP_BITAND(BOOST_PP_COMPL(CONTRACT_AUX_CALL_IS_STATIC),
                    BOOST_PP_COMPL(CONTRACT_AUX_CALL_IS_CONSTRUCTOR_ENTRY))))
    BOOST_PP_EXPR_IIF(BOOST_PP_BITAND(CONTRACT_AUX_CALL_IS_MEMBER,
            BOOST_PP_BITAND(BOOST_PP_COMPL(CONTRACT_AUX_CALL_IS_STATIC),
                    BOOST_PP_COMPL(CONTRACT_AUX_CALL_IS_CONSTRUCTOR_ENTRY))),
        typename SignTraits::cv_qualified_obj_type const obj
    )
#if CONTRACT_AUX_CONFIG_CLASS_INVARIANTS_01 && CONTRACT_AUX_CALL_IS_MEMBER
    BOOST_PP_COMMA_IF(BOOST_PP_BITOR(CONTRACT_AUX_CALL_IS_DESTRUCTOR,
            BOOST_PP_BITOR(CONTRACT_AUX_CALL_IS_CONSTRUCTOR_ENTRY,
                    CONTRACT_AUX_CALL_IS_CONSTRUCTOR_EXIT)))
    BOOST_PP_EXPR_IIF(BOOST_PP_BITOR(CONTRACT_AUX_CALL_IS_DESTRUCTOR,
            BOOST_PP_BITOR(CONTRACT_AUX_CALL_IS_CONSTRUCTOR_ENTRY,
                    CONTRACT_AUX_CALL_IS_CONSTRUCTOR_EXIT)),
        typename SignTraits::static_class_invariant_type const
                this_static_class_inv
    )
#   if !CONTRACT_AUX_CALL_IS_CONSTRUCTOR_ENTRY
    BOOST_PP_COMMA_IF(BOOST_PP_BITOR(CONTRACT_AUX_CALL_IS_DESTRUCTOR,
            CONTRACT_AUX_CALL_IS_CONSTRUCTOR_EXIT))
    BOOST_PP_EXPR_IIF(BOOST_PP_BITOR(CONTRACT_AUX_CALL_IS_DESTRUCTOR,
            CONTRACT_AUX_CALL_IS_CONSTRUCTOR_EXIT),
        typename SignTraits::class_invariant_type const this_class_inv
    )
#       if !CONTRACT_AUX_CALL_IS_CONSTRUCTOR_EXIT
    , typename SignTraits::
            BOOST_PP_IIF(CONTRACT_AUX_CALL_IS_STATIC,
                static_class_invariant_type const sub_static_class_inv
            ,
                class_invariant_type const sub_class_inv
            )
#       endif
#   endif
#endif
#if CONTRACT_AUX_CONFIG_PRECONDITIONS_01 && !CONTRACT_AUX_CALL_IS_DESTRUCTOR \
        && !CONTRACT_AUX_CALL_IS_CONSTRUCTOR_EXIT
    , typename SignTraits::
            BOOST_PP_IIF(CONTRACT_AUX_CALL_IS_CONSTRUCTOR_ENTRY,
                static_precondition_type
            ,
                precondition_type 
            )
            const
            BOOST_PP_IIF(BOOST_PP_BITAND(CONTRACT_AUX_CALL_IS_MEMBER,
                    BOOST_PP_BITAND(BOOST_PP_COMPL(
                            CONTRACT_AUX_CALL_IS_STATIC), BOOST_PP_COMPL(
                            CONTRACT_AUX_CALL_IS_CONSTRUCTOR_ENTRY))),
                sub_pre
            ,
                this_pre
            )
#endif
#if CONTRACT_AUX_CONFIG_POSTCONDITIONS_01 && !CONTRACT_AUX_CALL_IS_DESTRUCTOR \
        && !CONTRACT_AUX_CALL_IS_CONSTRUCTOR_ENTRY
    , typename SignTraits::
            BOOST_PP_IIF(CONTRACT_AUX_CALL_IS_CONSTRUCTOR_EXIT,
                constructor_oldof_type const this_cons_oldof
            , BOOST_PP_IIF(BOOST_PP_BITAND(CONTRACT_AUX_CALL_IS_MEMBER,
                    BOOST_PP_COMPL(CONTRACT_AUX_CALL_IS_STATIC)),
                subcontracted_oldof_type const sub_oldof
            ,
                oldof_type const this_oldof
            ))
#endif
) {
    if(call_globals<>::is_checking_contract) {
        CONTRACT_AUX_DEBUGN(file, line, CONTRACT_func, dbg <<
                "Entering, executing body, and exiting function contract " <<
                "without checking contracts because assertions disabled " <<
                "within assertions " << BOOST_PP_STRINGIZE(CONTRACT_body_func))
        return
#if !CONTRACT_AUX_CALL_IS_CONSTRUCTOR_ENTRY
        CONTRACT_body_func(
            BOOST_PP_ENUM(CONTRACT_AUX_CALL_ARITY, CONTRACT_arg, ~)
        )
#endif
        ;
    }
    CONTRACT_AUX_DEBUGN(file, line, CONTRACT_func, dbg <<
            "Entering function contract")

    // POLICY: For constructors and destructors, subcontracting is realized by
    // the automatic invocation of all base constructor and destructor
    // contracts via C++ object creation and disposal mechanism so here we
    // just check this class constructor and destructor contract (not bases').

#if CONTRACT_AUX_CONFIG_CLASS_INVARIANTS_01 && CONTRACT_AUX_CALL_IS_MEMBER && \
        !CONTRACT_AUX_CALL_IS_CONSTRUCTOR_ENTRY
    bool calling_body = false; // Used only for class inv.
    try {
#endif

    // Check class invariants on entry.
#if CONTRACT_AUX_CONFIG_CLASS_INVARIANTS_01 && CONTRACT_AUX_CALL_IS_MEMBER && \
        !CONTRACT_AUX_CALL_IS_CONSTRUCTOR_EXIT
        // POLICY: Class inv are checked on entry/exit before pre/post so
        // pre/post assertions can be simplified assuming inv are true (e.g.,
        // don't check a ptr for nullity because inv already checked).
        // POLICY: Class inv are not checked if class inv func ptr is null so
        // caller can disable class inv checking for non public members.
        // POLICY: Destructor check this class inv (and not subcontracted ones)
        // because base class inv will be automatically invoked by C++ when
        // calling base destructors.
        if(
            BOOST_PP_IIF(CONTRACT_AUX_CALL_IS_STATIC,
                sub_static_class_inv
            , BOOST_PP_IIF(CONTRACT_AUX_CALL_IS_DESTRUCTOR,
                this_class_inv
            , BOOST_PP_IIF(CONTRACT_AUX_CALL_IS_CONSTRUCTOR_ENTRY,
                this_static_class_inv
            ,
                sub_class_inv
            )))
        ) {
            try {
                CONTRACT_AUX_DEBUGN(file, line, CONTRACT_func, dbg <<
                        "Checking class invariants on entry " <<
                        BOOST_PP_STRINGIZE(CONTRACT_entry_class_inv_func))
                call_globals<>::is_checking_contract = true;
                CONTRACT_entry_class_inv_func();
                call_globals<>::is_checking_contract = false;
            } catch(...) { 
                CONTRACT_AUX_DEBUGN(file, line, CONTRACT_from, dbg <<
                        "Calling class invariant broken handler on entry")
                call_globals<>::is_checking_contract = false;
                class_invariant_broken_on_entry(CONTRACT_from);
            }
        }
#   if CONTRACT_AUX_CONFIG_DEBUG_01
        else {
            CONTRACT_AUX_DEBUGN(file, line, CONTRACT_func, dbg <<
                    "Class invariant checking disabled on entry for " <<
                    "non-public member")
        }
#   endif
#endif

    // Check preconditions.
#if CONTRACT_AUX_CONFIG_PRECONDITIONS_01 && !CONTRACT_AUX_CALL_IS_DESTRUCTOR \
        && !CONTRACT_AUX_CALL_IS_CONSTRUCTOR_EXIT
        try {
            // POLICY: By default, pre disable assertion checking globally like
            // any other contract checking func to avoid infinite recursion but
            // this can be changed for pre to comply with N1962.
#   if !CONTRACT_AUX_CONFIG_PRECONDITIONS_DISABLE_NO_ASSERTION_01
            CONTRACT_AUX_DEBUGN(file, line, CONTRACT_func, dbg <<
                    "Checking preconditions " <<
                    BOOST_PP_STRINGIZE(CONTRACT_pre_func))
            call_globals<>::is_checking_contract = true;
#   else
            CONTRACT_AUX_DEBUGN(file, line, CONTRACT_func, dbg <<
                    "Checking preconditions configured to not disable " <<
                    "other assertions " <<
                    BOOST_PP_STRINGIZE(CONTRACT_pre_func))
#   endif
            CONTRACT_pre_func(
                // NOTE: Body func ptr is also passed to the contract checking
                // functions (pre, old-of, and post) to handle overloading.
                typename SignTraits::body_type()
                BOOST_PP_REPEAT(CONTRACT_AUX_CALL_ARITY, CONTRACT_comma_arg, ~)
            );
#   if !CONTRACT_AUX_CONFIG_PRECONDITIONS_DISABLE_NO_ASSERTION_01
            call_globals<>::is_checking_contract = false;
#   endif
        } catch(...) {
            CONTRACT_AUX_DEBUGN(file, line, CONTRACT_func, dbg <<
                    "Calling precondition broken handler")
#   if !CONTRACT_AUX_CONFIG_PRECONDITIONS_DISABLE_NO_ASSERTION_01
            call_globals<>::is_checking_contract = false;
#   endif
            precondition_broken(CONTRACT_from);
        }
#endif

    // Copy old-ofs.
#if CONTRACT_AUX_CONFIG_POSTCONDITIONS_01 && !CONTRACT_AUX_CALL_IS_DESTRUCTOR \
        && !CONTRACT_AUX_CALL_IS_CONSTRUCTOR_ENTRY
        // POLICY: An exception thrown while evaluating and copying old-ofs
        // is threated as a post failure (while keeping the same active
        // exception that failed the old-of) because (1) class inv at entry and
        // pre passed so body can/should be executed but (2) old-ofs were not
        // copied so post cannot be checked.
        BOOST_PP_IIF(BOOST_PP_BITAND(CONTRACT_AUX_CALL_IS_MEMBER,
                BOOST_PP_BITAND(BOOST_PP_COMPL(CONTRACT_AUX_CALL_IS_STATIC),
                        BOOST_PP_COMPL(CONTRACT_AUX_CALL_IS_CONSTRUCTOR_EXIT))),
            std::list< typename SignTraits::bound_postcondition_type > sub_post;
        ,
            typename SignTraits::bound_postcondition_type this_post;
        )
        bool oldof_failed = true;
        try {
            CONTRACT_AUX_DEBUGN(file, line, CONTRACT_func, dbg <<
                    "Evaluating and coping postcondition old-ofs (" <<
                    BOOST_PP_STRINGIZE(CONTRACT_oldof_assignment_func) << ")")
            // POLICY: Disable all assertions also during old-of evaluation and
            // copy to prevent infinite recursion.
            call_globals<>::is_checking_contract = true;
            CONTRACT_oldof_assignment_func(
                typename SignTraits::body_type()
                BOOST_PP_COMMA_IF(CONTRACT_AUX_CALL_IS_CONSTRUCTOR_EXIT)
                BOOST_PP_EXPR_IIF(CONTRACT_AUX_CALL_IS_CONSTRUCTOR_EXIT,
                    obj
                )
                BOOST_PP_REPEAT(CONTRACT_AUX_CALL_ARITY, CONTRACT_comma_arg, ~)
            );
            call_globals<>::is_checking_contract = false;
            // NOTE: Following throw is used to jump to catch below (this trick
            // is necessary to keep eventual old-of error in active exception
            // to re-throw it later.
            throw oldof_failed = false;
        } catch(...) {
            // NOTE: Got here with oldof_failed == false iff no old-of error,
            // or with oldof_failed == true iff old-of error (in which case the
            // error is in the active exception).
            call_globals<>::is_checking_contract = false;
#endif

    // Call body (and copy result).
#if CONTRACT_AUX_CONFIG_CLASS_INVARIANTS_01 && CONTRACT_AUX_CALL_IS_MEMBER && \
        !CONTRACT_AUX_CALL_IS_CONSTRUCTOR_ENTRY
            calling_body = true;
#endif
#   if CONTRACT_AUX_IS_CONSTRUCTOR_EXIT
            // POLICY: Only exceptions thrown by the body are handled by the
            // function (and constructor) try-block. In particular, contract
            // assertions and this library implementation code is executed
            // outside the function (and constructor) try-block (see N1962).
            // Function-try-blocks for functions other than constructors are
            // programmed outside the macros and just around the body
            // (constructors need special care because their member
            // initializers are programmed within the macros and constructor
            // try-blocks need to handle exceptions thrown by initializers).
            // NOTE: This enables constructor try-blocks also during
            // copy_result so eventual copy_result constructor exceptions
            // will also be handled by the try-block while ideally the
            // try-block will only handle body exceptions. However, copy_result
            // constructor simply calls the body and copies the result so no
            // exception but the one thrown by the body should be thrown.
            dynamic_cast< constructor_try_block_guard< typename
                    SignTraits::class_type > >(obj)->
                    CONTRACT_AUX_SYMBOL((enable))();
#   endif
#if !CONTRACT_AUX_CONFIG_POSTCONDITIONS_01 && \
        !CONTRACT_AUX_CONFIG_CLASS_INVARIANTS_01 && \
        !CONTRACT_AUX_CALL_IS_CONSTRUCTOR_ENTRY
            CONTRACT_AUX_DEBUGN(file, line, CONTRACT_func, dbg <<
                    "Executing body and returning without copying result " <<
                    BOOST_PP_STRINGIZE(CONTRACT_body_func))
            // Optimization if no post (don't copy result).
            return CONTRACT_body_func(
                BOOST_PP_ENUM(CONTRACT_AUX_CALL_ARITY, CONTRACT_arg, ~)
            );
#elif !CONTRACT_AUX_CALL_IS_CONSTRUCTOR_ENTRY
            CONTRACT_AUX_DEBUGN(file, line, CONTRACT_func, dbg <<
                    "Executing body and copying eventual result " <<
                    BOOST_PP_STRINGIZE(CONTRACT_body_func))
            copy_result<
                typename SignTraits::result_type
                BOOST_PP_COMMA_IF(BOOST_PP_BITAND(CONTRACT_AUX_CALL_IS_MEMBER,
                        BOOST_PP_COMPL(CONTRACT_AUX_CALL_IS_STATIC)))
                BOOST_PP_EXPR_IIF(BOOST_PP_BITAND(CONTRACT_AUX_CALL_IS_MEMBER,
                        BOOST_PP_COMPL(CONTRACT_AUX_CALL_IS_STATIC)),
                    typename SignTraits::cv_qualified_obj_type
                )
            > result(
                  body // Result copy will call actual body.
                BOOST_PP_COMMA_IF(BOOST_PP_BITAND(CONTRACT_AUX_CALL_IS_MEMBER,
                        BOOST_PP_COMPL(CONTRACT_AUX_CALL_IS_STATIC)))
                BOOST_PP_EXPR_IIF(BOOST_PP_BITAND(CONTRACT_AUX_CALL_IS_MEMBER,
                        BOOST_PP_COMPL(CONTRACT_AUX_CALL_IS_STATIC)),
                    obj
                )
                BOOST_PP_REPEAT(CONTRACT_AUX_CALL_ARITY, CONTRACT_comma_arg, ~)
            );
#   if CONTRACT_AUX_IS_CONSTRUCTOR_EXIT
            dynamic_cast< constructor_try_block_guard< typename
                    SignTraits::class_type > >(obj)->
                    CONTRACT_AUX_SYMBOL((disable))();
#   endif

    // Check class invariants on exit.
#   if CONTRACT_AUX_CONFIG_CLASS_INVARIANTS_01 && CONTRACT_AUX_CALL_IS_MEMBER
            calling_body = false;

            // POLICY: For destructors, cannot check dynamic class inv because
            // there is no longer an object here after destructor body
            // execution but we can still check this static class inv (again,
            // do not check subcontracted static class inv because base static
            // class inv will be automatically invoked by C++ when calling base
            // destructors).
            if(
                BOOST_PP_IIF(CONTRACT_AUX_CALL_IS_STATIC,
                    sub_static_class_inv
                , BOOST_PP_IIF(CONTRACT_AUX_CALL_IS_DESTRUCTOR,
                    this_static_class_inv
                , BOOST_PP_IIF(CONTRACT_AUX_CALL_IS_CONSTRUCTOR_EXIT,
                    this_class_inv
                ,
                    sub_class_inv
                )))
            ) {
                CONTRACT_AUX_DEBUGN(file, line, CONTRACT_func, dbg <<
                        "Checking class invariants on exit " <<
                        BOOST_PP_STRINGIZE(CONTRACT_exit_class_inv_func))
                try {
                    call_globals<>::is_checking_contract = true;
                    CONTRACT_exit_class_inv_func();
                    call_globals<>::is_checking_contract = false;
                } catch(...) {
                    CONTRACT_AUX_DEBUGN(file, line, CONTRACT_func, dbg <<
                            "Calling class invariant on exit broken handler")
                    call_globals<>::is_checking_contract = false;
                    class_invariant_broken_on_exit(CONTRACT_from);
                }
            }
#       if CONTRACT_AUX_CONFIG_DEBUG_01
        else {
            CONTRACT_AUX_DEBUGN(file, line, CONTRACT_func, dbg <<
                    "Class invariant checking on exit disabled for " <<
                    "non-public member")
        }
#       endif
#   endif

    // Check postconditions.
#   if CONTRACT_AUX_CONFIG_POSTCONDITIONS_01 && !CONTRACT_AUX_CALL_IS_DESTRUCTOR
            try {
                if(oldof_failed) { 
                    CONTRACT_AUX_DEBUGN(file, line, CONTRACT_func, dbg <<
                            "Unable to evaluate or copy old-of expressions (" <<
                            BOOST_PP_STRINGIZE(CONTRACT_oldof_assignment_func)
                            << ")")
                    throw; // Re-throw old-of error (from active exception).
                }
                CONTRACT_AUX_DEBUGN(file, line, CONTRACT_func, dbg <<
                        "Checking postconditions (" <<
                        BOOST_PP_STRINGIZE(CONTRACT_post_func) << ")")
                call_globals<>::is_checking_contract = true;
                CONTRACT_post_func(
                    BOOST_PP_EXPR_IIF(BOOST_PP_BITAND(
                                    CONTRACT_AUX_CALL_IS_MEMBER,
                            BOOST_PP_BITAND(BOOST_PP_COMPL(
                                    CONTRACT_AUX_CALL_IS_STATIC),
                            BOOST_PP_COMPL(
                                    CONTRACT_AUX_CALL_IS_CONSTRUCTOR_EXIT))),
                        sub_post
                    )
                    BOOST_PP_COMMA_IF(BOOST_PP_AND(CONTRACT_AUX_CALL_ARITY,
                            BOOST_PP_BITAND(CONTRACT_AUX_CALL_IS_MEMBER,
                            BOOST_PP_BITAND(BOOST_PP_COMPL(
                                    CONTRACT_AUX_CALL_IS_STATIC),
                            BOOST_PP_COMPL(
                                    CONTRACT_AUX_CALL_IS_CONSTRUCTOR_EXIT)))))
                    BOOST_PP_ENUM(CONTRACT_AUX_CALL_ARITY, CONTRACT_arg, ~)
                    BOOST_PP_COMMA_IF(BOOST_PP_OR(CONTRACT_AUX_CALL_ARITY,
                            BOOST_PP_BITAND(CONTRACT_AUX_CALL_IS_MEMBER,
                            BOOST_PP_BITAND(BOOST_PP_COMPL(
                                    CONTRACT_AUX_CALL_IS_STATIC),
                            BOOST_PP_COMPL(
                                    CONTRACT_AUX_CALL_IS_CONSTRUCTOR_EXIT)))))
                    result.param()
                );
                call_globals<>::is_checking_contract = false;
            } catch(...) {
                CONTRACT_AUX_DEBUGN(file, line, CONTRACT_func, dbg <<
                        "Calling postcondition broken handler")
                call_globals<>::is_checking_contract = false;
                postcondition_broken(CONTRACT_from);
            }
#   endif

            CONTRACT_AUX_DEBUGN(file, line, CONTRACT_func, dbg <<
                    "Exiting function contract normally")
            return result.value();

#   if CONTRACT_AUX_CONFIG_POSTCONDITIONS_01 && !CONTRACT_AUX_CALL_IS_DESTRUCTOR
        } // old-of catch
#   endif

#endif // !post01 && !inv && !cons_entry

    // Check class invariants on throw.
#if CONTRACT_AUX_CONFIG_CLASS_INVARIANTS_01 && CONTRACT_AUX_CALL_IS_MEMBER && \
        !CONTRACT_AUX_CALL_IS_CONSTRUCTOR_ENTRY
    } catch(...) {
#   if CONTRACT_AUX_IS_CONSTRUCTOR_EXIT
        // Make sure to disable try-block before checking invariants on exit.
        dynamic_cast< constructor_try_block_guard< typename
                SignTraits::class_type > >(obj)->
                CONTRACT_AUX_SYMBOL((disable))();
#   endif
        // POLICY: Following exception safety guarantees, class inv (but not
        // post) are checked also when body throws.
        // If constructor body throws, only static class invariants can be
        // checked here (because constructor body was not able to create the
        // object).
        // If a destructor body throws (but note that following C++ STL
        // exception safety guarantees, destructors should be programmed to
        // never throw), subcontracted (to check that also base objects are in a
        // consistent state) class dynamic (because the destructor body failed
        // so the object was not destructed and it still exists) inv are
        // checked. However, if a destructor of one of the base classes throw
        // there is no way to go back and check the class invariants of the
        // derived classes (plus the derived constructor did not throw so the
        // derived part of the object is actually destructed) and in this case
        // the overall object is left only partially destructed and in an
        // undefined state (again, following exception safety rule destructors
        // should never throw so this should never happen).
        if(
            BOOST_PP_IIF(CONTRACT_AUX_CALL_IS_STATIC,
                sub_static_class_inv
            , BOOST_PP_IIF(CONTRACT_AUX_CALL_IS_CONSTRUCTOR_EXIT,
                this_static_class_inv
            ,
                sub_class_inv
            ))
            && calling_body
        ) {
            try {
                try {
                    CONTRACT_AUX_DEBUGN(file, line, CONTRACT_func, dbg <<
                            "Checking class invariants on throw " <<
                            BOOST_PP_STRINGIZE(CONTRACT_throw_class_inv_func))
                    call_globals<>::is_checking_contract = true;
                    CONTRACT_throw_class_inv_func();
                    call_globals<>::is_checking_contract = false;
                } catch(...) {
                    CONTRACT_AUX_DEBUGN(file, line, CONTRACT_func, dbg <<
                            "Calling class invariant on throw broken handler")
                    call_globals<>::is_checking_contract = false;
                    class_invariant_broken_on_throw(CONTRACT_from);
                }
            } catch(...) {
                // NOTE: Re-throw eventual inv broken exception (this is needed
                // to allow the user to reprogram the contract handlers to
                // throw and exception instead of terminating).
                throw;
            }

            CONTRACT_AUX_DEBUGN(file, line, CONTRACT_func, dbg <<
                    "Exiting function contract on throw")
            throw; // If invariant passed, re-throw body exception.
        }
#   if CONTRACT_AUX_CONFIG_DEBUG_01
        else if(calling_body) {
            CONTRACT_AUX_DEBUGN(file, line, CONTRACT_func, dbg <<
                    "Class invariant checking on throw disabled for " <<
                    "non-public member")
        }
#   endif
        CONTRACT_AUX_DEBUGN(file, line, CONTRACT_func, dbg <<
                "Exiting function contract on throw")
#   if CONTRACT_AUX_IS_CONSTRUCTOR_EXIT
        if(calling_body) {
            // Enable constructor-try-block before re-throwing body exception.
            dynamic_cast< constructor_try_block_guard< typename
                    SignTraits::class_type > >(obj)->
                    CONTRACT_AUX_SYMBOL((enable))();
        }
#   endif
        throw; // Re-throw (if no body call or no invariant checking).
    }
#endif
    CONTRACT_AUX_DEBUGN(file, line, CONTRACT_func, dbg <<
            "Exiting function contract normally")
}

// Undefine named external arg macros (similar to BOOST_PP_ITERATION_PARAMS).
#undef CONTRACT_AUX_CALL_ARITY
#undef CONTRACT_AUX_CALL_IS_MEMBER
#undef CONTRACT_AUX_CALL_IS_STATIC
#undef CONTRACT_AUX_CALL_IS_DESTRUCTOR
#undef CONTRACT_AUX_CALL_IS_CONSTRUCTOR_ENTRY
#undef CONTRACT_AUX_CALL_IS_CONSTRUCTOR_EXIT

