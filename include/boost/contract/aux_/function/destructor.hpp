
#ifndef BOOST_CONTRACT_AUX_DESTRUCTOR_HPP_
#define BOOST_CONTRACT_AUX_DESTRUCTOR_HPP_

#include <boost/contract/core/exception.hpp>
#include <boost/contract/aux_/condition/check_pre_post_inv.hpp>
#include <boost/contract/aux_/call.hpp>
/** @cond */
#include <exception>
/** @endcond */

namespace boost { namespace contract { namespace aux {

template<class C>
class destructor : public boost::contract::aux::check_pre_post_inv<C> {
public:
    explicit destructor(C const* obj) :
        boost::contract::aux::check_pre_post_inv<C>(
                boost::contract::from_destructor, obj)
    { init(); }
    
    explicit destructor(boost::shared_ptr<boost::contract::aux::call> call,
            C const* obj) :
        boost::contract::aux::check_pre_post_inv<C>(
                boost::contract::from_destructor, call, obj)
    { init(); }

private:
    // Obj still exists (before dtor body) so check static and non-static inv
    // (subcontracting implemented automatically via C++ object destruction
    // mechanism, so no calls to check_subcontracted_... in this case).
    void init() {
        this->check_entry_inv();
        if(this->contract_call()) {
            this->check_exit_inv(/* static_inv_only = */
                    !std::uncaught_exception());
        }
    }

    // Dtor cannot have pre because it has no parameters.
    
    // Ctor post always checked after body, at exit (see below).
    // NOTE: Even if there is no obj after dtor body, this library allows for
    // dtor post (e.g., to check static members for an instance counter class).
    void post_available() /* override */ {
        if(this->contract_call() && !std::uncaught_exception()) {
            this->check_post();
        }
    }
    
public:
    // If dtor body threw, obj still exists so check subcontracted static and
    // non-static inv (but no post because of throw), otherwise obj destructed
    // so check static static inv and post (subcontracting implemented
    // automatically via C++ object destruction mechanism, so no calls to
    // check_subcontracted_... in this case).
    // NOTE: In theory C++ destructors should not throw, but the language allows
    // for that so this library must handle such a case.
    ~destructor() {
        if(!this->contract_call()) {
            this->check_exit_inv(/* static_inv_only = */
                    !std::uncaught_exception());
            if(!std::uncaught_exception()) this->check_post();
        }
    }
};

} } } // namespace

#endif // #include guard

