
#ifndef BOOST_CONTRACT_DETAIL_INLINED_EXCEPTION_HPP_
#define BOOST_CONTRACT_DETAIL_INLINED_EXCEPTION_HPP_

// Copyright (C) 2008-2016 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0 (see accompanying
// file LICENSE_1_0.txt or a copy at http://www.boost.org/LICENSE_1_0.txt).
// See: http://www.boost.org/doc/libs/release/libs/contract/doc/html/index.html

#include <boost/contract/core/exception.hpp>
#ifndef BOOST_CONTRACT_DISABLE_THREADS
    #include <boost/thread/lock_guard.hpp>
    #include <boost/thread/mutex.hpp>
#endif
#include <boost/exception/diagnostic_information.hpp>
#include <boost/preprocessor/facilities/empty.hpp>
#include <string>
#include <sstream>
#include <iostream>
#include <exception>

/* PRIVATE */

#ifndef BOOST_CONTRACT_DISABLE_THREADS
    #define BOOST_CONTRACT_EXCEPTION_HANDLER_SCOPED_LOCK_(handler_mutex) \
        boost::lock_guard<boost::mutex> lock(handler_mutex);
#else
    #define BOOST_CONTRACT_EXCEPTION_HANDLER_SCOPED_LOCK_(handler_mutex) \
        /* nothing */
#endif

#define BOOST_CONTRACT_EXCEPTION_HANDLER_SET_(handler_mutex, handler_type, \
        handler, f) \
    BOOST_CONTRACT_EXCEPTION_HANDLER_SCOPED_LOCK_(handler_mutex); \
    handler_type result = handler; \
    handler = f; \
    return result;
    
#define BOOST_CONTRACT_EXCEPTION_HANDLER_GET_(handler_mutex, handler) \
    BOOST_CONTRACT_EXCEPTION_HANDLER_SCOPED_LOCK_(handler_mutex); \
    return handler;
    
#define BOOST_CONTRACT_EXCEPTION_HANDLER_(handler_mutex, handler, where) \
    BOOST_CONTRACT_EXCEPTION_HANDLER_SCOPED_LOCK_(handler_mutex); \
    handler(where);

/* CODE */

namespace boost { namespace contract {

exception::~exception() BOOST_NOEXCEPT_OR_NOTHROW {}

bad_virtual_result_cast::bad_virtual_result_cast(char const* from_type_name,
            char const* to_type_name) {
    std::ostringstream text;
    text
        << "incompatible contracted virtual function result type "
        << "conversion from '" << from_type_name << "' to '"
        << to_type_name  << "'"
    ;
    what_ = text.str();
}

bad_virtual_result_cast::~bad_virtual_result_cast() BOOST_NOEXCEPT_OR_NOTHROW {}

char const* bad_virtual_result_cast::what() const BOOST_NOEXCEPT_OR_NOTHROW {
    return what_.c_str();
}

assertion_failure::assertion_failure(char const* const file,
        unsigned long const line, char const* const code) :
    file_(file), line_(line), code_(code)
{ init(); }

assertion_failure::assertion_failure(char const* const code) :
    file_(""), line_(0), code_(code)
{ init(); }

assertion_failure::~assertion_failure() BOOST_NOEXCEPT_OR_NOTHROW {}

char const* assertion_failure::what() const BOOST_NOEXCEPT_OR_NOTHROW {
    return what_.c_str();
}

char const* const assertion_failure::file() const { return file_; }

unsigned long assertion_failure::line() const { return line_; }

char const* const assertion_failure::code() const { return code_; }

void assertion_failure::init() {
    std::ostringstream text;
    text << "assertion";
    if(std::string(code_) != "") text << " \"" << code_ << "\"";
    text << " failed";
    if(std::string(file_) != "") {
        text << ": file \"" << file_ << "\"";
        if(line_ != 0) text << ", line " << line_;
    }
    what_ = text.str();
}

namespace exception_ {
    enum failure_key {
        check_key, pre_key, post_key, entry_inv_key, exit_inv_key
    };

    template<failure_key Key>
    void default_handler() {
        std::string k = "";
        switch(Key) {
            case check_key: k = "check "; break;
            case pre_key: k = "precondition "; break;
            case post_key: k = "postcondition "; break;
            case entry_inv_key: k = "entry invariant "; break;
            case exit_inv_key: k = "exit invariant "; break;
            // No default (so compiler warning/error on missing enum case).
        }
        try { throw; }
        catch(boost::contract::assertion_failure const& error) {
            // what = "assertion '...' failed: ...".
            std::cerr << k << error.what() << std::endl;
        } catch(...) {
            std::cerr << k << "threw following exception:" << std::endl
                    << boost::current_exception_diagnostic_information();
        }
        std::terminate(); // Default handlers log and call terminate.
    }
    
    template<failure_key Key>
    void default_from_handler(from) { default_handler<Key>(); }

    #ifndef BOOST_CONTRACT_DISABLE_THREAD
        boost::mutex check_failure_mutex;
    #endif
    failure_handler check_failure_handler = &default_handler<check_key>;

    #ifndef BOOST_CONTRACT_DISABLE_THREADS
        boost::mutex pre_failure_mutex;
    #endif
    from_failure_handler pre_failure_handler = &default_from_handler<pre_key>;
    
    #ifndef BOOST_CONTRACT_DISABLE_THREADS
        boost::mutex post_failure_mutex;
    #endif
    from_failure_handler post_failure_handler = &default_from_handler<post_key>;
    
    #ifndef BOOST_CONTRACT_DISABLE_THREADS
        boost::mutex entry_inv_failure_mutex;
    #endif
    from_failure_handler entry_inv_failure_handler =
            &default_from_handler<entry_inv_key>;
    
    #ifndef BOOST_CONTRACT_DISABLE_THREADS
        boost::mutex exit_inv_failure_mutex;
    #endif
    from_failure_handler exit_inv_failure_handler =
            &default_from_handler<exit_inv_key>;
}

// IMPORTANT: Following func cannot be declared inline (on GCC, Clang, etc.) and
// their definition code should not be changed by contract on/off macros.

failure_handler set_check_failure(failure_handler const& f)
        BOOST_NOEXCEPT_OR_NOTHROW {
    BOOST_CONTRACT_EXCEPTION_HANDLER_SET_(exception_::check_failure_mutex,
            failure_handler, exception_::check_failure_handler, f);
}

failure_handler get_check_failure() BOOST_NOEXCEPT_OR_NOTHROW {
    BOOST_CONTRACT_EXCEPTION_HANDLER_GET_(exception_::check_failure_mutex,
            exception_::check_failure_handler);
}

void check_failure() /* can throw */ {
    BOOST_CONTRACT_EXCEPTION_HANDLER_(exception_::check_failure_mutex,
            exception_::check_failure_handler, BOOST_PP_EMPTY())
}

from_failure_handler set_precondition_failure(from_failure_handler const& f)
        BOOST_NOEXCEPT_OR_NOTHROW {
    BOOST_CONTRACT_EXCEPTION_HANDLER_SET_(exception_::pre_failure_mutex,
            from_failure_handler, exception_::pre_failure_handler, f);
}

from_failure_handler get_precondition_failure() BOOST_NOEXCEPT_OR_NOTHROW {
    BOOST_CONTRACT_EXCEPTION_HANDLER_GET_(exception_::pre_failure_mutex,
            exception_::pre_failure_handler);
}

void precondition_failure(from where) /* can throw */ {
    BOOST_CONTRACT_EXCEPTION_HANDLER_(exception_::pre_failure_mutex,
            exception_::pre_failure_handler, where)
}

from_failure_handler set_postcondition_failure(from_failure_handler const& f)
        BOOST_NOEXCEPT_OR_NOTHROW {
    BOOST_CONTRACT_EXCEPTION_HANDLER_SET_(exception_::post_failure_mutex,
            from_failure_handler, exception_::post_failure_handler, f);
}

from_failure_handler get_postcondition_failure() BOOST_NOEXCEPT_OR_NOTHROW {
    BOOST_CONTRACT_EXCEPTION_HANDLER_GET_(exception_::post_failure_mutex,
            exception_::post_failure_handler);
}

void postcondition_failure(from where) /* can throw */ {
    BOOST_CONTRACT_EXCEPTION_HANDLER_(exception_::post_failure_mutex,
            exception_::post_failure_handler, where);
}

from_failure_handler set_entry_invariant_failure(from_failure_handler const& f)
        BOOST_NOEXCEPT_OR_NOTHROW {
    BOOST_CONTRACT_EXCEPTION_HANDLER_SET_(exception_::entry_inv_failure_mutex,
            from_failure_handler, exception_::entry_inv_failure_handler, f);
}

from_failure_handler get_entry_invariant_failure() BOOST_NOEXCEPT_OR_NOTHROW {
    BOOST_CONTRACT_EXCEPTION_HANDLER_GET_(exception_::entry_inv_failure_mutex,
            exception_::entry_inv_failure_handler);
}

void entry_invariant_failure(from where) /* can throw */ {
    BOOST_CONTRACT_EXCEPTION_HANDLER_(exception_::entry_inv_failure_mutex,
            exception_::entry_inv_failure_handler, where);
}

from_failure_handler set_exit_invariant_failure(from_failure_handler const& f)
        BOOST_NOEXCEPT_OR_NOTHROW {
    BOOST_CONTRACT_EXCEPTION_HANDLER_SET_(exception_::exit_inv_failure_mutex,
            from_failure_handler, exception_::exit_inv_failure_handler, f);
}

from_failure_handler get_exit_invariant_failure() BOOST_NOEXCEPT_OR_NOTHROW {
    BOOST_CONTRACT_EXCEPTION_HANDLER_GET_(exception_::exit_inv_failure_mutex,
            exception_::exit_inv_failure_handler);
}

void exit_invariant_failure(from where) /* can throw */ {
    BOOST_CONTRACT_EXCEPTION_HANDLER_(exception_::exit_inv_failure_mutex,
            exception_::exit_inv_failure_handler, where);
}

void set_invariant_failure(from_failure_handler const& f)
        BOOST_NOEXCEPT_OR_NOTHROW {
    set_entry_invariant_failure(f);
    set_exit_invariant_failure(f);
}

} } // namespace

#endif // #include guard

