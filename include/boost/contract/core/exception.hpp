
#ifndef BOOST_CONTRACT_EXCEPTION_HPP_
#define BOOST_CONTRACT_EXCEPTION_HPP_

// Copyright (C) 2008-2016 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0 (see accompanying
// file LICENSE_1_0.txt or a copy at http://www.boost.org/LICENSE_1_0.txt).
// See: http://www.boost.org/doc/libs/release/libs/contract/doc/html/index.html

/** @file
Exception and utilities to report contract assertion failures.
*/

#include <boost/contract/detail/declspec.hpp>
#include <boost/function.hpp>
#include <boost/config.hpp>
#include <exception>
#include <string>

// NOTE: This code should not change (not even its impl) based on the
// CONFIG_NO_... macros. For example, preconditions_failure() should still call
// the set precondition failure handler even when NO_PRECONDITIONS is #defined,
// because user code might explicitly call precondition_failure() (for whatever
// reason...). Otherwise, the public API of this lib will change.

namespace boost { namespace contract {

/**
Public base class for all this library exceptions.
This class does not inherit from @c std::exception because derived exceptions
will (inheriting from @c std::exception, or @c std::bad_cast, etc.).
@see @RefSect{advanced_topics, Advanced Topics}.
*/
class BOOST_CONTRACT_DETAIL_DECLSPEC exception {
public:
    /** Destruct this object. */
    virtual ~exception() BOOST_NOEXCEPT_OR_NOTHROW;
};

/**
Exception internally thrown by for inconsistent return values passed to
overridden virtual public functions.
This exception is internally thrown by this library when users specify a return
value for an overriding public function in a derived class that is inconsistent
with the return type of the virtual public function being overridden in the base
class.

<b>Rationale:</b>   The @c boost::bad_any_cast exception could not be used
                    because it does not print the from and to type names (so it
                    is not descriptive enough).

@see @RefSect{tutorial, Tutorial}.
*/
class BOOST_CONTRACT_DETAIL_DECLSPEC bad_virtual_result_cast : // Copy (as str).
        public std::bad_cast, public boost::contract::exception {
public:
    /**
    Construct this object with the name of the from and to types.
    @param from_type_name Name of the source type.
    @param to_type_name Name of the type destination type.
    */
    explicit bad_virtual_result_cast(char const* from_type_name,
            char const* to_type_name);

    /** Destruct this object. */
    virtual ~bad_virtual_result_cast() BOOST_NOEXCEPT_OR_NOTHROW;

    /** Return an error description (containing both from and to type names). */
    virtual char const* what() const BOOST_NOEXCEPT_OR_NOTHROW;

/** @cond */
private:
    std::string what_;
/** @endcond */
};

/**
Exception typically used to report a contract assertion failure.
This exception is thrown by code expanded by @RefMacro{BOOST_CONTRACT_ASSERT}
(but it can also be thrown by user code programmed manually without that macro).
@see @RefSect{advanced_topics, Advanced Topics}.
*/
class BOOST_CONTRACT_DETAIL_DECLSPEC assertion_failure : // Copy (as str, etc.).
        public std::exception, public boost::contract::exception {
public:
    /**
    Construct this object optionally with assertion file, line, and code
    information.
    This constructor can also be used to specify no information, or to specify
    only file and line but not code information (because of its parameter
    default values).
    @param file Name of the file containing the assertion (usually set using
                <c>__FILE__</c>).
    @param line Number of the line containing the assertion (usually set using
                <c>__LINE__</c>).
    @param code String text of the condition code being asserted.
    */
    explicit assertion_failure(char const* const file = "",
            unsigned long const line = 0, char const* const code = "");

    /**
    Construct this object with code information.
    This constructor can be used to specify only code but no file and line
    information.
    @param code String text of the condition code being asserted.
    */
    explicit assertion_failure(char const* const code);
    
    /** Destruct this object. */
    virtual ~assertion_failure() BOOST_NOEXCEPT_OR_NOTHROW;

    /**
    Return string describing the failed assertion.
    @return Return a string similar to
            <c>assertion "`code()`" failed: file "`file()`", line \`line()\`</c>
            (parts of this information will be omitted if they were not
            specified at construction).
    */
    virtual char const* what() const BOOST_NOEXCEPT_OR_NOTHROW;

    /**
    Return assertion file.
    @return Return file as specified at construction (or @c "" if no file was
            specified).
    */
    char const* const file() const;
    
    /**
    Return assertion line number.
    @return Return line number as specified at construction (or @c 0 if no line
            number was specified).
    */
    unsigned long line() const;
    
    /**
    Return assertion condition code.
    @return Return assertion condition code as specified at construction (or
            @c "" if no code was specified at construction).
    */
    char const* const code() const;

/** @cond */
private:
    void init();

    char const* const file_;
    unsigned long const line_;
    char const* const code_;
    std::string what_;
/** @endcond */
};

/**
Context of assertion failure.
This is passed as a parameter of the assertion failure handler functions.
For example, it might be necessary to know the kind of operation that threw an
assertion failure to make sure exception are never thrown by destructors even
when contract failures are handled by throwing exceptions instead of terminating
the program (default).
@see @RefSect{advanced_topics, Advanced Topics}.
*/
enum from {
    /** Assertion failed in constructor contract. */
    from_constructor,
    /** Assertion failed in destructor contract. */
    from_destructor,
    /** Assertion failed in function (member or not) contract. */
    from_function
};

/**
Typef all assertion failure handler functions.
<b>Rationale:</b> Using Boost.Function to handle also lambdas, binds, etc.
@see @RefSect{advanced_topics, Advanced Topics}.
*/
typedef boost::function<void (from)> assertion_failure_handler;

/**
Set the precondition failure handler.
@param f New precondition failure handler functor.
@return Old precondition failure handler functor.
@see @RefSect{advanced_topics, Advanced Topics}.
*/
assertion_failure_handler BOOST_CONTRACT_DETAIL_DECLSPEC
set_precondition_failure(assertion_failure_handler const& f)
        BOOST_NOEXCEPT_OR_NOTHROW;

/**
Return the precondition failure handler.
@return Current precondition failure handler functor.
@see @RefSect{advanced_topics, Advanced Topics}.
*/
assertion_failure_handler BOOST_CONTRACT_DETAIL_DECLSPEC
get_precondition_failure() BOOST_NOEXCEPT_OR_NOTHROW;

/**
Call the precondition hander functor.
This is typically only called internally by this library.
@param where Context of precondition failure.
*/
void BOOST_CONTRACT_DETAIL_DECLSPEC
precondition_failure(from where) /* can throw */;

/**
Set the postcondition failure handler.
@param f New postcondition failure handler functor.
@return Old postcondition failure handler functor.
@see @RefSect{advanced_topics, Advanced Topics}.
*/
assertion_failure_handler BOOST_CONTRACT_DETAIL_DECLSPEC
set_postcondition_failure(assertion_failure_handler const& f)
        BOOST_NOEXCEPT_OR_NOTHROW;

/**
Return the postcondition failure handler.
@return Current postcondition failure handler functor.
@see @RefSect{advanced_topics, Advanced Topics}.
*/
assertion_failure_handler BOOST_CONTRACT_DETAIL_DECLSPEC
get_postcondition_failure() BOOST_NOEXCEPT_OR_NOTHROW;

/**
Call the postcondition hander functor.
This is typically only called internally by this library.
@param where Context of postcondition failure.
*/
void BOOST_CONTRACT_DETAIL_DECLSPEC
postcondition_failure(from where) /* can throw */;

/**
Set the entry invariant failure handler.
@param f New entry invariant failure handler functor.
@return Old entry invariant failure handler functor.
@see @RefSect{advanced_topics, Advanced Topics}.
*/
assertion_failure_handler BOOST_CONTRACT_DETAIL_DECLSPEC
set_entry_invariant_failure(assertion_failure_handler const& f)
        BOOST_NOEXCEPT_OR_NOTHROW;

/**
Return the entry invariant failure handler.
@return Current entry invariant failure handler functor.
@see @RefSect{advanced_topics, Advanced Topics}.
*/
assertion_failure_handler BOOST_CONTRACT_DETAIL_DECLSPEC
get_entry_invariant_failure() BOOST_NOEXCEPT_OR_NOTHROW;

/**
Call the entry invariant hander functor.
This is typically only called internally by this library.
@param where Context of entry invariant failure.
*/
void BOOST_CONTRACT_DETAIL_DECLSPEC
entry_invariant_failure(from where) /* can throw */;

/**
Set the exit invariant failure handler.
@param f New exit invariant failure handler functor.
@return Old exit invariant failure handler functor.
@see @RefSect{advanced_topics, Advanced Topics}.
*/
assertion_failure_handler BOOST_CONTRACT_DETAIL_DECLSPEC
set_exit_invariant_failure(assertion_failure_handler const& f)
        BOOST_NOEXCEPT_OR_NOTHROW;

/**
Return the exit invariant failure handler.
@return Current exit invariant failure handler functor.
@see @RefSect{advanced_topics, Advanced Topics}.
*/
assertion_failure_handler
BOOST_CONTRACT_DETAIL_DECLSPEC get_exit_invariant_failure()
        BOOST_NOEXCEPT_OR_NOTHROW;

/**
Call the exit invariant hander functor.
This is typically only called internally by this library.
@param where Context of exit invariant failure.
*/
void BOOST_CONTRACT_DETAIL_DECLSPEC
exit_invariant_failure(from where) /* can throw */;

/**
Set the both entry and exit invariant failure handlers at once (for
convenience).
@param f New invariant failure handler functor.
@see @RefSect{advanced_topics, Advanced Topics}.
*/
void BOOST_CONTRACT_DETAIL_DECLSPEC
set_invariant_failure(assertion_failure_handler const& f)
        BOOST_NOEXCEPT_OR_NOTHROW;

/**
Set the all (precondition, postcondition, entry and exit invariant) failure
handlers at once (for convenience).
@param f New failure handler functor.
@see @RefSect{advanced_topics, Advanced Topics}.
*/
void BOOST_CONTRACT_DETAIL_DECLSPEC
set_failure(assertion_failure_handler const& f) BOOST_NOEXCEPT_OR_NOTHROW;

} } // namespace

#if BOOST_CONTRACT_HEADER_ONLY
    #include <boost/contract/detail/inlined/core/exception.hpp>
#endif

#endif // #include guard

