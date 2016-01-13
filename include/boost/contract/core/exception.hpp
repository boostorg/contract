
#ifndef BOOST_CONTRACT_EXCEPTION_HPP_
#define BOOST_CONTRACT_EXCEPTION_HPP_

/** @file */

#include <boost/contract/core/config.hpp>
/** @cond */
#include <boost/function.hpp>
#include <boost/exception/diagnostic_information.hpp>
#include <boost/config.hpp>
#include <exception>
#include <sstream>
#include <string>
#include <iostream>
/** @endcond */

// NOTE: This code should not change (not even its impl) based on the
// CONFIG_NO_... macros. For example, preconditions_failure() should still call
// the set precondition failure handler even when CONFIG_NO_PRECONDITIONS is
// #defined, because user code might explicitly call precondition_failure() (for
// whatever reason...). Otherwise, the public API of this lib will change.

/* PRIVATE */

#define BOOST_CONTRACT_EXCEPTION_HANDLER_SCOPED_LOCK_(_mutex) \
    /*boost::mutex::scoped_lock lock(_mutex);*/

#define BOOST_CONTRACT_EXCEPTION_HANDLER_SET_(_mutex, handler, f) \
    BOOST_CONTRACT_EXCEPTION_HANDLER_SCOPED_LOCK_(_mutex); \
    assertion_failure_handler result = handler; \
    handler = f; \
    return result;
    
#define BOOST_CONTRACT_EXCEPTION_HANDLER_GET_(_mutex, handler) \
    BOOST_CONTRACT_EXCEPTION_HANDLER_SCOPED_LOCK_(_mutex); \
    return handler;
    
#define BOOST_CONTRACT_EXCEPTION_HANDLER_(_mutex, handler, where) \
    BOOST_CONTRACT_EXCEPTION_HANDLER_SCOPED_LOCK_(_mutex); \
    handler(where);

/* CODE */

namespace boost { namespace contract {

// Placeholder base class to group all this lib exceptions.
// IMPORTANT: Must not inherit from std::exception as derived exceptions will.
class exception {};

// Rationale: boost::bad_any_cast exception does not print from/to type names,
// so throw custom exception.
class bad_virtual_result_cast : // Copyable (as string, etc.).
        public std::bad_cast, public boost::contract::exception {
public:
    explicit bad_virtual_result_cast(char const* from_type_name,
            char const* to_type_name) {
        std::ostringstream text;
        text
            << "incompatible contracted virtual function result type "
            << "conversion from '" << from_type_name << "' to '"
            << to_type_name  << "'"
        ;
        what_ = text.str();
    }

    virtual char const* what() const BOOST_NOEXCEPT { return what_.c_str(); }

private:
    std::string what_;
};

class assertion_failure : // Copyable (as string, etc.).
        public std::exception, public boost::contract::exception {
public:
    explicit assertion_failure(char const* const file = "",
            unsigned long const line = 0, char const* const code = "") :
        file_(file), line_(line), code_(code)
    { init(); }
    
    explicit assertion_failure(char const* const code) :
            file_(""), line_(0), code_(code)
    { init(); }

    virtual ~assertion_failure() {}

    // Return `assertion "..." failed: file "...", line ...`.
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
            text << ": file \"" << file_ << "\"";
            if(line_ != 0) text << ", line " << line_;
        }
        what_ = text.str();
    }

    char const* const file_;
    unsigned long const line_;
    char const* const code_;
    std::string what_;
};

enum from {
    from_constructor,
    from_destructor,
    from_function
};

// Use Boost.Function to handle also lambdas, binds, etc,
typedef boost::function<void (from)> assertion_failure_handler;

namespace exception_ {
    enum failure_key { pre_key, post_key, entry_inv_key, exit_inv_key };

    template<failure_key Key>
    void default_handler(from) {
        std::string k = "";
        switch(Key) {
            case pre_key: k = "precondition "; break;
            case post_key: k = "postcondition "; break;
            case entry_inv_key: k = "entry invariant "; break;
            case exit_inv_key: k = "exit invariant "; break;
            // No default (so compiler warning/error on missing enum case).
        }
        try {
            throw;
        } catch(boost::contract::assertion_failure const& error) {
            // what = "assertion '...' failed: ...".
            std::cerr << k << error.what() << std::endl;
        } catch(...) {
            std::cerr << k << "checking threw following exception:" << std::endl
                    << boost::current_exception_diagnostic_information();
        }
        std::terminate(); // Default handlers log and call terminate.
    }

    // TODO: These (and some of the related def code) should be moved in a .cpp.

    //boost::mutex pre_failure_mutex;
    assertion_failure_handler pre_failure_handler =
            &default_handler<pre_key>;
    
    //boost::mutex post_failure_mutex;
    assertion_failure_handler post_failure_handler =
            &default_handler<post_key>;
    
    //boost::mutex entry_inv_failure_mutex;
    assertion_failure_handler entry_inv_failure_handler =
            &default_handler<entry_inv_key>;
    
    //boost::mutex exit_inv_failure_mutex;
    assertion_failure_handler exit_inv_failure_handler =
            &default_handler<exit_inv_key>;
}

// Contract compilation on/off cannot change following set/get.

assertion_failure_handler set_precondition_failure(
        assertion_failure_handler const& f) BOOST_NOEXCEPT_OR_NOTHROW {
    BOOST_CONTRACT_EXCEPTION_HANDLER_SET_(exception_::pre_failure_mutex,
            exception_::pre_failure_handler, f);
}

assertion_failure_handler get_precondition_failure()
        BOOST_NOEXCEPT_OR_NOTHROW {
    BOOST_CONTRACT_EXCEPTION_HANDLER_GET_(exception_::pre_failure_mutex,
            exception_::pre_failure_handler);
}

void precondition_failure(from where) /* can throw */ {
    BOOST_CONTRACT_EXCEPTION_HANDLER_(exception_::pre_failure_mutex,
            exception_::pre_failure_handler, where)
}

assertion_failure_handler set_postcondition_failure(
        assertion_failure_handler const& f) BOOST_NOEXCEPT_OR_NOTHROW {
    BOOST_CONTRACT_EXCEPTION_HANDLER_SET_(exception_::post_failure_mutex,
            exception_::post_failure_handler, f);
}

assertion_failure_handler get_postcondition_failure()
        BOOST_NOEXCEPT_OR_NOTHROW {
    BOOST_CONTRACT_EXCEPTION_HANDLER_GET_(exception_::post_failure_mutex,
            exception_::post_failure_handler);
}

void postcondition_failure(from where) /* can throw */ {
    BOOST_CONTRACT_EXCEPTION_HANDLER_(exception_::post_failure_mutex,
            exception_::post_failure_handler, where);
}

assertion_failure_handler set_entry_invariant_failure(
        assertion_failure_handler const& f) BOOST_NOEXCEPT_OR_NOTHROW {
    BOOST_CONTRACT_EXCEPTION_HANDLER_SET_(exception_::entry_inv_failure_mutex,
        exception_::entry_inv_failure_handler, f);
}

assertion_failure_handler get_entry_invariant_failure()
        BOOST_NOEXCEPT_OR_NOTHROW {
    BOOST_CONTRACT_EXCEPTION_HANDLER_GET_(exception_::entry_inv_failure_mutex,
            exception_::entry_inv_failure_handler);
}

void entry_invariant_failure(from where) /* can throw */ {
    BOOST_CONTRACT_EXCEPTION_HANDLER_(exception_::entry_inv_failure_mutex,
            exception_::entry_inv_failure_handler, where);
}

assertion_failure_handler set_exit_invariant_failure(
        assertion_failure_handler const& f) BOOST_NOEXCEPT_OR_NOTHROW {
    BOOST_CONTRACT_EXCEPTION_HANDLER_SET_(exception_::exit_inv_failure_mutex,
        exception_::exit_inv_failure_handler, f);
}

assertion_failure_handler get_exit_invariant_failure()
        BOOST_NOEXCEPT_OR_NOTHROW {
    BOOST_CONTRACT_EXCEPTION_HANDLER_GET_(exception_::exit_inv_failure_mutex,
            exception_::exit_inv_failure_handler);
}

void exit_invariant_failure(from where) /* can throw */ {
    BOOST_CONTRACT_EXCEPTION_HANDLER_(exception_::exit_inv_failure_mutex,
            exception_::exit_inv_failure_handler, where);
}

void set_invariant_failure(assertion_failure_handler const& f)
        BOOST_NOEXCEPT_OR_NOTHROW {
    set_entry_invariant_failure(f);
    set_exit_invariant_failure(f);
}

} } // namespace

#endif // #include guard

