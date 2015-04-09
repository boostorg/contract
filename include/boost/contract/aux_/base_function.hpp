
#ifndef BOOST_CONTRACT_AUX_BASE_FUNCTION_HPP_
#define BOOST_CONTRACT_AUX_BASE_FUNCTION_HPP_

#include <boost/contract/virtual_body.hpp>
#include <boost/contract/aux_/exception.hpp>
#include <boost/contract/aux_/none.hpp>
#include <boost/function_types/result_type.hpp>
#include <boost/function_types/parameter_types.hpp>
#include <boost/function_types/member_function_pointer.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/mpl/pop_front.hpp>
#include <boost/mpl/push_front.hpp>
#include <boost/mpl/push_back.hpp>
#include <boost/mpl/back.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/identity.hpp>
#include <cassert>

namespace boost { namespace contract { namespace aux {

template<
    class Intro,
    class Class,
    typename FuncPtr,
    typename Arg0
> class function;

template< class Intro, class Class, typename FuncPtr, typename Arg0 >
class base_function {
    typedef boost::contract::aux::function<Intro, Class, FuncPtr, Arg0>
            derived_function_type;
        
    typedef typename boost::function_types::result_type<FuncPtr>::type
            result_type;
    typedef typename boost::mpl::pop_front<typename boost::function_types::
            parameter_types<FuncPtr>::type>::type arg_types;
    typedef typename boost::mpl::eval_if<boost::is_same<typename
            boost::mpl::back<arg_types>::type, boost::contract::virtual_body>,
        boost::mpl::identity<arg_types>
    ,
        boost::mpl::push_back<arg_types, boost::contract::virtual_body>
    >::type virtual_arg_types;

public:
    base_function ( ) : virt_(boost::contract::virtual_body::user_call) {}

    void derived_function ( derived_function_type* derived_func ) {
        derived_func_ = derived_func;
    }

    base_function& action ( boost::contract::virtual_body const virt ) {
        virt_ = virt;
        return *this;
    }

    template< class Base >
    void operator() ( Base* ) {
        call<Base>(boost::mpl::bool_<Intro::template has_member_function<
                Base, result_type, virtual_arg_types>::value>());
    }

private:
    template< class Base > void call ( boost::mpl::false_ const& ) {}
    template< class Base > void call ( boost::mpl::true_ const& ) {
        typedef typename boost::mpl::push_front<
            typename boost::mpl::push_front<virtual_arg_types, Base*>::type,
            result_type
        >::type base_virtual_func_types;
        typedef typename boost::function_types::member_function_pointer<
                base_virtual_func_types>::type base_virtual_func_ptr;
        base_virtual_func_ptr base_virtual_func = Intro::template
                member_function_address<Base, base_virtual_func_ptr>();
        assert(base_virtual_func);
        
        assert(derived_func_);
        Base* const base = derived_func_->obj_;
        assert(base);
        
        try {
            (base->*base_virtual_func)(derived_func_->arg0_, virt_);
        } catch(boost::contract::aux::no_error const&) {
            if(virt_.action == boost::contract::virtual_body::check_pre_only) {
                throw; // Pre logic-or: Stop at 1st no_error (throw to caller).
            }
        } catch(...) {
            if(virt_.action == boost::contract::virtual_body::check_pre_only) {
                // Pre logic-or: Ignore errors, possibly checking up to caller.
            }
        }
    }

    derived_function_type* derived_func_;
    boost::contract::virtual_body virt_;
};

template< class Class, typename Arg0 >
struct base_function<boost::contract::aux::none, Class,
        boost::contract::aux::none, Arg0> {
    void derived_function (
        boost::contract::aux::function<boost::contract::aux::none, Class,
                boost::contract::aux::none, Arg0>*
    ) {}

    base_function& action ( boost::contract::virtual_body const ) {
        return *this;
    }
};
    
} } } // namespace

#endif // #include guard

