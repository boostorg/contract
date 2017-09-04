/**
 * @file
 * @author Copyright (C) 2009 Lorenzo Caminiti.
 *  Distributed under DBC++ Software License (see file LICENSE_1_0.txt).
 */

#ifndef DBC_EXCEPTION_HPP_
#define DBC_EXCEPTION_HPP_

#include "detail/pp/defines.hpp" // Must be 1st include.
#include "config.hpp"
#include "detail/logging.hpp"
#include <stdexcept>
#include <string>
#include <iostream>

#ifdef DBC

#define DBC_RETHROW_VIOLATION_AS_(rethrow_violation_type, code) { \
    try { code; } \
    catch (::dbc::condition_violation& ex) \
            { throw ::dbc::rethrow_violation_type(ex.what()); } \
    /* leave other exceptions uncathed */ \
}

#endif // DBC

// Following must be present regardless of DBC #definition.

namespace dbc {

// Exceptions //

class condition_violation: public std::logic_error {
public:
    explicit condition_violation(const std::string& what): 
            std::logic_error(what) {}
};

class precondition_violation: public condition_violation {
public:
    explicit precondition_violation(const std::string& what): 
            condition_violation(what) {}
};

class postcondition_violation: public condition_violation {
public:
    explicit postcondition_violation(const std::string& what): 
            condition_violation(what) {}
};

class invariant_violation: public condition_violation {
public:
    explicit invariant_violation(const std::string& what): 
            condition_violation(what) {}
};

class variant_violation: public condition_violation {
public:
    explicit variant_violation(const std::string& what): 
            condition_violation(what) {}
};

// Broken Destructor Handler //

// This follows std::terminate() handling mechanism and conventions (also, it's
// defined here as std::terminate() handling is defined in <exception>).

/** @todo Can I specify this unthorw()? */
typedef void (*broken_destructor_invariant_handler)();

static broken_destructor_invariant_handler 
        broken_destructor_invariant_handler_ = 0;

inline broken_destructor_invariant_handler set_broken_destructor_invariant(
        broken_destructor_invariant_handler handler) {
    return (broken_destructor_invariant_handler_ = handler);
}

inline void broken_destructor_invariant() {
    if (broken_destructor_invariant_handler_) {
        broken_destructor_invariant_handler_(); 
    } else {
#if defined DBC_CONFIG_ENABLE_TERMINATING_ASSERTIONS
        // If user is accepting termination, we terminate on broken destr.
        DBC_LOG_VIOLATION_(
            log << "Terminating because destrcutor thrown unhandeled "
                    << "invariant violation exception";
        );
        std::terminate();
#elif defined DBC_CONFIG_ENABLE_EXITING_ASSERTIONS
        // Otherwise, if user is accepting exiting, we exit on broken destr.
        const int exit_code = 1;
        DBC_LOG_VIOLATION_(
            log << "Exiting with code " << exit_code 
                    << " because destrcutor thrown unhandeled invariant "
                    << "violation exception";
        );
        ::exit(exit_code);
#else
        // Otherwise, if user is not accepting DBC assertion neither terminate
        // nor exit, we just log a message. However, this is very dangerous as 
        // the program is now in a bad state and we are continuing its 
        // execution...
        DBC_LOG_VIOLATION_(
            log << "Ignoring unhandeled invariant violation exception "
                    << "thrown in destructor -- program might be in a bad "
                    << "state";
        );
#endif
    }
}

} // namespace dbc

#endif // DBC_EXCEPTION_HPP_

