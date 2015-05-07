
#ifndef BOOST_CONTRACT_EXCEPTION_HPP_
#define BOOST_CONTRACT_EXCEPTION_HPP_

#include <boost/config.hpp>
#include <exception>
#include <sstream>

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
        text << "assertion";
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

namespace aux {
    extern failure_handler pre_failure_handler;
    extern failure_handler post_failure_handler;

    extern failure_handler const_entry_inv_failure_handler;
    extern failure_handler const_volatile_entry_inv_failure_handler;
    extern failure_handler static_entry_inv_failure_handler;

    extern failure_handler const_exit_inv_failure_handler;
    extern failure_handler const_volatile_exit_inv_failure_handler;
    extern failure_handler static_exit_inv_failure_handler;
}

failure_handler set_precondition_failure(failure_handler f)
        BOOST_NOEXCEPT_OR_NOTHROW {
    failure_handler result = boost::contract::aux::pre_failure_handler;
    boost::contract::aux::pre_failure_handler = f;
    return result;
}

failure_handler set_postcondition_failure(failure_handler f)
        BOOST_NOEXCEPT_OR_NOTHROW {
    failure_handler result = boost::contract::aux::post_failure_handler;
    boost::contract::aux::post_failure_handler = f;
    return result;
}

// Entry invariants.

failure_handler set_const_entry_invariant_failure(failure_handler f)
        BOOST_NOEXCEPT_OR_NOTHROW {
    failure_handler result = boost::contract::aux::
            const_entry_inv_failure_handler;
    boost::contract::aux::const_entry_inv_failure_handler = f;
    return result;
}

failure_handler set_const_volatile_entry_invariant_failure(failure_handler f)
        BOOST_NOEXCEPT_OR_NOTHROW {
    failure_handler result = boost::contract::aux::
            const_volatile_entry_inv_failure_handler;
    boost::contract::aux::const_volatile_entry_inv_failure_handler = f;
    return result;
}

failure_handler set_static_entry_invariant_failure(failure_handler f)
        BOOST_NOEXCEPT_OR_NOTHROW {
    failure_handler result = boost::contract::aux::
            static_entry_inv_failure_handler;
    boost::contract::aux::static_entry_inv_failure_handler = f;
    return result;
}

void set_entry_invariant_failure(failure_handler f) BOOST_NOEXCEPT_OR_NOTHROW {
    set_const_entry_invariant_failure(f);
    set_const_volatile_entry_invariant_failure(f);
    set_static_entry_invariant_failure(f);
}

// Exit invariants.

failure_handler set_const_exit_invariant_failure(failure_handler f)
        BOOST_NOEXCEPT_OR_NOTHROW {
    failure_handler result = boost::contract::aux::
            const_exit_inv_failure_handler;
    boost::contract::aux::const_exit_inv_failure_handler = f;
    return result;
}

failure_handler set_const_volatile_exit_invariant_failure(failure_handler f)
        BOOST_NOEXCEPT_OR_NOTHROW {
    failure_handler result = boost::contract::aux::
            const_volatile_exit_inv_failure_handler;
    boost::contract::aux::const_volatile_exit_inv_failure_handler = f;
    return result;
}

failure_handler set_static_exit_invariant_failure(failure_handler f)
        BOOST_NOEXCEPT_OR_NOTHROW {
    failure_handler result = boost::contract::aux::
            static_exit_inv_failure_handler;
    boost::contract::aux::static_exit_inv_failure_handler = f;
    return result;
}

void set_exit_invariant_failure(failure_handler f) BOOST_NOEXCEPT_OR_NOTHROW {
    set_const_exit_invariant_failure(f);
    set_const_volatile_exit_invariant_failure(f);
    set_static_exit_invariant_failure(f);
}

// All invariants.

void set_invariant_failure(failure_handler f) BOOST_NOEXCEPT_OR_NOTHROW {
    set_entry_invariant_failure(f);
    set_exit_invariant_failure(f);
}

} } // namespace

#endif // #include guard

