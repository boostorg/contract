
#ifndef BOOST_CONTRACT_AUX_CHECK_BASE_HPP_
#define BOOST_CONTRACT_AUX_CHECK_BASE_HPP_

#include <boost/contract/core/exception.hpp>
/** @cond */
// TODO: Can I reduce boost.function overhead? Check also everywhere else boost.function is used.
#include <boost/function.hpp>
#include <boost/config.hpp>
#include <cassert>
/** @endcond */

namespace boost { namespace contract { namespace aux {

class check_base { // Base to hold all contract objects for RAII.
public:
    explicit check_base(boost::contract::from from) :
        BOOST_CONTRACT_ERROR_missing_guard_declaration(false),
        from_(from),
        failed_(false)
    {}

    void guard() { // Must be called by contract guard ctor.
        BOOST_CONTRACT_ERROR_missing_guard_declaration = true;
        this->init(); // All inits (pre, old, post) done after guard decl.
    }

    // Assert in case derived don't.
    virtual ~check_base() BOOST_NOEXCEPT_IF(false) { assert_guarded(); }
        
    void assert_guarded() { // Derived dtors should call this (earlier errors).
        assert(BOOST_CONTRACT_ERROR_missing_guard_declaration);
    }
    
    template<typename F>
    void set_pre(F const& f) { pre_ = f; }

    template<typename F>
    void set_old(F const& f) { old_ = f; }

protected:
    virtual void init() {}
    
    bool check_pre(bool throw_on_failure = false) {
        if(!pre_) return false;
        if(failed()) return true;
        try { pre_(); }
        catch(...) {
            // Subcontracted pre must throw on failure (instead of
            // calling failure handler) so to be checked in logic-or.
            if(throw_on_failure) throw;
            fail(&boost::contract::precondition_failed);
        }
        return true;
    }

    void copy_old() {
        if(failed()) return;
        // TODO: Document that when old copies throw, using .old() calls post failure handler (more correct), while using = OLDOF makes enclosing user function throw (less correct). Plus of course using .old() makes old copies after inv and pre are checked, while using = OLDOF makes old copies before inv and pre checking (this is less correct in theory, but it should not really matter in most practical cases unless the old copy are programmed assuming inv and pre are satisfied).
        try { if(old_) old_(); }
        catch(...) { fail(&boost::contract::postcondition_failed); }
    }
    
    void fail(void (*h)(boost::contract::from)) {
        failed(true);
        if(h) h(from_);
    }
    
    // Virtual so overriding public functions can use virtual_::failed_ instead.
    virtual bool failed() const { return failed_; }
    virtual void failed(bool value) { failed_ = value; }

private:
    bool BOOST_CONTRACT_ERROR_missing_guard_declaration;
    boost::contract::from from_;
    boost::function<void ()> pre_;
    boost::function<void ()> old_;
    bool failed_;
};

} } } // namespace

#endif // #include guard

