
#ifndef BOOST_CONTRACT_AUX_CHECK_SUBCONTRACTED_PRE_POST_INV_HPP_
#define BOOST_CONTRACT_AUX_CHECK_SUBCONTRACTED_PRE_POST_INV_HPP_

#include <boost/contract/core/decl.hpp>
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
class check_subcontracted_pre_post_inv : // Copyable (as * and &).
        public check_pre_post_inv<C> {
    // Base types as pointers because mpl::for_each will construct them.
    typedef typename boost::mpl::transform<
        typename boost::mpl::eval_if<has_base_types<C>,
            base_types_of<C>
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
        check_pre_post_inv<C>(from, obj),
        c_(boost::make_shared<call>()),
        a0_(a0)
    { init(); }
    
    explicit check_subcontracted_pre_post_inv(
        boost::contract::from from,
        boost::shared_ptr<call> decl_call,
        C const* obj,
        A0 const& a0
    ) :
        check_pre_post_inv<C>(from, decl_call, obj),
        c_(decl_call),
        a0_(a0)
    { init(); }

    virtual ~check_subcontracted_pre_post_inv() {}
    
protected:
    void copy_subcontracted_oldof() {
        if(this->decl_call() && this->decl_call()->action != call::copy_oldof) {
            return;
        }
        c_.call_->action = call::copy_oldof;
        boost::mpl::for_each<base_ptrs>(check_base_class_);
        // No this->... here (calling func old-ofs on stack or handled by bind).
    }
    
    void check_subcontracted_entry_inv() {
        if(this->decl_call() && this->decl_call()->action !=
                call::check_entry_inv) {
            return;
        }
        c_.call_->action = call::check_entry_inv;
        boost::mpl::for_each<base_ptrs>(check_base_class_);
        this->check_entry_inv();
    }
    
    // Allow to throw on failure for relaxing subcontracted pre.
    void check_subcontracted_pre(bool throw_on_failure = false) {
        if(this->decl_call() && this->decl_call()->action != call::check_pre) {
            return;
        }
        c_.call_->action = call::check_pre;
        try {
            boost::mpl::for_each<base_ptrs>(check_base_class_);
            // Pre logic-or: Last check, error also throws.
            this->check_pre(throw_on_failure);
        } catch(no_error const&) {
            // Pre logic-or: Stop at 1st no_error (thrown by callee).
        }
    }

    void check_subcontracted_exit_inv() {
        if(this->decl_call() && this->decl_call()->action !=
                call::check_exit_inv) {
            return;
        }
        c_.call_->action = call::check_exit_inv;
        boost::mpl::for_each<base_ptrs>(check_base_class_);
        this->check_exit_inv();
    }

    void check_subcontracted_post() {
        if(this->decl_call() && this->decl_call()->action != call::check_post) {
            return;
        }
        c_.call_->action = call::check_post;
        boost::mpl::for_each<base_ptrs>(check_base_class_);
        this->check_post();
    }

private:
    void init() { check_base_class_.nest(this); }
    
    class check_base_class { // Copyable (as *).
    public:
        explicit check_base_class() : nest_() {}

        void nest(check_subcontracted_pre_post_inv* n) { nest_ = n; }

        template<class B>
        void operator()(B*) {
            typedef void result_type;
            typedef boost::mpl::vector<A0 const&, boost::contract::decl>
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

            try {
                (base_obj->*base_func)(nest_->a0_, nest_->c_);
            } catch(no_error const&) {
                if(nest_->c_.call_->action == call::check_pre) {
                    throw; // Pre logic-or: 1st no_err stops (throw to caller).
                }
            } catch(...) {
                if(nest_->c_.call_->action == call::check_pre) {
                    // Pre logic-or: Ignore err, possibly checks up to caller.
                }
            }
        }

        check_subcontracted_pre_post_inv* nest_;
    };

    boost::contract::decl c_; // Copyable (as *).
    check_base_class check_base_class_; // Copyable (as *).
    A0 const& a0_; // TODO: Support configurable func arity.
};

} } } // namespace

#endif // #include guard

