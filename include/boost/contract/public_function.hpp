
#ifndef BOOST_CONTRACT_PUBLIC_FUNCTION_HPP_
#define BOOST_CONTRACT_PUBLIC_FUNCTION_HPP_

/** @file */

#include <boost/contract/core/access.hpp>
#include <boost/contract/core/set_precondition_old_postcondition.hpp>
#include <boost/contract/core/virtual.hpp>
#include <boost/contract/aux_/operation/public_function.hpp>
#include <boost/contract/aux_/operation/public_static_function.hpp>
#include <boost/contract/aux_/none.hpp>
/** @cond */
#include <boost/optional.hpp>
#include <boost/function_types/result_type.hpp>
#include <boost/function_types/function_arity.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/type_traits/remove_reference.hpp>
#include <boost/static_assert.hpp>
/** @endcond */

#if BOOST_CONTRACT_PRECONDITIONS || BOOST_CONTRACT_POSTCONDITIONS || \
        BOOST_CONTRACT_INVARIANTS

/* PRIVATE */

// This check is not strictly necessary because compilation will fail anyways,
// but it helps limiting cryptic compiler's errors.
#define BOOST_CONTRACT_PUBLIC_FUNCTION_ASSERT_ARITY_(F, arity) \
    BOOST_STATIC_ASSERT_MSG( \
        /* -2 for both `this` and `virtual_*` extra parameters */ \
        boost::function_types::function_arity<F>::value - 2 == arity, \
        "missing one or more arguments for specified function" \
    );

// Always enforce this so base contracts can always specify postconditions with
// result, without need to change derived contracts.
#define BOOST_CONTRACT_PUBLIC_FUNCTION_ASSERT_NO_RESULT_(F) \
    BOOST_STATIC_ASSERT_MSG( \
        boost::is_same< \
            typename boost::function_types::result_type<F>::type, \
            void \
        >::value, \
        "missing 'result' argument for non-void function" \
    );

#define BOOST_CONTRACT_PUBLIC_FUNCTION_ASSERT_RESULT_(F, R) \
    BOOST_STATIC_ASSERT_MSG( \
        boost::is_same< \
            typename boost::remove_reference<typename boost::function_types:: \
                    result_type<F>::type>::type, \
            typename boost::contract::public_function_:: \
                    remove_optional_ref<R>::type \
        >::value, \
        "mismatching result type for specified function" \
    );

// Always enforce this so this lib can check and enforce override.
#define BOOST_CONTRACT_PUBLIC_FUNCTION_ASSERT_BASE_TYPES_(C) \
    BOOST_STATIC_ASSERT_MSG( \
        boost::contract::access::has_base_types<C>::value, \
        "enclosing class missing 'base-types' typedef" \
    );

/* CODE */

namespace boost { namespace contract {

namespace public_function_ {
    template<typename R>
    struct remove_optional_ref { typedef R type; };

    template<typename R>
    struct remove_optional_ref<boost::optional<R> > {
        typedef typename boost::remove_reference<R>::type type;
    };
}

#endif

// For static member functions.
template<class C>
set_precondition_old_postcondition<> public_function() {
    #if BOOST_CONTRACT_PRECONDITIONS || BOOST_CONTRACT_POSTCONDITIONS || \
            BOOST_CONTRACT_INVARIANTS
        return set_precondition_old_postcondition<>(
            new boost::contract::aux::public_static_function<C>());
    #else
        return set_precondition_old_postcondition<>();
    #endif
}

// For non-virtual, non-overriding member functions.
template<class C>
set_precondition_old_postcondition<> public_function(C* obj) {
    #if BOOST_CONTRACT_PRECONDITIONS || BOOST_CONTRACT_POSTCONDITIONS || \
            BOOST_CONTRACT_INVARIANTS
        boost::contract::aux::none n;
        return set_precondition_old_postcondition<>(
            new boost::contract::aux::public_function<
                boost::contract::aux::none,
                boost::contract::aux::none,
                boost::contract::aux::none,
                C,
                boost::contract::aux::none, boost::contract::aux::none
            >(static_cast<boost::contract::virtual_*>(0), obj, n, n, n)
        );
    #else
        return set_precondition_old_postcondition<>();
    #endif
}

// NOTE: O and R (optionally) allowed only when v is present because:
// * An overriding func must override a base func declared virtual so with
//   v extra param, thus the overriding func must also always have v (i.e., O
//   might be present only if v is also present).
//   However, the first appearing virtual func (e.g., in root class) will not
//   override any previously declared virtual func so does not need O (i.e., O
//   always optional).
//   Furthermore, F needs to be specified only together with O.
// * R is only used for virtual functions (i.e., R might be present only if v
//   is also present).
//   However, R is never specified, not even for virtual functions, when the
//   return type is void (i.e., R always optional).

// For virtual, non-overriding, void function.
template<class C>
set_precondition_old_postcondition<> public_function(virtual_* v, C* obj) {
    #if BOOST_CONTRACT_PRECONDITIONS || BOOST_CONTRACT_POSTCONDITIONS || \
            BOOST_CONTRACT_INVARIANTS
        // NOTE: No F so cannot enforce enclosing function is void (up to user).
        boost::contract::aux::none n;
        return set_precondition_old_postcondition<>(
            new boost::contract::aux::public_function<
                boost::contract::aux::none,
                boost::contract::aux::none,
                boost::contract::aux::none,
                C,
                boost::contract::aux::none, boost::contract::aux::none
            >(v, obj, n, n, n)
        );
    #else
        return set_precondition_old_postcondition<>();
    #endif
}

// For virtual, non-overriding, non-void member functions.
template<typename R, class C>
set_precondition_old_postcondition<R> public_function(
        virtual_* v, R& r, C* obj) {
    #if BOOST_CONTRACT_PRECONDITIONS || BOOST_CONTRACT_POSTCONDITIONS || \
            BOOST_CONTRACT_INVARIANTS
        // NOTE: No F so cannot enforce enclosing func returns R (up to user).
        boost::contract::aux::none n;
        return set_precondition_old_postcondition<R>(
            new boost::contract::aux::public_function<
                boost::contract::aux::none,
                R,
                boost::contract::aux::none,
                C,
                boost::contract::aux::none, boost::contract::aux::none
            >(v, obj, r, n, n)
        );
    #else
        return set_precondition_old_postcondition<R>(
    #endif
}

/* Overriding (arity = 0) */

// For virtual, overriding, void member functions.
template<class O, typename F, class C>
set_precondition_old_postcondition<> public_function(virtual_* v, F, C* obj) {
    #if BOOST_CONTRACT_PRECONDITIONS || BOOST_CONTRACT_POSTCONDITIONS || \
            BOOST_CONTRACT_INVARIANTS
        BOOST_CONTRACT_PUBLIC_FUNCTION_ASSERT_ARITY_(F, 0)
        BOOST_CONTRACT_PUBLIC_FUNCTION_ASSERT_NO_RESULT_(F)
        BOOST_CONTRACT_PUBLIC_FUNCTION_ASSERT_BASE_TYPES_(C)
        boost::contract::aux::none n;
        return set_precondition_old_postcondition<>(
            new boost::contract::aux::public_function<
                O,
                boost::contract::aux::none,
                F,
                C,
                boost::contract::aux::none, boost::contract::aux::none
            >(v, obj, n, n, n)
        );
    #else
        return set_precondition_old_postcondition<>();
    #endif
}

// For virtual, overriding, non-void member functions of class with bases.
template<class O, typename R, typename F, class C>
set_precondition_old_postcondition<R> public_function(
        virtual_* v, R& r, F, C* obj) {
    #if BOOST_CONTRACT_PRECONDITIONS || BOOST_CONTRACT_POSTCONDITIONS || \
            BOOST_CONTRACT_INVARIANTS
        BOOST_CONTRACT_PUBLIC_FUNCTION_ASSERT_ARITY_(F, 0)
        BOOST_CONTRACT_PUBLIC_FUNCTION_ASSERT_RESULT_(F, R)
        BOOST_CONTRACT_PUBLIC_FUNCTION_ASSERT_BASE_TYPES_(C)
        boost::contract::aux::none n;
        return set_precondition_old_postcondition<R>(
            new boost::contract::aux::public_function<
                O,
                R,
                F,
                C,
                boost::contract::aux::none, boost::contract::aux::none
            >(v, obj, r, n, n)
        );
    #else
        return set_precondition_old_postcondition<R>();
    #endif
}

/* Overriding (arity = 1) */

template<class O, typename F, class C, typename A0>
set_precondition_old_postcondition<> public_function(
        virtual_* v, F, C* obj, A0& a0) {
    #if BOOST_CONTRACT_PRECONDITIONS || BOOST_CONTRACT_POSTCONDITIONS || \
            BOOST_CONTRACT_INVARIANTS
        BOOST_CONTRACT_PUBLIC_FUNCTION_ASSERT_ARITY_(F, 1)
        BOOST_CONTRACT_PUBLIC_FUNCTION_ASSERT_NO_RESULT_(F)
        BOOST_CONTRACT_PUBLIC_FUNCTION_ASSERT_BASE_TYPES_(C)
        boost::contract::aux::none n;
        return set_precondition_old_postcondition<>(
            new boost::contract::aux::public_function<
                O,
                boost::contract::aux::none,
                F,
                C,
                A0, boost::contract::aux::none
            >(v, obj, n, a0, n)
        );
    #else
        return set_precondition_old_postcondition<>();
    #endif
}

template<class O, typename R, typename F, class C, typename A0>
set_precondition_old_postcondition<R> public_function(
        virtual_* v, R& r, F, C* obj, A0& a0) {
    #if BOOST_CONTRACT_PRECONDITIONS || BOOST_CONTRACT_POSTCONDITIONS || \
            BOOST_CONTRACT_INVARIANTS
        BOOST_CONTRACT_PUBLIC_FUNCTION_ASSERT_ARITY_(F, 1)
        BOOST_CONTRACT_PUBLIC_FUNCTION_ASSERT_RESULT_(F, R)
        BOOST_CONTRACT_PUBLIC_FUNCTION_ASSERT_BASE_TYPES_(C)
        boost::contract::aux::none n;
        return set_precondition_old_postcondition<R>(
            new boost::contract::aux::public_function<
                O,
                R,
                F,
                C,
                A0, boost::contract::aux::none
            >(v, obj, r, a0, n)
        );
    #else
        return set_precondition_old_postcondition<R>(
    #endif
}

/* Overriding (arity = 2) */

template<class O, typename F, class C, typename A0, typename A1>
set_precondition_old_postcondition<> public_function(
        virtual_* v, F, C* obj, A0& a0, A1& a1) {
    #if BOOST_CONTRACT_PRECONDITIONS || BOOST_CONTRACT_POSTCONDITIONS || \
            BOOST_CONTRACT_INVARIANTS
        BOOST_CONTRACT_PUBLIC_FUNCTION_ASSERT_ARITY_(F, 2)
        BOOST_CONTRACT_PUBLIC_FUNCTION_ASSERT_NO_RESULT_(F)
        BOOST_CONTRACT_PUBLIC_FUNCTION_ASSERT_BASE_TYPES_(C)
        boost::contract::aux::none n;
        return set_precondition_old_postcondition<>(
            new boost::contract::aux::public_function<
                O,
                boost::contract::aux::none,
                F,
                C,
                A0, A1
            >(v, obj, n, a0, a1)
        );
    #else
        return set_precondition_old_postcondition<>(
    #endif
}
    
template<class O, typename R, typename F, class C, typename A0, typename A1>
set_precondition_old_postcondition<R> public_function(
        virtual_* v, R& r, F, C* obj, A0& a0, A1& a1) {
    #if BOOST_CONTRACT_PRECONDITIONS || BOOST_CONTRACT_POSTCONDITIONS || \
            BOOST_CONTRACT_INVARIANTS
        BOOST_CONTRACT_PUBLIC_FUNCTION_ASSERT_ARITY_(F, 2)
        BOOST_CONTRACT_PUBLIC_FUNCTION_ASSERT_RESULT_(F, R)
        BOOST_CONTRACT_PUBLIC_FUNCTION_ASSERT_BASE_TYPES_(C)
        return set_precondition_old_postcondition<R>(
            new boost::contract::aux::public_function<
                O,
                R,
                F,
                C,
                A0, A1
            >(v, obj, r, a0, a1)
        );
    #else
        return set_precondition_old_postcondition<R>();
    #endif
}

} } // namespace

#endif // #include guard

