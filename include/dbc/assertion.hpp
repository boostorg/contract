/**
 * @file
 * @author Copyright (C) 2009 Lorenzo Caminiti.
 *  Distributed under DBC++ Software License (see file LICENSE_1_0.txt).
 */

#ifndef DBC_ASSERTION_HPP_
#define DBC_ASSERTION_HPP_

#include "detail/pp/defines.hpp" // Must be 1st include.
#include "config.hpp"

#if defined DBC_DOC

#define DBC_ASSERT(condition, label) \
    DBC_CONFIG_DOC_ASSERTION(condition, label)
#define DBC_ASSERT_STREAM(condition, label, stream_error_code) \
    DBC_CONFIG_DOC_ASSERTION(condition, label)

#elif !defined DBC

#define DBC_ASSERT(condition, label)
#define DBC_ASSERT_STREAM(condition, label, stream_error_code)

#else // DBC

#include "exception.hpp"
#include "detail/logging.hpp"
#include <string>
#include <sstream>
#include <iostream>

#if DBC_CONFIG_DEFAULT_ON_ASSERTION_VIOLATION == \
        DBC_DEFAULT_RAISE_ON_ASSERTION_VIOLATION
#   define DBC_ASSERTION_VIOLATION_ACTION_() raise()
#elif DBC_CONFIG_DEFAULT_ON_ASSERTION_VIOLATION == \
        DBC_DEFAULT_EXIT_ON_ASSERTION_VIOLATION
#   define DBC_ASSERTION_VIOLATION_ACTION_() exit(1)
#elif DBC_CONFIG_DEFAULT_ON_ASSERTION_VIOLATION == \
        DBC_DEFAULT_TERMINATE_ON_ASSERTION_VIOLATION
#   define DBC_ASSERTION_VIOLATION_ACTION_() terminate()
#endif

#define DBC_ASSERT(condition, label) { \
    ::dbc::assertion(condition, label, __FILE__, __LINE__, \
        #condition).DBC_ASSERTION_VIOLATION_ACTION_(); \
}

#define DBC_ASSERT_STREAM(condition, label, stream_error_code) { \
    bool dbc_passed_ = (condition); \
    if (!dbc_passed_) { \
        /* This assertion always fails as cond is false. */ \
        ::dbc::oassertionstream err(false, label, __FILE__, __LINE__, \
                #condition); \
        /* User stream code might also throw, exit, terminate, etc. */ \
        { stream_error_code; } /* code only executed if false cond */ \
        /* This check always fails throwing the exception. */ \
        err.DBC_ASSERTION_VIOLATION_ACTION_(); \
    } else if (::dbc::log_level_ > ::dbc::LOG_LEVEL_VIOLATION) { \
        /* This assertion never fails as cond is true, but logs a msg. */ \
        ::dbc::oassertionstream(true, label, __FILE__, __LINE__, \
                #condition).DBC_ASSERTION_VIOLATION_ACTION_(); \
    } \
}

namespace dbc {

class assertion {
public:
    // Instance //

    explicit assertion(const bool& condition = true, 
            const std::string& label = "",
            const char* file = "", const int& line = 0, 
            const std::string& code = ""):
            condition_(condition), label_(label),
            file_(file), line_(line), code_(code) {}
    virtual ~assertion() {}

    // Accessors //

    virtual void condition(const bool& the_condition) 
        { condition_ = the_condition; }
    virtual bool condition() const { return condition_; }

    virtual void label(const std::string& the_label) { label_ = the_label; }
    virtual std::string label() const { return label_; }

    virtual void at(const char* file, const int& line) 
        { file_ = file; line_ = line; }
    virtual void at(const std::string& file, const int& line)
        { at(file.c_str(), line); }
    virtual std::string file() const { return file_; }
    virtual int line() const { return line_; }

    virtual void code(const std::string& the_code) { code_ = the_code; }
    virtual std::string code() const { return code_; }

    // Checking //

    void raise() const { raise<condition_violation>(); }
    
    template<typename E>
    void raise() const {
        std::string msg = log();
        if (!DBC_CONFIG_ENABLE_THROWING_ASSERTIONS) {
            DBC_LOG_DEBUG_(log << "Skipped disabled throwing assertion "
                    << msg);
        } else if (!condition()) {
            throw E(msg); 
        }
    }
    
    template<typename E>
    void raise(const E& exception) const {
        std::string msg = log();
        if (!DBC_CONFIG_ENABLE_THROWING_ASSERTIONS) {
            DBC_LOG_DEBUG_(log << "Skipped disabled throwing assertion " 
                    << msg);
        } else if (!condition()) { 
            throw exception;
        }
    }

    void exit(const int& code) const {
        std::string msg = log();
        if (!DBC_CONFIG_ENABLE_EXITING_ASSERTIONS) {
            DBC_LOG_DEBUG_(log << "Skipped disabled exiting assertion " 
                    << msg);
        } else if (!condition()) { 
            DBC_LOG_VIOLATION_(log << "Exiting with code " << code 
                    << " because: " << msg);
            ::exit(code); 
        }
    }

    void terminate() const {
        std::string msg = log();
        if (!DBC_CONFIG_ENABLE_TERMINATING_ASSERTIONS) {
            DBC_LOG_DEBUG_(log << "Skipped disabled terminating assertion " 
                    << msg);
        } else if (!condition()) { 
            DBC_LOG_VIOLATION_(log << "Terminating because: " << msg);
            std::terminate();
        }
    }

protected:
    virtual std::string what() const {
        std::ostringstream oss;
        oss << "Assertion";
        if ("" != label()) { oss << " \"" << label() << "\""; }
        oss << (condition() ? " passed" : " failed");
        if ("" != code()) { oss << " as { " << code() << "; }"; }
        if ("" != file()) {
            oss << " at " << file();
            if (0 != line()) { oss << ":" << line(); }
        }
        return oss.str();
    }

private:
    std::string log() const {
        std::string msg = what();
        if (!condition()) { DBC_LOG_VIOLATION_(log << msg); }
        else { DBC_LOG_DEBUG_(log << msg); }
        return msg;
    }

    bool condition_;
    std::string label_;
    std::string file_;
    int line_;
    std::string code_;
};

// Streams //

class oassertionstream: public assertion, public std::ostringstream {
public:
    explicit oassertionstream(const bool& condition = true, 
            const std::string& label = "",
            const char* file = "", const int& line = 0,
            const std::string& code = ""):
            assertion(condition, label, file, line, code),
            std::ostringstream() {}
    virtual ~oassertionstream() {}

protected:
    virtual std::string what() const {
        std::ostringstream oss;
        oss << "Assertion";
        if ("" != label()) { oss << " \"" << label() << "\""; }
        oss << (condition() ? " passed" : " failed");
        std::string reason = str();
        if ("" != reason) { oss << " because \"" << reason << "\""; }
        if ("" != code()) { oss << " as { " << code() << "; }"; }
        if ("" != file()) {
            oss << " at " << file();
            if (0 != line()) { oss << ":" << line(); }
        }
        return oss.str();
    }
};

/** Raise DBC default exceptions (will be automatically converted to 
 * precondition/postcondition/invariant_violation exception depending on where 
 * it was originally thrown from. */
template<typename E = condition_violation>
class raise {
public:
    friend std::ostream& operator<<(std::ostream& s, const raise& o) {
        oassertionstream& oas = dynamic_cast<oassertionstream&>(s);
        oas.raise<E>();
        return oas;
    }
};

/** Raise user specified exception (instead of DBC default one). */
template<typename E>
class uraise {
public:
    explicit uraise(const E& exception): exception_(exception) {}

    friend std::ostream& operator<<(std::ostream& s, const uraise& o) {
        oassertionstream& oas = dynamic_cast<oassertionstream&>(s);
        oas.raise(o.exception_);
        return oas;
    }

private:
    const E& exception_;
};

class exit {
public:
    explicit exit(const int& code): code_(code) {}

    friend std::ostream& operator<<(std::ostream& s, const exit& o) {
        oassertionstream& oas = dynamic_cast<oassertionstream&>(s);
        oas.exit(o.code_);
        return oas;
    }

private:
    const int code_;
};

class terminate {
public:
    friend std::ostream& operator<<(std::ostream& s, const terminate& o) {
        oassertionstream& oas = dynamic_cast<oassertionstream&>(s);
        oas.terminate();
        return oas;
    }
};

} // namespace dbc

#endif // DBC
 
#endif // DBC_ASSERTION_HPP_

