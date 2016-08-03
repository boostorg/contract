
#ifndef BOOST_CONTRACT_DETAIL_CHECK_BASE_HPP_
#define BOOST_CONTRACT_DETAIL_CHECK_BASE_HPP_

// Copyright (C) 2008-2016 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0 (see accompanying
// file LICENSE_1_0.txt or a copy at http://www.boost.org/LICENSE_1_0.txt).
// See: http://www.boost.org/doc/libs/release/libs/contract/doc/html/index.html

#include <boost/contract/core/exception.hpp>
#include <boost/contract/core/config.hpp>
#if !defined(BOOST_CONTRACT_NO_PRECONDITIONS) || \
        !defined(BOOST_CONTRACT_NO_POSTCONDITIONS)
    #include <boost/function.hpp>
#endif
#include <boost/noncopyable.hpp>
#include <boost/config.hpp>
#ifndef BOOST_CONTRACT_ON_MISSING_GUARD
    #include <cassert>
#endif

namespace boost { namespace contract { namespace detail {

class check_base : // Base to hold all contract objects for RAII.
    private boost::noncopyable // Avoid copying possible user's ftor captures.
{
public:
    explicit check_base(boost::contract::from from) :
          BOOST_CONTRACT_ERROR_missing_guard_declaration(false)
        , guard_asserted_(false)
        #if !defined(BOOST_CONTRACT_NO_PRECONDITIONS) || \
                !defined(BOOST_CONTRACT_NO_POSTCONDITIONS) || \
                !defined(BOOST_CONTRACT_NO_INVARIANTS)
            , from_(from)
            , failed_(false)
        #endif
    {}
    
    // Override for checking on exit (but overrides call `assert_guarded()`).
    virtual ~check_base() BOOST_NOEXCEPT_IF(false) {
        if(!guard_asserted_) assert_guarded();
    }

    void assert_guarded() { // Derived dtors must assert this at entry.
        guard_asserted_ = true;
        #ifdef BOOST_CONTRACT_ON_MISSING_GUARD
            if(!BOOST_CONTRACT_ERROR_missing_guard_declaration) {
                BOOST_CONTRACT_ON_MISSING_GUARD;
            }
        #else
            assert(BOOST_CONTRACT_ERROR_missing_guard_declaration);
        #endif
    }
    
    void guard() { // Must be called by contract guard ctor.
        BOOST_CONTRACT_ERROR_missing_guard_declaration = true;
        this->init(); // All inits (pre, old, post) done after guard decl.
    }
    
    #ifndef BOOST_CONTRACT_NO_PRECONDITIONS
        template<typename F>
        void set_pre(F const& f) { pre_ = f; }
    #endif

    #ifndef BOOST_CONTRACT_NO_POSTCONDITIONS
        template<typename F>
        void set_old(F const& f) { old_ = f; }
    #endif

protected:
    virtual void init() {} // Override for checking on entry.
    
    // Return true if actually checked calling user ftor.
    #ifndef BOOST_CONTRACT_NO_PRECONDITIONS
        bool check_pre(bool throw_on_failure = false) {
            if(failed()) return true;
            try { if(pre_) pre_(); else return false; }
            catch(...) {
                // Subcontracted pre must throw on failure (instead of
                // calling failure handler) so to be checked in logic-or.
                if(throw_on_failure) throw;
                fail(&boost::contract::precondition_failure);
            }
            return true;
        }
    #endif

    #ifndef BOOST_CONTRACT_NO_POSTCONDITIONS
        void copy_old() {
            if(failed()) return;
            try { if(old_) old_(); }
            catch(...) { fail(&boost::contract::postcondition_failure); }
        }
    #endif
    
    #if !defined(BOOST_CONTRACT_NO_PRECONDITIONS) || \
            !defined(BOOST_CONTRACT_NO_POSTCONDITIONS) || \
            !defined(BOOST_CONTRACT_NO_INVARIANTS)
        void fail(void (*h)(boost::contract::from)) {
            failed(true);
            if(h) h(from_);
        }
    
        // Virtual so overriding pub func can use virtual_::failed_ instead.
        virtual bool failed() const { return failed_; }
        virtual void failed(bool value) { failed_ = value; }
    #endif

private:
    bool BOOST_CONTRACT_ERROR_missing_guard_declaration;
    bool guard_asserted_; // Avoid throwing twice from dtors (undef behavior).
    #if !defined(BOOST_CONTRACT_NO_PRECONDITIONS) || \
            !defined(BOOST_CONTRACT_NO_POSTCONDITIONS) || \
            !defined(BOOST_CONTRACT_NO_INVARIANTS)
        boost::contract::from from_;
        bool failed_;
    #endif
    #ifndef BOOST_CONTRACT_NO_PRECONDITIONS
        boost::function<void ()> pre_; // Use Boost.Function to also...
    #endif
    #ifndef BOOST_CONTRACT_NO_POSTCONDITIONS
        boost::function<void ()> old_; // ...handle lambdas, binds, etc.
    #endif
};

} } } // namespace

#endif // #include guard

