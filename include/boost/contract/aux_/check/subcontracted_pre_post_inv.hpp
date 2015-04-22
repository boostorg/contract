
#ifndef BOOST_CONTRACT_AUX_CHECK_SUBCONTRACTED_PRE_POST_INV_HPP_
#define BOOST_CONTRACT_AUX_CHECK_SUBCONTRACTED_PRE_POST_INV_HPP_

#include <boost/contract/config.hpp>
#include <boost/contract/virtual_body.hpp>
#include <boost/contract/aux_/check/pre_post_inv.hpp>
#include <boost/contract/aux_/type_traits/bases.hpp>
#include <boost/contract/aux_/exception.hpp>
#include <boost/contract/aux_/none.hpp>
#include <boost/contract/aux_/debug.hpp>
#include <boost/contract/virtual_body.hpp>
#include <boost/function_types/result_type.hpp>
#include <boost/function_types/parameter_types.hpp>
#include <boost/function_types/member_function_pointer.hpp>
#include <boost/type_traits/add_pointer.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/mpl/for_each.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/mpl/transform.hpp>
#include <boost/mpl/pop_front.hpp>
#include <boost/mpl/push_front.hpp>
#include <boost/mpl/push_back.hpp>
#include <boost/mpl/back.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/noncopyable.hpp>

// TODO: Modelling after Clang message for assert() failure:
// assertion "(Key != boost::contract::aux::constructor)" failed: file "..\include/boost/contract/aux_/function.hpp", line 156
// This library should say:
// precondition/postcondition/invariant/... "..." failed: file "...", line ...
// for exception classes precondition/postcondition/..._failure (inheriting from
// assertion_failure base exception to be thrown by CONTRACT_ASSERT) and failure
// handlers [set_]precondition_failed.

namespace boost { namespace contract { namespace aux { namespace check {

template<
    class Class,
    class Intro = boost::contract::aux::none,
    typename Func = boost::contract::aux::none,
    typename Arg0 = boost::contract::aux::none
> class subcontracted_pre_post_inv :
    public boost::contract::aux::check::pre_post_inv<Class>,
    private boost::noncopyable // Avoid copying captured function arguments.
{
    // Base types as pointers because mpl::for_each will construct them.
    typedef typename boost::mpl::transform<
        typename boost::mpl::eval_if<boost::contract::aux::type_traits::
                has_bases<Class>,
            boost::contract::aux::type_traits::bases_of<Class>
        ,
            boost::mpl::identity<boost::mpl::vector<> >
        >::type,
        boost::add_pointer<boost::mpl::placeholders::_1>
    >::type base_ptrs;

#if !BOOST_CONTRACT_CONFIG_PERMISSIVE
    // TODO: Fix those.
    //BOOST_STATIC_ASSERT_MSG(!boost::contract::aux::has_mutable_invariant<
    //        Class>::value, "class invariant function must be const");
    //BOOST_STATIC_ASSERT_MSG(
    //    (!boost::mpl::and_<
    //        boost::contract::aux::has_bases<Class>,
    //        boost::mpl::or_<
    //            boost::is_same<Intro, boost::contract::aux::none>,
    //            boost::is_same<Func, boost::contract::aux::none>
    //        >
    //    >::value),
    //    "must specify introspection type, function type, and function "
    //    "arguments for member contract of class with bases"
    //);
    // TODO: static_assert(Func == none || class<Func>::type == Class)
#endif

public:
    explicit subcontracted_pre_post_inv(Class* const obj, Arg0 arg0) :
        boost::contract::aux::check::pre_post_inv<Class>(obj),
        arg0_(arg0)
    {}
    
    explicit subcontracted_pre_post_inv(Class* const obj) : boost::contract::
            aux::check::pre_post_inv<Class>(obj) {
    }
    
protected:
    void check_subcontracted_inv(bool const static_inv_only = false) {
        boost::mpl::for_each<base_ptrs>(check_base(*this,
            static_inv_only ?
                boost::contract::virtual_body::check_static_inv_only
            :
                boost::contract::virtual_body::check_inv_only
        ));
        this->check_inv(static_inv_only);
    }

    void check_subcontracted_pre() {
        try {
            boost::mpl::for_each<base_ptrs>(check_base(*this,
                    boost::contract::virtual_body::check_pre_only));
            this->check_pre(); // Pre logic-or: Last check, error also throws.
        } catch(boost::contract::aux::no_error const&) {
            // Pre logic-or: Stop at 1st no_error (thrown by callee).
        }
    }

    void check_subcontracted_post() {
        boost::mpl::for_each<base_ptrs>(check_base(*this,
                boost::contract::virtual_body::check_post_only));
        this->check_post();
    }

    class check_base {
    public:
        explicit check_base(subcontracted_pre_post_inv& outer,
                boost::contract::virtual_body const virt) :
            outer_(outer), virt_(virt)
        {}

        template<class Base>
        void operator()(Base*) {
            typedef typename boost::function_types::result_type<Func>::type
                    result_type;
            typedef typename boost::mpl::pop_front<
                typename boost::function_types::parameter_types<Func>::type
            >::type arg_types;
            typedef typename boost::mpl::eval_if<boost::is_same<typename boost::
                    mpl::back<arg_types>::type, boost::contract::virtual_body>,
                boost::mpl::identity<arg_types>
            ,
                boost::mpl::push_back<arg_types, boost::contract::virtual_body>
            >::type virtual_arg_types;

            call_base_function<Base, result_type, virtual_arg_types>(
                boost::mpl::bool_<Intro::template has_member_function<Base,
                        result_type, virtual_arg_types>::value>()
            );
        }

    private:
        template<class Base, typename ResultType, class VirtualArgTypes>
        void call_base_function(boost::mpl::false_ const&) {}
        template<class Base, typename ResultType, class VirtualArgTypes>
        void call_base_function(boost::mpl::true_ const&) {
            typedef typename boost::mpl::push_front<
                typename boost::mpl::push_front<VirtualArgTypes, Base*>::type,
                ResultType
            >::type base_virtual_func_types;
            typedef typename boost::function_types::member_function_pointer<
                    base_virtual_func_types>::type base_virtual_func_ptr;

            base_virtual_func_ptr base_virtual_func = Intro::template
                    member_function_address<Base, base_virtual_func_ptr>();
            BOOST_CONTRACT_AUX_DEBUG(base_virtual_func);
            
            Base* const base = outer_.object();
            BOOST_CONTRACT_AUX_DEBUG(base);
            
            try {
                (base->*base_virtual_func)(outer_.arg0_, virt_);
            } catch(boost::contract::aux::no_error const&) {
                if(virt_.action == boost::contract::virtual_body::
                        check_pre_only) {
                    throw; // Pre logic-or: 1st no_err stops (throw to caller).
                }
            } catch(...) {
                if(virt_.action == boost::contract::virtual_body::
                        check_pre_only) {
                    // Pre logic-or: Ignore err, possibly checks up to caller.
                }
            }
        }

        subcontracted_pre_post_inv& outer_;
        boost::contract::virtual_body virt_;
    };

    // TODO: add_reference/perfect fwd to all these Arg-i types.
    // TODO: Support 0-to-n args.
    Arg0 arg0_;
};

} } } } // namespace

#endif // #include guard

