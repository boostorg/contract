
#ifndef BOOST_CONTRACT_AUX_CHECK_SUBCONTRACTED_PRE_POST_INV_HPP_
#define BOOST_CONTRACT_AUX_CHECK_SUBCONTRACTED_PRE_POST_INV_HPP_

#include <boost/contract/virtual_body.hpp>
#include <boost/contract/exception.hpp>
#include <boost/contract/config.hpp>
#include <boost/contract/aux_/check/pre_post_inv.hpp>
#include <boost/contract/aux_/type_traits/bases.hpp>
#include <boost/contract/aux_/virtual_call.hpp>
#include <boost/contract/aux_/exception.hpp>
#include <boost/contract/aux_/none.hpp>
#include <boost/contract/aux_/debug.hpp>
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

// TODO: Fix !CONFIG_PERMISSIVE static assertions.
//#if !BOOST_CONTRACT_CONFIG_PERMISSIVE
//    BOOST_STATIC_ASSERT_MSG(!boost::contract::aux::has_mutable_invariant<
//            Class>::value, "class invariant function must be const");
//    BOOST_STATIC_ASSERT_MSG(
//        (!boost::mpl::and_<
//            boost::contract::aux::has_bases<Class>,
//            boost::mpl::or_<
//                boost::is_same<Intro, boost::contract::aux::none>,
//                boost::is_same<Func, boost::contract::aux::none>
//            >
//        >::value),
//        "must specify introspection type, function type, and function "
//        "arguments for member contract of class with bases"
//    );
//    // TODO: static_assert(Func == none || class<Func>::type == Class)
//#endif


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

public:
    explicit subcontracted_pre_post_inv(
        boost::contract::from const from,
        boost::contract::virtual_body const virt, Class* const obj,
        Arg0 arg0
    ) :
        boost::contract::aux::check::pre_post_inv<Class>(from, obj),
        virt_(virt),
        arg0_(arg0)
    { init(); }
    
    explicit subcontracted_pre_post_inv(boost::contract::from const from,
            boost::contract::virtual_body const virt, Class* const obj) :
        boost::contract::aux::check::pre_post_inv<Class>(from, obj),
        virt_(virt)
    { init(); }

    virtual ~subcontracted_pre_post_inv() {}
    
protected:
    void copy_subcontracted_oldof() {
        boost::mpl::for_each<base_ptrs>(check_base_.action(
                boost::contract::aux::virtual_call::copy_oldof));
        // Old-of values always copied on stack for derived func being called.
    }
    
    void check_subcontracted_entry_inv() {
        boost::mpl::for_each<base_ptrs>(check_base_.action(
                boost::contract::aux::virtual_call::check_entry_inv));
        this->check_entry_inv();
    }
    
    // Allow to throw on failure for relaxing subcontracted pre.
    void check_subcontracted_pre(bool const throw_on_failure = false) {
        try {
            boost::mpl::for_each<base_ptrs>(check_base_.action(
                    boost::contract::aux::virtual_call::check_pre));
            // Pre logic-or: Last check, error also throws.
            this->check_pre(throw_on_failure);
        } catch(boost::contract::aux::no_error const&) {
            // Pre logic-or: Stop at 1st no_error (thrown by callee).
        }
    }

    void check_subcontracted_exit_inv() {
        boost::mpl::for_each<base_ptrs>(check_base_.action(
                boost::contract::aux::virtual_call::check_exit_inv));
        this->check_exit_inv();
    }

    void check_subcontracted_post() {
        boost::mpl::for_each<base_ptrs>(check_base_.action(
                boost::contract::aux::virtual_call::check_post));
        this->check_post();
    }

    boost::contract::virtual_body virtual_call() { return virt_; }

private:
    void init() {
        if(!virt_) {
            virt_ = boost::contract::virtual_body(
                    new boost::contract::aux::virtual_call());
        }
        check_base_.nest(this);
    }

    class check_base {
    public:
        explicit check_base() : nest_(0),
                action_(boost::contract::aux::virtual_call::user_call) {}

        void nest(subcontracted_pre_post_inv* n) { nest_ = n; }

        check_base& action(
                boost::contract::aux::virtual_call::action_type const a) {
            action_ = a;
            return *this;
        }

        template<class Base>
        void operator()(Base*) {
            typedef typename boost::function_types::result_type<Func>::type
                    result_type;
            typedef typename boost::mpl::pop_front<
                typename boost::function_types::parameter_types<Func>::type
            >::type arg_types;
            typedef typename boost::mpl::eval_if<
                boost::is_same<typename boost::mpl::back<arg_types>::type,
                        boost::contract::virtual_body>
            ,
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
            
            BOOST_CONTRACT_AUX_DEBUG(nest_);
            Base* const base = nest_->object();
            BOOST_CONTRACT_AUX_DEBUG(base);
            
            boost::contract::aux::virtual_call::action_type a =
                    nest_->virt_->action;
            nest_->virt_->action = action_;
            try {
                (base->*base_virtual_func)(nest_->arg0_, nest_->virt_);
            } catch(boost::contract::aux::no_error const&) {
                if(nest_->virt_->action ==
                        boost::contract::aux::virtual_call::check_pre) {
                    nest_->virt_->action = a;
                    throw; // Pre logic-or: 1st no_err stops (throw to caller).
                }
            } catch(...) {
                if(nest_->virt_->action ==
                        boost::contract::aux::virtual_call::check_pre) {
                    // Pre logic-or: Ignore err, possibly checks up to caller.
                }
            }
            nest_->virt_->action = a;
        }

        subcontracted_pre_post_inv* nest_;
        boost::contract::aux::virtual_call::action_type action_;
    };

    check_base check_base_;
    boost::contract::virtual_body virt_;
    // TODO: add_reference/perfect fwd to all these Arg-i types.
    // TODO: Support 0-to-n args.
    Arg0 arg0_;
};

} } } } // namespace

#endif // #include guard

