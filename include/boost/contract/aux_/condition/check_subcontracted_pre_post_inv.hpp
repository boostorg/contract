
#ifndef BOOST_CONTRACT_AUX_CHECK_SUBCONTRACTED_PRE_POST_INV_HPP_
#define BOOST_CONTRACT_AUX_CHECK_SUBCONTRACTED_PRE_POST_INV_HPP_

#include <boost/contract/core/virtual.hpp>
#include <boost/contract/core/config.hpp>
#include <boost/contract/aux_/condition/check_pre_post_inv.hpp>
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
#include <boost/mpl/vector.hpp>
#include <boost/mpl/for_each.hpp>
#include <boost/mpl/fold.hpp>
#include <boost/mpl/push_back.hpp>
#include <boost/mpl/contains.hpp>
#include <boost/mpl/empty.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/mpl/or.hpp>
#include <boost/mpl/not.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/static_assert.hpp>
/** @endcond */

// TODO: If overriding function does not specify .precondition(...), make sure the overridden preconditions are still checked (and not that subcontracted preconditions always pass just because the overriding function does not specify them).
    
namespace boost { namespace contract { namespace aux {

namespace check_subcontracted_pre_post_inv_ {
    struct no_error {}; // Exception to signal OK (must not inherit).
}

// O, R, F, and A-i can be none types (but C cannot).
template<class O, typename R, typename F, class C, typename A0, typename A1>
class check_subcontracted_pre_post_inv : // Copyable (as * and &).
        public check_pre_post_inv<R, C> {
    template<class Class, typename Result = boost::mpl::vector<> >
    class overridden_bases_of {
        struct search_bases {
            typedef typename boost::mpl::fold<
                typename base_types_of<Class>::type,
                Result,
                // Fold: _1 = result, _2 = current base type from base_types.
                boost::mpl::eval_if<boost::mpl::contains<boost::mpl::_1,
                        boost::add_pointer<boost::mpl::_2> >,
                    boost::mpl::_1 // Base already in result, do not add again.
                ,
                    boost::mpl::eval_if<
                        typename O::template BOOST_CONTRACT_AUX_NAME1(
                                has_member_function)<
                            boost::mpl::_2,
                            typename member_function_types<C, F>::
                                    result_type,
                            typename member_function_types<C, F>::
                                    virtual_argument_types,
                            typename member_function_types<C, F>::
                                    property_tag
                        >
                    ,
                        boost::mpl::push_back<
                            overridden_bases_of<boost::mpl::_2,
                                    boost::mpl::_1>,
                            // Bases as * since for_each later constructs them.
                            boost::add_pointer<boost::mpl::_2>
                        >
                    ,
                        overridden_bases_of<boost::mpl::_2, boost::mpl::_1>
                    >
                >
            >::type type;
        };
    public:
        typedef typename boost::mpl::eval_if<has_base_types<Class>,
            search_bases
        ,
            boost::mpl::identity<Result> // Return result (stop recursion).
        >::type type;
    };
    
    typedef typename boost::mpl::eval_if<boost::is_same<O, none>,
        boost::mpl::vector<>
    ,
        overridden_bases_of<C>
    >::type overridden_bases;

#ifndef BOOST_CONTRACT_CONFIG_PERMISSIVE
    BOOST_STATIC_ASSERT_MSG(boost::mpl::or_<boost::is_same<O, none>,
            boost::mpl::not_<boost::mpl::empty<overridden_bases> > >::value,
        "subcontracting function marked 'override' but does not override "
        "any contracted member function"
    );
#endif

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
            if(!boost::mpl::empty<overridden_bases>::value) {
                v_ = new boost::contract::virtual_(
                        boost::contract::virtual_::no_action);
                // C-style cast to handle both pointer type and const.
                v_->result_ = (void*)&r_;
            } else v_ = 0;
        }
        check_base_.nest(this);
    }
    

    virtual ~check_subcontracted_pre_post_inv() {
        if(!base_call_ && v_) delete v_;
    }

protected:
    void init_subcontracted_old() {
        // Old values of overloaded func on stack (so no functor `f` here).
        execute(boost::contract::virtual_::push_old_init);
    }
    
    void check_subcontracted_entry_inv() {
        execute(boost::contract::virtual_::check_entry_inv,
                &check_subcontracted_pre_post_inv::check_entry_inv);
    }
    
    // Allow to throw on failure for relaxing subcontracted pre.
    void check_subcontracted_pre() {
        if(!base_call_ || v_->action_ ==
                boost::contract::virtual_::check_pre) {
            try {
                if(!base_call_ && v_) {
                    v_->action_ = boost::contract::virtual_::check_pre;
                    boost::mpl::for_each<overridden_bases>(check_base_);
                }
                // Pre logic-or: Last check, error also throws.
                this->check_pre(/* throw_on_failure = */ base_call_);
            } catch(check_subcontracted_pre_post_inv_::no_error const&) {
                // Pre logic-or: Stop at 1st no_error (thrown by callee).
            }
            if(base_call_) throw check_subcontracted_pre_post_inv_::no_error();
        }
    }

    void copy_subcontracted_old() {
        execute(boost::contract::virtual_::call_old_copy,
                &check_subcontracted_pre_post_inv::copy_old_v);
    }

    void check_subcontracted_exit_inv() {
        execute(boost::contract::virtual_::check_exit_inv,
                &check_subcontracted_pre_post_inv::check_exit_inv);
    }

    void check_subcontracted_post() {
        execute(boost::contract::virtual_::check_post,
                &check_subcontracted_pre_post_inv::check_post_v);
    }

    bool base_call() const { return base_call_; }

private:
    void check_post_v() {
        if(base_call_) {
            boost::contract::virtual_::action_enum a = v_->action_;
            v_->action_ = boost::contract::virtual_::pop_old_copy;
            this->copy_old();
            v_->action_ = a;
        }
        // Ternary op here avoids extra copy of R (because constructing a &).
        R& r = base_call_ ? *static_cast<R*>(v_->result_) : r_;
        this->check_post(r);
    }

    void copy_old_v() {
        boost::contract::virtual_::action_enum a;
        if(base_call_) {
            a = v_->action_;
            v_->action_ = boost::contract::virtual_::push_old_copy;
        }
        this->copy_old();
        if(base_call_) v_->action_ = a;
    }
    
    void execute(boost::contract::virtual_::action_enum a,
            void (check_subcontracted_pre_post_inv::* f)() = 0) {
        if(!base_call_ || v_->action_ == a) {
            if(!base_call_ && v_) {
                v_->action_ = a;
                boost::mpl::for_each<overridden_bases>(check_base_);
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

    private:
        check_subcontracted_pre_post_inv* nest_;
    };
    
    boost::contract::virtual_* v_;
    bool base_call_;
    check_base check_base_; // Copyable (as *).
    R& r_;
    // TODO: Support configurable func arity (using both C++11 variadic templates and boost.preprocessor when C++11 variadic template are not supported).
    A0& a0_;
    A1& a1_;
};

} } } // namespace

#endif // #include guard

