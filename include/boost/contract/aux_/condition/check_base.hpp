
#ifndef BOOST_CONTRACT_AUX_CHECK_BASE_HPP_
#define BOOST_CONTRACT_AUX_CHECK_BASE_HPP_

#include <boost/contract/core/exception.hpp>
/** @cond */
#include <boost/function.hpp> // TODO: Can I reduce boost.function overhead?
#include <cassert>
/** @endcond */

namespace boost { namespace contract { namespace aux {

class check_base { // Base to hold all contract objects for RAII.
public:
    explicit check_base(boost::contract::from from) :
        BOOST_CONTRACT_ERROR_missing_guard_declaration(false),
        from_(from)
    {}

    virtual ~check_base() { assert_guarded(); } // Assert in case derived don't.
    
    void guard() { // Must be called by contract guard ctor.
        BOOST_CONTRACT_ERROR_missing_guard_declaration = true;
        this->init(); // All inits (pre, old, post) done after guard decl.
    }
        
    void assert_guarded() { // Derived dtors should call this (earlier errors).
        assert(BOOST_CONTRACT_ERROR_missing_guard_declaration);
    }
    
    template<typename F>
    void set_pre(F const& f) { pre_ = f; }

    template<typename F>
    void set_old(F const& f) { old_ = f; }

protected:
    virtual void init() {}
    
    void check_pre(bool throw_on_failure = false) {
        try { if(pre_) pre_(); }
        catch(...) {
            // Subcontracted pre must throw on failure (instead of
            // calling failure handler) so to be checked in logic-or.
            if(throw_on_failure) throw;
            boost::contract::precondition_failed(from());
        }
    }

    void copy_old() {
        // TODO: Document that using .old calls failure handler, = OLDOF makes
        // enclosing function throw instead, when old copy throws.
        try { if(old_) old_(); }
        catch(...) { boost::contract::postcondition_failed(from()); }
    }
    
    boost::contract::from from() const { return from_; }

private:
    bool BOOST_CONTRACT_ERROR_missing_guard_declaration;
    boost::contract::from from_;
    boost::function<void ()> pre_;
    boost::function<void ()> old_;
};

} } } // namespace

#endif // #include guard

