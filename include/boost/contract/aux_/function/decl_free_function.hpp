
#ifndef BOOST_CONTRACT_AUX_BIND_FREE_FUNCTION_HPP_
#define BOOST_CONTRACT_AUX_BIND_FREE_FUNCTION_HPP_

#include <boost/contract/core/decl.hpp>
#include <boost/contract/aux_/condition/check_base.hpp>
#include <boost/contract/aux_/call.hpp>
#include <boost/contract/aux_/exception.hpp>
#include <boost/contract/aux_/none.hpp>
/** @cond */
#include <boost/make_shared.hpp>
/** @endcond */

namespace boost { namespace contract { namespace aux {

template<typename FPtr, typename A0, typename A1>
class decl_free_function : public check_base { // Copyable (as * and &).
public:
    explicit decl_free_function(FPtr f, A0 const& a0, A1 const& a1) :
        c_(boost::make_shared<boost::contract::aux::call>()),
        f_(f), a0_(a0), a1_(a1)
    {
        execute(call::copy_oldof);
        execute(call::check_pre);
    }
    
    ~decl_free_function() {
        execute(call::check_post);
    }

private:
    void execute(call::action_enum a) {
        c_.call_->action = a;
        c_.call_->after_contract = false;
        try { call(a0_, a1_); }
        catch(no_error&) {} // Continue (no_error signals OK).
    }

    void call(none const&, none const&) { (*f_)(c_); }

    template<typename T0>
    void call(T0 const&, none const&) { (*f_)(a0_, c_); }

    template<typename T0, typename T1>
    void call(T0 const&, T1 const&) { (*f_)(a0_, a1_, c_); }

    boost::contract::decl c_; // Copyable as *.
    FPtr f_;
    A0 const& a0_; // TODO: Support configurable func arity.
    A1 const& a1_;
};


} } } // namespace

#endif // #include guard

