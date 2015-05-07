
#ifndef BOOST_CONTRACT_AUX_EXCEPTION_HPP_
#define BOOST_CONTRACT_AUX_EXCEPTION_HPP_

#include <boost/contract/core/exception.hpp>
#include <exception>
#include <string>
#include <iostream>

namespace boost { namespace contract { namespace aux {

struct no_error {}; // Do not inherit from anything (this is internal only).

namespace exception_ {
    enum failure_handler_key {
        pre_key,
        post_key,
        const_entry_inv_key,
        const_volatile_entry_inv_key,
        static_entry_inv_key,
        const_exit_inv_key,
        const_volatile_exit_inv_key,
        static_exit_inv_key,
    };

    template<failure_handler_key Key, typename From>
    void default_failure_handler(From const) {
        std::string s = "";
        switch(Key) {
            case pre_key:
                s = "precondition "; break;
            case post_key:
                s = "postcondition "; break;
            case const_entry_inv_key:
                s = "const entry invariant "; break;
            case const_volatile_entry_inv_key:
                s = "const volatile entry invariant "; break;
            case static_entry_inv_key:
                s = "static entry invariant "; break;
            case const_exit_inv_key:
                s= "const exit invariant "; break;
            case const_volatile_exit_inv_key:
                s= "const volatile exit invariant "; break;
            case static_exit_inv_key:
                s = "static exit invariant "; break;
            // No default (so compiler warning/error on missing enum case).
        }
        try {
            throw;
        } catch(boost::contract::assertion_failure const& error) {
            // what = 'assertion "..." failed: ...'.
            std::cerr << s << error.what() << std::endl;
        } catch(std::exception const& error) {
            std::cerr << s << "checking threw standard exception with " <<
                    "what(): " << error.what() << std::endl;
        } catch(...) {
            std::cerr << s << "checking threw unknown exception" <<
                    std::endl;
        }
        std::terminate(); // Default handlers log and call terminate.
    }
}

// TODO: These are part of the lib state. They should prob be put in a .cpp and
// exported (so they are the same across DLL, etc.), plus they should be
// protected by mutexes.
failure_handler pre_failure_handler = &exception_::
        default_failure_handler<exception_::pre_key>;
failure_handler post_failure_handler = &exception_::
        default_failure_handler<exception_::post_key>;

failure_handler const_entry_inv_failure_handler = &exception_::
        default_failure_handler<exception_::const_entry_inv_key>;
failure_handler const_volatile_entry_inv_failure_handler = &exception_::
        default_failure_handler<exception_::const_volatile_entry_inv_key>;
failure_handler static_entry_inv_failure_handler = &exception_::
        default_failure_handler<exception_::static_entry_inv_key>;

failure_handler const_exit_inv_failure_handler = &exception_::
        default_failure_handler<exception_::const_exit_inv_key>;
failure_handler const_volatile_exit_inv_failure_handler = &exception_::
        default_failure_handler<exception_::const_volatile_exit_inv_key>;
failure_handler static_exit_inv_failure_handler = &exception_::
        default_failure_handler<exception_::static_exit_inv_key>;

} } } // namespace

#endif // #include guard

