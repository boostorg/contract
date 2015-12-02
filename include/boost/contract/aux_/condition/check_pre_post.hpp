
#ifndef BOOST_CONTRACT_AUX_CHECK_PRE_POST_HPP_
#define BOOST_CONTRACT_AUX_CHECK_PRE_POST_HPP_

#include <boost/contract/core/exception.hpp>
#include <boost/contract/aux_/condition/check_base.hpp>
#include <boost/contract/aux_/type_traits/optional.hpp>
#include <boost/contract/aux_/debug.hpp>
#include <boost/contract/aux_/none.hpp>
/** @cond */
#include <boost/optional.hpp>
#include <boost/function.hpp>
#include <boost/type_traits/remove_reference.hpp>
#include <boost/mpl/if.hpp>
#include <boost/config.hpp>
/** @endcond */

namespace boost { namespace contract { namespace aux {

// TODO: Does this need to be copied? Copying function<> could copy captures (if function is a lambda) and it could be expensive... check all classes that MUST be copyable, make sure their copies are efficient, make all other classes noncopyable. Same consideration for all other classes, make noncopyable all classes that do not have to be necessarily copyable.

template<typename R>
class check_pre_post : public check_base {
    typedef typename boost::mpl::if_<is_optional<R>,
        boost::optional<typename boost::remove_reference<
                typename optional_value_type<R>::type>::type const&> const&
    ,
        R const&
    >::type r_cref;

public:
    explicit check_pre_post(boost::contract::from from) : check_base(from) {}

    virtual ~check_pre_post() BOOST_NOEXCEPT_IF(false) {}

    template<typename F>
    void set_post(F const& f) {
        BOOST_CONTRACT_ERROR_postcondition_result_parameter_required = f;
    }

protected:
    void check_post(r_cref const& r) {
        if(failed()) return;
        try {
            if(BOOST_CONTRACT_ERROR_postcondition_result_parameter_required) {
                BOOST_CONTRACT_ERROR_postcondition_result_parameter_required(r);
            }
        } catch(...) { fail(&boost::contract::postcondition_failed); }
    }
    
private:
    boost::function<void (r_cref)>
            BOOST_CONTRACT_ERROR_postcondition_result_parameter_required;
};

template<>
class check_pre_post<none> : public check_base {
public:
    explicit check_pre_post(boost::contract::from from) : check_base(from) {}

    virtual ~check_pre_post() {}

    template<typename F>
    void set_post(F const& f) {
        BOOST_CONTRACT_ERROR_postcondition_result_parameter_not_allowed = f;
    }

protected:
    void check_post(none const&) {
        if(failed()) return;
        try {
            if(BOOST_CONTRACT_ERROR_postcondition_result_parameter_not_allowed){
  BOOST_CONTRACT_ERROR_postcondition_result_parameter_not_allowed();
            }
        } catch(...) { fail(&boost::contract::postcondition_failed); }
    }
    
private:
    boost::function<void ()>
            BOOST_CONTRACT_ERROR_postcondition_result_parameter_not_allowed;
};

} } }

#endif // #include guard

