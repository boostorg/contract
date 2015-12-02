
#ifndef BOOST_CONTRACT_AUX_CHECK_SUBCONTRACTED_PRE_POST_INV_HPP_
#define BOOST_CONTRACT_AUX_CHECK_SUBCONTRACTED_PRE_POST_INV_HPP_

#include <boost/contract/core/access.hpp>
#include <boost/contract/core/virtual.hpp>
#include <boost/contract/core/config.hpp>
#include <boost/contract/core/exception.hpp>
#include <boost/contract/aux_/condition/check_pre_post_inv.hpp>
#include <boost/contract/aux_/type_traits/member_function_types.hpp>
#include <boost/contract/aux_/type_traits/optional.hpp>
#include <boost/contract/aux_/debug.hpp>
/** @cond */
#include <boost/optional.hpp>
#include <boost/any.hpp>
#include <boost/function_types/result_type.hpp>
#include <boost/function_types/parameter_types.hpp>
#include <boost/function_types/member_function_pointer.hpp>
#include <boost/function_types/property_tags.hpp>
#include <boost/type_traits/add_pointer.hpp>
#include <boost/type_traits/remove_reference.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/mpl/for_each.hpp>
#include <boost/mpl/fold.hpp>
#include <boost/mpl/front.hpp>
#include <boost/mpl/push_back.hpp>
#include <boost/mpl/pop_front.hpp>
#include <boost/mpl/contains.hpp>
#include <boost/mpl/empty.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/mpl/or.hpp>
#include <boost/mpl/not.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/static_assert.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/config.hpp>
#include <sstream>
#include <typeinfo>
/** @endcond */

namespace boost { namespace contract { namespace aux {

namespace check_subcontracted_pre_post_inv_ {
    // Exception signals (must not inherit).
    struct signal_no_error {};
    struct signal_not_checked {};
}

// O, R, F, and A-i can be none types (but C cannot).
template<class O, typename R, typename F, class C, typename A0, typename A1>
class check_subcontracted_pre_post_inv : // Copyable (as * and &).
        public check_pre_post_inv<R, C> {
    template<class Class, typename Result = boost::mpl::vector<> >
    class overridden_bases_of {
        struct search_bases {
            typedef typename boost::mpl::fold<
                typename boost::contract::access::base_types_of<Class>::type,
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
        typedef typename boost::mpl::eval_if<
                boost::contract::access::has_base_types<Class>,
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
    BOOST_STATIC_ASSERT_MSG(
        boost::mpl::or_<
            boost::is_same<O, none>,
            boost::mpl::not_<boost::mpl::empty<overridden_bases> >
        >::value,
        "subcontracting function specified as 'override' but does not "
        "override any contracted member function"
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
                v_->result_ptr_ = &r_;
                v_->result_type_name_ = typeid(R).name();
                v_->result_optional_ = is_optional<R>::value;
            } else v_ = 0;
        }
    }

    virtual ~check_subcontracted_pre_post_inv() BOOST_NOEXCEPT_IF(false) {
        if(!base_call_ && v_) delete v_;
    }

protected:
    void init_subcontracted_old() {
        exec_and(boost::contract::virtual_::push_old_init
                /* old values of overloaded func on stack (so no `f` here) */);
    }
    
    void check_subcontracted_entry_inv() {
        exec_and(boost::contract::virtual_::check_entry_inv,
                &check_subcontracted_pre_post_inv::check_entry_inv);
    }
    
    void check_subcontracted_pre() {
        exec_or(
            boost::contract::virtual_::check_pre,
            &check_subcontracted_pre_post_inv::check_pre,
            &boost::contract::precondition_failed
        );
    }

    void copy_subcontracted_old() {
        exec_and(boost::contract::virtual_::call_old_copy,
                &check_subcontracted_pre_post_inv::copy_old_v);
    }

    void check_subcontracted_exit_inv() {
        exec_and(boost::contract::virtual_::check_exit_inv,
                &check_subcontracted_pre_post_inv::check_exit_inv);
    }

    void check_subcontracted_post() {
        exec_and(boost::contract::virtual_::check_post,
                &check_subcontracted_pre_post_inv::check_post_v);
    }

    bool base_call() const { return base_call_; }

    bool failed() const /* override */ {
        if(v_) return v_->failed_;
        else return check_base::failed();
    }

    void failed(bool value) /* override */ {
        if(v_) v_->failed_ = value;
        else check_base::failed(value);
    }

private:
    void copy_old_v() {
        boost::contract::virtual_::action_enum a;
        if(base_call_) {
            a = v_->action_;
            v_->action_ = boost::contract::virtual_::push_old_copy;
        }
        this->copy_old();
        if(base_call_) v_->action_ = a;
    }
    
    void check_post_v() {
        if(base_call_) {
            boost::contract::virtual_::action_enum a = v_->action_;
            v_->action_ = boost::contract::virtual_::pop_old_copy;
            this->copy_old();
            v_->action_ = a;
        }

        typedef typename boost::remove_reference<typename
                optional_value_type<R>::type>::type r_type;
        boost::optional<r_type const&> r; // No result copy in following code.
        if(!base_call_) r = r_;
        else if(v_->result_optional_) {
            try {
                r = **boost::any_cast<boost::optional<r_type>*>(
                        v_->result_ptr_);
            } catch(boost::bad_any_cast const&) {
                try { // Handle optional<...&>.
                    r = **boost::any_cast<boost::optional<r_type&>*>(
                            v_->result_ptr_);
                } catch(boost::bad_any_cast const&) {
                    try { // No type names in bad_any_cast so use custom except.
                        throw boost::contract::bad_virtual_result_cast(
                                v_->result_type_name_, typeid(r_type).name());
                    } catch(...) {
                        this->fail(&boost::contract::postcondition_failed);
                    }
                }
            }
        } else {
            try {
                r = *boost::any_cast<r_type*>(v_->result_ptr_);
            } catch(boost::bad_any_cast const&) {
                try {
                    throw boost::contract::bad_virtual_result_cast(
                            v_->result_type_name_, typeid(r_type).name());
                } catch(...) {
                    this->fail(&boost::contract::postcondition_failed);
                }
            }
        }
        check_post_r<R>(r);
    }

    // TODO: See if these and other enable_if can be replaced using template specializations and a base class for template where to put common code (that might be faster to compile... not sure...).
    
    template<typename R_, typename Result>
    typename boost::enable_if<is_optional<R_> >::type
    check_post_r(Result const& r) { this->check_post(r); }
    
    template<typename R_, typename Result>
    typename boost::disable_if<is_optional<R_> >::type
    check_post_r(Result const& r) {
        BOOST_CONTRACT_AUX_DEBUG(r);
        this->check_post(*r);
    }
    
    void exec_and(
        boost::contract::virtual_::action_enum a,
        void (check_subcontracted_pre_post_inv::* f)() = 0
    ) {
        if(failed()) return;
        if(!base_call_ || v_->action_ == a) {
            if(!base_call_ && v_) {
                v_->action_ = a;
                boost::mpl::for_each<overridden_bases>(call_base(this));
            }
            if(f) (this->*f)();
            if(base_call_) {
                throw check_subcontracted_pre_post_inv_::signal_no_error();
            }
        }
    }

    void exec_or(
        boost::contract::virtual_::action_enum a,
        bool (check_subcontracted_pre_post_inv::* f)(bool) = 0,
        void (*h)(boost::contract::from) = 0
    ) {
        if(failed()) return;
        if(!base_call_ || v_->action_ == a) {
            if(!base_call_ && v_) {
                v_->action_ = a;
                try { 
                    exec_or_bases<overridden_bases>();
                    return; // At lest one base checked with no error (done).
                } catch(...) {
                    bool checked =  f ?
                            (this->*f)(/* throw_on_failure = */ false) : false;
                    if(!checked) {
                        try { throw; } // Report latest exception found.
                        catch(...) { this->fail(h); }
                    }
                    return; // Checked and no exception (done).
                }
            }
            bool checked = f ?
                    (this->*f)(/* throw_on_failure = */ base_call_) : false;
            if(base_call_) {
                if(!checked) {
                    throw check_subcontracted_pre_post_inv_::
                            signal_not_checked();
                }
                throw check_subcontracted_pre_post_inv_::signal_no_error();
            }
        }
    }
    
    template<typename Bases>
    typename boost::enable_if<boost::mpl::empty<Bases>, bool>::type
    exec_or_bases() { return false; }

    template<typename Bases>
    typename boost::disable_if<boost::mpl::empty<Bases>, bool>::type
    exec_or_bases() {
        if(boost::mpl::empty<Bases>::value) return false;
        try {
            call_base(this)(typename boost::mpl::front<Bases>::type());
        } catch(check_subcontracted_pre_post_inv_::signal_not_checked const&) {
            return exec_or_bases<
                    typename boost::mpl::pop_front<Bases>::type>();
        } catch(...) {
            bool checked = false;
            try {
                checked = exec_or_bases<
                        typename boost::mpl::pop_front<Bases>::type>();
            } catch(...) { checked = false; }
            if(!checked) throw;
        }
        return true;
    }
    
    class call_base { // Copyable (as *).
    public:
        explicit call_base(check_subcontracted_pre_post_inv* outer) :
                outer_(outer) {
            BOOST_CONTRACT_AUX_DEBUG(outer_);
        }

        template<class B>
        void operator()(B*) {
            BOOST_CONTRACT_AUX_DEBUG(outer_->object());
            BOOST_CONTRACT_AUX_DEBUG(outer_->v_);
            BOOST_CONTRACT_AUX_DEBUG(outer_->v_->action_ !=
                    boost::contract::virtual_::no_action);
            try {
                O::template BOOST_CONTRACT_AUX_NAME1(call_base)<B>(
                        outer_->object(), outer_->a0_, outer_->a1_, outer_->v_);
            } catch(check_subcontracted_pre_post_inv_::signal_no_error const&) {
                // No error (do not throw).
            }
        }

    private:
        check_subcontracted_pre_post_inv* outer_;
    };

    boost::contract::virtual_* v_;
    bool base_call_;
    R& r_;
    // TODO: Support configurable func arity (using both C++11 variadic templates and boost.preprocessor when C++11 variadic template are not supported).
    A0& a0_;
    A1& a1_;
};

} } } // namespace

#endif // #include guard

