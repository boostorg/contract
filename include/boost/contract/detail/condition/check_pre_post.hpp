
#ifndef BOOST_CONTRACT_DETAIL_CHECK_PRE_POST_HPP_
#define BOOST_CONTRACT_DETAIL_CHECK_PRE_POST_HPP_

// Copyright (C) 2008-2016 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0 (see accompanying
// file LICENSE_1_0.txt or a copy at http://www.boost.org/LICENSE_1_0.txt).
// See: http://www.boost.org/doc/libs/release/libs/contract/doc/html/index.html

#include <boost/contract/core/exception.hpp>
#include <boost/contract/core/config.hpp>
#include <boost/contract/detail/condition/check_base.hpp>
#include <boost/contract/detail/none.hpp>
#ifndef BOOST_CONTRACT_NO_POSTCONDITIONS
    #include <boost/contract/detail/type_traits/optional.hpp>
    #include <boost/optional.hpp>
    #include <boost/function.hpp>
    #include <boost/type_traits/remove_reference.hpp>
    #include <boost/mpl/if.hpp>
#endif

/* PRIVATE */

#define BOOST_CONTRACT_DETAIL_CHECK_PRE_POST_DEF_( \
        result_type, result_param, ftor_type, ftor_var, ftor_call) \
    public: \
        template<typename F> \
        void set_post(F const& f) { ftor_var = f; } \
    \
    protected: \
        void check_post(result_type const& result_param) { \
            if(failed()) return; \
            try { if(ftor_var) { ftor_call; } } \
            catch(...) { fail(&boost::contract::postcondition_failure); } \
        } \
    \
    private: \
        boost::function<ftor_type> ftor_var; /* Boost.Func for lambdas, etc. */

/* CODE */

namespace boost { namespace contract { namespace detail {

template<typename VR>
class check_pre_post : public check_base { // Non-copyable base.
public:
    explicit check_pre_post(boost::contract::from from) : check_base(from) {}
    
    #ifndef BOOST_CONTRACT_NO_POSTCONDITIONS
private:
        typedef typename boost::mpl::if_<is_optional<VR>,
            boost::optional<typename boost::remove_reference<typename
                    optional_value_type<VR>::type>::type const&> const&
        ,
            VR const&
        >::type r_type;

        BOOST_CONTRACT_DETAIL_CHECK_PRE_POST_DEF_(
            r_type,
            r,
            void (r_type),
            // Won't raise this error if NO_POST (for optimization).
            BOOST_CONTRACT_ERROR_postcondition_result_parameter_required,
            BOOST_CONTRACT_ERROR_postcondition_result_parameter_required(r)
        )
    #endif
};

template<>
class check_pre_post<none> : public check_base { // Non-copyable base.
public:
    explicit check_pre_post(boost::contract::from from) : check_base(from) {}
    
    #ifndef BOOST_CONTRACT_NO_POSTCONDITIONS
        BOOST_CONTRACT_DETAIL_CHECK_PRE_POST_DEF_(
            none,
            unused,
            void (),
            // Won't raise this error if NO_POST (for optimization).
            BOOST_CONTRACT_ERROR_postcondition_result_parameter_not_allowed,
            BOOST_CONTRACT_ERROR_postcondition_result_parameter_not_allowed()
        )
    #endif
};

} } } // namespace

#endif // #include guard

