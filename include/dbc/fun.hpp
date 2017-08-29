/**
* @file
 * @author Copyright (C) 2009 Lorenzo Caminiti.
 *  Distributed under DBC++ Software License (see file LICENSE_1_0.txt).
 */

#include "detail/pp/defines.hpp" // Must be 1st include.

#ifndef DBC

#undef DBC_CONTRACT

#else // DBC

#include "config.hpp"
#include "post.hpp"
#include "exception.hpp"
#include "object.hpp"
#include "detail/type_traits.hpp"
#include "detail/none.hpp"
#include "detail/checking.hpp"
#include "detail/logging.hpp"
#include <boost/preprocessor.hpp>
#include <boost/type_traits.hpp>
#include <boost/mpl/assert.hpp>
#include <string>
#include <typeinfo>

// No Self-Iteration //

#if !BOOST_PP_IS_ITERATING
    // Include guards but ONLY when not self-iterating (and NOT below).
#   ifndef DBC_FUN_HPP_
#       define DBC_FUN_HPP_

#define DBC_CONTRACT(fun_name_args_const) \
        DBC_CONTRACT_NAME_FROM_SEQ_(fun_name_args_const)

        // Iterate over function-arity (i.e., argument number).
#       define BOOST_PP_ITERATION_PARAMS_1 (3, (0, DBC_CONFIG_MAX_ARGC, \
                DBC_CONFIG_FUN_HPP_FILE_PATH))
#       include BOOST_PP_ITERATE() // Iterate.
#   endif // DBC_FUN_HPP_

// 1st Self-Iteration (over function argument count) //

#elif BOOST_PP_ITERATION_DEPTH() == 1
    // Iterate over 0 void, 1 non-void function.
#   define BOOST_PP_ITERATION_PARAMS_2 (3, (0, 1, \
            DBC_CONFIG_FUN_HPP_FILE_PATH))
#   include BOOST_PP_ITERATE() // Iterate.

// 2nd Self-Iteration (over void/non-void Functions) //

#elif BOOST_PP_ITERATION_DEPTH() == 2
    // Remaining argument number = max arg count - current arg number.
#   define DBC_rest_arg_num BOOST_PP_FRAME_ITERATION(1)
    // Argument number for fun template of this iteration.
#   define DBC_arg_num BOOST_PP_SUB(BOOST_PP_FRAME_FINISH(1), \
            DBC_rest_arg_num)
    // Wheter fun template of this iteration is for void function.
#   define DBC_is_void BOOST_PP_FRAME_ITERATION(2) // Is void fun.
#   define DBC_is_not_void BOOST_PP_NOT(DBC_is_void)
    // It's templ specialization if void or arg num less than max arg cnt.
#   define DBC_is_spec BOOST_PP_OR(DBC_is_void, DBC_rest_arg_num)
#   define DBC_is_not_spec BOOST_PP_NOT(DBC_is_spec)
    // Arguments.
#   define DBC_arg_name(z, n, data) BOOST_PP_CAT(arg, n)
#   define DBC_arg_type(z, n, data) \
            BOOST_PP_CAT(DBC_arg_name(z, n, data), _type)
#   define DBC_arg_copyable_type(z, n, data) \
            BOOST_PP_CAT(DBC_arg_name(z, n, data), _copyable_type)
#   define DBC_arg(z, n, data) DBC_arg_type(z, n, data) \
            DBC_arg_name(z, n, data)
#   define DBC_arg_const_ref(z, n, data) DBC_ADD_CONST_REF_(typename, \
            DBC_arg_type(z, n, data)) DBC_arg_name(z, n, data)
#   define DBC_post_arg_const_ref(z, n, data) \
            DBC_ADD_POST_CONST_REF_(typename, \
            DBC_arg_copyable_type(z, n, data)) DBC_arg_name(z, n, data)
    // Post local variable.
#   define DBC_post_var_name(z, n, data) \
            BOOST_PP_CAT(post_, DBC_arg_name(z, n, data)) 
#   define DBC_post_var_decl(z, n, data) \
            DBC_ADD_POST_(typename, DBC_arg_copyable_type(z, n, data)) \
            DBC_post_var_name(z, n, data)(DBC_arg_name(z, n, data));

// Here "xzy_copyable_type" is for a type that keep the dbc::copyable<>
// attribute if had one, while "xzy_type" will have the dbc::copyable<> 
// removed. Therefore, "xzy_type" is guarranteed to not be copyable, while
// "xzy_copyable_type" will be copyable only if the type was specified as
// dbc::copyable<>.

namespace dbc {

template<
        BOOST_PP_EXPR_IF(DBC_is_not_void, typename R)
        BOOST_PP_COMMA_IF(BOOST_PP_AND(DBC_is_not_void, DBC_arg_num))
#   define DBC_tparam_arg(z, n, data) BOOST_PP_CAT(typename A, n) \
                BOOST_PP_EXPR_IF(DBC_is_not_spec, = none_)
        // A0 = none_, ... (if spec, no " = none_").
        BOOST_PP_ENUM(DBC_arg_num, DBC_tparam_arg, ~)
#   undef DBC_tparam_arg
        >
class fun
        // Need separate lines because macro can't pass "< , >" tokens.
        BOOST_PP_EXPR_IF(DBC_is_spec, <)
        // void or R
        BOOST_PP_IF(DBC_is_void, void, BOOST_PP_EXPR_IF(DBC_rest_arg_num, R))
        BOOST_PP_COMMA_IF(BOOST_PP_AND(DBC_is_spec, DBC_arg_num))
        // A0, ...
        BOOST_PP_IF(DBC_is_spec, BOOST_PP_ENUM_PARAMS, BOOST_PP_TUPLE_EAT(2))
                (DBC_arg_num, A)
#   define DBC_none(z, n, data) none_
        // none_, ...
        BOOST_PP_ENUM_TRAILING(DBC_rest_arg_num, DBC_none, ~)
#   undef DBC_none
        BOOST_PP_EXPR_IF(DBC_is_spec, >) {
public:
    typedef BOOST_PP_IF(DBC_is_void, void, R) result_type;
    
    // Generate "typedef An argn_copyable_type;".
    // Use An instead of argn_type when copyable qualification needed.
#   define DBC_arg_copyable_typedef(z, n, data) \
            typedef BOOST_PP_CAT(A, n) DBC_arg_copyable_type(z, n, data);
    BOOST_PP_REPEAT(DBC_arg_num, DBC_arg_copyable_typedef, ~)
#   undef DBC_arg_copyable_typedef

    // Generate "typedef typename remove_copyable<An> argn_type;".
    // Use An instead of argn_type when copyable qualification needed.
#   define DBC_arg_typedef(z, n, data) \
            typedef typename ::dbc::remove_copyable_< \
            BOOST_PP_CAT(A, n) >::type DBC_arg_type(z, n, data);
    BOOST_PP_REPEAT(DBC_arg_num, DBC_arg_typedef, ~)
#   undef DBC_arg_typedef

/** @todo[LC] Fix this "statically assert no Ai is void", it gives me compilation errors... also is should use argi_type (without copyable<> qualifier) and not Ai. */
//#   define DBC_assert_non_void_arg(z, n, data) 
//        && boost::mpl::not_<boost::is_void< BOOST_PP_CAT(A, n) > >::value
//    BOOST_MPL_ASSERT_MSG((1 /* start w/ 1 so all repeats can use && prefix */
//        BOOST_PP_REPEAT(DBC_arg_num, DBC_assert_non_void_arg, ~)),
//        DBC_ERROR_function_argument_type_An_cannot_be_void_, ());
//#   undef DBC_assert_non_void_arg

private:
    /** Dummy implementation never executed at run-time (but must compile). */
    template<class C>
    class no_base_ {
    public:
        typedef C copyable_class_type;
        typedef typename remove_copyable_<C>::type class_type;

        void fun_name(const std::string& name) {}

        void check_invariant(
                DBC_ADD_CONST_REF_(typename, class_type) self) {}

        void check_require(
                DBC_ADD_CONST_REF_(typename, class_type) self
                BOOST_PP_ENUM_TRAILING(DBC_arg_num, DBC_arg_const_ref, ~)
                ) {}

        void check_ensure(
                DBC_ADD_POST_CONST_REF_(typename, copyable_class_type) self
                BOOST_PP_ENUM_TRAILING(DBC_arg_num, 
                        DBC_post_arg_const_ref, ~)
                BOOST_PP_COMMA_IF(DBC_is_not_void)
                BOOST_PP_EXPR_IF(DBC_is_not_void, 
                        DBC_ADD_CONST_REF_(typename, result_type) result)
                ) {}
    }; // class no_base_

    // Following code heavely uses #ifdef DBC_CHECKING... to complie only the
    // code that must be there based on #defined symbol combinations. This is
    // done for optimization (1) reducing object code size and (2) removing
    // executiong of code that is not needed -- but it complicates this code
    // structure a bit.

public:
    template<class C, class B = no_base_<C> >
    class mem {
    public:
        BOOST_MPL_ASSERT_MSG(boost::is_class<C>::value, 
                DBC_ERROR_class_type_C_must_be_a_class_, ());
        BOOST_MPL_ASSERT_MSG(boost::is_class<B>::value, 
                DBC_ERROR_base_contract_type_B_must_be_a_class_, ());
        // Static asserting "C inherits from dbc::object<C>" is done by
        // DBC_INVARIANT() so to generate compiler error in a signle spot if
        // assertion is false.
        /** @todo[LC] Statically assert:
         * (3)  if B != no_base<C> then C is derived from B::class_type
         * (4)  there exist a friend non-mem fun dbc_invariant_() for C -- can 
         *      I statically assert this?
         * (5)  C is not a template (incomple type)... this is the error I get
         *      if I forget to declare (template) the class_type... but I can I
         *      statically assert this?
         */
//        BOOST_MPL_ASSERT_MSG((boost::mpl::if_<!boost::is_same<no_base<C>, B>, 
//                boost::is_base_of<B::class_type, C>, 
//                boost::mpl::true_type)::value,
//                DBC_ERROR_class_type_C_must_be_derived_from_base_B_class_type_,
//                ());

        typedef mem<C, B> this_type;
        typedef C copyable_class_type;
        typedef typename remove_copyable_<C>::type class_type;
        typedef B base_contract_type;

        // [LC] Some compilers (e.g., MSVC) need 'const' explicitly at end of
        // fun mem type (but for GCC it is enough if class_type is const).
        typedef result_type (class_type::* mem_fun_type_)
                // ( arg0_type, ... );
                ( BOOST_PP_ENUM(DBC_arg_num, DBC_arg_type, ~) );
        typedef result_type (class_type::* mem_fun_const_type_)
                // ( arg0_type, ... );
                ( BOOST_PP_ENUM(DBC_arg_num, DBC_arg_type, ~) ) const;
        typedef typename boost::mpl::if_<boost::is_const<class_type>,
                mem_fun_const_type_, mem_fun_type_>::type mem_fun_type;

        /** 
         * @todo[LC] Is there a better way to get the type-name using MPL?
         * @note I wanted to provide def constr for all contract class fun,
         *  fun::mem, etc so they are easier to use. In particular if a mem var
         *  of a contract class type is declared, C++ will init automatically
         *  using it's default constr. This feature is currently not used in 
         *  the library (as contracts are init manually in the fun declaration 
         *  that then call operator()) but it might turn out to be handy in
         *  future. 
         */
        explicit mem(): base_contract_(), 
                class_name_(typeid(class_type).name()), fun_name_(), 
                required_(false) {
#if DBC_CHECK_REQUIRE || DBC_CHECK_ENSURE || DBC_CHECK_INVAIRANT
            // For optimization, don't construct base if not checking.
            if (!boost::is_same<
                    base_contract_type, no_base_<class_type> >::value) {
                base_contract_ = new base_contract_type();
            }
#endif // check
        }

        virtual ~mem() { if (base_contract_) { delete base_contract_; } }

        inline void fun_name(const std::string& name) {
            fun_name_ = name;
            if (base_contract_) { base_contract_->fun_name(name); }
        }

        // Call //
        
        inline virtual result_type call(
                // Only add ref here (it's const only if it was already const).
                typename boost::add_reference<class_type>::type self
                , mem_fun_type body
                // , arg0_type arg0, ...
                BOOST_PP_ENUM_TRAILING(DBC_arg_num, DBC_arg, ~)
                , const std::string& the_fun_name = ""
                ) {
            return exec(self, body
                    // , arg0, ...
                    BOOST_PP_ENUM_TRAILING(DBC_arg_num, DBC_arg_name, ~)
                    , the_fun_name);
        }
        
        class functor {
        public:
            functor(mem& mem_fun,
                    typename boost::add_reference<class_type>::type self,
                    mem_fun_type body,
                    const std::string& the_fun_name):
                    mem_fun_(mem_fun), self_(self),
                    body_(body), the_fun_name_(the_fun_name) {}
        
            inline result_type operator()(
                    // arg0_type arg0, ...
                    BOOST_PP_ENUM(DBC_arg_num, DBC_arg, ~)
                    ) {
                return mem_fun_.call(self_, body_
                        // , arg0, ...
                        BOOST_PP_ENUM_TRAILING(DBC_arg_num, DBC_arg_name, ~)
                        , the_fun_name_);
            }

        private:
            mem& mem_fun_; // Ref (no copy).
            // By ref so no copy (constructor) required.
            typename boost::add_reference<class_type>::type self_;
            mem_fun_type body_;
            std::string the_fun_name_;
        };

        functor bind(typename boost::add_reference<class_type>::type self,
                mem_fun_type body,
                const std::string& the_fun_name = ""
                ) {
            return functor(*this, self, body, the_fun_name);
        }
        
        // Check //
        
#if DBC_CHECK_INVARIANT
        inline virtual void check_invariant(
                DBC_ADD_CONST_REF_(typename, class_type) self) {
            try {
                ::dbc::globally_checking_contract_ = true;
                DBC_LOG_DEBUG_(log << name() << "checking invariant");
                DBC_RETHROW_VIOLATION_AS_(invariant_violation, {
                    dbc_invariant_(self);
                });
                // And, base contract invariant (subcontracting).
                if (base_contract_) { base_contract_->check_invariant(self); }
                ::dbc::globally_checking_contract_ = false;
            } catch (...) {
                ::dbc::globally_checking_contract_ = false;
                throw;
            }
        }
#endif // check

#if DBC_CHECK_REQUIRE
        inline virtual void check_require(
                DBC_ADD_CONST_REF_(typename, class_type) self
                // , const arg0_type& arg0, ...
                BOOST_PP_ENUM_TRAILING(DBC_arg_num, DBC_arg_const_ref, ~)
                ) {
            try {
                ::dbc::globally_checking_contract_ = true;
                DBC_LOG_DEBUG_(log << name() << "checking preconditions");
                required_ = false;
                try {
                    DBC_RETHROW_VIOLATION_AS_(precondition_violation, {
                        require(self
                                // , arg0, ...
                                BOOST_PP_ENUM_TRAILING(DBC_arg_num,
                                        DBC_arg_name, ~));
                    });
                    // Iff my required and only mine passed (no invariant 
                    // and/or base contract's require checking) -- user can use
                    // this in subcontract guards.
                    required_ = true;
                } catch (...) { // Or, base contract preconditions (subcontr).
                    if (base_contract_) {
                        base_contract_->check_require(self
                                // , arg0, ...
                                BOOST_PP_ENUM_TRAILING(DBC_arg_num,
                                        DBC_arg_name, ~)
                                );
                    } else { throw; }
                } // try require or base contract require.
                ::dbc::globally_checking_contract_ = false;
            } catch (...) {
                ::dbc::globally_checking_contract_ = false;
                throw;
            }
        }
#endif // check

#if DBC_CHECK_ENSURE
        inline virtual void check_ensure(
                DBC_ADD_POST_CONST_REF_(typename, copyable_class_type) self
                // , const post<arg0_copyable_type>& arg0, ...
                BOOST_PP_ENUM_TRAILING(DBC_arg_num, 
                        DBC_post_arg_const_ref, ~)
                BOOST_PP_COMMA_IF(DBC_is_not_void)
                BOOST_PP_EXPR_IF(DBC_is_not_void, 
                        DBC_ADD_CONST_REF_(typename, result_type) result)
                ) {
            try {
                ::dbc::globally_checking_contract_ = true;
                DBC_LOG_DEBUG_(log << name() << "checking postconditions");
                DBC_RETHROW_VIOLATION_AS_(postcondition_violation, {
                    ensure(self
                            // , arg0, ...
                            BOOST_PP_ENUM_TRAILING(DBC_arg_num,
                                    DBC_arg_name, ~)
                            BOOST_PP_COMMA_IF(DBC_is_not_void)
                            BOOST_PP_EXPR_IF(DBC_is_not_void, result));
                });
                // And, base contract postconditions (subcontracting).
                if (base_contract_) {
                    /** @todo[LC] Can this base_self be declared const? 
                     * "const DBC_ASS_POST_(...) base_self(self);" */
                    /** @todo[LC] Does this require a copy constr? E.g., can
                     * a non-copyable class subcontract from a non-copyable
                     * parent? Make a test... */
                    DBC_ADD_POST_(typename, typename 
                            base_contract_type::copyable_class_type) 
                            base_self(self);
                    base_contract_->check_ensure(base_self
                            // , arg0, ...
                            BOOST_PP_ENUM_TRAILING(DBC_arg_num,
                                    DBC_arg_name, ~)
                            BOOST_PP_COMMA_IF(DBC_is_not_void)
                            BOOST_PP_EXPR_IF(DBC_is_not_void,result)
                            );
                }
                ::dbc::globally_checking_contract_ = false;
            } catch (...) {
                ::dbc::globally_checking_contract_ = false;
                throw;
            }
        }
#endif // check

    // Contract //

    protected:
#if DBC_CHECK_REQUIRE
        virtual void require(
                DBC_ADD_CONST_REF_(typename, class_type) self
                // , arg0, ...
                BOOST_PP_ENUM_TRAILING(DBC_arg_num, DBC_arg_const_ref, ~)
                ) = 0;
#endif // check

#if DBC_CHECK_ENSURE
        virtual void ensure(
                DBC_ADD_POST_CONST_REF_(typename, copyable_class_type) self
                // , arg0, ...
                BOOST_PP_ENUM_TRAILING(DBC_arg_num, 
                        DBC_post_arg_const_ref, ~)
                BOOST_PP_COMMA_IF(DBC_is_not_void)
                BOOST_PP_EXPR_IF(DBC_is_not_void, 
                        DBC_ADD_CONST_REF_(typename, result_type) result)
                ) = 0;
#endif // check

        /**
         * If this contract preconditions passed (for subcontracting guards).
         * If the preconditions of this contract passed -- regardless of 
         * whether its invariant, its base contract preconditions, and its base
         * contract invariant passed or not. This is set correctly only when 
         * this contract ensure() is called while it is always false within 
         * this contract require(). This can be used to write postconditions
         * guards in this contract ensure() that allow for more flexible
         * subcontracting -- see Design By Contract, by Examples.
         * @return Whether this contract preconditions (and only those) passed.
         */
        inline bool required() const { return required_; }
        
        inline result_type exec(
                // Only add ref here (it's const only if it was already const).
                typename boost::add_reference<class_type>::type self
                , mem_fun_type body
                // , arg0_type arg0, ...
                BOOST_PP_ENUM_TRAILING(DBC_arg_num, DBC_arg, ~)
                , const std::string& the_fun_name = ""
                , const bool& pre_invariant_check = true
                , const bool& require_check = true
                , const bool& post_invariant_check = true
                , const bool& ensure_check = true
                ) {
#if !DBC_CHECK_REQUIRE && !DBC_CHECK_ENSURE && !DBC_CHECK_INVARIANT
            // For optimization, just call body if not checking.
            return (self.*body)(
                    // arg0, ...
                    BOOST_PP_ENUM(DBC_arg_num, DBC_arg_name, ~)
            );

#else // check
            fun_name(the_fun_name);

            // Assertions disabled within assertions.
            if (globally_checking_contract_) {
                DBC_LOG_DEBUG_(log << name() << "entering, executing "
                    << "body, and returning (assertions disabled within "
                    << "assertion checking)"
                );
                return (self.*body)(
                        // arg0, ...
                        BOOST_PP_ENUM(DBC_arg_num, DBC_arg_name, ~)
                );
            }
            DBC_LOG_DEBUG_(log << name() << "entering");

            bool invariant_check = false;
#if DBC_CHECK_INVARIANT
            if (pre_invariant_check || post_invariant_check) {
                // Invariant checking disabled in class' nested calls (in 
                // nested calls, obj will be checing contract).
                // Casting resolves ambiguities with base class' dbc::object<>.
                invariant_check = !(
                    ((const object<class_type>&)self)
                    .dbc_object_checking_contract_);
                if (!invariant_check) {
                    DBC_LOG_DEBUG_(log << name() 
                            << "invariant checking disabled (nested call)");
                }
            }
#endif // check
            // Casting resolves ambiguities with base class' dbc::object<>.
            ((const object<class_type>&)self)
                    .dbc_object_checking_contract_ = true;

            try {
#if DBC_CHECK_ENSURE
                // Ideally, the post args will be declared only if 
                // (ensure_check) but then they will be local to the if code
                // complicating this code structure quite a bit. For now, the
                // only time ensure_check == false is for destrcustors which
                // have no arguments and a noncopyable self so these post 
                // declaration do not affect performances even when 
                // ensure_check is false.

                // If copyable, copy self and args for postconditions.
                DBC_ADD_POST_(typename, copyable_class_type) post_self(self);
                // post<arg0_copyable_type> post_arg0(arg0); ...
                BOOST_PP_REPEAT(DBC_arg_num, DBC_post_var_decl, ~)
#endif // check

                // In following code, invariant is checked *before* 
                // require/ensure so pre/post condition assertions can relay
                // on invariant to hold (e.g., if a precondition assertion was 
                // to dereference a ptr it could do so safely if inv asserted
                // prt not NULL...).

                // Effective preconditions: invariant AND require.
#if DBC_CHECK_INVARIANT
                if (invariant_check && pre_invariant_check) 
                    { check_invariant(self); }
#endif // check
#if DBC_CHECK_REQUIRE
                if (require_check) {
                    check_require(self
                            // , arg0, ...
                            BOOST_PP_ENUM_TRAILING(
                                    DBC_arg_num, DBC_arg_name, ~)
                            );
                }
#endif // check

                // Body call.
                DBC_LOG_DEBUG_(log << name() << "executing body");
                // If non-void "result_type result((self.*body)(arg0, ...));",
                // else just call "(self.*body)(arg0, ...);" (no result).
                BOOST_PP_EXPR_IF(DBC_is_not_void, result_type result)
                    BOOST_PP_LPAREN_IF(DBC_is_not_void) // "(" result constr.
                    (self.*body)(
                        // arg0, ...
                        BOOST_PP_ENUM(DBC_arg_num, DBC_arg_name, ~)
                    )
                    BOOST_PP_RPAREN_IF(DBC_is_not_void) // ")" result contr.
                ;

                // Effective postconditions: invariant AND ensure.
#if DBC_CHECK_INVARIANT
                if (invariant_check && post_invariant_check) 
                    { check_invariant(self); }
#endif // check
#if DBC_CHECK_ENSURE
                if (ensure_check) {
                    check_ensure(post_self
                            // , post_arg0, ...
                            BOOST_PP_ENUM_TRAILING(
                                    DBC_arg_num, DBC_post_var_name, ~)
                            // , result
                            BOOST_PP_COMMA_IF(DBC_is_not_void)
                            BOOST_PP_EXPR_IF(DBC_is_not_void, result)
                            );
                }
#endif // check

                DBC_LOG_DEBUG_(log << name() << "returning");
                // Casting resolves ambiguities with base class' dbc::object<>.
                ((const object<class_type>&)self)
                        .dbc_object_checking_contract_ = false;

                // If not void "return result;", else "return;" (no result).
                return BOOST_PP_EXPR_IF(DBC_is_not_void, result);
            } catch (...) {
                // Casting resolves ambiguities with base class' dbc::object<>.
                ((const object<class_type>&)self)
                        .dbc_object_checking_contract_ = false;
                throw;
            }
#endif // check
        }
    
    private:
        inline std::string name() const {
            std::string n = class_name_;
            if ("" != fun_name_) { n += "::" + fun_name_ + "()"; }
            if ("" != n) { n += ": "; }
            return n;
        }

        base_contract_type* base_contract_;
        std::string class_name_;
        std::string fun_name_;
        bool required_;
    }; // class mem

#   ifdef DBC_is_void // Constructors cannot return value.
public:
    /** 
     * Constructors do not check invariant together with preconditions. 
     * Invariant is checked only with postconditions. This is because before
     * body is executed (i.e., when preconditions are checked) object is not
     * fully created yet so invariant may not hold yet. Furthermore, 
     * constructors preconditions do not have access to object instance self
     * (as technically object does not exist yet and its invariant has not been
     * checked yet).
     */
    template<class C> // Constructors cannot have base.
    class constr: public mem<C, no_base_<C> > {
    public:
        BOOST_MPL_ASSERT_MSG(is_not_copyable_<C>::value,
                DBC_ERROR_class_type_cannot_be_specified_copyable_in_constructor_, ());

        typedef constr<C> this_type;
        typedef C copyable_class_type;
        typedef typename remove_copyable_<C>::type class_type;

        inline result_type call(
                // Only add ref here (it's const only if it was already const).
                typename boost::add_reference<class_type>::type self
                , typename mem<C, no_base_<C> >::mem_fun_type body
                // , arg0_type arg0, ...
                BOOST_PP_ENUM_TRAILING(DBC_arg_num, DBC_arg, ~)
                , const std::string& the_fun_name = ""
                ) {
            return exec(self, body
                    // , arg0, ...
                    BOOST_PP_ENUM_TRAILING(DBC_arg_num, DBC_arg_name, ~)
                    , the_fun_name
                    , false /* never check inv with preconditions */);
        }

#if DBC_CHECK_REQUIRE
    protected:
        virtual void require(
                /* User's require() has no self (obj doesn't exist yet */
                // const arg0_type& arg0, ...
                BOOST_PP_ENUM(DBC_arg_num, DBC_arg_const_ref, ~)
                ) = 0;
    
    private:
        inline void require(
                DBC_ADD_CONST_REF_(typename, class_type) self
                // , const arg0_type& arg0, ...
                BOOST_PP_ENUM_TRAILING(DBC_arg_num, DBC_arg_const_ref, ~)
                ) {
            // Invoke require() w/no self defined above as pure virtual.
            require(
                // arg0, ...
                BOOST_PP_ENUM(DBC_arg_num, DBC_arg_name, ~)
            );
        }
#endif // check
    }; // class constr
#   endif // DBC_is_void

#   ifdef DBC_is_void // Destructor cannot return value.
#   if DBC_arg_num == 0 // Destructor cannot have arguments.
public:
    /**
     * Destructor only check invariant at entry. No precondition checking as
     * there is no arugment. No postcondition and invariant checking at exit
     * because there is no object any more (it has been destructed).
     * Destructor must not throw to comply with STL exception safety 
     * requirements. Therefore, broken_destructor_invariant() is called if
     * invariant fails.
     */
    // Destr have no base (C++ will automatically invoke base's destr w/ its 
    // contract if it has one).
    template<class C> 
    class destr: public mem<C, no_base_<C> > {
    public:
        BOOST_MPL_ASSERT_MSG(is_not_copyable_<C>::value,
                DBC_ERROR_class_type_cannot_be_specified_copyable_in_destructor_, ());

        typedef destr<C> this_type;
        typedef C copyable_class_type;
        typedef typename remove_copyable_<C>::type class_type;

        destr(): invariant_violated_(false) {}

        inline result_type call( 
                // Only add ref here (it's const only if it was already const).
                typename boost::add_reference<class_type>::type self
                , typename mem<C, no_base_<C> >::mem_fun_type body
                // , arg0_type arg0, ...
                BOOST_PP_ENUM_TRAILING(DBC_arg_num, DBC_arg, ~)
                , const std::string& the_fun_name = ""
                ) {
            bool uncaught_ex = std::uncaught_exception();
            try {
                return exec(self, body
                        // , arg0, ...
                        BOOST_PP_ENUM_TRAILING(DBC_arg_num, DBC_arg_name, ~)
                        , the_fun_name
                        , true /* check inv with preconditions (at entry) */
                        , false /* never check preconditions */
                        , false /* never check inv with postconditions */
                        , false /* never check postcond (and no post copy) */);
            } catch (...) {
                if (invariant_violated_) {
                    if (uncaught_ex) {
                        // During stack unwinding invarint might be broken so
                        // no action is taken but the destructor body cannot be
                        // called as its invariant is broken. E.g., if a mem 
                        // fun brakes the invariant and its postcond+inv 
                        // checking throw, the invariant is broken, but if the 
                        // user attempts to handle such exception, the 
                        // destructor will be called while exception handling 
                        // is unwinding the stack and while the invariant is 
                        // broken.
                        DBC_LOG_VIOLATION_(
                            log << "Ignoring invariant violation because "
                                    << "destructor called during stack "
                                    << "unwinding (but unable to execute "
                                    << "destructor body)";
                        );
                    } else {
                        // If destr not called during exception handling 
                        // (uncaught_ex is false), then this destr should 
                        // notify the broken destructor invarint but destructor
                        // cannot throw, borken_destructor_invarint() is used.
                        broken_destructor_invariant();
                    }
                } else { 
                    // Re-throw exceptions if inv not violated so user destr
                    // code can throw (however, STL requires destr not to throw
                    // so such user destr is probably badly written...).
                    throw;
                }
            }
        }

#if DBC_CHECK_INVARIANT
        inline void check_invariant(
                DBC_ADD_CONST_REF_(typename, class_type) self) {
            invariant_violated_ = false;
            try {
                mem<C, no_base_<C> >::check_invariant(self); 
            } catch (...) {
                invariant_violated_ = true;
                throw;
            }
        }
#endif // check
        
        // Make sure no other operation throws.
        
#if DBC_CHECK_REQUIRE
        inline virtual void check_require(
                DBC_ADD_CONST_REF_(typename, class_type) self
                // , const arg0_type& arg0, ...
                BOOST_PP_ENUM_TRAILING(DBC_arg_num, DBC_arg_const_ref, ~)
                ) throw() {}
#endif // check

#if DBC_CHECK_ENSURE
        inline virtual void check_ensure(
                DBC_ADD_POST_CONST_REF_(typename, copyable_class_type) self
                // , const post<arg0_copyable_type>& arg0, ...
                BOOST_PP_ENUM_TRAILING(DBC_arg_num, 
                        DBC_post_arg_const_ref, ~)
                BOOST_PP_COMMA_IF(DBC_is_not_void)
                BOOST_PP_EXPR_IF(DBC_is_not_void, 
                        DBC_ADD_CONST_REF_(typename, result_type) result)
                ) throw() {}
#endif // check

    private:
        // Hide no require/ensure impl and make sure nothing throws (but can't
        // define these throw() otherwise they won't properly impl their pure
        // virtual base function).
#if DBC_CHECK_REQUIRE
        inline void require(
                DBC_ADD_CONST_REF_(typename, class_type) self) {}
#endif // check

#if DBC_CHECK_ENSURE
        inline void ensure(
                DBC_ADD_POST_CONST_REF_(typename, copyable_class_type) self) {}
#endif // check
    
        bool invariant_violated_;
    }; // class destr
#   endif // DBC_arg_num
#   endif // DBC_is_void

}; // class fun

} // namespace dbc

    // Undef ALL local macros.
#   undef DBC_post_var_decl
#   undef DBC_post_var_name
#   undef DBC_post_arg_const_ref
#   undef DBC_arg_const_ref
#   undef DBC_arg
#   undef DBC_arg_type
#   undef DBC_arg_name
#   undef DBC_is_not_spec
#   undef DBC_is_spec
#   undef DBC_is_not_void
#   undef DBC_is_void
#   undef DBC_arg_num
#   undef DBC_rest_arg_num

// Self-Iteration Out-of-range (should never happen...) //

#else
#   error "DBC preprocessor iteration depth out-of-range (internal error)"

#endif // BOOST_PP_IS_ITERATING

#endif // DBC

