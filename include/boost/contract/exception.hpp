
#ifndef BOOST_CONTRACT_EXCEPTION_HPP_
#define BOOST_CONTRACT_EXCEPTION_HPP_

#include <boost/config.hpp>
#include <exception>
#include <string>
#include <sstream>
#include <iostream>

// TODO: Implement set_precondition/postcondition/invariant/entry_invariant/
// exit_invariant_failed handlers.

namespace boost { namespace contract {

// Exceptions.

struct assertion_failure : public std::exception {
    explicit assertion_failure(char const* const file = "",
            unsigned long const line = 0, char const* const code = "") :
        file_(file), line_(line), code_(code)
    { init(); }
    
    explicit assertion_failure(char const* const code) :
            file_(""), line_(0), code_(code)
    { init(); }

    virtual ~assertion_failure() {}

    // Return `assertion "XYZ" failed: file "ABC", line 123`.
    virtual char const* what() const BOOST_NOEXCEPT { return what_.c_str(); }

    char const* const file() const { return file_; }
    unsigned long line() const { return line_; }
    char const* const code() const { return code_; }

private:
    void init() {
        std::ostringstream text;
        text.str("assertion");
        if(std::string(code_) != "") text << " \"" << code_ << "\"";
        text << " failed";
        if(std::string(file_) != "") {
            text << ": \"" << file_ << "\"";
            if(line_ != 0) text << ", line " << line_;
        }
        what_ = text.str();
    }

    char const* const file_;
    unsigned long const line_;
    char const* const code_;
    std::string what_;
};

struct precondition_failure : public assertion_failure {
    explicit precondition_failure(assertion_failure const& failure) :
            assertion_failure(failure) {
        what_ = std::string("precondition ") + assertion_failure::what();
    }
    virtual char const* what() const BOOST_NOEXCEPT { return what_.c_str(); }
private:
    std::string what_;
};

struct postcondition_failure : public assertion_failure {
    explicit postcondition_failure(assertion_failure const& failure) :
            assertion_failure(failure) {
        what_ = std::string("postcondition ") + assertion_failure::what();
    }
    virtual char const* what() const BOOST_NOEXCEPT { return what_.c_str(); }
private:
    std::string what_;
};

struct invariant_failure : public assertion_failure {};

struct entry_invariant_failure : public assertion_failure {
    explicit entry_invariant_failure(assertion_failure const& failure) :
            assertion_failure(failure) {
        what_ = std::string("exit invariant ") + assertion_failure::what();
    }
    virtual char const* what() const BOOST_NOEXCEPT { return what_.c_str(); }
private:
    std::string what_;
};

struct exit_invariant_failure : public assertion_failure {
    explicit exit_invariant_failure(assertion_failure const& failure) :
            assertion_failure(failure) {
        what_ = std::string("exit invariant ") + assertion_failure::what();
    }
    virtual char const* what() const BOOST_NOEXCEPT { return what_.c_str(); }
private:
    std::string what_;
};

// Handlers.

enum from {
    from_constructor,
    from_destructor,
    from_public_member,
    from_protected_member,
    from_private_member,
    from_free_function
};

typedef void (*failure_handler)(from);

// TODO: These are part of the lib state. They should prob be put in a .cpp and
// exported (so they are the same across DLL, etc.), plus they should be
// protected by mutexes.
namespace aux {
    void default_handler(from const) {
        try {
            throw;
        } catch(boost::contract::assertion_failure const& error) {
            std::cerr << error.what() << std::endl;
            std::terminate();
        } catch(...) {
            std::terminate();
        }
    }

    failure_handler precondition_failure_handler = &default_handler;
    failure_handler postcondition_failure_handler = &default_handler;
    failure_handler entry_invariant_failure_handler = &default_handler;
    failure_handler exit_invariant_failure_handler = &default_handler;
}

failure_handler set_precondition_failure(failure_handler f)
        BOOST_NOEXCEPT_OR_NOTHROW {
    failure_handler result = boost::contract::aux::precondition_failure_handler;
    boost::contract::aux::precondition_failure_handler = f;
    return result;
}

failure_handler set_postcondition_failure(failure_handler f)
        BOOST_NOEXCEPT_OR_NOTHROW {
    failure_handler result = boost::contract::aux::
            postcondition_failure_handler;
    boost::contract::aux::postcondition_failure_handler = f;
    return result;
}

failure_handler set_entry_invariant_failure(failure_handler f)
        BOOST_NOEXCEPT_OR_NOTHROW {
    failure_handler result = boost::contract::aux::
            entry_invariant_failure_handler;
    boost::contract::aux::entry_invariant_failure_handler = f;
    return result;
}

failure_handler set_exit_invariant_failure(failure_handler f)
        BOOST_NOEXCEPT_OR_NOTHROW {
    failure_handler result = boost::contract::aux::
            exit_invariant_failure_handler;
    boost::contract::aux::exit_invariant_failure_handler = f;
    return result;
}

void set_invariant_failure(failure_handler f) BOOST_NOEXCEPT_OR_NOTHROW {
    set_entry_invariant_failure(f);
    set_exit_invariant_failure(f);
}

} } // namespace

#endif // #include guard

