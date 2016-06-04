
#ifndef BOOST_CONTRACT_EXCEPTION_HPP_
#define BOOST_CONTRACT_EXCEPTION_HPP_

// Copyright (C) 2008-2016 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0 (see accompanying
// file LICENSE_1_0.txt or a copy at http://www.boost.org/LICENSE_1_0.txt).
// See: http://www.boost.org/doc/libs/release/libs/contract/doc/html/index.html

/** @file
Exceptions and other facilities to handle contract assertion failures.
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

#ifdef DOXYGEN
// Needed for `std::` prefix to show (but remove via `EXCLUDE_SYMBOLS=std`).
namespace std {
    class exception {};
    class bad_cast {};
}
#endif

namespace boost { namespace contract {

/**
Public base class for all this library exceptions.
This class does not inherit from @c std::exception because derived exceptions
will (inheriting from @c std::exception, @c std::bad_cast, etc.).
@see @RefSect{advanced_topics, Advanced Topics}
*/
class BOOST_CONTRACT_DETAIL_DECLSPEC exception {
public:
    /**
    Destruct this object.
    @b Throws: @c noexcept (or @c throw() if no C++11).
    */
    virtual ~exception() /** @cond */ BOOST_NOEXCEPT_OR_NOTHROW /** @endcond */;
};

/**
Exception thrown when inconsistent return values are passed to overridden
virtual public functions.
This exception is internally thrown by this library when programmers specify
return values for overriding public functions in derived classes that are
inconsistent with the return types of the virtual public functions being
overridden from base classes.

@b Rationale:   The @c boost::bad_any_cast exception could not be used because
                it does not print the from- and to- type names (so it is not
                descriptive enough).
@see @RefSect{tutorial, Tutorial}
*/
class BOOST_CONTRACT_DETAIL_DECLSPEC bad_virtual_result_cast : // Copy (as str).
        public std::bad_cast, public boost::contract::exception {
public:
    /**
    Construct this object with the name of the from- and to- types.
    @param from_type_name Name of the from-type (source).
    @param to_type_name Name of the to-type (destination).
    */
    explicit bad_virtual_result_cast(char const* from_type_name,
            char const* to_type_name);

    /**
    Destruct this object.
    @b Throws: @c noexcept (or @c throw() if no C++11).
    */
    virtual ~bad_virtual_result_cast()
            /** @cond */ BOOST_NOEXCEPT_OR_NOTHROW /** @endcond */;

    /**
    Description for this error (containing both from- and to- type names).
    @b Throws: @c noexcept (or @c throw() if no C++11).
    */
    virtual char const* what() const
            /** @cond */ BOOST_NOEXCEPT_OR_NOTHROW /** @endcond */;

/** @cond */
private:
    std::string what_;
/** @endcond */
};

/**
Exception typically used to report a contract assertion failure.
This exception is thrown by code expanded by @RefMacro{BOOST_CONTRACT_ASSERT}
(but it can also be thrown by user code programmed manually without that macro).
This exception is typically used to report contract assertion failures because
it contains detailed information about the assertion file name, line number,
condition source code, etc. (so it provides detailed error messages), but any
other exception can be used to report a contract assertion failure. This library
will call the appropriate contract failure handler function
(@RefFunc{boost::contract::precondition_failure}, etc.) when this or any other
exception is thrown while checking contracts (by default, these failure handler
functions terminate the program but they can be customized to take any other
action).
@see @RefSect{advanced_topics, Advanced Topics}
*/
class BOOST_CONTRACT_DETAIL_DECLSPEC assertion_failure : // Copy (as str, etc.).
        public std::exception, public boost::contract::exception {
public:
    /**
    Construct this object with the asserted condition file name, line number,
    and source code text (all optional).
    This constructor can also be used to specify no information (default
    constructor), or to specify only file name and line number but not source
    code text (because of its parameter default values).
    @param file Name of the file containing the assertion (usually set using
                <c>__FILE__</c>).
    @param line Number of the line containing the assertion (usually set using
                <c>__LINE__</c>).
    @param code Text listing the source code of the asserted condition.
    */
    explicit assertion_failure(char const* const file = "",
            unsigned long const line = 0, char const* const code = "");

    /**
    Construct this object with the asserted condition source code text only.
    @param code Text listing the source code of the asserted condition.
    */
    explicit assertion_failure(char const* const code);
    
    /**
    Destruct this object.
    @b Throws: @c noexcept (or @c throw() if no C++11).
    */
    virtual ~assertion_failure()
            /** @cond */ BOOST_NOEXCEPT_OR_NOTHROW /** @endcond */;

    /**
    String describing the failed assertion.
    @b Throws: @c noexcept (or @c throw() if no C++11).
    @return A string formatted similarly to the following:
      <c>assertion "`code()`" failed: file "`file()`", line \`line()\`</c>.
            File, line, and code will be omitted from this string if they were
            not specified at construction.
    */
    virtual char const* what() const
            /** @cond */ BOOST_NOEXCEPT_OR_NOTHROW /** @endcond */;

    /**
    Name of the file listing the assertion.
    @return File as specified at construction (or @c "" if no file was
            specified).
    */
    char const* const file() const;
    
    /**
    Number of the line listing the assertion.
    @return Line number as specified at construction (or @c 0 if no line number
            was specified).
    */
    unsigned long line() const;
    
    /**
    Text listing the source code of the asserted condition.
    @return Asserted condition source code as specified at construction (or
            @c "" if no code was specified).
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
Represent the operation where the contract assertion failed.
This is passed as a parameter to the assertion failure handler functions.
For example, it might be necessary to know in which operation an assertion
failed to make sure exceptions are never thrown from destructors, not even
when contract failure handlers are reprogrammed by users to throw exceptions
instead of terminating the program.
do).
@see @RefSect{advanced_topics, Advanced Topics}
*/
enum from {
    /** Assertion failed when checking constructor contracts. */
    from_constructor,
    /** Assertion failed when checking destructor contracts. */
    from_destructor,
    /** Assertion failed when checking function (member or not) contracts. */
    from_function
};

/**
Type of all assertion failure handler functions.
As specified by this type, assertion failure handler functions must be functors
returning @c void and taking a single parameter of type
@RefEnum{boost::contract::from}.

@b Rationale: Using Boost.Function allows to handle any functor (functions but
also lambdas, binds, etc.).
@see @RefSect{advanced_topics, Advanced Topics}
*/
typedef boost::function<void (from)> assertion_failure_handler;

/**
Set the precondition failure handler.
Set a new precondition failure handler and return the old one.

@b Throws: @c noexcept (or @c throw() if no C++11).
@param f New precondition failure handler functor.
@return Old precondition failure handler functor.
@see @RefSect{advanced_topics, Advanced Topics}
*/
assertion_failure_handler
/** @cond */ BOOST_CONTRACT_DETAIL_DECLSPEC /** @endcond */
set_precondition_failure(assertion_failure_handler const& f)
        /** @cond */ BOOST_NOEXCEPT_OR_NOTHROW /** @endcond */;

/**
Return the precondition failure handler.
This is often called only internally by this library.

@b Throws: @c noexcept (or @c throw() if no C++11).
@return Precondition failure handler functor.
@see @RefSect{advanced_topics, Advanced Topics}
*/
assertion_failure_handler
/** @cond */ BOOST_CONTRACT_DETAIL_DECLSPEC /** @endcond */
get_precondition_failure()
        /** @cond */ BOOST_NOEXCEPT_OR_NOTHROW /** @endcond */;

/**
Call the precondition hander functor.
This is often called only internally by this library.

@b Throws:  This can throw in case programmers specify a failure handler that
            throws exceptions on precondition failures (not the default).
@param where    Operation that failed preconditions (note that destructors
                never have preconditions).
            
*/
void /** @cond */ BOOST_CONTRACT_DETAIL_DECLSPEC /** @endcond */
precondition_failure(from where) /* can throw */;

/**
Set the postcondition failure handler.
Set a new postcondition failure handler and return the old one.

@b Throws: @c noexcept (or @c throw() if no C++11).
@param f New postcondition failure handler functor.
@return Old postcondition failure handler functor.
@see @RefSect{advanced_topics, Advanced Topics}
*/
assertion_failure_handler
/** @cond */ BOOST_CONTRACT_DETAIL_DECLSPEC /** @endcond */
set_postcondition_failure(assertion_failure_handler const& f)
        /** @cond */ BOOST_NOEXCEPT_OR_NOTHROW /** @endcond */;

/**
Return the postcondition failure handler.
This is often called only internally by this library.

@b Throws: @c noexcept (or @c throw() if no C++11).
@return Postcondition failure handler functor.
@see @RefSect{advanced_topics, Advanced Topics}
*/
assertion_failure_handler
/** @cond */ BOOST_CONTRACT_DETAIL_DECLSPEC /** @endcond */
get_postcondition_failure()
        /** @cond */ BOOST_NOEXCEPT_OR_NOTHROW /** @endcond */;

/**
Call the postcondition hander functor.
This is often called only internally by this library.

@b Throws:  This can throw in case programmers specify a failure handler that
            throws exceptions on postcondition failures (not the default).
@param where    Operation that failed postconditions (e.g., this might be useful
                to program failure handler functors that never throw from
                destructors, not even when they are programmed by users to throw
                exceptions instead of terminating the program).
*/
void /** @cond */ BOOST_CONTRACT_DETAIL_DECLSPEC /** @endcond */
postcondition_failure(from where) /* can throw */;

/**
Set the entry invariant failure handler.
Set a new entry invariant failure handler and return the old one.

@b Throws: @c noexcept (or @c throw() if no C++11).
@param f New entry invariant failure handler functor.
@return Old entry invariant failure handler functor.
@see @RefSect{advanced_topics, Advanced Topics}
*/
assertion_failure_handler
/** @cond */ BOOST_CONTRACT_DETAIL_DECLSPEC /** @endcond */
set_entry_invariant_failure(assertion_failure_handler const& f)
        /** @cond */ BOOST_NOEXCEPT_OR_NOTHROW /** @endcond */;

/**
Return the entry invariant failure handler.
This is often called only internally by this library.

@b Throws: @c noexcept (or @c throw() if no C++11).
@return Entry invariant failure handler functor.
@see @RefSect{advanced_topics, Advanced Topics}
*/
assertion_failure_handler
/** @cond */ BOOST_CONTRACT_DETAIL_DECLSPEC /** @endcond */
get_entry_invariant_failure()
        /** @cond */ BOOST_NOEXCEPT_OR_NOTHROW /** @endcond */;

/**
Call the entry invariant hander functor.
This is often called only internally by this library.

@b Throws:  This can throw in case programmers specify a failure handler that
            throws exceptions on entry invariant failures (not the default).
@param where    Operation that failed entry invariants (e.g., this might be
                useful to program failure handler functors that never throw from
                destructors, not even when they are programmed by users to throw
                exceptions instead of terminating the program).
*/
void /** @cond */ BOOST_CONTRACT_DETAIL_DECLSPEC /** @endcond */
entry_invariant_failure(from where) /* can throw */;

/**
Set the exit invariant failure handler.
Set a new exit invariant failure handler and return the old one.

@b Throws: @c noexcept (or @c throw() if no C++11).
@param f New exit invariant failure handler functor.
@return Old exit invariant failure handler functor.
@see @RefSect{advanced_topics, Advanced Topics}
*/
assertion_failure_handler
/** @cond */ BOOST_CONTRACT_DETAIL_DECLSPEC /** @endcond */
set_exit_invariant_failure(assertion_failure_handler const& f)
        /** @cond */ BOOST_NOEXCEPT_OR_NOTHROW /** @endcond */;

/**
Return the exit invariant failure handler.
This is often called only internally by this library.

@b Throws: @c noexcept (or @c throw() if no C++11).
@return Exit invariant failure handler functor.
@see @RefSect{advanced_topics, Advanced Topics}
*/
assertion_failure_handler
/** @cond */ BOOST_CONTRACT_DETAIL_DECLSPEC /** @endcond */
get_exit_invariant_failure()
        /** @cond */ BOOST_NOEXCEPT_OR_NOTHROW /** @endcond */;

/**
Call the exit invariant hander functor.
This is often called only internally by this library.

@b Throws:  This can throw in case programmers specify a failure handler that
            throws exceptions on exit invariant failures (not the default).
@param where    Operation that failed exit invariants (e.g., this might be
                useful to program failure handler functors that never throw from
                destructors, not even when they are programmed by users to throw
                exceptions instead of terminating the program).
*/
void /** @cond */ BOOST_CONTRACT_DETAIL_DECLSPEC /** @endcond */
exit_invariant_failure(from where) /* can throw */;

/**
Set both entry and exit invariant failure handlers at once (for convenience).
This is equivalent to calling both
@RefFunc{boost::contract::set_entry_invariant_failure}<c>(f)</c> and
@RefFunc{boost::contract::set_exit_invariant_failure}<c>(f)</c>.

@b Throws: @c noexcept (or @c throw() if no C++11).
@param f New invariant failure handler functor.
@see @RefSect{advanced_topics, Advanced Topics}
*/
void /** @cond */ BOOST_CONTRACT_DETAIL_DECLSPEC /** @endcond */
set_invariant_failure(assertion_failure_handler const& f)
        /** @cond */ BOOST_NOEXCEPT_OR_NOTHROW /** @endcond */;

/**
Set the all contract failure handlers at once (for convenience).
This is equivalent to calling
@RefFunc{boost::contract::set_entry_invariant_failure}<c>(f)</c>,
@RefFunc{boost::contract::set_precondition_failure}<c>(f)</c>,
@RefFunc{boost::contract::set_exit_invariant_failure}<c>(f)</c>, and
@RefFunc{boost::contract::set_postcondition_failure}<c>(f)</c>.

@b Throws: @c noexcept (or @c throw() if no C++11).
@param f New contract failure handler functor.
@see @RefSect{advanced_topics, Advanced Topics}
*/
void /** @cond */ BOOST_CONTRACT_DETAIL_DECLSPEC /** @endcond */
set_failure(assertion_failure_handler const& f)
        /** @cond */ BOOST_NOEXCEPT_OR_NOTHROW /** @endcond */;

} } // namespace

/** @cond */
#if BOOST_CONTRACT_HEADER_ONLY
    #include <boost/contract/detail/inlined/core/exception.hpp>
#endif
/** @endcond */

#endif // #include guard

