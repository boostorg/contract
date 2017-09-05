
// Copyright (C) 2008-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://sourceforge.net/projects/contractpp

#ifndef CONTRACT_BROKEN_HPP_
#define CONTRACT_BROKEN_HPP_

/** @file
@brief Contract broken handlers (this header is automatically included by
<c>contract.hpp</c>).
*/

#include <contract/aux_/thread_variable.hpp>
#include <stdexcept>
#include <sstream>
#include <string>
#include <iostream> // For default broken handler.

// IMPORTANT: Most of these functions do no throw so they comply with
// C++ STL exception safety requirements.

// NOTE: The contract broken handlers are similar to std::temrinate (inlining
// functions also to avoid multiple definitions error).

namespace contract {

/**
@brief Exception automatically thrown by the library to signal a contract
assertion failure.

This exception contains detailed information about the failed contract
assertion (file name, line number, etc).

A contract assertion is considered failed if it cannot be evaluated to be true
(so if it is evaluated to be false but also if an exception is thrown by the
code that evaluates the assertion condition).
In case a contract assertion fails, the library automatically calls the
appropriate contract broken handler with this exception as the active exception
(the fact that assertion failures are signaled by this library by throwing this
exception does not necessarily mean that the exception will be ultimately
thrown by the broken contract, that is entirely up to the implementation of the
contract broken handlers).
By default, contract broken handlers print an error message to <c>std::cerr</c>
and terminate the program calling <c>std::terminate</c>, but programmers can
redefine this behaviour by customizing the contract broken handlers (for
example to have the handlers throw exceptions instead of terminating the
program).
Within customized contract broken handlers, programmers can re-throw and catch
this exception to obtained information about the failed asserted condition
(file name, line number, etc).

@Note This exception is guaranteed to publicly inherit from
<c>std::logic_error</c> (because <c>std::logic_error</c> models programming
errors and those are the type of errors that contract assertions detect).

@SeeAlso @RefSect{advanced_topics, Advanced Topics} section.
*/
class broken: public std::logic_error // This is a logic error or "bug".
{
public:
    /**
    @brief Construct this exception specifying the failed assertion file name,
    line number, assertion code, and assertion number (no-throw).

    The assertion number is optional and it defaults to zero (an assertion
    number equal to zero is ignored and not shown in the error description).
    */
    explicit broken (
            char const* file_name,
            unsigned long const& line_number,
            char const* assertion_code,
            unsigned int const& assertion_number = 0
        ) throw( )
        : std::logic_error("")
        , file_name_(file_name)
        , line_number_(line_number)
        , assertion_code_(assertion_code)
        , assertion_number_(assertion_number)
    {}

    /** @brief Copy constructor (no-throw). */
    broken ( broken const& source ) throw( ) // Make sure unthrow.
        : std::logic_error("")
        , file_name_(source.file_name_)
        , line_number_(source.line_number_)
        , assertion_code_(source.assertion_code_)
        , assertion_number_(source.assertion_number_)
    {}

    /** @brief Copy operator (no-throw). */
    broken& operator= ( broken const& source ) throw( ) { // Make sure unthrow.
        file_name_ = source.file_name_;
        line_number_ = source.line_number_;
        assertion_code_ = source.assertion_code_;
        assertion_number_ = source.assertion_number_;
        return *this;
    }

    /** @brief Virtual destructor (no-throw). */
    virtual ~broken ( void ) throw( ) {} // Make sure unthrow.

    /** @brief Return a description of the assertion failure (no-throw). */
    virtual char const* what ( void ) const throw( ) {
        // IMPORTANT: The format of this error message is based on GCC text
        // provided in case of C-style `assert()` failure (so don't change it).
        // Don't print assertion number here (because we don't know which type
        // of assertion this is) -- contract handlers know also the assertion
        // type and context and they will print at this information.
        std::ostringstream msg;
        msg << "assertion \"" << assertion_code() << "\" failed: file \"" <<
                file_name() << "\", line " << line_number();
        what_ = msg.str();
        return what_.c_str();
    }

    /**
    @brief Return the name of the file containing the failed assertion
    (no-throw).
    */
    virtual char const* file_name ( void ) const throw( )
        { return file_name_.c_str(); }

    /** @brief Return the number of the line containing the failed
    assertion (no-throw). */
    virtual unsigned long const line_number ( void ) const throw( )
        { return line_number_; }
    
    /** @brief Return the text of the asserted code that failed (no-throw). */
    virtual char const* assertion_code ( void ) const throw( )
        { return assertion_code_.c_str(); }

    /**
    @brief Return the number of the failed assertion (no-throw). 

    The assertion number is useful only within the context of a specific
    contract broken handler that can differentiates between broken
    preconditions, postconditions, etc because different preconditions,
    postconditions, etc will in general have the same assertion number (the
    first precondition is assertion number 1, the first postcondition is also
    assertion number 1, etc).

    If this number is zero then no sensible assertion number was specified and
    it should be ignored (e.g., loop variant assertions have no assertion
    number because there can only be one single variant for a loop).
    */
    virtual unsigned int const assertion_number ( void ) const throw( )
        { return assertion_number_; }

private:
    std::string file_name_;
    unsigned long line_number_;
    std::string assertion_code_;
    unsigned int assertion_number_;
    mutable std::string what_; // This state needed to keep c_str() ptr valid.
};

/**
@brief Specify the context from which the contract assertion failed.

This information is important because in order to comply with STL exception
safety requirements, destructors shall never throw an exception.
Therefore, even if programmers customize the contract broken handlers to throw
an exception instead of terminating the program, it is still important to know
at least if the assertion failed from a destructor's contract so programmers
can avoid throwing an exception from the broken handlers in such a case.

@Note All the different contexts identified by this enumeration have different
contract checking semantics (see also
@RefSect{contract_programming_overview, Contract Programming Overview}) so it
might be relevant to differentiate between them in the contract broken
handlers.

@SeeAlso @RefSect{advanced_topics, Advanced Topics} section.
*/
typedef enum
{
    /** @brief Assertion failed from within constructor contracts. */
    FROM_CONSTRUCTOR,
    /** @brief Assertion failed from within destructor contracts. */
    FROM_DESTRUCTOR,
    /** @brief Assertion failed from within non-static member function
    contracts. */
    FROM_NONSTATIC_MEMBER_FUNCTION,
    /** @brief Assertion failed from within static member function contracts. */
    FROM_STATIC_MEMBER_FUNCTION,
    /** @brief Assertion failed from within free function contracts. */
    FROM_FREE_FUNCTION,
    /** @brief Assertion failed from within body contracts (for both block
    invariants and loop variants). */
    FROM_BODY
} from;

#ifndef DOXYGEN
typedef void (*broken_contract_handler) ( from const& context ) ;
#else // Doxygen can correctly parse the typedef above...
/**
@brief Contract broken handler function pointer.

A contract broken handler is a function returning <c>void</c> and taking only
one parameter of type @RefEnum{from} indicating the context from which the
contract assertion failed:

@code
typedef void (*handler_function_pointer) ( from const& context ) ;
@endcode

@Note This function prototype is not non-throw to allow programmers to
customize the contract broken handlers to throw exceptions if they wish to do
so.

@SeeAlso @RefSect{advanced_topics, Advanced Topics} section.
*/
typedef handler_function_pointer broken_contract_handler ;
#endif

#ifndef DOXYGEN

// NOTE: This private code is here instead that in the aux director because
// it is the only way to resolve inclusion problems without splitting into
// multiple headers (having multiple headers for the broken handlers, one
// for the broken exception, etc is confusing for the user).
namespace aux {

// Default broken handler do not throw (exception specification throw()) so 
// they comply with STL exception safety requirements. Inlined function also 
// to avoid multiple definition error.
inline void default_broken_handler(char const* contract_description,
        from const& context) throw() {
    // Default handlers are verbose and prints to standard-error the error
    // before terminating (redefine the default handlers to be quite, etc).
    try {
        try {
            throw; // To catch below and print to standard error.
        } catch(broken& failure) {
            // IMPORTANT: The format of this error message is based on GCC
            // error in case of C-style `assert` failure -- don't change it.
            std::cerr << contract_description << " ";
            if(failure.assertion_number())
                std::cerr << "number " << failure.assertion_number() << " ";
            std::cerr << "\"" << failure.assertion_code() <<
                    "\" failed: file \"" << failure.file_name() <<
                    "\", line " << failure.line_number() << std::endl;
            throw; // Re-throw.
        } catch(std::exception& failure) {
            std::cerr << contract_description << " failed: " << failure.what()
                    << std::cerr;
            throw; // Re-throw.
        } catch(...) {
            std::cerr << contract_description <<
                    " failed: unknown error" << std::endl;
            throw; // Re-throw.
        }
    } catch(...) {
        std::terminate(); // Terminate with active exception.
    }
    std::terminate(); // Always terminate.
}

inline void default_precondition_broken_handler(from const& context) throw()
    { default_broken_handler("precondition", context); }
inline void default_postcondition_broken_handler(from const& context) throw()
    { default_broken_handler("postcondition", context); }
inline void default_class_invariant_broken_on_entry_handler(
        from const& context) throw()
    { default_broken_handler("class invariant (on entry)", context); }
inline void default_class_invariant_broken_on_exit_handler(
        from const& context) throw()
    { default_broken_handler("class invariant (on exit)", context); }
inline void default_class_invariant_broken_on_throw_handler(
        from const& context) throw()
    { default_broken_handler("class invariant (on throw)", context); }
inline void default_block_invariant_broken_handler(from const& context) throw()
    { default_broken_handler("block invariant", context); }
inline void default_loop_variant_broken_handler(from const& context) throw()
    { default_broken_handler("loop variant", context); }

// NOTE: A template is used to wrap these variables so they can be defined in
// this header (instead of requiring to link a pre-compiled .cpp for these
// definitions) without causing a multiple definition error (static or extern
// specifiers cannot be used here because static creates a different variable
// copy for each translation unit when these variables need to globally have
// the same value for the entire program, and extern still requires the
// definitions somewhere in a .cpp which we wanted to avoid).
template<int Unused = 0>
struct broken_handlers {
    static thread_variable<broken_contract_handler> precondition;
    static thread_variable<broken_contract_handler> postcondition;
    static thread_variable<broken_contract_handler> class_invariant_on_entry;
    static thread_variable<broken_contract_handler> class_invariant_on_exit;
    static thread_variable<broken_contract_handler> class_invariant_on_throw;
    static thread_variable<broken_contract_handler> block_invariant;
    static thread_variable<broken_contract_handler> loop_variant;
};

template<int Unused>
thread_variable<broken_contract_handler> broken_handlers<Unused>::
        precondition = &default_precondition_broken_handler;
template<int Unused>
thread_variable<broken_contract_handler> broken_handlers<Unused>::
        postcondition = &default_postcondition_broken_handler;
template<int Unused>
thread_variable<broken_contract_handler> broken_handlers<Unused>::
        class_invariant_on_entry = 
                &default_class_invariant_broken_on_entry_handler;
template<int Unused>
thread_variable<broken_contract_handler> broken_handlers<Unused>::
        class_invariant_on_exit = 
                &default_class_invariant_broken_on_exit_handler;
template<int Unused>
thread_variable<broken_contract_handler> broken_handlers<Unused>::
        class_invariant_on_throw = 
                &default_class_invariant_broken_on_throw_handler;
template<int Unused>
thread_variable<broken_contract_handler> broken_handlers<Unused>::
        block_invariant = &default_block_invariant_broken_handler;
template<int Unused>
thread_variable<broken_contract_handler> broken_handlers<Unused>::
        loop_variant = &default_loop_variant_broken_handler;

} // namespace aux

#endif

/** @brief Set precondition broken handler to specified handler returning
replaced handler. */
inline broken_contract_handler set_precondition_broken (
        broken_contract_handler handler ) throw( ) {
    broken_contract_handler prev = aux::broken_handlers<>::precondition;
    aux::broken_handlers<>::precondition = handler;
    return prev;
}

/**
@brief Broken handler called when a precondition assertion fails.

By default, it prints information about the failed assertion to
<c>std::cerr</c> and it calls <c>std::terminate</c>.
However, it can be customized using
@RefFunc{contract::set_precondition_broken} (even to throw exceptions).

@Params
@Param{context,
Context from which the precondition assertion failed.
}
@EndParams

This handler is automatically called by the library in case of a precondition
assertion failure (an assertion fails if it is not evaluated to be true, so
if it is evaluated to be false but also if it cannot be evaluated because an
exception is thrown by the asserted condition).

@SeeAlso @RefSect{advanced_topics, Advanced Topics} section.
*/
inline void precondition_broken ( from const& context )
    // In general this could throw for user defined handlers.
    { aux::broken_handlers<>::precondition(context); }

/** @brief Set postcondition broken handler to specified handler returning
replaced handler. */
inline broken_contract_handler set_postcondition_broken (
        broken_contract_handler handler ) throw( )
{
    broken_contract_handler prev = aux::broken_handlers<>::postcondition;
    aux::broken_handlers<>::postcondition = handler;
    return prev;
}

/**
@brief Broken handler called when a postcondition assertion fails.

By default, it prints information about the failed assertion to
<c>std::cerr</c> and it calls <c>std::terminate</c>.
However, it can be customized using
@RefFunc{contract::set_postcondition_broken} (even to throw exceptions).

@Params
@Param{context,
Context from which the postcondition assertion failed.
}
@EndParams

This handler is automatically called by the library in case of a postcondition
assertion failure (an assertion fails if it is not evaluated to be true, so
if it is evaluated to be false but also if it cannot be evaluated because an
exception is thrown by the asserted condition).

@SeeAlso @RefSect{advanced_topics, Advanced Topics} section.
*/
inline void postcondition_broken ( from const& context )
    // In general this could throw for user defined handlers.
    { aux::broken_handlers<>::postcondition(context); }

/** @brief Set handler for class invariant broken on entry to specified handler
returning replaced handler. */
inline broken_contract_handler set_class_invariant_broken_on_entry (
        broken_contract_handler handler ) throw( )
{
    broken_contract_handler prev = aux::broken_handlers<>::
            class_invariant_on_entry;
    aux::broken_handlers<>::class_invariant_on_entry = handler;
    return prev;
}

/**
@brief Broken handler called when a class invariant assertion fails on function
entry.

By default, it prints information about the failed assertion to
<c>std::cerr</c> and it calls <c>std::terminate</c>.
However, it can be customized using
@RefFunc{contract::set_class_invariant_broken_on_entry} (even to throw
exceptions, but programmers should be careful to never throw from destructors).

@Params
@Param{context,
Context from which the class invariants assertion failed (destructors\, etc).
}
@EndParams

This handler is automatically called by the library in case of a class invariant
assertion failure (an assertion fails if it is not evaluated to be true, so
if it is evaluated to be false but also if it cannot be evaluated because an
exception is thrown by the asserted condition).

@SeeAlso @RefSect{advanced_topics, Advanced Topics} section.
*/
inline void class_invariant_broken_on_entry ( from const& context )
    // In general this could throw for user defined handlers.
    { aux::broken_handlers<>::class_invariant_on_entry(context); }

/** @brief Set handler for class invariant broken on exit to specified handler
returning replaced handler. */
inline broken_contract_handler set_class_invariant_broken_on_exit (
        broken_contract_handler handler ) throw( )
{
    broken_contract_handler prev = aux::broken_handlers<>::
            class_invariant_on_exit;
    aux::broken_handlers<>::class_invariant_on_exit = handler;
    return prev;
}

/**
@brief Broken handler called when a class invariant assertion fails on function
exit.

By default, it prints information about the failed assertion to
<c>std::cerr</c> and it calls <c>std::terminate</c>.
However, it can be customized using
@RefFunc{contract::set_class_invariant_broken_on_exit} (even to throw
exceptions, but programmers should be careful to never throw from destructors).

@Params
@Param{context,
Context from which the class invariants assertion failed (destructors\, etc).
}
@EndParams

This handler is automatically called by the library in case of a class invariant
assertion failure (an assertion fails if it is not evaluated to be true, so
if it is evaluated to be false but also if it cannot be evaluated because an
exception is thrown by the asserted condition).

@SeeAlso @RefSect{advanced_topics, Advanced Topics} section.
*/
inline void class_invariant_broken_on_exit ( from const& context )
    // In general this could throw for user defined handlers.
    { aux::broken_handlers<>::class_invariant_on_exit(context); }

/** @brief Set handler for class invariant broken on throw to specified
handler returning replaced handler. */
inline broken_contract_handler set_class_invariant_broken_on_throw (
        broken_contract_handler handler ) throw( )
{
    broken_contract_handler prev = aux::broken_handlers<>::
            class_invariant_on_throw;
    aux::broken_handlers<>::class_invariant_on_throw = handler;
    return prev;
}

/**
@brief Broken handler called when a class invariant assertion fails on function
exit after the function body threw an exception.

By default, it prints information about the failed assertion to
<c>std::cerr</c> and it calls <c>std::terminate</c>.
However, it can be customized using
@RefFunc{contract::set_class_invariant_broken_on_throw} (even to throw
exceptions, but programmers should be careful to never throw from destructors).

@Params
@Param{context,
Context from which the class invariants assertion failed (destructors\, etc).
}
@EndParams

This handler is automatically called by the library in case of a class invariant
assertion failure (an assertion fails if it is not evaluated to be true, so
if it is evaluated to be false but also if it cannot be evaluated because an
exception is thrown by the asserted condition).

@SeeAlso @RefSect{advanced_topics, Advanced Topics} section.
*/
inline void class_invariant_broken_on_throw ( from const& context )
    // In general this could throw for user defined handlers.
    { aux::broken_handlers<>::class_invariant_on_throw(context); }

/** @brief For convenience, set all class invariant broken handlers (on entry,
on exit, and on throw) to specified handler. */
inline void set_class_invariant_broken ( broken_contract_handler handler )
    throw( )
{
    set_class_invariant_broken_on_entry(handler);
    set_class_invariant_broken_on_exit(handler);
    set_class_invariant_broken_on_throw(handler);
}

/** @brief Set block invariant broken handler to specified handler returning
replaced handler. */
inline broken_contract_handler set_block_invariant_broken (
        broken_contract_handler handler ) throw( )
{
    broken_contract_handler prev = aux::broken_handlers<>::block_invariant;
    aux::broken_handlers<>::block_invariant = handler;
    return prev;
}

/**
@brief Broken handler called when a block invariant assertion fails.

By default, it prints information about the failed assertion to
<c>std::cerr</c> and it calls <c>std::terminate</c>.
However, it can be customized using
@RefFunc{contract::set_block_invariant_broken} (even to throw exceptions, but
programmers should be careful to never throw from destructors).

@Params
@Param{context,
Context from which the block invariants assertion failed (i.e.\, the body).
}
@EndParams

This handler is automatically called by the library in case of a block invariant
assertion failure (an assertion fails if it is not evaluated to be true, so
if it is evaluated to be false but also if it cannot be evaluated because an
exception is thrown by the asserted condition).

@SeeAlso @RefSect{advanced_topics, Advanced Topics} section.
*/
inline void block_invariant_broken ( from const& context )
    // In general this could throw for user defined handlers.
    { aux::broken_handlers<>::block_invariant(context); }

/** @brief Set the loop variant broken handler to specified handler returning
replaced handler. */
inline broken_contract_handler set_loop_variant_broken (
        broken_contract_handler handler ) throw( )
{
    broken_contract_handler prev = aux::broken_handlers<>::loop_variant;
    aux::broken_handlers<>::loop_variant = handler;
    return prev;
}

/**
@brief Broken handler called when a loop variant assertion fails.

By default, it prints information about the failed assertion to
<c>std::cerr</c> and it calls <c>std::terminate</c>.
However, it can be customized using
@RefFunc{contract::set_loop_variant_broken} (even to throw exceptions, but
programmers should be careful to never throw from destructors).

@Params
@Param{context,
Context from which the loop variants assertion failed (i.e.\, the body).
}
@EndParams

This handler is automatically called by the library in case of a loop invariant
assertion failure (an assertion fails if it is not evaluated to be true, so
if it is evaluated to be false but also if it cannot be evaluated because an
exception is thrown by the asserted condition).

@SeeAlso @RefSect{advanced_topics, Advanced Topics} section.
*/
inline void loop_variant_broken ( from const& context )
    // In general this could throw for user defined handlers.
    { aux::broken_handlers<>::loop_variant(context); }

} // namespace

#endif // #include guard

