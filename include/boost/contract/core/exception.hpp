
#ifndef BOOST_CONTRACT_EXCEPTION_HPP_
#define BOOST_CONTRACT_EXCEPTION_HPP_

/** @file */

/** @cond */
//#include <boost/thread/mutex.hpp>
#include <boost/config.hpp>
#include <exception>
#include <sstream>
#include <string>
#include <iostream>
/** @endcond */

namespace boost { namespace contract {

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

typedef void (*assertion_failed_handler)(from);

namespace exception_ {
    enum failed_key {
        pre_key,
        post_key,
        const_entry_inv_key,
        const_volatile_entry_inv_key,
        static_entry_inv_key,
        const_exit_inv_key,
        const_volatile_exit_inv_key,
        static_exit_inv_key,
    };

    template<failed_key Key>
    void default_handler(from) {
        std::string s = "";
        switch(Key) {
            case pre_key:
                s = "precondition "; break;
            case post_key:
                s = "postcondition "; break;
            // NOTE: Following only needs to distinguish between entry and
            // exit invariant (const, volatile, static, etc. can already be
            // distinguished by code around assertion failure line number).
            case const_entry_inv_key:
                s = "entry invariant "; break;
            case const_volatile_entry_inv_key:
                s = "entry invariant "; break;
            case static_entry_inv_key:
                s = "entry invariant "; break;
            case const_exit_inv_key:
                s= "exit invariant "; break;
            case const_volatile_exit_inv_key:
                s= "exit invariant "; break;
            case static_exit_inv_key:
                s = "exit invariant "; break;
            // No default (so compiler warning/error on missing enum case).
        }
        try {
            throw;
        } catch(boost::contract::assertion_failure const& error) {
            // what = 'assertion "..." failed: ...'.
            std::cerr << s << error.what() << std::endl;
        // TODO: Below, I should use Boost.Exception diagnostic message...
        } catch(std::exception const& error) {
            std::cerr << s << "checking threw standard exception with " <<
                    "what(): " << error.what() << std::endl;
        } catch(...) {
            std::cerr << s << "checking threw unknown exception" <<
                    std::endl;
        }
        std::terminate(); // Default handlers log and call terminate.
    }

    // TODO: These (and some of the related def code) should be moved in a .cpp.
    //boost::mutex pre_failed_mutex;
    assertion_failed_handler pre_failed_handler =
            &default_handler<pre_key>;
    
    //boost::mutex post_failed_mutex;
    assertion_failed_handler post_failed_handler =
            &default_handler<post_key>;
    
    //boost::mutex const_entry_inv_failed_mutex;
    assertion_failed_handler const_entry_inv_failed_handler =
            &default_handler<const_entry_inv_key>;
    
    //boost::mutex const_volatile_entry_inv_failed_mutex;
    assertion_failed_handler const_volatile_entry_inv_failed_handler =
            &default_handler<const_volatile_entry_inv_key>;
    
    //boost::mutex static_entry_inv_failed_mutex;
    assertion_failed_handler static_entry_inv_failed_handler =
            &default_handler<static_entry_inv_key>;
    
    //boost::mutex const_exit_inv_failed_mutex;
    assertion_failed_handler const_exit_inv_failed_handler =
            &default_handler<const_exit_inv_key>;
    
    //boost::mutex const_volatile_exit_inv_failed_mutex;
    assertion_failed_handler const_volatile_exit_inv_failed_handler =
            &default_handler<const_volatile_exit_inv_key>;
    
    //boost::mutex static_exit_inv_failed_mutex;
    assertion_failed_handler static_exit_inv_failed_handler =
            &default_handler<static_exit_inv_key>;
}

#define BOOST_CONTRACT_EXCEPTION_SET_HANDLER_(_mutex, handler, f) \
    /*boost::mutex::scoped_lock lock(exception_::_mutex);*/ \
    assertion_failed_handler result = exception_::handler; \
    exception_::handler = f; \
    return result;
    
#define BOOST_CONTRACT_EXCEPTION_GET_HANDLER_(_mutex, handler) \
    /*boost::mutex::scoped_lock lock(exception_::_mutex)*/; \
    return exception_::handler;
    
#define BOOST_CONTRACT_EXCEPTION_CALL_HANDLER_(_mutex, handler, where) \
    /*boost::mutex::scoped_lock lock(exception_::_mutex);*/ \
    exception_::handler(where);

assertion_failed_handler set_precondition_failed(assertion_failed_handler f)
        BOOST_NOEXCEPT_OR_NOTHROW {
    BOOST_CONTRACT_EXCEPTION_SET_HANDLER_(pre_failed_mutex, pre_failed_handler,
            f)
}
assertion_failed_handler get_precondition_failed() BOOST_NOEXCEPT_OR_NOTHROW {
    BOOST_CONTRACT_EXCEPTION_GET_HANDLER_(pre_failed_mutex, pre_failed_handler)
}
void precondition_failed(from where) /* can throw */ {
    BOOST_CONTRACT_EXCEPTION_CALL_HANDLER_(pre_failed_mutex, pre_failed_handler,
            where)
}

assertion_failed_handler set_postcondition_failed(assertion_failed_handler f)
        BOOST_NOEXCEPT_OR_NOTHROW {
    BOOST_CONTRACT_EXCEPTION_SET_HANDLER_(post_failed_mutex,
            post_failed_handler, f)
}
assertion_failed_handler get_postcondition_failed() BOOST_NOEXCEPT_OR_NOTHROW {
    BOOST_CONTRACT_EXCEPTION_GET_HANDLER_(post_failed_mutex,
            post_failed_handler)
}
void postcondition_failed(from where) /* can throw */ {
    BOOST_CONTRACT_EXCEPTION_CALL_HANDLER_(post_failed_mutex,
            post_failed_handler, where)
}

assertion_failed_handler set_const_entry_invariant_failed(
        assertion_failed_handler f) BOOST_NOEXCEPT_OR_NOTHROW {
    BOOST_CONTRACT_EXCEPTION_SET_HANDLER_(const_entry_inv_failed_mutex,
            const_entry_inv_failed_handler, f)
}
assertion_failed_handler get_const_entry_invariant_failed()
        BOOST_NOEXCEPT_OR_NOTHROW {
    BOOST_CONTRACT_EXCEPTION_GET_HANDLER_(const_entry_inv_failed_mutex,
            const_entry_inv_failed_handler)
}
void const_entry_invariant_failed(from where) /* can throw */ {
    BOOST_CONTRACT_EXCEPTION_CALL_HANDLER_(const_entry_inv_failed_mutex,
            const_entry_inv_failed_handler, where)
}

assertion_failed_handler set_const_volatile_entry_invariant_failed(
        assertion_failed_handler f) BOOST_NOEXCEPT_OR_NOTHROW {
    BOOST_CONTRACT_EXCEPTION_SET_HANDLER_(const_volatile_entry_inv_failed_mutex,
            const_volatile_entry_inv_failed_handler, f)
}
assertion_failed_handler get_const_volatile_entry_invariant_failed()
        BOOST_NOEXCEPT_OR_NOTHROW {
    BOOST_CONTRACT_EXCEPTION_GET_HANDLER_(const_volatile_entry_inv_failed_mutex,
            const_volatile_entry_inv_failed_handler)
}
void const_volatile_entry_invariant_failed(from where) /* can throw */ {
    BOOST_CONTRACT_EXCEPTION_CALL_HANDLER_(
        const_volatile_entry_inv_failed_mutex, 
        const_volatile_entry_inv_failed_handler,
        where
    )
}

assertion_failed_handler set_static_entry_invariant_failed(
        assertion_failed_handler f) BOOST_NOEXCEPT_OR_NOTHROW {
    BOOST_CONTRACT_EXCEPTION_SET_HANDLER_(static_entry_inv_failed_mutex,
            static_entry_inv_failed_handler, f)
}
assertion_failed_handler get_static_entry_invariant_failed()
        BOOST_NOEXCEPT_OR_NOTHROW {
    BOOST_CONTRACT_EXCEPTION_GET_HANDLER_(static_entry_inv_failed_mutex,
            static_entry_inv_failed_handler)
}
void static_entry_invariant_failed(from where) /* can throw */ {
    BOOST_CONTRACT_EXCEPTION_CALL_HANDLER_(static_entry_inv_failed_mutex,
            static_entry_inv_failed_handler, where)
}

assertion_failed_handler set_const_exit_invariant_failed(
        assertion_failed_handler f) BOOST_NOEXCEPT_OR_NOTHROW {
    BOOST_CONTRACT_EXCEPTION_SET_HANDLER_(const_exit_inv_failed_mutex,
            const_exit_inv_failed_handler, f)
}
assertion_failed_handler get_const_exit_invariant_failed()
        BOOST_NOEXCEPT_OR_NOTHROW {
    BOOST_CONTRACT_EXCEPTION_GET_HANDLER_(const_exit_inv_failed_mutex,
            const_exit_inv_failed_handler)
}
void const_exit_invariant_failed(from where) /* can throw */ {
    BOOST_CONTRACT_EXCEPTION_CALL_HANDLER_(const_exit_inv_failed_mutex,
            const_exit_inv_failed_handler, where)
}

assertion_failed_handler set_const_volatile_exit_invariant_failed(
        assertion_failed_handler f) BOOST_NOEXCEPT_OR_NOTHROW {
    BOOST_CONTRACT_EXCEPTION_SET_HANDLER_(const_volatile_exit_inv_failed_mutex,
            const_volatile_exit_inv_failed_handler, f)
}
assertion_failed_handler get_const_volatile_exit_invariant_failed()
        BOOST_NOEXCEPT_OR_NOTHROW {
    BOOST_CONTRACT_EXCEPTION_GET_HANDLER_(const_volatile_exit_inv_failed_mutex,
            const_volatile_exit_inv_failed_handler)
}
void const_volatile_exit_invariant_failed(from where) /* can throw */ {
    BOOST_CONTRACT_EXCEPTION_CALL_HANDLER_(const_volatile_exit_inv_failed_mutex,
            const_volatile_exit_inv_failed_handler, where)
}

assertion_failed_handler set_static_exit_invariant_failed(
        assertion_failed_handler f) BOOST_NOEXCEPT_OR_NOTHROW {
    BOOST_CONTRACT_EXCEPTION_SET_HANDLER_(static_exit_inv_failed_mutex,
            static_exit_inv_failed_handler, f)
}
assertion_failed_handler get_static_exit_invariant_failed()
        BOOST_NOEXCEPT_OR_NOTHROW {
    BOOST_CONTRACT_EXCEPTION_GET_HANDLER_(static_exit_inv_failed_mutex,
            static_exit_inv_failed_handler)
}
void static_exit_invariant_failed(from where) /* can throw */ {
    BOOST_CONTRACT_EXCEPTION_CALL_HANDLER_(static_exit_inv_failed_mutex,
            static_exit_inv_failed_handler, where)
}

void set_entry_invariant_failed(assertion_failed_handler f)
        BOOST_NOEXCEPT_OR_NOTHROW {
    set_const_entry_invariant_failed(f);
    set_const_volatile_entry_invariant_failed(f);
    set_static_entry_invariant_failed(f);
}
void set_exit_invariant_failed(assertion_failed_handler f)
        BOOST_NOEXCEPT_OR_NOTHROW {
    set_const_exit_invariant_failed(f);
    set_const_volatile_exit_invariant_failed(f);
    set_static_exit_invariant_failed(f);
}
void set_invariant_failed(assertion_failed_handler f)
        BOOST_NOEXCEPT_OR_NOTHROW {
    set_entry_invariant_failed(f);
    set_exit_invariant_failed(f);
}

// TODO: Simplify the invariant failure handlers. I only need two, one for entry_inv and one for exit_inv (I do not need to distinguish volatile, const, static... they are all inv).

} } // namespace

#endif // #include guard

