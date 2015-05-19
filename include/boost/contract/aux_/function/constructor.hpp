
#ifndef BOOST_CONTRACT_AUX_CONSTRUCTOR_HPP_
#define BOOST_CONTRACT_AUX_CONSTRUCTOR_HPP_

#include <boost/contract/core/exception.hpp>
#include <boost/contract/aux_/condition/check_pre_post_inv.hpp>
/** @cond */
#include <exception>
/** @endcond */

namespace boost { namespace contract { namespace aux {

template<class C>
class constructor :
        // Ctor subcontracting impl via C++ obj construction mechanism.
        public boost::contract::aux::check_pre_post_inv<C> {
public:
    explicit constructor(boost::shared_ptr<boost::contract::aux::call> call,
            C const* obj) :
        boost::contract::aux::check_pre_post_inv<C>(boost::contract::
                from_constructor, call, obj)
    { init(); }
    
    explicit constructor(C const* obj) : boost::contract::aux::
            check_pre_post_inv<C>(boost::contract::from_constructor, obj)
    { init(); }

private:
    void init() {
        // No object before ctor body so only static inv at entry.
        this->check_entry_inv(/* static_inv_only = */ true);
        if(this->decl_call()) { // Throw no error (so not in dtor).
            this->check_exit_inv(/* static_inv_only = */
                    std::uncaught_exception());
        }
    }

    // Ctor pre checked by constructor_precondition at start of init list.

    void post_available() /* override */ {
        if(this->decl_call() && !std::uncaught_exception()) {
            this->check_post(); // Throw no_error (so not in dtor).
        }
    }

public:
    // If ctor body threw, only check static inv, otherwise obj constructed so
    // check also non-static inv and post (subcontracting implemented
    // automatically via C++ object constructor mechanism, so no calls to
    // check_subcontracted_... in this case).
    ~constructor() {
        if(!this->decl_call()) {
            this->check_exit_inv(/* static_inv_only = */
                    std::uncaught_exception());
            if(!std::uncaught_exception()) this->check_post();
        }
    }
};

} } } // namespace

#endif // #include guard

