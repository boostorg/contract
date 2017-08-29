// Copyright (C) 2009-2010 Lorenzo Caminiti.
// Use, modification, and distribution is subject to the
// Contract++ Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt.)

#ifndef CONTRACT_ASSERT_HPP_
#define CONTRACT_ASSERT_HPP_

#include "aux_/assert.hpp"
#include <stdexcept>
#include <sstream>
#include <string>

// IMPORTANT: Most of these functions do no throw so they comply with
// C++ STL exception safety requirements.

#define CONTRACT_ASSERT_MSG(boolean_condition, string_description) \
    /* must use `!` as MSVC does not support he `not` keyword */ \
    if (!(boolean_condition)) { \
        throw ::contract::failure(__FILE__, __LINE__, \
                string_description); \
    }

#define CONTRACT_ASSERT(boolean_condition) \
    /* Do not use BOOST_PP_STRINGIZE() so condition NOT expanded */ \
    CONTRACT_ASSERT_MSG(boolean_condition, # boolean_condition)

namespace contract {

// A contract condition failure is a logic error or "bug".
class failure: public std::logic_error {
public:
    // File and line mandatory (use __FILE__ and __LINE__).
    explicit failure(char const* file, unsigned long const& line,
            char const* description = "") throw():
            std::logic_error(""), file_(file), line_(line),
            description_(description) {}

    failure(failure const& source) throw(): std::logic_error(""),
            file_(source.file_), line_(source.line_),
            description_(source.description_) {}

    virtual failure& operator=(failure const& source) throw() {
        file_ = source.file_;
        line_ = source.line_;
        description_ = source.description_;
        return *this;
    }

    virtual ~failure() throw() {}

    virtual char const* what() const throw() {
        // File and line always present when constructed (but this
        // code also handles case when they are "" and 0).
        std::ostringstream oss;
        oss << "contract";
        std::string d = description();
        // Use "'" beacuse that is what rest of terminate() msg uses.
        if ("" != d) { oss << " \"" << d << "\" "; }
        oss << "failed";
        std::string f = file();
        if ("" != f) {
            oss << " at " << f;
            unsigned long l = line();
            // Line printed only if there is also a file name.
            if (0 != l) { oss << ":" << l; }
        }
        return oss.str().c_str();
    }

    virtual char const* file() const throw() { return file_.c_str(); }

    virtual unsigned long line() const throw() { return line_; }
    
    virtual char const* description() const throw()
        { return description_.c_str(); }

private:
    std::string file_;
    unsigned long line_;
    std::string description_;
};

// Expose type from aux.
typedef aux::contract_failed_handler contract_failed_handler;

// Inlining functions also to avoid multiple definitions error.

// Block Invariant //

inline contract_failed_handler set_block_invariant_failed(
        contract_failed_handler handler) throw() {
    return aux::block_invariant_failed_handler = handler;
}

// In general this could throw for user defined handlers.
inline void block_invariant_failed(from const& where)
    { aux::block_invariant_failed_handler(where); }

// Class Invariant //

inline contract_failed_handler set_class_invariant_failed(
        contract_failed_handler handler) throw() {
    return aux::class_invariant_failed_handler = handler;
}

// In general this could throw for user defined handlers.
inline void class_invariant_failed(from const& where)
    { aux::class_invariant_failed_handler(where); }

// Precondition //

inline contract_failed_handler set_precondition_failed(
        contract_failed_handler handler) throw() {
    return aux::precondition_failed_handler = handler; 
}

// In general this could throw for user defined handlers.
inline void precondition_failed(from const& where)
    { aux::precondition_failed_handler(where); }

// Postcondition //

inline contract_failed_handler set_postcondition_failed(
        contract_failed_handler handler) throw() {
    return aux::postcondition_failed_handler = handler;
}

// In general this could throw for user defined handlers.
inline void postcondition_failed(from const& where)
    { aux::postcondition_failed_handler(where); }

} // namespace

#endif // #include guard

