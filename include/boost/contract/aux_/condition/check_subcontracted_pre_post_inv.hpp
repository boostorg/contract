
#ifndef BOOST_CONTRACT_AUX_CHECK_SUBCONTRACTED_PRE_POST_INV_HPP_
#define BOOST_CONTRACT_AUX_CHECK_SUBCONTRACTED_PRE_POST_INV_HPP_

#include <boost/contract/core/call.hpp>
#include <boost/contract/aux_/condition/check_pre_post_inv.hpp>
#include <boost/contract/aux_/type_traits/base_types.hpp>
#include <boost/contract/aux_/exception.hpp>
#include <boost/contract/aux_/debug.hpp>
/** @cond */
#include <boost/function_types/result_type.hpp>
#include <boost/function_types/parameter_types.hpp>
#include <boost/function_types/member_function_pointer.hpp>
#include <boost/function_types/property_tags.hpp>
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
#include <boost/make_shared.hpp>
#include <boost/shared_ptr.hpp>
/** @endcond */

namespace boost { namespace contract { namespace aux {

// TODO: Can I make this, other check_... classes, and maybe even other
// calsses noncopyable? What does truly need to be copyable and why?

template<class I, class C, typename A0>
class check_subcontracted_pre_post_inv : // Copyable as shallow ptr and ref.
        public boost::contract::aux::check_pre_post_inv<C> {
    // Base types as pointers because mpl::for_each will construct them.
    typedef typename boost::mpl::transform<
        typename boost::mpl::eval_if<boost::contract::aux::has_base_types<C>,
            boost::contract::aux::base_types_of<C>
        ,
            boost::mpl::identity<boost::mpl::vector<> >
        >::type,
        boost::add_pointer<boost::mpl::placeholders::_1>
    >::type base_ptrs;

public:
    explicit check_subcontracted_pre_post_inv(
        boost::contract::from from,
        C const* obj,
        A0 const& a0
    ) :
        boost::contract::aux::check_pre_post_inv<C>(from, obj),
        subcontracting_call_(boost::make_shared<boost::contract::aux::call>()),
        a0_(a0)
    { init(); }
    
    explicit check_subcontracted_pre_post_inv(
        boost::contract::from from,
        boost::shared_ptr<boost::contract::aux::call> call,
        C const* obj,
        A0 const& a0
    ) :
        boost::contract::aux::check_pre_post_inv<C>(from, call, obj),
        subcontracting_call_(boost::make_shared<boost::contract::aux::call>()),
        a0_(a0)
    { init(); }

    virtual ~check_subcontracted_pre_post_inv() {}
    
protected:
    void copy_subcontracted_oldof() {
        subcontracting_call_->action = boost::contract::aux::call::copy_oldof;
        boost::mpl::for_each<base_ptrs>(check_base_);
        // No this->... here (calling func old-ofs on stack or handled by bind).
    }
    
    void check_subcontracted_entry_inv() {
        subcontracting_call_->action =
                boost::contract::aux::call::check_entry_inv;
        boost::mpl::for_each<base_ptrs>(check_base_);
        this->check_entry_inv();
    }
    
    // Allow to throw on failure for relaxing subcontracted pre.
    void check_subcontracted_pre(bool throw_on_failure = false) {
        subcontracting_call_->action = boost::contract::aux::call::check_pre;
        try {
            boost::mpl::for_each<base_ptrs>(check_base_);
            // Pre logic-or: Last check, error also throws.
            this->check_pre(throw_on_failure);
        } catch(boost::contract::aux::no_error const&) {
            // Pre logic-or: Stop at 1st no_error (thrown by callee).
        }
    }

    void check_subcontracted_exit_inv() {
        subcontracting_call_->action =
                boost::contract::aux::call::check_exit_inv;
        boost::mpl::for_each<base_ptrs>(check_base_);
        this->check_exit_inv();
    }

    void check_subcontracted_post() {
        subcontracting_call_->action = boost::contract::aux::call::check_post;
        boost::mpl::for_each<base_ptrs>(check_base_);
        this->check_post();
    }

private:
    void init() { check_base_.nest(this); }

    class check_base {
    public:
        explicit check_base() : nest_() {}

        void nest(check_subcontracted_pre_post_inv* n) { nest_ = n; }

        template<class B>
        void operator()(B*) {
            typedef void result_type;
            typedef boost::mpl::vector<A0 const&, boost::contract::call>
                    arg_types;

            call<B, result_type, arg_types>(
                boost::mpl::bool_<I::template has_member_function<
                    B,
                    result_type,
                    arg_types,
                    boost::function_types::const_qualified
                >::value>()
            );
        }

    private:
        template<class, typename, class>
        void call(boost::mpl::false_ const&) {}

        template<class B, typename R, class Args>
        void call(boost::mpl::true_ const&) {
            typedef typename boost::mpl::push_front<typename boost::mpl::
                    push_front<Args, B*>::type, R>::type base_func_types;
            typedef typename boost::function_types::member_function_pointer<
                base_func_types, boost::function_types::const_qualified
            >::type base_func_ptr;

            base_func_ptr base_func = I::template member_function_address<B,
                    base_func_ptr>();
            BOOST_CONTRACT_AUX_DEBUG(base_func);
            
            BOOST_CONTRACT_AUX_DEBUG(nest_);
            B const* base_obj = nest_->object();
            BOOST_CONTRACT_AUX_DEBUG(base_obj);

            boost::contract::call c(nest_->subcontracting_call_);
            if(nest_->contract_call()) {
                BOOST_CONTRACT_AUX_DEBUG(nest_->contract_call()->action ==
                        c.call_->action);
                c.call_ = nest_->contract_call(); // Use existing call.
            }

            try {
                (base_obj->*base_func)(nest_->a0_, c);
            } catch(boost::contract::aux::no_error const&) {
                if(c.call_->action == boost::contract::aux::call::check_pre) {
                    throw; // Pre logic-or: 1st no_err stops (throw to caller).
                }
            } catch(...) {
                if(c.call_->action == boost::contract::aux::call::check_pre) {
                    // Pre logic-or: Ignore err, possibly checks up to caller.
                }
            }
        }

        check_subcontracted_pre_post_inv* nest_;
    };

    boost::shared_ptr<boost::contract::aux::call> subcontracting_call_;
    check_base check_base_;
    A0 const& a0_;
};

} } } // namespace

#endif // #include guard

