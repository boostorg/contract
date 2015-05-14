
#ifndef BOOST_CONTRACT_AUX_BIND_HPP_
#define BOOST_CONTRACT_AUX_BIND_HPP_

#include <boost/contract/core/call.hpp>
#include <boost/contract/aux_/condition/check_nothing.hpp>
#include <boost/contract/aux_/call.hpp>
#include <boost/contract/aux_/exception.hpp>
#include <boost/contract/aux_/none.hpp>
/** @cond */
#include <boost/make_shared.hpp>
#include <boost/function_types/is_member_pointer.hpp>
/** @endcond */

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
        // Cannot check std::uncaught_exception here because it is up to
        // specific function contract to check that and decide what to check if
        // body threw (e.g., ctors do not check exit inv on throw but dtors do).
        execute(boost::contract::aux::call::check_exit_inv);
        execute(boost::contract::aux::call::check_post);
    }

private:
    void execute(boost::contract::aux::call::action_enum a) {
        c_.call_->action = a;
        try { // Call contract decl func for given action.
            call(boost::mpl::bool_<boost::function_types::
                    is_member_pointer<F>::value>(), a0_, a1_);
        } catch(boost::contract::aux::no_error&) {
            // no_error exception used to signal OK (so just continue).
        } // Else: If other exceptions, throw them to caller.
    }

    // Overload dispatch to correct call: 1st arg determines if member call or
    // not, other arguments determine arity when they are not none type.

    template<typename T0>
    void call(boost::mpl::false_ const&, T0 const&,
            boost::contract::aux::none const&) {
        (*f_)(a0_, c_);
    }
    template<typename T0, typename T1>
    void call(boost::mpl::false_ const&, T0 const&, T1 const&) {
        (*f_)(a0_, a1_, c_);
    }

    template<typename T0>
    void call(boost::mpl::true_ const&, T0 const&,
            boost::contract::aux::none const&) {
        (a0_->*f_)(c_);
    }
    template<typename T0, typename T1>
    void call(boost::mpl::true_ const&, T0 const&, T1 const&) {
        (a0_->*f_)(a1_, c_);
    }

    boost::contract::call c_; // Copy as ptr.
    F f_; // Copy as func. ptr.
    A0 const& a0_; // Object for member func ptrs, 1st func arg otherwise.
    A1 const& a1_;
};


} } } // namespace

#endif // #include guard

