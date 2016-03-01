
#ifndef BOOST_CONTRACT_EXCEPTION_HPP_
#define BOOST_CONTRACT_EXCEPTION_HPP_

// Copyright (C) 2008-2016 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0 (see accompanying
// file LICENSE_1_0.txt or a copy at http://www.boost.org/LICENSE_1_0.txt).
// See: http://www.boost.org/doc/libs/release/libs/contract/doc/html/index.html

/** @file */

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

// Placeholder base class to group all this lib exceptions.
// IMPORTANT: Must not inherit from std::exception as derived exceptions will.
class BOOST_CONTRACT_DETAIL_DECLSPEC exception {
public:
    virtual ~exception();
};

// Rationale: boost::bad_any_cast exception does not print from/to type names,
// so throw custom exception.
class BOOST_CONTRACT_DETAIL_DECLSPEC bad_virtual_result_cast : // Copy (as str).
        public std::bad_cast, public boost::contract::exception {
public:
    explicit bad_virtual_result_cast(char const* from_type_name,
            char const* to_type_name);
    virtual ~bad_virtual_result_cast();

    virtual char const* what() const BOOST_NOEXCEPT;

private:
    std::string what_;
};

class BOOST_CONTRACT_DETAIL_DECLSPEC assertion_failure : // Copy (as str, etc.).
        public std::exception, public boost::contract::exception {
public:
    explicit assertion_failure(char const* const file = "",
            unsigned long const line = 0, char const* const code = "");
    explicit assertion_failure(char const* const code);
    virtual ~assertion_failure();

    // Return something like `assertion "..." failed: file "...", line ...`.
    virtual char const* what() const BOOST_NOEXCEPT;

    char const* const file() const;
    unsigned long line() const;
    char const* const code() const;

private:
    void init();

    char const* const file_;
    unsigned long const line_;
    char const* const code_;
    std::string what_;
};

enum from { from_constructor, from_destructor, from_function };

// Use Boost.Function to handle also lambdas, binds, etc,
typedef boost::function<void (from)> assertion_failure_handler;

assertion_failure_handler
BOOST_CONTRACT_DETAIL_DECLSPEC set_precondition_failure(
        assertion_failure_handler const& f) BOOST_NOEXCEPT_OR_NOTHROW;

assertion_failure_handler
BOOST_CONTRACT_DETAIL_DECLSPEC get_precondition_failure()
        BOOST_NOEXCEPT_OR_NOTHROW;

void BOOST_CONTRACT_DETAIL_DECLSPEC precondition_failure(from where)
        /* can throw */;

assertion_failure_handler
BOOST_CONTRACT_DETAIL_DECLSPEC set_postcondition_failure(
        assertion_failure_handler const& f) BOOST_NOEXCEPT_OR_NOTHROW;

assertion_failure_handler
BOOST_CONTRACT_DETAIL_DECLSPEC get_postcondition_failure()
        BOOST_NOEXCEPT_OR_NOTHROW;

void BOOST_CONTRACT_DETAIL_DECLSPEC postcondition_failure(from where)
        /* can throw */;

assertion_failure_handler BOOST_CONTRACT_DETAIL_DECLSPEC
set_entry_invariant_failure(assertion_failure_handler const& f)
        BOOST_NOEXCEPT_OR_NOTHROW;

assertion_failure_handler BOOST_CONTRACT_DETAIL_DECLSPEC
get_entry_invariant_failure() BOOST_NOEXCEPT_OR_NOTHROW;

void BOOST_CONTRACT_DETAIL_DECLSPEC entry_invariant_failure(from where)
        /* can throw */;

assertion_failure_handler BOOST_CONTRACT_DETAIL_DECLSPEC
set_exit_invariant_failure(assertion_failure_handler const& f)
        BOOST_NOEXCEPT_OR_NOTHROW;

assertion_failure_handler
BOOST_CONTRACT_DETAIL_DECLSPEC get_exit_invariant_failure()
        BOOST_NOEXCEPT_OR_NOTHROW;

void BOOST_CONTRACT_DETAIL_DECLSPEC exit_invariant_failure(from where)
        /* can throw */;

// Set all inv failures (entry inv and exit inv) at once.
void BOOST_CONTRACT_DETAIL_DECLSPEC set_invariant_failure(
        assertion_failure_handler const& f) BOOST_NOEXCEPT_OR_NOTHROW;

// Set all failures (pre, post, entry inv, and exit int) at once.
void BOOST_CONTRACT_DETAIL_DECLSPEC set_failure(
        assertion_failure_handler const& f) BOOST_NOEXCEPT_OR_NOTHROW;

} } // namespace

#if BOOST_CONTRACT_HEADER_ONLY
    #include <boost/contract/detail/inlined/core/exception.hpp>
#endif

#endif // #include guard

