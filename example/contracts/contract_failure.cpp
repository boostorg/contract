
// Copyright (C) 2008-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://sourceforge.net/projects/contractpp

#include <contract.hpp>
#include <boost/detail/lightweight_test.hpp>
#include <string>
#include <iostream>

bool // Fail the asserted conditions.
      class_inv = true
    , static_class_inv = true
    , volatile_class_inv = true
    , pre = true
    , post = true
;

struct check_pre // Check pre asserted before member initializers.
{
    check_pre ( void ) { BOOST_TEST(pre); }
};

struct forced_exception {};

CONTRACT_CLASS(
    struct (failer) extends( check_pre )
) {
    CONTRACT_CLASS_INVARIANT(
        class_inv,
        static class( static_class_inv ),
        volatile class( volatile_class_inv )
    )

    CONTRACT_CONSTRUCTOR(
        public (failer) (
                (bool*) inv, default 0,
                bool const throwing, default false
            )
            precondition( pre )
            postcondition( post )
            initialize(
                check_pre(),
                destructor_inv(0),
                destructor_throwing(false)
            )
    ) {
        if(inv) *inv = false;
        if(throwing) throw forced_exception();
    }

    bool* destructor_inv;       // Destructor has not parameter,
    bool destructor_throwing;   // use data members instead.

    CONTRACT_DESTRUCTOR(
        public virtual (~failer) ( void )
    ) {
        if(destructor_inv) *destructor_inv = false;
        // STL says destrcutors shall not throw, throwing here just for testing.
        if(destructor_throwing) throw forced_exception();
    }

    CONTRACT_FUNCTION(
        public void (fail) (
                (bool*) inv, default 0,
                bool const throwing, default false
            )
            precondition( pre )
            postcondition( post )
    ) {
        if(inv) *inv = false;
        if(throwing) throw forced_exception();
    }
    
    CONTRACT_FUNCTION(
        public void (fail) (
                (bool*) inv, default 0,
                bool const throwing, default false
            ) volatile
            precondition( pre )
            postcondition( post )
    ) {
        if(inv) *inv = false;
        if(throwing) throw forced_exception();
    }
    
    CONTRACT_FUNCTION(
        public static void (static_failure) (
                (bool*) inv, default 0,
                bool const throwing, default false
            )
            precondition( pre )
            postcondition( post )
    ) {
        if(inv) *inv = false;
        if(throwing) throw forced_exception();
    }
};

CONTRACT_FUNCTION(
    void (free_failure) ( bool const throwing, default false )
        precondition( pre )
        postcondition( post )
) {
    if(throwing) throw forced_exception();
}

std::string str ( contract::from const& context )
{
    switch(context) {
    case contract::FROM_CONSTRUCTOR: return "constructor";
    case contract::FROM_DESTRUCTOR: return "destructor";
    case contract::FROM_NONSTATIC_MEMBER_FUNCTION:
        return "non-static member function";
    case contract::FROM_STATIC_MEMBER_FUNCTION: return "static member function";
    case contract::FROM_FREE_FUNCTION: return "free function";
    case contract::FROM_BODY: return "body";
    }
    return "<unknown>";
}

#define THROWING_HANDLER(name) \
    struct name \
    { \
        contract::from context; \
        contract::broken error; \
        name ( contract::from const& a_context, \
                contract::broken const& an_error ) \
            : context(a_context), error(an_error) {} \
    }; \
    void BOOST_PP_CAT(name, _handler) ( contract::from const& context ) \
    { \
        try { \
            throw; \
        } catch(contract::broken& error) { \
            std::cerr << "checking " << BOOST_PP_STRINGIZE(name) << \
                    " from " << str(context) << ":" << std::endl; \
            std::cerr << "    " << error.what() << std::endl; \
            throw name(context, error); \
        } \
    }
    
#define CHECK(assertion, exception, from_context, body) \
    pass = false; \
    try { \
        body \
    } catch(exception& ex) { \
        assertion = true; \
        BOOST_TEST(ex.context == from_context); \
        BOOST_TEST(std::string(ex.error.assertion_code()) == \
                BOOST_PP_STRINGIZE(assertion)); \
        BOOST_TEST(ex.error.assertion_number() == 1); \
        pass = true; \
    } \
    assertion = true; \
    BOOST_TEST(pass); \
    
#define CHECK_THROW(body) \
    pass = false; \
    try { \
        body \
    } catch(forced_exception) { \
        std::cerr << "checking throw with no contract failure:" << std::endl; \
        std::cerr << "    no broken contract: file \"" << __FILE__ << \
                "\", line " << __LINE__ << std::endl; \
        pass = true; \
    } \
    BOOST_TEST(pass);

THROWING_HANDLER(class_inv_broken_on_entry)
THROWING_HANDLER(class_inv_broken_on_exit)
THROWING_HANDLER(class_inv_broken_on_throw)
THROWING_HANDLER(pre_broken)
THROWING_HANDLER(post_broken)
THROWING_HANDLER(block_inv_broken)
THROWING_HANDLER(loop_var_broken)

int main ( void )
{
    contract::set_class_invariant_broken_on_entry(
            &class_inv_broken_on_entry_handler);
    contract::set_class_invariant_broken_on_exit(
            &class_inv_broken_on_exit_handler);
    contract::set_class_invariant_broken_on_throw(
            &class_inv_broken_on_throw_handler);
    contract::set_precondition_broken(&pre_broken_handler);
    contract::set_postcondition_broken(&post_broken_handler);
    contract::set_block_invariant_broken(&block_inv_broken_handler);
    contract::set_loop_variant_broken(&loop_var_broken_handler);

    bool const throwing = true;
    bool* const no_broken_inv = 0;
    contract::from context;
    bool pass = false;

    // Check constructor contract failures.
    context = contract::FROM_CONSTRUCTOR;
#ifndef CONTRACT_CONFIG_NO_CLASS_INVARIANTS
    // Fail static class invariants on entry.
    CHECK(static_class_inv, class_inv_broken_on_entry, context,
        static_class_inv = false;
        failer failure;
    )
    // Fail static class invariants on exit.
    CHECK(static_class_inv, class_inv_broken_on_exit, context,
        failer failure(&static_class_inv);
    )
    // Fail static class invariants on throw.
    CHECK(static_class_inv, class_inv_broken_on_throw, context,
        failer failure(&static_class_inv, throwing);
    )
    // Class invariants on entry do not apply.
    // Fail class invariants on exit.
    CHECK(class_inv, class_inv_broken_on_exit, context,
        failer failure(&class_inv);
    )
    // Class invariants on throw do not apply.
    // Volatile class invariants on entry do not apply.
    // Volatile class invariants on exit do not apply.
    // Volatile class invariants on throw do not apply.
#endif
#ifndef CONTRACT_CONFIG_NO_PRECONDITIONS
    // Fail preconditions on entry (before member initializers).
    CHECK(pre, pre_broken, context,
        pre = false;
        failer failure;
    )
#endif
#ifndef CONTRACT_CONFIG_NO_POSTCONDITIONS
    // Fail postconditions on exit (when no throw).
    CHECK(post, post_broken, context,
        post = false;
        failer failure;
    )
#endif
    // Throw with no contract failure.
    CHECK_THROW(
        failer failure(no_broken_inv, throwing);
    )
    std::cerr << std::endl;

    // Check destructor contract failures.
    context = contract::FROM_DESTRUCTOR;
#ifndef CONTRACT_CONFIG_NO_CLASS_INVARIANTS
    // Fail static class invariants on entry.
    CHECK(static_class_inv, class_inv_broken_on_entry, context,
        failer failure;
        static_class_inv = false;
    )
    // Fail static class invariants on exit.
    CHECK(static_class_inv, class_inv_broken_on_exit, context,
        failer failure;
        failure.destructor_inv = &static_class_inv;
    )
    // Fail static class invariants on throw.
    CHECK(static_class_inv, class_inv_broken_on_throw, context,
        failer failure;
        failure.destructor_inv = &static_class_inv;
        failure.destructor_throwing = true;
    )
    // Fail class invariants on entry.
    CHECK(class_inv, class_inv_broken_on_entry, context,
        failer failure;
        class_inv = false;
    )
    // Class invariants on exit do not apply.
    // Fail class invariants on throw.
    CHECK(class_inv, class_inv_broken_on_throw, context,
        failer failure;
        failure.destructor_inv = &class_inv;
        failure.destructor_throwing = true;
    )
    // Volatile class invariants on entry do not apply.
    // Volatile class invariants on exit do not apply.
    // Volatile class invariants on throw do not apply.
#endif
    // Preconditions on entry do not apply.
    // Postconditions on exit (when no throw) do not apply.
    // Throw with no contract failure.
    CHECK_THROW(
        failer failure;
        failure.destructor_throwing = true;
    )
    std::cerr << std::endl;

    // Failure objects declared here to they are not destructed within the
    // code checking member function contracts (otherwise, that code would also
    // re-check constructor and destructor contracts all the times).
    failer failure;
    failer volatile volatile_failure;
    
    // Check non-static member function contract failures.
    context = contract::FROM_NONSTATIC_MEMBER_FUNCTION;
#ifndef CONTRACT_CONFIG_NO_CLASS_INVARIANTS
    // Fail static class invariants on entry.
    CHECK(static_class_inv, class_inv_broken_on_entry, context,
        static_class_inv = false;
        failure.fail();
    )
    // Fail static class invariants on exit.
    CHECK(static_class_inv, class_inv_broken_on_exit, context,
        failure.fail(&static_class_inv);
    )
    // Fail static class invariants on throw.
    CHECK(static_class_inv, class_inv_broken_on_throw, context,
        failure.fail(&static_class_inv, throwing);
    )
    // Fail class invariants on entry.
    CHECK(class_inv, class_inv_broken_on_entry, context,
        class_inv = false;
        failure.fail();
    )
    // Fail class invariants on exit.
    CHECK(class_inv, class_inv_broken_on_exit, context,
        failure.fail(&class_inv);
    )
    // Fail class invariants on throw.
    CHECK(class_inv, class_inv_broken_on_throw, context,
        failure.fail(&class_inv, throwing);
    )
    // Fail volatile class invariants on entry.
    CHECK(volatile_class_inv, class_inv_broken_on_entry, context,
        volatile_class_inv = false;
        volatile_failure.fail();
    )
    // Fail volatile class invariants on exit.
    CHECK(volatile_class_inv, class_inv_broken_on_exit, context,
        volatile_failure.fail(&volatile_class_inv);
    )
    // Fail volatile class invariants on throw.
    CHECK(volatile_class_inv, class_inv_broken_on_throw, context,
        volatile_failure.fail(&volatile_class_inv, throwing);
    )
#endif
#ifndef CONTRACT_CONFIG_NO_PRECONDITIONS
    // Fail preconditions on entry.
    CHECK(pre, pre_broken, context,
        pre = false;
        failure.fail();
    )
#endif
#ifndef CONTRACT_CONFIG_NO_POSTCONDITIONS
    // Fail postconditions on exit (when no throw).
    CHECK(post, post_broken, context,
        post = false;
        failure.fail();
    )
#endif
    // Throw with no contract failure.
    CHECK_THROW(
        failure.fail(no_broken_inv, throwing);
    )
    std::cerr << std::endl;
    
    // Check static member function contract failures.
    context = contract::FROM_STATIC_MEMBER_FUNCTION;
#ifndef CONTRACT_CONFIG_NO_CLASS_INVARIANTS
    // Fail static class invariants on entry.
    CHECK(static_class_inv, class_inv_broken_on_entry, context,
        static_class_inv = false;
        failer::static_failure();
    )
    // Fail static class invariants on exit.
    CHECK(static_class_inv, class_inv_broken_on_exit, context,
        failer::static_failure(&static_class_inv);
    )
    // Fail static class invariants on throw.
    CHECK(static_class_inv, class_inv_broken_on_throw, context,
        failer::static_failure(&static_class_inv, throwing);
    )
    // Class invariants on entry do not apply.
    // Class invariants on exit do not apply.
    // Class invariants on throw do not apply.
    // Volatile class invariants on entry do not apply.
    // Volatile class invariants on exit do not apply.
    // Volatile class invariants on throw do not apply.
#endif
#ifndef CONTRACT_CONFIG_NO_PRECONDITIONS
    // Fail preconditions on entry.
    CHECK(pre, pre_broken, context,
        pre = false;
        failer::static_failure();
    )
#endif
#ifndef CONTRACT_CONFIG_NO_POSTCONDITIONS
    // Fail postconditions on exit (when no throw).
    CHECK(post, post_broken, context,
        post = false;
        failer::static_failure();
    )
#endif
    // Throw with no contract failure.
    CHECK_THROW(
        failer::static_failure(no_broken_inv, throwing);
    )
    std::cerr << std::endl;
    
    // Check free function contract failures.
    context = contract::FROM_FREE_FUNCTION;
    // Static class invariants on entry do not apply.
    // Static class invariants on exit do not apply.
    // Static class invariants on throw do not apply.
    // Class invariants on entry do not apply.
    // Class invariants on exit do not apply.
    // Class invariants on throw do not apply.
    // Volatile class invariants on entry do not apply.
    // Volatile class invariants on exit do not apply.
    // Volatile class invariants on throw do not apply.
#ifndef CONTRACT_CONFIG_NO_PRECONDITIONS
    // Fail preconditions on entry.
    CHECK(pre, pre_broken, context,
        pre = false;
        free_failure();
    )
#endif
#ifndef CONTRACT_CONFIG_NO_POSTCONDITIONS
    // Fail postconditions on exit (when no throw).
    CHECK(post, post_broken, context,
        post = false;
        free_failure();
    )
#endif
    // Throw with no contract failure.
    CHECK_THROW(
        free_failure(throwing);
    )
    std::cerr << std::endl;

    // Check block invariant contract failure.
#ifndef CONTRACT_CONFIG_NO_BLOCK_INVARIANTS
    pass = false;
    try {
        CONTRACT_BLOCK_INVARIANT(false)
    } catch(block_inv_broken) {
        pass = true;
    }
    BOOST_TEST(pass);
    std::cerr << std::endl;
#endif
    
    // Check loop variant contract failures.
#ifndef CONTRACT_CONFIG_NO_LOOP_VARIANTS
    // OK, decreasing to 0.
    CONTRACT_LOOP( for(int i = 0; i < 10; ++i) ) {
        CONTRACT_LOOP_VARIANT( 9 - i )
    }
    // Failure, decreasing to negative.
    pass = false;
    try {
        CONTRACT_LOOP( for(int i = 0; i < 10; ++i) ) {
            CONTRACT_LOOP_VARIANT( 8 - i )
        }
    } catch(loop_var_broken) {
        pass = true;
    }
    BOOST_TEST(pass);
    // Failure, not decreasing.
    pass = false;
    try {
        CONTRACT_LOOP( for(int i = 0; i < 10; ++i) ) {
            CONTRACT_LOOP_VARIANT( 10 )
        }
    } catch(loop_var_broken) {
        pass = true;
    }
    BOOST_TEST(pass);
    std::cerr << std::endl;
#endif

    return boost::report_errors();
}

