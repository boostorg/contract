
#ifndef BOOST_CONTRACT_AUX_CHECK_PRE_POST_HPP_
#define BOOST_CONTRACT_AUX_CHECK_PRE_POST_HPP_

#include <boost/contract/core/exception.hpp>
#include <boost/contract/aux_/condition/check_pre_only.hpp>
#include <boost/contract/aux_/debug.hpp>
#include <boost/contract/aux_/none.hpp>
/** @cond */
#include <boost/optional.hpp>
#include <boost/function.hpp> // TODO: Can I reduce boost.function overhead?
/** @endcond */

namespace boost { namespace contract { namespace aux {

// TODO: Does this need to be copied? Copying function<> could copy captures
// (if function is a lambda) and it could be expensive... check all classes
// that MUST be copiable, make sure their copies are effecient, make all other
// calsses noncopyable.

// TODO: This also handles R = boost::optional<...> but the case where base and
// derived function used mixed (one does not use optional but the other does)
// still gives a run-time error because optional is not set (at least when
// the base uses optional but the derived does not). Fix that.

template<typename R>
class check_pre_post : public check_pre_only {
public:
    explicit check_pre_post(boost::contract::from from) :
            check_pre_only(from) {}

    virtual ~check_pre_post() {}

    template<typename F>
    void set_post(F const& f) {
        BOOST_CONTRACT_ERROR_postcondition_result_parameter_required = f;
        post_available();
    }

protected:
    void check_post(R& r) {
        try {
            if(BOOST_CONTRACT_ERROR_postcondition_result_parameter_required) {
                BOOST_CONTRACT_ERROR_postcondition_result_parameter_required(r);
            }
        } catch(...) { boost::contract::postcondition_failed(from()); }
    }
    
    virtual void post_available() {}

private:
    boost::function<void (R const&)>
    BOOST_CONTRACT_ERROR_postcondition_result_parameter_required;
};

// TODO: Try to limit code repetition between code below and above.
template<>
class check_pre_post<none> : public check_pre_only {
public:
    explicit check_pre_post(boost::contract::from from) :
            check_pre_only(from) {}

    virtual ~check_pre_post() {}

    template<typename F>
    void set_post(F const& f) {
        BOOST_CONTRACT_ERROR_postcondition_result_parameter_not_allowed = f;
        post_available();
    }

protected:
    void check_post() {
        try {
            if(BOOST_CONTRACT_ERROR_postcondition_result_parameter_not_allowed){
  BOOST_CONTRACT_ERROR_postcondition_result_parameter_not_allowed();
            }
        } catch(...) { boost::contract::postcondition_failed(from()); }
    }
    
    void check_post(none&) { check_post(); }
    
    virtual void post_available() {}

private:
    boost::function<void ()>
    BOOST_CONTRACT_ERROR_postcondition_result_parameter_not_allowed;
};

} } }

#endif // #include guard

