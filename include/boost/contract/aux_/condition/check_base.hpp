
#ifndef BOOST_CONTRACT_AUX_CHECK_BASE_HPP_
#define BOOST_CONTRACT_AUX_CHECK_BASE_HPP_

// Copyright (C) 2008-2016 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0 (see accompanying
// file LICENSE_1_0.txt or a copy at http://www.boost.org/LICENSE_1_0.txt).
// See: http://www.boost.org/doc/libs/release/libs/contract/doc/html/index.html

#include <boost/contract/core/exception.hpp>
#include <boost/contract/core/config.hpp>
#if BOOST_CONTRACT_PRECONDITIONS || BOOST_CONTRACT_POSTCONDITIONS
    #include <boost/function.hpp>
#endif
#include <boost/noncopyable.hpp>
#include <boost/config.hpp>
#ifndef BOOST_CONTRACT_CONFIG_ON_MISSING_GUARD
    #include <cassert>
#endif

namespace boost { namespace contract { namespace aux {

class check_base : // Base to hold all contract objects for RAII.
    private boost::noncopyable // Avoid copying possible user's ftor captures.
{
public:
    explicit check_base(boost::contract::from from) :
          BOOST_CONTRACT_ERROR_missing_guard_declaration(false)
        , guard_asserted_(false)
        , from_(from)
        #if BOOST_CONTRACT_PRECONDITIONS || BOOST_CONTRACT_POSTCONDITIONS || \
                BOOST_CONTRACT_INVARIANTS
            , failed_(false)
        #endif
    {}
    
    // Override for checking on exit (but overrides call `assert_guarded()`).
    virtual ~check_base() BOOST_NOEXCEPT_IF(false) {
        if(!guard_asserted_) assert_guarded();
    }

    void assert_guarded() { // Derived dtors must assert this at entry.
        guard_asserted_ = true;
        #ifdef BOOST_CONTRACT_CONFIG_ON_MISSING_GUARD
            if(!BOOST_CONTRACT_ERROR_missing_guard_declaration) {
                BOOST_CONTRACT_CONFIG_ON_MISSING_GUARD;
            }
        #else
            assert(BOOST_CONTRACT_ERROR_missing_guard_declaration);
        #endif
    }
    
    void guard() { // Must be called by contract guard ctor.
        BOOST_CONTRACT_ERROR_missing_guard_declaration = true;
        this->init(); // All inits (pre, old, post) done after guard decl.
    }
    
    #if BOOST_CONTRACT_PRECONDITIONS
        template<typename F>
        void set_pre(F const& f) { pre_ = f; }
    #endif

    #if BOOST_CONTRACT_POSTCONDITIONS
        template<typename F>
        void set_old(F const& f) { old_ = f; }
    #endif

protected:
    virtual void init() {} // Override for checking on entry.
    
    // Return true if actually checked calling user ftor.
    #if BOOST_CONTRACT_PRECONDITIONS
        bool check_pre(bool throw_on_failure = false) {
            if(!pre_) return false;
            if(failed()) return true;
            try { pre_(); }
            catch(...) {
                // Subcontracted pre must throw on failure (instead of
                // calling failure handler) so to be checked in logic-or.
                if(throw_on_failure) throw;
                fail(&boost::contract::precondition_failure);
            }
            return true;
        }
    #endif

    #if BOOST_CONTRACT_POSTCONDITIONS
        void copy_old() {
            if(failed()) return;
            // TODO: Document that when old copies throw, using .old() calls post failure handler (more correct), while using = OLDOF makes enclosing user function throw (less correct). Plus of course using .old() makes old copies after inv and pre are checked, while using = OLDOF makes old copies before inv and pre checking (this is less correct in theory, but it should not really matter in most practical cases unless the old copy are programmed assuming inv and pre are satisfied). Also document in a rationale that it would be possible to wrap all old.hpp operations (old_ptr copy constructor, make_old, etc.) in try-catch statements so for this lib to call postcondition_failure handler also when ... = OLDOF is used. However, in that case this lib cannot populate the from parameter (and destructors can have postconditions so from would be necessary for ... = OLDOF used in a destructor) so the authors decided to not do that and leave that in the hands of the programmers (that can manually wrap ... = OLDOF with a try-catch in their user code if necessary, or better just use .old(...) when calling the failure handler for old value copies is important).
            try { if(old_) old_(); }
            catch(...) { fail(&boost::contract::postcondition_failure); }
        }
    #endif
    
    #if BOOST_CONTRACT_PRECONDITIONS || BOOST_CONTRACT_POSTCONDITIONS || \
            BOOST_CONTRACT_INVARIANTS
        void fail(void (*h)(boost::contract::from)) {
            failed(true);
            if(h) h(from_);
        }
    
        // Virtual so overriding pub func can use virtual_::failed_ instead.
        virtual bool failed() const { return failed_; }
        virtual void failed(bool value) { failed_ = value; }
    #endif

private:
    // TODO: Document all BOOST_CONTRACT_ERROR_... and BOOST_STATIC_ASSERT_MSG errors (in an annex...).
    bool BOOST_CONTRACT_ERROR_missing_guard_declaration;
    bool guard_asserted_; // Avoid throwing twice from dtors (undef behavior).
    boost::contract::from from_;
    #if BOOST_CONTRACT_PRECONDITIONS || BOOST_CONTRACT_POSTCONDITIONS || \
            BOOST_CONTRACT_INVARIANTS
        bool failed_;
    #endif
    #if BOOST_CONTRACT_PRECONDITIONS
        boost::function<void ()> pre_; // Use Boost.Function to also...
    #endif
    #if BOOST_CONTRACT_POSTCONDITIONS
        boost::function<void ()> old_; // ...handle lambdas, binds, etc.
    #endif
};

} } } // namespace

#endif // #include guard

