
#ifndef BOOST_CONTRACT_AUX_CHECK_PRE_POST_HPP_
#define BOOST_CONTRACT_AUX_CHECK_PRE_POST_HPP_

#include <boost/contract/core/exception.hpp>
#include <boost/contract/aux_/condition/check_nothing.hpp>
#include <boost/contract/aux_/call.hpp>
#include <boost/contract/aux_/exception.hpp>
/** @cond */
#include <boost/shared_ptr.hpp>
#include <boost/function.hpp>
/** @endcond */

namespace boost { namespace contract { namespace aux {

// TODO: Does this need to be copied? Copying function<> could copy captures
// (if function is a lambda) and it could be expensive... check all classes
// that MUST be copiable, make sure their copies are effecient, make all other
// calsses noncopyable.
class check_pre_post : public boost::contract::aux::check_nothing {
public:
    explicit check_pre_post(boost::contract::from from) : from_(from) {}
    
    explicit check_pre_post(boost::contract::from from, boost::shared_ptr<
            boost::contract::aux::call> call) :
        from_(from), contract_call_(call)
    {}

    virtual ~check_pre_post() {}

    template<typename F>
    void set_pre(F f) { pre_ = f; pre_available(); }

    template<typename F>
    void set_post(F f) { post_ = f; post_available(); }

protected:
    void check_pre(bool throw_on_failure = false) {
        if(!contract_call_ || contract_call_->action ==
                boost::contract::aux::call::check_pre) {
            if(pre_) {
                try { pre_(); }
                catch(...) {
                    // Subcontracted pre must throw on failure (instead of
                    // calling failure handler) so to be checked in logic-or.
                    if(throw_on_failure) throw;
                    boost::contract::precondition_failed(from_);
                }
            }
            if(contract_call_) throw boost::contract::aux::no_error();
        }
    }

    // TODO: I should be able to get rid of throw no_error everywhere (because
    // the checking call_ allows the rest of the code to just do nothing). That
    // way post and exit_inv checking can go in dtor also when bind is used.
    // That will require to use scoped contract = ... also in contract decl
    // functions.
    // Then I should be able to set a state in c to false when a
    // contract decl func is first called and then to true after the
    // scoped contract = ... assignment is done. OLDOF can check that state so
    // if I add from bind a call with action coped_entry_oldof and
    // copy_oldof_after_pre_and_inv, I can then support copying old values
    // after pre/inv have been checked also in contract decl func when users
    // simply assign old values old_x = OLDOF(c, ...) after the contract decl
    // (old_x variable will always have to be decl before the contract decl, but
    // assigned before the contract decl to be copied before pre/inv, or after
    // the contract decl to be copied after pre/inv). The same syntax, assigned
    // before/after contract decl, can be used when bind is not used (that
    // should work without changing current impl).
    
    // If call(), can't call from a dtor (as throw no_error on OK).
    void check_post() {
        if(!contract_call_ || contract_call_->action ==
                boost::contract::aux::call::check_post) {
            if(post_) {
                try { post_(); }
                catch(...) { boost::contract::postcondition_failed(from_); }
            }
            if(contract_call_) throw boost::contract::aux::no_error();
        }
    }
    
    virtual void pre_available() {}
    virtual void post_available() {}

    boost::contract::from from() const { return from_; }

    boost::shared_ptr<boost::contract::aux::call> contract_call() {
        return contract_call_;
    }

private:
    boost::function<void ()> pre_;
    boost::function<void ()> post_;
    boost::contract::from from_;
    boost::shared_ptr<boost::contract::aux::call> contract_call_;
};

} } }

#endif // #include guard

