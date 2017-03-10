
#ifndef BOOST_CONTRACT_DETAIL_INLINED_EXCEPTION_HPP_
#define BOOST_CONTRACT_DETAIL_INLINED_EXCEPTION_HPP_

// Copyright (C) 2008-2016 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0 (see accompanying
// file LICENSE_1_0.txt or a copy at http://www.boost.org/LICENSE_1_0.txt).
// See: http://www.boost.org/doc/libs/release/libs/contract/doc/html/index.html

// IMPORTANT: Do NOT use config macros BOOST_CONTRACT_... in this file so lib
// .cpp does not need recompiling if config changes (recompile only user code).

#include <boost/contract/core/exception.hpp>
#include <boost/thread/lock_guard.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/exception/diagnostic_information.hpp>
#include <string>
#include <sstream>
#include <iostream>
#include <exception>

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

char const* assertion_failure::file() const { return file_; }

unsigned long assertion_failure::line() const { return line_; }

char const* assertion_failure::code() const { return code_; }

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
        check_failure_key,
        pre_failure_key,
        post_failure_key,
        except_failure_key,
        old_failure_key,
        entry_inv_failure_key,
        exit_inv_failure_key
    };

    template<failure_key Key>
    void default_handler() {
        std::string k = "";
        switch(Key) {
            case check_failure_key: k = "check "; break;
            case pre_failure_key: k = "precondition "; break;
            case post_failure_key: k = "postcondition "; break;
            case except_failure_key: k = "except "; break;
            case old_failure_key: k = "old copy "; break;
            case entry_inv_failure_key: k = "entry invariant "; break;
            case exit_inv_failure_key: k = "exit invariant "; break;
            // No default (so compiler warning/error on missing enum case).
        }
        try { throw; }
        catch(boost::contract::assertion_failure const& error) {
            // what = "assertion '...' failed: ...".
            std::cerr << k << error.what() << std::endl;
        } catch(...) { // old_failure_key prints this, not above.
            std::cerr << k << "threw following exception:" << std::endl
                    << boost::current_exception_diagnostic_information();
        }
        std::terminate(); // Default handlers log and call terminate.
    }
    
    template<failure_key Key>
    void default_from_handler(from) { default_handler<Key>(); }

    // Check failure.

    boost::mutex check_failure_mutex;
    failure_handler check_failure_handler = &default_handler<check_failure_key>;

    failure_handler const& set_check_failure_unlocked(failure_handler const& f)
            BOOST_NOEXCEPT_OR_NOTHROW {
        check_failure_handler = f;
        return f;
    }
    
    failure_handler const& set_check_failure_locked(failure_handler const& f)
            BOOST_NOEXCEPT_OR_NOTHROW {
        boost::lock_guard<boost::mutex> lock(check_failure_mutex);
        return set_check_failure_unlocked(f);
    }

    failure_handler get_check_failure_unlocked() BOOST_NOEXCEPT_OR_NOTHROW {
        return check_failure_handler;
    }

    failure_handler get_check_failure_locked() BOOST_NOEXCEPT_OR_NOTHROW {
        boost::lock_guard<boost::mutex> lock(check_failure_mutex);
        return get_check_failure_unlocked();
    }

    void check_failure_unlocked() /* can throw */ {
        check_failure_handler();
    }
    
    void check_failure_locked() /* can throw */ {
        boost::lock_guard<boost::mutex> lock(check_failure_mutex);
        check_failure_unlocked();
    }
    
    // Precondition failure.

    boost::mutex pre_failure_mutex;
    from_failure_handler pre_failure_handler =
            &default_from_handler<pre_failure_key>;

    from_failure_handler const& set_pre_failure_unlocked(from_failure_handler
            const& f) BOOST_NOEXCEPT_OR_NOTHROW {
        pre_failure_handler = f;
        return f;
    }
    
    from_failure_handler const& set_pre_failure_locked(from_failure_handler
            const& f) BOOST_NOEXCEPT_OR_NOTHROW {
        boost::lock_guard<boost::mutex> lock(pre_failure_mutex);
        return set_pre_failure_unlocked(f);
    }

    from_failure_handler get_pre_failure_unlocked() BOOST_NOEXCEPT_OR_NOTHROW {
        return pre_failure_handler;
    }

    from_failure_handler get_pre_failure_locked() BOOST_NOEXCEPT_OR_NOTHROW {
        boost::lock_guard<boost::mutex> lock(pre_failure_mutex);
        return get_pre_failure_unlocked();
    }

    void pre_failure_unlocked(from where) /* can throw */ {
        pre_failure_handler(where);
    }
    
    void pre_failure_locked(from where) /* can throw */ {
        boost::lock_guard<boost::mutex> lock(pre_failure_mutex);
        pre_failure_unlocked(where);
    }
    
    // Postcondition failure.

    boost::mutex post_failure_mutex;
    from_failure_handler post_failure_handler =
            &default_from_handler<post_failure_key>;

    from_failure_handler const& set_post_failure_unlocked(from_failure_handler
            const& f) BOOST_NOEXCEPT_OR_NOTHROW {
        post_failure_handler = f;
        return f;
    }
    
    from_failure_handler const& set_post_failure_locked(from_failure_handler
            const& f) BOOST_NOEXCEPT_OR_NOTHROW {
        boost::lock_guard<boost::mutex> lock(post_failure_mutex);
        return set_post_failure_unlocked(f);
    }

    from_failure_handler get_post_failure_unlocked() BOOST_NOEXCEPT_OR_NOTHROW {
        return post_failure_handler;
    }

    from_failure_handler get_post_failure_locked() BOOST_NOEXCEPT_OR_NOTHROW {
        boost::lock_guard<boost::mutex> lock(post_failure_mutex);
        return get_post_failure_unlocked();
    }

    void post_failure_unlocked(from where) /* can throw */ {
        post_failure_handler(where);
    }
    
    void post_failure_locked(from where) /* can throw */ {
        boost::lock_guard<boost::mutex> lock(post_failure_mutex);
        post_failure_unlocked(where);
    }
    
    // Except failure.

    boost::mutex except_failure_mutex;
    from_failure_handler except_failure_handler =
            &default_from_handler<except_failure_key>;

    from_failure_handler const& set_except_failure_unlocked(from_failure_handler
            const& f) BOOST_NOEXCEPT_OR_NOTHROW {
        except_failure_handler = f;
        return f;
    }
    
    from_failure_handler const& set_except_failure_locked(from_failure_handler
            const& f) BOOST_NOEXCEPT_OR_NOTHROW {
        boost::lock_guard<boost::mutex> lock(except_failure_mutex);
        return set_except_failure_unlocked(f);
    }

    from_failure_handler get_except_failure_unlocked()
            BOOST_NOEXCEPT_OR_NOTHROW {
        return except_failure_handler;
    }

    from_failure_handler get_except_failure_locked() BOOST_NOEXCEPT_OR_NOTHROW {
        boost::lock_guard<boost::mutex> lock(except_failure_mutex);
        return get_except_failure_unlocked();
    }

    void except_failure_unlocked(from where) /* can throw */ {
        except_failure_handler(where);
    }
    
    void except_failure_locked(from where) /* can throw */ {
        boost::lock_guard<boost::mutex> lock(except_failure_mutex);
        except_failure_unlocked(where);
    }

    // Old-copy failure.

    boost::mutex old_failure_mutex;
    from_failure_handler old_failure_handler =
            &default_from_handler<old_failure_key>;

    from_failure_handler const& set_old_failure_unlocked(from_failure_handler
            const& f) BOOST_NOEXCEPT_OR_NOTHROW {
        old_failure_handler = f;
        return f;
    }
    
    from_failure_handler const& set_old_failure_locked(from_failure_handler
            const& f) BOOST_NOEXCEPT_OR_NOTHROW {
        boost::lock_guard<boost::mutex> lock(old_failure_mutex);
        return set_old_failure_unlocked(f);
    }

    from_failure_handler get_old_failure_unlocked() BOOST_NOEXCEPT_OR_NOTHROW {
        return old_failure_handler;
    }

    from_failure_handler get_old_failure_locked() BOOST_NOEXCEPT_OR_NOTHROW {
        boost::lock_guard<boost::mutex> lock(old_failure_mutex);
        return get_old_failure_unlocked();
    }

    void old_failure_unlocked(from where) /* can throw */ {
        old_failure_handler(where);
    }
    
    void old_failure_locked(from where) /* can throw */ {
        boost::lock_guard<boost::mutex> lock(old_failure_mutex);
        old_failure_unlocked(where);
    }
    
    // Entry invariant failure.

    boost::mutex entry_inv_failure_mutex;
    from_failure_handler entry_inv_failure_handler =
            &default_from_handler<entry_inv_failure_key>;

    from_failure_handler const& set_entry_inv_failure_unlocked(
            from_failure_handler const& f) BOOST_NOEXCEPT_OR_NOTHROW {
        entry_inv_failure_handler = f;
        return f;
    }
    
    from_failure_handler const& set_entry_inv_failure_locked(
            from_failure_handler const& f) BOOST_NOEXCEPT_OR_NOTHROW {
        boost::lock_guard<boost::mutex> lock(entry_inv_failure_mutex);
        return set_entry_inv_failure_unlocked(f);
    }

    from_failure_handler get_entry_inv_failure_unlocked()
            BOOST_NOEXCEPT_OR_NOTHROW {
        return entry_inv_failure_handler;
    }

    from_failure_handler get_entry_inv_failure_locked()
            BOOST_NOEXCEPT_OR_NOTHROW {
        boost::lock_guard<boost::mutex> lock(entry_inv_failure_mutex);
        return get_entry_inv_failure_unlocked();
    }

    void entry_inv_failure_unlocked(from where) /* can throw */ {
        entry_inv_failure_handler(where);
    }
    
    void entry_inv_failure_locked(from where) /* can throw */ {
        boost::lock_guard<boost::mutex> lock(entry_inv_failure_mutex);
        entry_inv_failure_unlocked(where);
    }
    
    // Exit invariant failure.

    boost::mutex exit_inv_failure_mutex;
    from_failure_handler exit_inv_failure_handler =
            &default_from_handler<exit_inv_failure_key>;

    from_failure_handler const& set_exit_inv_failure_unlocked(
            from_failure_handler const& f) BOOST_NOEXCEPT_OR_NOTHROW {
        exit_inv_failure_handler = f;
        return f;
    }
    
    from_failure_handler const& set_exit_inv_failure_locked(
            from_failure_handler const& f) BOOST_NOEXCEPT_OR_NOTHROW {
        boost::lock_guard<boost::mutex> lock(exit_inv_failure_mutex);
        return set_exit_inv_failure_unlocked(f);
    }

    from_failure_handler get_exit_inv_failure_unlocked()
            BOOST_NOEXCEPT_OR_NOTHROW {
        return exit_inv_failure_handler;
    }

    from_failure_handler get_exit_inv_failure_locked()
            BOOST_NOEXCEPT_OR_NOTHROW {
        boost::lock_guard<boost::mutex> lock(exit_inv_failure_mutex);
        return get_exit_inv_failure_unlocked();
    }

    void exit_inv_failure_unlocked(from where) /* can throw */ {
        exit_inv_failure_handler(where);
    }
    
    void exit_inv_failure_locked(from where) /* can throw */ {
        boost::lock_guard<boost::mutex> lock(exit_inv_failure_mutex);
        exit_inv_failure_unlocked(where);
    }
}

} } // namespace

#endif // #include guard

