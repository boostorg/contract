
#ifndef BOOST_CONTRACT_AUX_CHECK_PRE_POST_HPP_
#define BOOST_CONTRACT_AUX_CHECK_PRE_POST_HPP_

#include <boost/contract/core/config.hpp>
#if BOOST_CONTRACT_POSTCONDITIONS
#   include <boost/contract/core/exception.hpp>
#endif
#include <boost/contract/aux_/condition/check_base.hpp>
#include <boost/contract/aux_/type_traits/optional.hpp>
#include <boost/contract/aux_/none.hpp>
#include <boost/optional.hpp>
#if BOOST_CONTRACT_POSTCONDITIONS
#   include <boost/function.hpp>
#endif
#include <boost/type_traits/remove_reference.hpp>
#include <boost/mpl/if.hpp>
#include <boost/preprocessor/control/expr_iif.hpp>

/* PRIVATE */

#define BOOST_CONTRACT_AUX_CHECK_PRE_POST_IMPL_(ftor_var, ftor_call, f_type) \
    public: \
        explicit check_pre_post(boost::contract::from from) : \
                check_base(from) {} \
    \
        template<typename F> \
        void set_post(F const& f) { \
            BOOST_PP_EXPR_IIF(BOOST_CONTRACT_POSTCONDITIONS, \
                ftor_var = f; \
            ) \
        } \
    \
    protected: \
        void check_post(r_type const& r) { \
            BOOST_PP_EXPR_IIF(BOOST_CONTRACT_POSTCONDITIONS, \
                if(failed()) return; \
                try { if(ftor_var) { ftor_call; } } \
                catch(...) { fail(&boost::contract::postcondition_failure); } \
            ) \
        } \
    \
    private: \
        BOOST_PP_EXPR_IIF(BOOST_CONTRACT_POSTCONDITIONS, \
            /* use Boost.Function for lambdas, etc. */ \
            boost::function<f_type> ftor_var; \
        )

/* CODE */

namespace boost { namespace contract { namespace aux {

template<typename R>
class check_pre_post : public check_base { // Non-copyable base.
    typedef typename boost::mpl::if_<is_optional<R>,
        boost::optional<typename boost::remove_reference<
                typename optional_value_type<R>::type>::type const&> const&
    ,
        R const&
    >::type r_type;

    BOOST_CONTRACT_AUX_CHECK_PRE_POST_IMPL_(
        BOOST_CONTRACT_ERROR_postcondition_result_parameter_required,
        BOOST_CONTRACT_ERROR_postcondition_result_parameter_required(r),
        void (r_type)
    )
};

template<>
class check_pre_post<none> : public check_base { // Non-copyable base.
    typedef none r_type;
    
    BOOST_CONTRACT_AUX_CHECK_PRE_POST_IMPL_(
        BOOST_CONTRACT_ERROR_postcondition_result_parameter_not_allowed,
        BOOST_CONTRACT_ERROR_postcondition_result_parameter_not_allowed(),
        void ()
    )
};

} } } // namespace

#endif // #include guard

