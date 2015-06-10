
#ifndef BOOST_CONTRACT_AUX_CHECK_SUBCONTRACTED_PRE_POST_INV_HPP_
#define BOOST_CONTRACT_AUX_CHECK_SUBCONTRACTED_PRE_POST_INV_HPP_

// TODO: Review and cleanup all #includes.
#include <boost/contract/core/virtual.hpp>
#include <boost/contract/aux_/check/check_pre_post_inv.hpp>
#include <boost/contract/aux_/type_traits/base_types.hpp>
#include <boost/contract/aux_/type_traits/member_function_types.hpp>
#include <boost/contract/aux_/debug.hpp>
/** @cond */
#include <boost/function_types/result_type.hpp>
#include <boost/function_types/parameter_types.hpp>
#include <boost/function_types/member_function_pointer.hpp>
#include <boost/function_types/property_tags.hpp>
#include <boost/type_traits/add_pointer.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/type_traits/is_const.hpp>
#include <boost/type_traits/is_volatile.hpp>
#include <boost/mpl/for_each.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/mpl/transform.hpp>
#include <boost/mpl/pop_front.hpp>
#include <boost/mpl/push_front.hpp>
#include <boost/mpl/push_back.hpp>
#include <boost/mpl/back.hpp>
#include <boost/mpl/empty.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/make_shared.hpp>
#include <boost/shared_ptr.hpp>
/** @endcond */

namespace boost { namespace contract { namespace aux {

namespace check_subcontracted_pre_post_inv_ {
    struct no_error {}; // Exception to signal OK (must not inherit).
}

// TODO: Can I make this, other check_... classes, and maybe even other
// calsses noncopyable? What does truly need to be copyable and why?

// TODO: Here I must assert that if O != none then at least one of the bases
// contains a virtual contracted function that can be overridden.

// O, R, F, and A-i can be none types (but C cannot).
template<class O, typename R, typename F, class C, typename A0, typename A1>
class check_subcontracted_pre_post_inv : // Copyable (as * and &).
        public check_pre_post_inv<R, C> {
    // Base types as pointers because mpl::for_each will construct them.
    typedef typename boost::mpl::transform<
        typename boost::mpl::eval_if<boost::is_same<O, none>,
            boost::mpl::identity<boost::mpl::vector<> >
        ,
            base_types_of<C> // Already asserted has_base_types<C> if O != none.
        >::type,
        boost::add_pointer<boost::mpl::placeholders::_1>
    >::type base_ptrs;

    // Followings evaluate to none if F is none type.
    typedef typename member_function_types<C, F>::result_type result_type;
    typedef typename member_function_types<C, F>::virtual_argument_types
            virt_arg_types;
    typedef typename member_function_types<C, F>::property_tag property_tag;

public:
    explicit check_subcontracted_pre_post_inv(boost::contract::from from,
            boost::contract::virtual_* v, C* obj, R& r, A0& a0, A1& a1) :
        check_pre_post_inv<R, C>(from, obj), r_(r), a0_(a0), a1_(a1)
    {
        if(v) {
            base_call_ = true;
            v_ = v; // Invariant: v_ never null if base_call_.
        } else {
            base_call_ = false;
            if(!boost::mpl::empty<base_ptrs>::value) {
                v_ = new boost::contract::virtual_(
                        boost::contract::virtual_::no_action);
                v_->result_ = &r_;
            } else v_ = 0;
        }
        check_base_.nest(this);
    }
    

    virtual ~check_subcontracted_pre_post_inv() {
        if(!base_call_ && v_) delete v_;
    }
    
protected:
    void copy_subcontracted_oldof() {
        // Old values of overloading func. on stack (so no `f` for copy_oldof).
        check(boost::contract::virtual_::copy_oldof);
    }
    
    void check_subcontracted_entry_inv() {
        check(boost::contract::virtual_::check_entry_inv,
                &check_subcontracted_pre_post_inv::check_entry_inv);
    }
    
    // Allow to throw on failure for relaxing subcontracted pre.
    void check_subcontracted_pre() {
        if(!base_call_ || v_->action_ ==
                boost::contract::virtual_::check_pre) {
            try {
                if(v_) {
                    v_->action_ = boost::contract::virtual_::check_pre;
                    boost::mpl::for_each<base_ptrs>(check_base_);
                }
                // Pre logic-or: Last check, error also throws.
                this->check_pre(/* throw_on_failure = */ base_call_);
            } catch(check_subcontracted_pre_post_inv_::no_error const&) {
                // Pre logic-or: Stop at 1st no_error (thrown by callee).
            }
            if(base_call_) throw check_subcontracted_pre_post_inv_::no_error();
        }
    }

    void check_subcontracted_exit_inv() {
        check(boost::contract::virtual_::check_exit_inv,
                &check_subcontracted_pre_post_inv::check_exit_inv);
    }

    void check_subcontracted_post() {
        check(boost::contract::virtual_::check_post,
                &check_subcontracted_pre_post_inv::check_post_result);
    }

    bool base_call() const { return base_call_; }

private:
    void check_post_result() {
        R& r = base_call_ ? *static_cast<R*>(v_->result_) : r_;
        this->check_post(r);
    }
    
    void check(boost::contract::virtual_::action_enum a,
            void (check_subcontracted_pre_post_inv::* f)() = 0) {
        if(!base_call_ || v_->action_ == a) {
            if(v_) {
                v_->action_ = a;
                boost::mpl::for_each<base_ptrs>(check_base_);
            }
            if(f) (this->*f)();
            if(base_call_) throw check_subcontracted_pre_post_inv_::no_error();
        }
    }

    class check_base { // Copyable (as *).
    public:
        explicit check_base() : nest_() {}

        void nest(check_subcontracted_pre_post_inv* n) { nest_ = n; }

        template<class B>
        void operator()(B*) {
            // TODO: If not in B, search B's inheritance graph deeply for f.
            call<B>(boost::mpl::bool_<O::template
                    BOOST_CONTRACT_AUX_NAME1(has_member_function)<
                B, result_type, virt_arg_types, property_tag
            >::value>());
        }

    private:
        template<class B>
        void call(boost::mpl::false_ const&) {}

        template<class B>
        void call(boost::mpl::true_ const&) {
            BOOST_CONTRACT_AUX_DEBUG(nest_->object());
            BOOST_CONTRACT_AUX_DEBUG(nest_->v_);
            BOOST_CONTRACT_AUX_DEBUG(nest_->v_->action_ !=
                    boost::contract::virtual_::no_action);
            try {
                O::template BOOST_CONTRACT_AUX_NAME1(base_call)<B>(
                        nest_->object(), nest_->a0_, nest_->a1_, nest_->v_);
            } catch(check_subcontracted_pre_post_inv_::no_error const&) {
                if(nest_->v_->action_ == boost::contract::virtual_::check_pre) {
                    throw; // Pre logic-or: 1st no_err stops (throw to caller).
                }
            } catch(...) {
                if(nest_->v_->action_ == boost::contract::virtual_::check_pre) {
                    // Pre logic-or: Ignore err, possibly checks up to caller.
                }
            }
        }

        check_subcontracted_pre_post_inv* nest_;
    };
    
    boost::contract::virtual_* v_;
    bool base_call_;
    check_base check_base_; // Copyable (as *).
    R& r_;
    A0& a0_;
    A1& a1_; // TODO: Support configurable func arity.
};

} } } // namespace

#endif // #include guard

