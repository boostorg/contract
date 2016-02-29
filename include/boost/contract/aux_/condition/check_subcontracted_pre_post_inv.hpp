
#ifndef BOOST_CONTRACT_AUX_CHECK_SUBCONTRACTED_PRE_POST_INV_HPP_
#define BOOST_CONTRACT_AUX_CHECK_SUBCONTRACTED_PRE_POST_INV_HPP_

// Copyright (C) 2008-2016 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0 (see accompanying
// file LICENSE_1_0.txt or a copy at http://www.boost.org/LICENSE_1_0.txt).
// See: http://www.boost.org/doc/libs/release/libs/contract/doc/html/index.html

#include <boost/contract/core/config.hpp>
#if !defined(BOOST_CONTRACT_NO_PRECONDITIONS) || \
        !defined(BOOST_CONTRACT_NO_POSTCONDITIONS)
    #include <boost/contract/core/exception.hpp>
#endif
#include <boost/contract/aux_/condition/check_pre_post_inv.hpp>
#include <boost/contract/aux_/decl.hpp>
#include <boost/contract/aux_/tvariadic.hpp>
#if !defined(BOOST_CONTRACT_NO_PRECONDITIONS) || \
        !defined(BOOST_CONTRACT_NO_POSTCONDITIONS) || \
        !defined(BOOST_CONTRACT_NO_INVARIANTS)
    #include <boost/contract/core/virtual.hpp>
    #include <boost/contract/core/access.hpp>
    #include <boost/contract/aux_/type_traits/optional.hpp>
    #include <boost/contract/aux_/type_traits/member_function_types.hpp>
    #include <boost/contract/aux_/debug.hpp>
    #include <boost/contract/aux_/none.hpp>
    #include <boost/contract/aux_/name.hpp>
    #include <boost/type_traits/add_pointer.hpp>
    #include <boost/mpl/fold.hpp>
    #include <boost/mpl/contains.hpp>
    #include <boost/mpl/empty.hpp>
    #include <boost/mpl/push_back.hpp>
    #include <boost/mpl/eval_if.hpp>
    #include <boost/mpl/identity.hpp>
    #include <boost/mpl/placeholders.hpp>
    #ifndef BOOST_CONTRACT_PERMISSIVE
        #include <boost/type_traits/is_same.hpp>
        #include <boost/mpl/or.hpp>
        #include <boost/mpl/not.hpp>
        #include <boost/static_assert.hpp>
    #endif
    #include <boost/preprocessor/punctuation/comma_if.hpp>
    #include <boost/config.hpp>
#endif
#include <boost/mpl/vector.hpp>
#if !defined(BOOST_CONTRACT_NO_POSTCONDITIONS) || \
        !defined(BOOST_CONTRACT_NO_INVARIANTS)
    #include <boost/mpl/for_each.hpp>
#endif
#ifndef BOOST_CONTRACT_NO_PRECONDITIONS
    #include <boost/mpl/pop_front.hpp>
    #include <boost/mpl/front.hpp>
#endif
#ifndef BOOST_CONTRACT_NO_POSTCONDITIONS
    #include <boost/any.hpp>
    #include <boost/optional.hpp>
    #include <boost/type_traits/remove_reference.hpp>
    #include <boost/utility/enable_if.hpp>
    #include <typeinfo>
#endif

namespace boost { namespace contract { namespace aux {

namespace check_subcontracted_pre_post_inv_ {
    // Exception signals (must not inherit).
    class signal_no_error {};
    class signal_not_checked {};
}

// O, R, F, and Args-i can be none types (but C cannot).
BOOST_CONTRACT_AUX_DECL_AUX_CHECK_SUBCONTRACTED_PRE_POST_INV_Z(1,
        /* is_friend = */ 0, O, R, F, C, Args) : // Non-copyable base.
    public check_pre_post_inv<R, C>
{
    #if !defined(BOOST_CONTRACT_NO_PRECONDITIONS) || \
            !defined(BOOST_CONTRACT_NO_POSTCONDITIONS) || \
            !defined(BOOST_CONTRACT_NO_INVARIANTS)
        template<class Class, typename Result = boost::mpl::vector<> >
        class overridden_bases_of {
            struct search_bases {
                typedef typename boost::mpl::fold<
                    typename boost::contract::access::base_types_of<Class>::
                            type,
                    Result,
                    // Fold: _1 = result, _2 = current base from base_types.
                    boost::mpl::eval_if<boost::mpl::contains<boost::mpl::_1,
                            boost::add_pointer<boost::mpl::_2> >,
                        boost::mpl::_1 // Base in result, do not add it again.
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
                                // Bases as * since for_each constructs them.
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

        #ifndef BOOST_CONTRACT_PERMISSIVE
            BOOST_STATIC_ASSERT_MSG(
                boost::mpl::or_<
                    boost::is_same<O, none>,
                    boost::mpl::not_<boost::mpl::empty<overridden_bases> >
                >::value,
                "subcontracting function specified as 'override' but does not "
                "override any contracted member function"
            );
        #endif
    #else
        typedef boost::mpl::vector<> overridden_bases;
    #endif

public:
    explicit check_subcontracted_pre_post_inv(
        boost::contract::from from,
        boost::contract::virtual_* v,
        C* obj,
        R& r
        BOOST_CONTRACT_AUX_TVARIADIC_COMMA(BOOST_CONTRACT_MAX_ARGS)
        BOOST_CONTRACT_AUX_TVARIADIC_FPARAMS_Z(1,
                BOOST_CONTRACT_MAX_ARGS, Args, &, args)
    ) :
        check_pre_post_inv<R, C>(from, obj)
        #ifndef BOOST_CONTRACT_NO_POSTCONDITIONS
            , r_(r)
        #endif
        #if !defined(BOOST_CONTRACT_NO_PRECONDITIONS) || \
                !defined(BOOST_CONTRACT_NO_POSTCONDITIONS) || \
                !defined(BOOST_CONTRACT_NO_INVARIANTS)
            BOOST_CONTRACT_AUX_TVARIADIC_COMMA(BOOST_CONTRACT_MAX_ARGS)
            BOOST_CONTRACT_AUX_TVARIADIC_TUPLE_INIT_Z(1,
                    BOOST_CONTRACT_MAX_ARGS, args_, args)
        #endif
    {
        #if !defined(BOOST_CONTRACT_NO_PRECONDITIONS) || \
                !defined(BOOST_CONTRACT_NO_POSTCONDITIONS) || \
                !defined(BOOST_CONTRACT_NO_INVARIANTS)
            if(v) {
                base_call_ = true;
                v_ = v; // Invariant: v_ never null if base_call_.
                BOOST_CONTRACT_AUX_DEBUG(v_);
            } else {
                base_call_ = false;
                if(!boost::mpl::empty<overridden_bases>::value) {
                    v_ = new boost::contract::virtual_(
                            boost::contract::virtual_::no_action);
                    #ifndef BOOST_CONTRACT_NO_POSTCONDITIONS
                        v_->result_ptr_ = &r_;
                        v_->result_type_name_ = typeid(R).name();
                        v_->result_optional_ = is_optional<R>::value;
                    #endif
                } else v_ = 0;
            }
        #endif
    }

    #if !defined(BOOST_CONTRACT_NO_PRECONDITIONS) || \
            !defined(BOOST_CONTRACT_NO_POSTCONDITIONS) || \
            !defined(BOOST_CONTRACT_NO_INVARIANTS)
        virtual ~check_subcontracted_pre_post_inv() BOOST_NOEXCEPT_IF(false) {
            if(!base_call_) delete v_;
        }
    #endif

protected:
    #ifndef BOOST_CONTRACT_NO_POSTCONDITIONS
        void init_subcontracted_old() {
            // Old values of overloaded func on stack (so no `f` param here).
            exec_and(boost::contract::virtual_::push_old_init);
        }
    #endif
    
    #ifndef BOOST_CONTRACT_NO_ENTRY_INVARIANTS
        void check_subcontracted_entry_inv() {
            exec_and(boost::contract::virtual_::check_entry_inv,
                    &check_subcontracted_pre_post_inv::check_entry_inv);
        }
    #endif
    
    #ifndef BOOST_CONTRACT_NO_PRECONDITIONS
        void check_subcontracted_pre() {
            exec_or(
                boost::contract::virtual_::check_pre,
                &check_subcontracted_pre_post_inv::check_pre,
                &boost::contract::precondition_failure
            );
        }
    #endif

    #ifndef BOOST_CONTRACT_NO_POSTCONDITIONS
        void copy_subcontracted_old() {
            exec_and(boost::contract::virtual_::call_old_copy,
                    &check_subcontracted_pre_post_inv::copy_old_v);
        }
    #endif

    #ifndef BOOST_CONTRACT_NO_EXIT_INVARIANTS
        void check_subcontracted_exit_inv() {
            exec_and(boost::contract::virtual_::check_exit_inv,
                    &check_subcontracted_pre_post_inv::check_exit_inv);
        }
    #endif

    #ifndef BOOST_CONTRACT_NO_POSTCONDITIONS
        void check_subcontracted_post() {
            exec_and(boost::contract::virtual_::check_post,
                    &check_subcontracted_pre_post_inv::check_post_v);
        }
    #endif

    #if !defined(BOOST_CONTRACT_NO_PRECONDITIONS) || \
            !defined(BOOST_CONTRACT_NO_POSTCONDITIONS) || \
            !defined(BOOST_CONTRACT_NO_INVARIANTS)
        bool base_call() const { return base_call_; }

        bool failed() const /* override */ {
            if(v_) return v_->failed_;
            else return check_base::failed();
        }

        void failed(bool value) /* override */ {
            if(v_) v_->failed_ = value;
            else check_base::failed(value);
        }
    #endif

private:
    #ifndef BOOST_CONTRACT_NO_POSTCONDITIONS
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
            boost::optional<r_type const&> r; // No result copy in this code.
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
                        try {
                            throw boost::contract::bad_virtual_result_cast(v_->
                                    result_type_name_, typeid(r_type).name());
                        } catch(...) {
                            this->fail(&boost::contract::postcondition_failure);
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
                        this->fail(&boost::contract::postcondition_failure);
                    }
                }
            }
            check_post_r<R>(r);
        }

        template<typename R_, typename Result>
        typename boost::enable_if<is_optional<R_> >::type
        check_post_r(Result const& r) { this->check_post(r); }
        
        template<typename R_, typename Result>
        typename boost::disable_if<is_optional<R_> >::type
        check_post_r(Result const& r) {
            BOOST_CONTRACT_AUX_DEBUG(r);
            this->check_post(*r);
        }
    #endif

    #if !defined(BOOST_CONTRACT_NO_POSTCONDITIONS) || \
            !defined(BOOST_CONTRACT_NO_INVARIANTS)
        void exec_and( // Execute action in short-circuit logic-and with bases.
            boost::contract::virtual_::action_enum a,
            void (check_subcontracted_pre_post_inv::* f)() = 0
        ) {
            if(failed()) return;
            if(!base_call_ || v_->action_ == a) {
                if(!base_call_ && v_) {
                    v_->action_ = a;
                    boost::mpl::for_each<overridden_bases>(call_base(*this));
                }
                if(f) (this->*f)();
                if(base_call_) {
                    throw check_subcontracted_pre_post_inv_::signal_no_error();
                }
            }
        }
    #endif

    #ifndef BOOST_CONTRACT_NO_PRECONDITIONS
        void exec_or( // Execute action in short-circuit logic-or with bases.
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
                        return; // A base checked with no error (done).
                    } catch(...) {
                        bool checked =  f ? (this->*f)(
                                /* throw_on_failure = */ false) : false;
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
                call_base(*this)(typename boost::mpl::front<Bases>::type());
            } catch(check_subcontracted_pre_post_inv_::
                    signal_not_checked const&) {
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
    #endif
    
    #if !defined(BOOST_CONTRACT_NO_PRECONDITIONS) || \
            !defined(BOOST_CONTRACT_NO_POSTCONDITIONS) || \
            !defined(BOOST_CONTRACT_NO_INVARIANTS)
        class call_base { // Copyable (as &).
        public:
            explicit call_base(check_subcontracted_pre_post_inv& me) :
                    me_(me) {}

            template<class B>
            void operator()(B*) {
                BOOST_CONTRACT_AUX_DEBUG(me_.object());
                BOOST_CONTRACT_AUX_DEBUG(me_.v_);
                BOOST_CONTRACT_AUX_DEBUG(me_.v_->action_ !=
                        boost::contract::virtual_::no_action);
                try {
                    call<B>(BOOST_CONTRACT_AUX_TVARIADIC_TUPLE_INDEXES_OF(
                            Args));
                } catch(check_subcontracted_pre_post_inv_::
                        signal_no_error const&) {
                    // No error (do not throw).
                }
            }

        private:
            template<
                class B
                // Can't use TVARIADIC_COMMA here.
                BOOST_PP_COMMA_IF(BOOST_CONTRACT_AUX_TVARIADIC)
                BOOST_CONTRACT_AUX_TVARIADIC_TUPLE_INDEXES_TPARAM(I)
            >
            void call(
                    BOOST_CONTRACT_AUX_TVARIADIC_TUPLE_INDEXES_FPARAM(I)) {
                O::template BOOST_CONTRACT_AUX_NAME1(call_base)<B>(
                    me_.v_,
                    me_.object()
                    BOOST_CONTRACT_AUX_TVARIADIC_COMMA(BOOST_CONTRACT_MAX_ARGS)
                    BOOST_CONTRACT_AUX_TVARIADIC_TUPLE_ELEMS_Z(1,
                            BOOST_CONTRACT_MAX_ARGS, I, me_.args_)
                );
            }
            
            check_subcontracted_pre_post_inv& me_;
        };
    #endif

    #ifndef BOOST_CONTRACT_NO_POSTCONDITIONS
        R& r_;
    #endif
    #if !defined(BOOST_CONTRACT_NO_PRECONDITIONS) || \
            !defined(BOOST_CONTRACT_NO_POSTCONDITIONS) || \
            !defined(BOOST_CONTRACT_NO_INVARIANTS)
        boost::contract::virtual_* v_;
        bool base_call_;
        BOOST_CONTRACT_AUX_TVARIADIC_TUPLE_Z(1,
                BOOST_CONTRACT_MAX_ARGS, Args, &, args_)
    #endif
};

} } } // namespace

#endif // #include guard

