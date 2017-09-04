
#ifndef DBC_EXCEPTION_HPP_
#define DBC_EXCEPTION_HPP_

#include "config.hpp"
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
        std::cerr << "Terminating because destrcutor thrown unhandeled "
                << "invariant violation exception" << std::endl;
        std::terminate();
#elif defined DBC_CONFIG_ENABLE_EXITING_ASSERTIONS
        std::cerr << "Exiting with code 1 because destrcutor thrown "
                << "unhandeled invariant violation exception" << std::endl;
        ::exit(1);
#else
        // If user does not want assertion to terminate or exit, we just log
        // an error. However, this is very dangerous as the program is now in
        // a bad state and we are continuing its execution...
        std::clog << "Ignoring unhandeled invariant violation exception "
                << "thrown in destructor -- program might be in a bad state" 
                << std::endl;
#endif
    }
}

} // namespace dbc

#endif // DBC_EXCEPTION_HPP_

