// Copyright (C) 2009-2010 Lorenzo Caminiti.
// Use, modification, and distribution is subject to the
// Contract++ Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt.)

/** @file
Facilities to assert contract conditions and specify actions to take in case of contract failure.
*/

/**
Macro used to assert contract conditions for class invariants, preconditions, and postconditions.

Whenever possible, it is recommended to use this macro instead of throwing @c contract::failure directly.
For example (see the Tutorial section for more information):
@code
    CONTRACT_ASSERT( true );
@endcode

The code asserting the specified boolean condition is used as the description of the assertion (otherwise use @c CONTRACT_ASSERT_MSG()).

@Params
@Param{boolean_condition, The boolean contract condition being asserted.}
@EndParams

@Returns This macro expands to code equivalent to the following (see the Without the Macros section):
@code
    if (!(boolean_condition))
        throw contract::failure(__FILE__, __LINE__, # boolean_condition);
@endcode
Note how @c __FILE__ and @c __LINE__ are automatically used by the macro to improve error reporting.
(The preprocessor operator @c # makes a string from the specified token.)

@See @c CONTRACT_ASSERT_MSG(), @c contract::failure
*/
#define CONTRACT_ASSERT(boolean_condition)

/**
Macro used to assert contract conditions for class invariants, preconditions, and postconditions specifying also a human readable message.

When possible, it is recommended to use this macro instead of throwing @c contract::failure directly.
For example (see the Tutorial section for more information):
@code
    CONTRACT_ASSERT_MSG( true, "always true" );
@endcode

@Params
@Param{boolean_condition, The boolean contract condition being asserted.}
@Param{string_description,
    A string providing a human readable description of the condition being (used for error reporting).}
@EndParams

@Returns This macro expands to code equivalent to the following (see the Without the Macros section):
@code
    if (!(boolean_condition))
        throw contract::failure(__FILE__, __LINE__, string_description);
@endcode
Note how @c __FILE__ and @c __LINE__ are automatically used by the macro to improve error reporting.

@See @c CONTRACT_ASSERT(), @c contract::failure
*/
#define CONTRACT_ASSERT_MSG(boolean_condition, string_description)

namespace contract {

/**
Default exception thrown when a contract condition is found to be false.

It is recommended to assert contract conditions using the @c CONTRACT_ASSERT() macro instead of throwing this exception directly.

The library handles exceptions (any exception, not just this one) when thrown from within block invariants (plus loop variants), class invariants, preconditions, and postconditions invoking @c contract::block_invariant_failed(), @c contract::class_invariant_failed(), @c contract::precondition_failed(), and @c contract::postcondition_failed() respectively (see the Without the Macros section).

Therefore, throwing this exception on a contract condition failure does @b not imply that an exception will be thrown overall to handle the failure.
It only implies that the correct contract failure handler function will be automatically invoked by the library (after checking eventual overridden contracts for subcontracting, etc).
It is not possible to call the failure handler functions directly instead of throwing the exception because that will not allow the library to check overridden contracts when subcontracting.
The failure handler functions will then decide the action to take (the default handlers provided by the library invoke @c std::terminate() but programmers can redefine this behaviour using @c contract::set_block_invariant_failed(), @c contract::set_class_invariant_failed(), @c contract::set_precondition_failed(), and @c contract::set_postcondition_failed()).

The member functions of this class do not throw (their exception specification is @c thow()) so they can be safely used when checking contracts in compliance with STL C++ exception safety requirements at all times.

@See Without the Macros section.
*/
class failure: public std::logic_error {
public:
    /**
    Create a condition failure object.
    
    All the constructor parameters are used to provide more descriptive error messages in case of contract condition failure.
    At least the file and line number must be specified so to uniquely identify the point of the contract condition failure.
    
    @Params
    @Param{file, The source code file containing the failed contract condition (use @c __FILE__).}
    @Param{line, The source code line number containing the failed contract condition (use @c __LINE__).}
    @Param{description, An optional human readable description of the contract condition failure (@c "" if not specified).}
    @EndParams
    */
    explicit failure(const char* file, const unsigned long& line,
            const char* description = "") throw();
    
    /** Create a condition failure object copying it from the specified one. */
    failure(const failure& source) throw();
    
    /** Copy a condition failure from the specified one. */
    virtual failure& operator=(const failure& source) throw();
    
    /** Destroy the condition failure object. */
    virtual ~failure() throw();

    /**
    Return a human readable message explaining the nature of the condition failure.
    
    @Returns The actual message text is library implementation specific but it will contain the condition description, the file name, and the line number (when specified).
    For example, the returned message could look like this:
    @code
        contract "size increased by 1" failed at myvector.cpp:40
    @endcode
    */
    virtual const char* what() const throw();

    /** Return the condition failure source file. */
    virtual const char* file() const throw();
    
    /** Return the condition failure source line number. */
    virtual unsigned long line() const throw();

    /** Return the condition failure description (@c "" if not specified).*/
    virtual const char* description() const throw();    
};

/**
Function pointer type of the contract condition failure handler functions.

Where the function pointer type __ContractFailedHandler__ is defined as follows:
@code
    typedef void (* contract_failed_handler)(const from& where);
@endcode

@Params
@Param{where, The source that found the condition failure. This is useful for example to program failure handlers that throw exceptions in general but never from within destructors.}
@EndParams

@See Throw on Failure annex for an example.
*/
typedef __ContractFailedHandler__ contract_failed_handler;

/**
Set the specified user defined handler function to call on block invariant failure.

This function can be used by programmers to specify an action to take in case of block invariant failure different from the default to terminate the program.

@Params
@Param{handler,
    A pointer to the new handler function.
    Passing an invalid pointer\, including 0\, has undefined behaviour and it will likely result in a segmentation fault.}
@EndParams

@Returns The previously set handler function pointer.

@See Throw on Failure annex for an example.
*/
inline contract_failed_handler set_block_invariant_failed(
        contract_failed_handler handler) throw();

/**
Automatically invoked by this library when a block invariant condition fails.

It calls @c std::terminate() by default but it can be redefined using @c contract::set_block_invariant_failed().
When this function is called, the exception raised by the contract failure is the active unhandled exception (which can be re-thrown using <c>throw</c> and then caught, see Throw on Failure annex).

@Params
@Param{where, The source that found the the block invariant failure.}
@EndParams
*/
inline void block_invariant_failed(const from& where);

/**
Set the specified user defined handler function to call on class invariant failure.

This function can be used by programmers to specify an action to take in case of class invariant failure different from the default to terminate the program.

@Params
@Param{handler,
    A pointer to the new handler function.
    Passing an invalid pointer\, including 0\, has undefined behaviour and it will likely result in a segmentation fault.}
@EndParams

@Returns The previously set handler function pointer.

@See Throw on Failure annex for an example.
*/
inline contract_failed_handler set_class_invariant_failed(
        contract_failed_handler handler) throw();

/**
Automatically invoked by this library when a class invariant condition fails.

It calls @c std::terminate() by default but it can be redefined using @c contract::set_class_invariant_failed().
When this function is called, the exception raised by the contract failure is the active unhandled exception (which can be re-thrown using <c>throw</c> and then caught, see Throw on Failure annex).

@Params
@Param{where, The source that found the the invariant failure.}
@EndParams
*/
inline void class_invariant_failed(const from& where);

/**
Set the specified user defined handler function to call on precondition failure.

This function can be used by programmers to specify an action to take in case of precondition failure different from the default to terminate the program.

@Params
@Param{handler,
    A pointer to the new handler function.
    Passing an invalid pointer\, including 0\, has undefined behaviour and it will likely result in a segmentation fault.}
@EndParams

@Returns The previously set handler function pointer.

@See Throw on Failure annex for an example.
*/
inline contract_failed_handler set_precondition_failed(
        contract_failed_handler handler) throw();

/**
Automatically invoked by this library when a precondition fails.

It calls @c std::terminate() by default but it can be redefined using @c contract::set_precondition_failed().
When this function is called, the exception raised by the contract failure is the active unhandled exception (which can be re-thrown using <c>throw</c> and then caught, see Throw on Failure annex).

@Params
@Param{where, The source that found the the invariant failure.}
@EndParams
*/
inline void precondition_failed(const from& where);
        
/**
Set the specified user defined handler function to call on postcondition failure.

This function can be used by programmers to specify an action to take in case of postcondition failure different from the default to terminate the program.

@Params
@Param{handler,
    A pointer to the new handler function.
    Passing an invalid pointer\, including 0\, has undefined behaviour and it will likely result in a segmentation fault.}
@EndParams

@Returns The previously set handler function pointer.

@See Throw on Failure annex for an example.
*/
inline contract_failed_handler set_postcondition_failed(
        contract_failed_handler handler) throw();

/**
Automatically invoked by this library when a postcondition fails.

It calls @c std::terminate() by default but it can be redefined using @c contract::set_postcondition_failed().
When this function is called, the exception raised by the contract failure is the active unhandled exception (which can be re-thrown using <c>throw</c> and then caught, see Throw on Failure annex).

@Params
@Param{where, The source that found the the invariant failure.}
@EndParams
*/
inline void postcondition_failed(const from& where);

} // namespace

