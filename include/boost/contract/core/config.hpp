
#ifndef BOOST_CONTRACT_CONFIG_HPP_
#define BOOST_CONTRACT_CONFIG_HPP_

// Copyright (C) 2008-2016 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0 (see accompanying
// file LICENSE_1_0.txt or a copy at http://www.boost.org/LICENSE_1_0.txt).
// See: http://www.boost.org/doc/libs/release/libs/contract/doc/html/index.html

/** @file
Configure this library compile-time and run-time behaviours.
*/

// IMPORTANT: This header MUST NOT #include any other header of this lib.
// That way users can #include this header and not #include any of this lib
// headers after that depending on the contract 0/1 macros below ensuring no
// compilation overhead.

#ifdef DOXYGEN
    /**
    Define this macro to compile this library as a static (instead of shared)
    library (undefined by default).

    If this macro is defined, this library is compiled so it can be linked
    statically to user code (and not as a shared library as by default).

    @warning    In general this library must be compiled as a shared library
                (i.e., not defining this macro) otherwise the contracts might
                not always be checked correctly at run-time.
                
    @see @RefSect{getting_started.install_and_compile, Install and Compile}
    */
    #define BOOST_CONTRACT_STATIC_LINK
#elif   defined(BOOST_CONTRACT_STATIC_LINK) && \
        ( \
            defined(BOOST_CONTRACT_HEADER_ONLY) || \
            defined(BOOST_ALL_DYN_LINK) \
        )
    #error "STATIC_LINK defined with HEADER_ONLY and/or ALL_DYN_LINK"
#endif

#ifdef DOXYGEN
    /**
    Define this macro when compiling user code to avoid compiling this library
    (undefined by default).

    If this macro is defined, this library does not have to be compiled
    separately from user code.
    This library headers are simply included in the user program and this
    library implementation code is compiled as part of the user program.
    
    @warning    In general this library must be compiled as a shared library
                (i.e., not defining this macro) otherwise the contracts might
                not always be checked correctly at run-time.
                
    @see @RefSect{getting_started.install_and_compile, Install and Compile}
    */
    #define BOOST_CONTRACT_HEADER_ONLY
#elif   defined(BOOST_CONTRACT_HEADER_ONLY) && \
        ( \
            defined(BOOST_CONTRACT_STATIC_LINK) || \
            defined(BOOST_ALL_DYN_LINK) \
        )
    #error "HEADER_ONLY defined with STATIC_LINK and/or ALL_DYN_LINK"
#endif

#ifdef DOXYGEN
    /**
    Define this macro to not lock internal library data for thread safety
    (undefined by default).

    Defining this macro will make the library implementation code not thread
    safe so this macro should not be defined unless the library is being used
    strictly under single-threaded applications.
    However, when this macro is left undefined this library needs to internally
    use some sort of "global" locks (to ensure contract checking is globally
    disabled when other contracts are being checked and also to safely access
    failure handler functors) and that could introduce an undesired amount of
    synchronization in some multi-threaded applications.
    
    @see @RefSect{contract_programming_overview, Contract Programming Overview}
    */
    #define BOOST_CONTRACT_DISABLE_THREADS
#endif

#ifndef BOOST_CONTRACT_MAX_ARGS
    /**
    Maximum number of function arguments on compilers that do not support
    variadic macros (default to @c 10).

    On compilers that support variadic macros, this macro has no effect.
    On compilers that do not support variadic macros, this macro can be defined
    to support a maximum number of arguments different than @c 10 for
    public function overrides (that use
    @RefFunc{boost::contract::public_function}).

    @note   Regardless of the value of this macro and of compiler support for
            variadic macros, there is an intrinsic limit of about 18 arguments
            for public function overrides (because of similar limits in
            Boost.MPL and Boost.FunctionTypes internally used by this library).

    @see @RefSect{extra_topics.no_macros__no_c__11_, No Macros}
    */
    #define BOOST_CONTRACT_MAX_ARGS 10
#endif

#ifndef BOOST_CONTRACT_BASES_TYPEDEF
    /**
    Define the name of the base type @c typedef (@c base_types by default).

    This macro expands to the name of the @c typedef that lists the base
    classes for subcontracting via @RefMacro{BOOST_CONTRACT_BASE_TYPES}.
    This macro can be defined if that @c typedef must have a name different from
    @c base_types.
    
    @see @RefSect{tutorial.base_classes__subcontracting_, Base Classes}
    */
    #define BOOST_CONTRACT_BASES_TYPEDEF base_types
#endif

#ifndef BOOST_CONTRACT_INVARIANT_FUNC
    /**
    Define the name of the invariant member functions (@c invariant by defult).

    This macro expands to the name of the @c const and <c>const volatile</c>
    member functions that check mutable and volatile class invariants
    respectively.
    This macro can be defined if these invariant functions must have a name
    different from @c invariant.
    
    @see    @RefSect{tutorial.class_invariants, Class Invariants},
            @RefSect{extra_topics.volatile_public_functions,
            Volatile Public Functions}
    */
    #define BOOST_CONTRACT_INVARIANT_FUNC invariant
#endif

#ifndef BOOST_CONTRACT_STATIC_INVARIANT_FUNC
    /**
    Define the name of the static invariant member function (@c static_invariant
    by default).

    This macro expands to the name of the @c static member function that checks
    static class invariants.
    This macro can be defined if this static invariant function must have a name
    different from @c static_invariant.

    @note   C++ does not allow to overload member functions based on the
            @c static qualifier, so this macro must always be defined to be
            different than the function name defined for
            @RefMacro{BOOST_CONTRACT_INVARIANT_FUNC}.
    
    @see    @RefSect{tutorial.class_invariants, Class Invariants}
    */
    #define BOOST_CONTRACT_STATIC_INVARIANT_FUNC static_invariant
#endif

#ifdef DOXYGEN
    /**
    Disable some compile-time errors generated by this library (undefined by
    default).

    Defining this macro disables a number of static checks and compile-time
    errors, for example:

    @li The static invariant member @c BOOST_CONTRACT_STATIC_INVARIANT_FUNC
        function must be declared @c static.
    @li Non-static invariant member functions @c BOOST_CONTRACT_INVARIANT_FUNC
        must be declared either @c const, <c>const volatile</c>, or
        <c>volatile const</c>.
    @li Derived classes that program contracts for one or more public function
        overrides via @RefFunc{boost::contract::public_function} must also
        define the @RefMacro{BOOST_CONTRACT_BASE_TYPES} @c typedef.
        
    @see    @RefSect{tutorial.class_invariants, Class Invariants},
            @RefSect{tutorial.base_classes__subcontracting_, Base Classes}
    */
    #define BOOST_CONTRACT_PERMISSIVE
#endif

#ifdef DOXYGEN
    /**
    Code block to execute if contracts are not assigned to a
    @RefClass{boost::contract::check} variable (undefined by default).

    In general, there is a logic error in the program when contracts are not
    assigned to a local variable of type @RefClass{boost::contract::check}.
    Therefore, by default (i.e., when this macro is not defined) this library
    calls <c>assert(false)</c> in those cases.
    If this macro is defined, this library will execute the code expanded by the
    macro instead of calling @c assert(false) (if programmers prefer to throw an
    exception, etc.).

    This macro can be defined to be any block of code (including @c {} to
    generate no error), for example (on GCC):
    @code
        -DBOOST_CONTRACT_ON_MISSING_CHECK_DECL='{ throw std::logic_error(); }'
    @endcode

    @see @RefSect{tutorial.non_member_functions, Non-Member Functions}
    */
    #define BOOST_CONTRACT_ON_MISSING_CHECK_DECL
#endif

#ifdef DOXYGEN
    /**
    Define this macro to not disable other assertions while checking
    preconditions (undefined by default).
    
    Not disabling other assertions while checking preconditions can lead to
    infinite recursion in user code so by default this macro is not defined.
    However, the @RefSect{bibliography, [1962]} proposal does not disable any
    assertion while checking preconditions because arguments can reach the
    function body unchecked if assertions are disabled while checking
    preconditions (when these same functions bodies are called to check the
    preconditions in question).
    This macro can be defined to obtain the behaviour specified in
    @RefSect{bibliography, [1962]} (at the risk of infinite recursion).

    @see @RefSect{contract_programming_overview, Contract Programming Overview}
    */
    #define BOOST_CONTRACT_PRECONDITIONS_DISABLE_NO_ASSERTION
#endif

#ifdef DOXYGEN
    /**
    Define this macro to not disable any assertions while checking any other
    assertion (undefined by default).
    
    Not disabling assertions while checking other assertions can lead to
    infinite recursion in user code so by default this macro is not defined.
    (Defining this macro automatically implies that other assertion checking is
    disabled while checking preconditions as if
    @RefMacro{BOOST_CONTRACT_PRECONDITIONS_DISABLE_NO_ASSERTION} was also
    defined.)

    @see @RefSect{contract_programming_overview, Contract Programming Overview}
    */
    #define BOOST_CONTRACT_ALL_DISABLE_NO_ASSERTION
#endif

// TODO: Add NO_CHECK to boost_contract_no build for tests, etc.
#ifdef DOXYGEN
    /**
    If defined, this library does not perform implementation checks (undefined
    by default).

    If this macro is defined, this library internal code is also optimized to
    reduce compile-time (not just run-time) overhead associated with
    implementation checks.
    Use @RefMacro{BOOST_CONTRACT_CHECK} to completely disable compilation of
    implementation checks when @RefMacro{BOOST_CONTRACT_NO_CHECKS} is defined.

    @see    @RefSect{advanced_topics.implementation_checks,
            Implementation Checks},
            @RefSect{extra_topics.disable_contract_checking,
            Disable Contract Checking},
           @RefSect{extra_topics.disable_contract_compilation__macro_interface_,
            Disable Contract Compilation}
    */
    #define BOOST_CONTRACT_NO_CHECKS
#endif

#ifdef DOXYGEN
    /**
    If defined, this library does not check preconditions (undefined by
    default).

    If this macro is defined, this library internal code is also optimized to
    reduce compile-time (not just run-time) overhead associated with
    checking preconditions.
    Users can manually program @c \#ifndef statements in their code using this
    macro to completely disable compilation of preconditions or use the macros
    defined in @c boost/contract_macro.hpp (recommended only for applications
    where it is truly necessary to completely remove contract code compilation
    from production code).

    @see    @RefSect{tutorial.preconditions, Preconditions},
            @RefSect{extra_topics.disable_contract_checking,
            Disable Contract Checking},
           @RefSect{extra_topics.disable_contract_compilation__macro_interface_,
            Disable Contract Compilation}
    */
    #define BOOST_CONTRACT_NO_PRECONDITIONS
#endif

#ifdef DOXYGEN
    /**
    If defined, this library does not check postconditions (undefined by
    default).

    If this macro is defined, this library internal code is also optimized to
    reduce compile-time (not just run-time) overhead associated with
    checking postconditions.
    Users can manually program @c \#ifndef statements in their code using this
    macro to completely disable compilation of postconditions or use the macros
    defined in @c boost/contract_macro.hpp (recommended only for applications
    where it is truly necessary to completely remove contract code compilation
    from production code).

    @see    @RefSect{tutorial.postconditions, Postconditions},
            @RefSect{extra_topics.disable_contract_checking,
            Disable Contract Checking},
           @RefSect{extra_topics.disable_contract_compilation__macro_interface_,
            Disable Contract Compilation}
    */
    #define BOOST_CONTRACT_NO_POSTCONDITIONS
#endif

#ifdef DOXYGEN
    /**
    If defined, this library does not check exception guarantees (undefined by
    default).

    If this macro is defined, this library internal code is also optimized to
    reduce compile-time (not just run-time) overhead associated with
    checking exception guarantees.
    Users can manually program @c \#ifndef statements in their code using this
    macro to completely disable compilation of exception guarantees or use the
    macros defined in @c boost/contract_macro.hpp (recommended only for
    applications where it is truly necessary to completely remove contract code
    compilation from production code).

    @see    @RefSect{tutorial.exception_guarantees, Exception Guarantees},
            @RefSect{extra_topics.disable_contract_checking,
            Disable Contract Checking},
           @RefSect{extra_topics.disable_contract_compilation__macro_interface_,
            Disable Contract Compilation}
    */
    #define BOOST_CONTRACT_NO_EXCEPTS
#endif

#if     defined(DOXYGEN) || \
        ( \
            !defined(BOOST_CONTRACT_NO_ENTRY_INVARIANTS) && \
            defined(BOOST_CONTRACT_NO_INVARIANTS) \
        )
    /**
    If defined, this library does not check class invariants at entry (undefined
    by default).

    If this macro is defined, this library internal code is also optimized to
    reduce compile-time (not just run-time) overhead associated with
    checking entry class invariants.
    Users can manually program @c \#ifndef statements in their code using this
    macro to completely disable compilation of entry class invariants or use the
    macros defined in @c boost/contract_macro.hpp (recommended only for
    applications where it is truly necessary to completely remove contract code
    compilation from production code).

    This macro is automatically defined when
    @RefMacro{BOOST_CONTRACT_NO_INVARIANTS} is defined.

    @see    @RefSect{tutorial.class_invariants, Class Invariants},
            @RefSect{extra_topics.disable_contract_checking,
            Disable Contract Checking},
           @RefSect{extra_topics.disable_contract_compilation__macro_interface_,
            Disable Contract Compilation}
    */
    #define BOOST_CONTRACT_NO_ENTRY_INVARIANTS
#endif

#if     defined(DOXYGEN) || \
        ( \
            !defined(BOOST_CONTRACT_NO_EXIT_INVARIANTS) && \
            defined(BOOST_CONTRACT_NO_INVARIANTS) \
        )
    /**
    If defined, this library does not check class invariants at exit (undefined
    by default).

    If this macro is defined, this library internal code is also optimized to
    reduce compile-time (not just run-time) overhead associated with
    checking exit class invariants.
    Users can manually program @c \#ifndef statements in their code using this
    macro to completely disable compilation of exit class invariants or use the
    macros defined in @c boost/contract_macro.hpp (recommended only for
    applications where it is truly necessary to completely remove contract code
    compilation from production code).

    This macro is automatically defined when
    @RefMacro{BOOST_CONTRACT_NO_INVARIANTS} is defined.

    @see    @RefSect{tutorial.class_invariants, Class Invariants},
            @RefSect{extra_topics.disable_contract_checking,
            Disable Contract Checking},
           @RefSect{extra_topics.disable_contract_compilation__macro_interface_,
            Disable Contract Compilation}
    */
    #define BOOST_CONTRACT_NO_EXIT_INVARIANTS
#endif

#if     !defined(BOOST_CONTRACT_NO_INVARIANTS) && \
        defined(BOOST_CONTRACT_NO_ENTRY_INVARIANTS) && \
        defined(BOOST_CONTRACT_NO_EXIT_INVARIANTS)
    /**
    If defined, this library does not check class invariants (undefined by
    default).

    If this macro is defined, this library internal code is also optimized to
    reduce compile-time (not just run-time) overhead associated with
    checking class invariants.
    Users can manually program @c \#ifndef statements in their code using this
    macro to completely disable compilation of class invariants or use the
    macros defined in @c boost/contract_macro.hpp (recommended only for
    applications where it is truly necessary to completely remove contract code
    compilation from production code).

    Defining this macro is equivalent to defining both
    @RefMacro{BOOST_CONTRACT_NO_ENTRY_INVARIANTS} and
    @RefMacro{BOOST_CONTRACT_NO_EXIT_INVARIANTS}.

    @see    @RefSect{tutorial.class_invariants, Class Invariants},
            @RefSect{extra_topics.disable_contract_checking,
            Disable Contract Checking},
           @RefSect{extra_topics.disable_contract_compilation__macro_interface_,
            Disable Contract Compilation}
    */
    #define BOOST_CONTRACT_NO_INVARIANTS
#endif

// Following are NOT configuration macros.

#ifdef BOOST_CONTRACT_NO_OLDS
    #error "define NO_POSTCONDITIONS and NO_EXCEPTS instead"
#elif   defined(BOOST_CONTRACT_NO_POSTCONDITIONS) && \
        defined(BOOST_CONTRACT_NO_EXCEPTS)
    /**
    Automatically defined by this library when old value copies are not to be
    performed.

    This library will define this macro when users define both
    @RefMacro{BOOST_CONTRACT_NO_POSTCONDITIONS} and
    @RefMacro{BOOST_CONTRACT_NO_EXCEPTS} (this macro is not a configuration
    macro and this library will generate a compile-time error if users try to
    define it directly).
    Users can manually program @c \#ifndef statements in their code using this
    macro to completely disable compilation of old value copies or use the
    macros defined in @c boost/contract_macro.hpp (recommended only for
    applications where it is truly necessary to completely remove contract code
    compilation from production code).

    @see    @RefSect{tutorial.old_values, Old Values},
            @RefSect{advanced_topics.old_values_at_body, Old Values at Body},
           @RefSect{extra_topics.disable_contract_compilation__macro_interface_,
            Disable Contract Compilation}
    */
    #define BOOST_CONTRACT_NO_OLDS
#endif

// Ctor pre checked separately and outside RAII so not part of this #define.
#ifdef BOOST_CONTRACT_NO_CONSTRUCTORS
    #error "define NO_INVARIANTS, NO_POSTCONDITIONS, and NO_EXCEPTS instead"
#elif   defined(BOOST_CONTRACT_NO_INVARIANTS) && \
        defined(BOOST_CONTRACT_NO_POSTCONDITIONS) && \
        defined(BOOST_CONTRACT_NO_EXCEPTS)
    /**
    Automatically defined by this library when contracts are not to be checked
    for constructors.

    This library will define this macro when users define all
    @RefMacro{BOOST_CONTRACT_NO_INVARIANTS},
    @RefMacro{BOOST_CONTRACT_NO_POSTCONDITIONS}, and
    @RefMacro{BOOST_CONTRACT_NO_EXCEPTS} (this macro is not a configuration
    macro and this library will generate a compile-time error if users try to
    define it directly).
    Users can manually program @c \#ifndef statements in their code using this
    macro to completely disable compilation of contracts for constructors or use
    the macros defined in @c boost/contract_macro.hpp (recommended only for
    applications where it is truly necessary to completely remove contract code
    compilation from production code).
    
    @note   Constructor preconditions are checked separately by
            @RefClass{boost::contract::constructor_precondition} so they are
            disabled by @RefMacro{BOOST_CONTRACT_NO_PRECONDITIONS} instead.

    @see    @RefSect{tutorial.constructors, Constructors},
           @RefSect{extra_topics.disable_contract_compilation__macro_interface_,
            Disable Contract Compilation}
    */
    #define BOOST_CONTRACT_NO_CONSTRUCTORS
#endif

#ifdef BOOST_CONTRACT_NO_DESTRUCTORS
    #error "define NO_INVARIANTS, NO_POSTCONDITIONS, and NO_EXCEPTS instead"
#elif   defined(BOOST_CONTRACT_NO_INVARIANTS) && \
        defined(BOOST_CONTRACT_NO_POSTCONDITIONS) && \
        defined(BOOST_CONTRACT_NO_EXCEPTS)
    /**
    Automatically defined by this library when contracts are not to be checked
    for destructors.

    This library will define this macro when users define all
    @RefMacro{BOOST_CONTRACT_NO_INVARIANTS},
    @RefMacro{BOOST_CONTRACT_NO_POSTCONDITIONS}, and
    @RefMacro{BOOST_CONTRACT_NO_EXCEPTS} (this macro is not a configuration
    macro and this library will generate a compile-time error if users try to
    define it directly).
    Users can manually program @c \#ifndef statements in their code using this
    macro to completely disable compilation of contracts for destructors or use
    the macros defined in @c boost/contract_macro.hpp (recommended only for
    applications where it is truly necessary to completely remove contract code
    compilation from production code).
    
    @see    @RefSect{tutorial.destructors, Destructors},
           @RefSect{extra_topics.disable_contract_compilation__macro_interface_,
            Disable Contract Compilation}
    */
    #define BOOST_CONTRACT_NO_DESTRUCTORS
#endif

#ifdef BOOST_CONTRACT_NO_PUBLIC_FUNCTIONS
    #error "define NO_INVARIANTS, NO_PRECONDITIONS, NO_POSTCONDITIONS, and NO_EXCEPTS instead"
#elif   defined(BOOST_CONTRACT_NO_INVARIANTS) && \
        defined(BOOST_CONTRACT_NO_PRECONDITIONS) && \
        defined(BOOST_CONTRACT_NO_POSTCONDITIONS) && \
        defined(BOOST_CONTRACT_NO_EXCEPTS)
    /**
    Automatically defined by this library when contracts are not to be checked
    for public functions.

    This library will define this macro when users define all
    @RefMacro{BOOST_CONTRACT_NO_INVARIANTS},
    @RefMacro{BOOST_CONTRACT_NO_PRECONDITIONS},
    @RefMacro{BOOST_CONTRACT_NO_POSTCONDITIONS}, and
    @RefMacro{BOOST_CONTRACT_NO_EXCEPTS} (this macro is not a configuration
    macro and this library will generate a compile-time error if users try to
    define it directly).
    Users can manually program @c \#ifndef statements in their code using this
    macro to completely disable compilation of contracts for public functions or
    use the macros defined in @c boost/contract_macro.hpp (recommended only for
    applications where it is truly necessary to completely remove contract code
    compilation from production code).
    
    @see    @RefSect{tutorial.public_functions, Public Functions},
           @RefSect{extra_topics.disable_contract_compilation__macro_interface_,
            Disable Contract Compilation}
    */
    #define BOOST_CONTRACT_NO_PUBLIC_FUNCTIONS
#endif
    
#ifdef BOOST_CONTRACT_NO_FUNCTIONS
    #error "define NO_PRECONDITIONS, NO_POSTCONDITIONS, and NO_EXCEPTS instead"
#elif   defined(BOOST_CONTRACT_NO_PRECONDITIONS) && \
        defined(BOOST_CONTRACT_NO_POSTCONDITIONS) && \
        defined(BOOST_CONTRACT_NO_EXCEPTS)
    /**
    Automatically defined by this library when contracts are not to be checked
    for (non-public) functions.

    This library will define this macro when users define all
    @RefMacro{BOOST_CONTRACT_NO_PRECONDITIONS},
    @RefMacro{BOOST_CONTRACT_NO_POSTCONDITIONS}, and
    @RefMacro{BOOST_CONTRACT_NO_EXCEPTS} (this macro is not a configuration
    macro and this library will generate a compile-time error if users try to
    define it directly).
    Users can manually program @c \#ifndef statements in their code using this
    macro to completely disable compilation of contracts for (non-public)
    functions or use the macros defined in @c boost/contract_macro.hpp
    (recommended only for applications where it is truly necessary to completely
    remove contract code compilation from production code).

    This macro is also used when contracts are not to be checked for private and
    protected functions, lambda functions, code blocks, loops, etc.

    @see    @RefSect{tutorial.non_member_functions, Non-Member Functions},
            @RefSect{advanced_topics.private_and_protected_functions,
            Private and Protected Functions},
            @RefSect{advanced_topics.lambdas__code_blocks__loops__etc_,
            Lambdas\, Code Blocks\, Loops\, Etc.},
           @RefSect{extra_topics.disable_contract_compilation__macro_interface_,
            Disable Contract Compilation}
    */
    #define BOOST_CONTRACT_NO_FUNCTIONS
#endif

#ifdef BOOST_CONTRACT_NO_ALL
    #error "define NO_INVARIANTS, NO_PRECONDITIONS, NO_POSTCONDITIONS, NO_EXCEPTS, and NO_CHECKS instead"
#elif   defined(BOOST_CONTRACT_NO_INVARIANTS) && \
        defined(BOOST_CONTRACT_NO_PRECONDITIONS) && \
        defined(BOOST_CONTRACT_NO_POSTCONDITIONS) && \
        defined(BOOST_CONTRACT_NO_EXCEPTS) && \
        defined(BOOST_CONTRACT_NO_CHECKS)
    /**
    Automatically defined by this library when contracts are not to be checked
    for any operation.

    This library will define this macro when users define all
    @RefMacro{BOOST_CONTRACT_NO_INVARIANTS},
    @RefMacro{BOOST_CONTRACT_NO_PRECONDITIONS},
    @RefMacro{BOOST_CONTRACT_NO_POSTCONDITIONS},
    @RefMacro{BOOST_CONTRACT_NO_EXCEPTS}, and
    @RefMacro{BOOST_CONTRACT_NO_CHECKS} (this macro is not a configuration
    macro and this library will generate a compile-time error if users try to
    define it directly).
    For example, users can manually program @c \#ifndef statements in their code
    using this macro to avoid including the @c boost/contract.hpp header all
    together:

    @code
    #include <boost/contract/core/config.hpp>
    #ifndef BOOST_CONTRACT_NO_ALL
        #include <boost/contract.hpp>
    #endif
    @endcode
    
    Or, include @c boost/contract_macro.hpp instead (recommended only for
    applications where it is truly necessary to completely remove contract
    code compilation from production code).

    @see   @RefSect{extra_topics.disable_contract_compilation__macro_interface_,
            Disable Contract Compilation}
    */
    #define BOOST_CONTRACT_NO_ALL
#endif

#ifdef BOOST_CONTRACT_DYN_LINK
    #error "define STATIC_LINK or HEADER_ONLY instead"
#elif   defined(DOXYGEN) || \
        defined(BOOST_ALL_DYN_LINK) || \
        ( \
            !defined(BOOST_CONTRACT_STATIC_LINK) && \
            !defined(BOOST_CONTRACT_HEADER_ONLY) \
        )
    /**
    Automatically defined when this library is being compiled as a shared
    library (automatically defined by default).
    
    This library will define this macro unless users define
    @RefMacro{BOOST_CONTRACT_STATIC_LINK} or
    @RefMacro{BOOST_CONTRACT_HEADER_ONLY} (this macro is not a configuration
    macro and this library will generate a compile-time error if users try to
    define it directly).
    Programmers should rarely, if ever, need to use this macro directly.

    @warning    In general this library will correctly check contracts at
                run-time only when compiled as a shared library (i.e., this
                macro will be automatically defined by default).
                
    @see @RefSect{getting_started.install_and_compile, Install and Compile}
    */
    #define BOOST_CONTRACT_DYN_LINK
#endif

#endif // #include guard

