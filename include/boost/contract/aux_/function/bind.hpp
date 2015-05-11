
#ifndef BOOST_CONTRACT_AUX_BIND_HPP_
#define BOOST_CONTRACT_AUX_BIND_HPP_

#include <boost/contract/core/call.hpp>
#include <boost/contract/aux_/condition/check_nothing.hpp>
#include <boost/contract/aux_/call.hpp>
#include <boost/contract/aux_/exception.hpp>
#include <boost/make_shared.hpp>
#include <boost/function_types/is_member_pointer.hpp>

namespace boost { namespace contract { namespace aux {

template<typename F, typename A0, typename A1>
class bind : // Shallow ptr copies or &.
        public boost::contract::aux::check_nothing {
public:
    explicit bind(F f, A0 const& a0, A1 const& a1) :
            c_(boost::make_shared<boost::contract::aux::call>()),
            f_(f), a0_(a0), a1_(a1)
    {
        execute(boost::contract::aux::call::copy_oldof);
        execute(boost::contract::aux::call::check_entry_inv);
        execute(boost::contract::aux::call::check_pre);
    }
    
    ~bind() {
        if(!std::uncaught_exception()) { // Body did not throw.
            execute(boost::contract::aux::call::check_exit_inv);
            execute(boost::contract::aux::call::check_post);
        }
    }

private:
    void execute(boost::contract::aux::call::action_enum a) {
        c_.call_->action = a;
        try { // Call contract decl func for given action.
            call(boost::mpl::bool_<boost::function_types::
                    is_member_pointer<F>::value>());
        } catch(boost::contract::aux::no_error&) {
            // no_error exception used to signal OK (so just continue).
        } // Else: If other exceptions, throw them to caller.
    }

    void call(boost::mpl::false_ const&) {
        (*f_)(a0_, a1_, c_);
    }
    void call(boost::mpl::true_ const&) {
        (a0_->*f_)(a1_, c_);
    }

    boost::contract::call c_; // Copy as ptr.
    F f_; // Copy as func. ptr.
    A0 const& a0_; // Object for member func ptrs, 1st func arg otherwise.
    A1 const& a1_;
};


} } } // namespace

#endif // #include guard

