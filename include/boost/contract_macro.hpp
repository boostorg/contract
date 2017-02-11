
#ifndef BOOST_CONTRACT_MACRO_HPP_
#define BOOST_CONTRACT_MACRO_HPP_

// IMPORTANT: Following headers can always be #included (without any #if-guard)
// because they expand to trivial code that does not affect compile-time. 
// IMPORTANT: Following header must always be #included here (without any
// #if-guard) because they define types and macros that are typically left in
// user code even when contracts are disables (these types and macros never
// affect run-time and their definitions are trivial when contracts are disabled
// so their impact on compile-time is negligible).
#include <boost/contract/core/constructor_precondition.hpp>
#include <boost/contract/core/virtual.hpp>
#include <boost/contract/core/access.hpp>
#include <boost/contract/core/check_macro.hpp>
#include <boost/contract/core/config.hpp>
#include <boost/contract/base_types.hpp>
#include <boost/contract/override.hpp>

#if     !defined(BOOST_CONTRACT_NO_INVARIANTS) || \
        !defined(BOOST_CONTRACT_NO_PRECONDITIONS) || \
        !defined(BOOST_CONTRACT_NO_POSTCONDITIONS) || \
        !defined(BOOST_CONTRACT_NO_EXCEPTS)
    #include <boost/contract/assert.hpp>
#endif

// TODO: Document this will cause all pre, post, inv assertions to have the same line number (but different code text) in the error message.
// PRECONDITION(ftor,,,)
#ifndef BOOST_CONTRACT_NO_PRECONDITIONS
    #define BOOST_CONTRACT_PRECONDITION(...) .precondition(__VA_ARGS__)
#else
    #define BOOST_CONTRACT_PRECONDITION(...) /* nothing */
#endif

// OLD(ftor,,,)
//
// OLD_PTR[_IF_COPYABLE](type,,,)(name);
// OLD_PTR[_IF_COPYABLE](type,,,)(name, value);
// OLD_PTR[_IF_COPYABLE](type,,,)(v, name, value);
#ifndef BOOST_CONTRACT_NO_OLDS
    #include <boost/contract/old.hpp>
    #include <boost/preprocessor/facilities/overload.hpp>
    #include <boost/preprocessor/facilities/empty.hpp>
    #include <boost/preprocessor/cat.hpp>
    
    #define BOOST_CONTRACT_OLD_VAR_1(name) \
        name
    #define BOOST_CONTRACT_OLD_VAR_2(name, value) \
        name = BOOST_CONTRACT_OLDOF(value)
    #define BOOST_CONTRACT_OLD_VAR_3(v, name, value) \
        name = BOOST_CONTRACT_OLDOF(v, value)

    #define BOOST_CONTRACT_OLD_VAR_(...) \
        BOOST_PP_CAT(BOOST_PP_OVERLOAD(BOOST_CONTRACT_OLD_VAR_, __VA_ARGS__) \
                (__VA_ARGS__), BOOST_PP_EMPTY())

    #define BOOST_CONTRACT_OLD_PTR(...) \
        boost::contract::old_ptr< __VA_ARGS__ > \
        BOOST_CONTRACT_OLD_VAR_
    #define BOOST_CONTRACT_OLD_PTR_IF_COPYABLE(...) \
        boost::contract::old_ptr_if_copyable< __VA_ARGS__ > \
        BOOST_CONTRACT_OLD_VAR_
    
    #define BOOST_CONTRACT_OLD(...) .old(__VA_ARGS__)
#else
    #include <boost/preprocessor/tuple/eat.hpp>

    #define BOOST_CONTRACT_OLD_PTR(...) BOOST_PP_TUPLE_EAT(0)
    #define BOOST_CONTRACT_OLD_PTR_IF_COPYABLE(...) BOOST_PP_TUPLE_EAT(0)
    #define BOOST_CONTRACT_OLD(...) /* nothing */
#endif
    
// POSTCONDITION(ftor,,,)
#ifndef BOOST_CONTRACT_NO_POSTCONDITIONS
    #define BOOST_CONTRACT_POSTCONDITION(...) .postcondition(__VA_ARGS__)
#else
    #define BOOST_CONTRACT_POSTCONDITION(...) /* nothing */
#endif

// TODO: Added .except and EXCEPT to ifdef and ifdef_macro tests.
// EXCEPT(ftor,,,)
#ifndef BOOST_CONTRACT_NO_EXCEPTS
    #define BOOST_CONTRACT_EXCEPT(...) .except(__VA_ARGS__)
#else
    #define BOOST_CONTRACT_EXCEPT(...) /* nothing */
#endif

// INVARIANT({ ,,, })
// INVARIANT_VOLATILE({ ,,, })
// STATIC_INVARIANT({ ,,, })
#ifndef BOOST_CONTRACT_NO_INVARIANTS
    #include <boost/contract/core/config.hpp>

    #define BOOST_CONTRACT_INVARIANT(...) \
        void BOOST_CONTRACT_INVARIANT_FUNC() const __VA_ARGS__
    #define BOOST_CONTRACT_INVARIANT_VOLATILE(...) \
        void BOOST_CONTRACT_INVARIANT_FUNC() const volatile __VA_ARGS__
    #define BOOST_CONTRACT_STATIC_INVARIANT(...) \
        static void BOOST_CONTRACT_STATIC_INVARIANT_FUNC() __VA_ARGS__
#else
    #define BOOST_CONTRACT_INVARIANT(...) /* nothing */
    #define BOOST_CONTRACT_INVARIANT_VOLATILE(...) /* nothing */
    #define BOOST_CONTRACT_STATIC_INVARIANT(...) /* nothing */
#endif

// FUNCTION() [...] ;
#ifndef BOOST_CONTRACT_NO_FUNCTIONS
    #include <boost/contract/function.hpp>
    #include <boost/contract/check.hpp>
    #include <boost/contract/detail/name.hpp>

    #define BOOST_CONTRACT_FUNCTION \
        boost::contract::check BOOST_CONTRACT_DETAIL_NAME2(c, __LINE__) = \
                boost::contract::function
#else
    #include <boost/preprocessor/facilities/empty.hpp>

    #define BOOST_CONTRACT_FUNCTION BOOST_PP_EMPTY
#endif

// STATIC_PUBLIC_FUNCTION(class_type,,,) [...] ;
//
// PUBLIC_FUNCTION(obj) [...] ;
// PUBLIC_FUNCTION(v, obj) [...] ;
// PUBLIC_FUNCTION(v, r, obj) [...] ;
//
// PUBLIC_FUNCTION_OVERRIDE(override_type)(v, fptr, obj, args...) [...] ;
// PUBLIC_FUNCTION_OVERRIDE(override_type)(v, r, fptr, obj, args...) [...] ;
#ifndef BOOST_CONTRACT_NO_PUBLIC_FUNCTIONS
    #include <boost/contract/public_function.hpp>
    #include <boost/contract/check.hpp>
    #include <boost/contract/detail/name.hpp>

    #define BOOST_CONTRACT_STATIC_PUBLIC_FUNCTION(...) \
        boost::contract::check BOOST_CONTRACT_DETAIL_NAME2(c, __LINE__) = \
                boost::contract::public_function< __VA_ARGS__ >()
    
    #define BOOST_CONTRACT_PUBLIC_FUNCTION \
        boost::contract::check BOOST_CONTRACT_DETAIL_NAME2(c, __LINE__) = \
                boost::contract::public_function

    #define BOOST_CONTRACT_PUBLIC_FUNCTION_OVERRIDE(override_type) \
        boost::contract::check BOOST_CONTRACT_DETAIL_NAME2(c, __LINE__) = \
                boost::contract::public_function<override_type>
#else
    #include <boost/preprocessor/tuple/eat.hpp>

    #define BOOST_CONTRACT_STATIC_PUBLIC_FUNCTION(...) /* nothing */
    #define BOOST_CONTRACT_PUBLIC_FUNCTION BOOST_PP_TUPLE_EAT(0)
    #define BOOST_CONTRACT_PUBLIC_FUNCTION_OVERRIDE(override_type) \
        BOOST_PP_TUPLE_EAT(0)
#endif

// CONSTRUCTOR(obj) [...] ;
#ifndef BOOST_CONTRACT_NO_CONSTRUCTORS
    #include <boost/contract/constructor.hpp>
    #include <boost/contract/check.hpp>
    #include <boost/contract/detail/name.hpp>

    #define BOOST_CONTRACT_CONSTRUCTOR(obj) \
        boost::contract::check BOOST_CONTRACT_DETAIL_NAME2(c, __LINE__) = \
                boost::contract::constructor(obj)
#else
    #define BOOST_CONTRACT_CONSTRUCTOR(obj) /* nothing */
#endif
// CONSTRUCTOR_PRECONDITION(class_type,,,)(ftor,,,)
#if     !defined(BOOST_CONTRACT_NO_CONSTRUCTORS) && \
        !defined(BOOST_CONTRACT_NO_PRECONDITIONS)
    // constructor_precondition.hpp already #included at top.
    #define BOOST_CONTRACT_CONSTRUCTOR_PRECONDITION(...) \
        boost::contract::constructor_precondition< __VA_ARGS__ >
#else
    #include <boost/preprocessor/tuple/eat.hpp>

    // constructor_precondition.hpp already #included at top.
    #define BOOST_CONTRACT_CONSTRUCTOR_PRECONDITION(...) \
        /* always use default ctor (i.e., do nothing) */ \
        boost::contract::constructor_precondition< __VA_ARGS__ >() \
        BOOST_PP_TUPLE_EAT(0)
#endif

// DESTRUCTOR(obj) [...] ;
#ifndef BOOST_CONTRACT_NO_DESTRUCTORS
    #include <boost/contract/destructor.hpp>
    #include <boost/contract/check.hpp>
    #include <boost/contract/detail/name.hpp>

    #define BOOST_CONTRACT_DESTRUCTOR(obj) \
        boost::contract::check BOOST_CONTRACT_DETAIL_NAME2(c, __LINE__) = \
                boost::contract::destructor(obj)
#else
    #define BOOST_CONTRACT_DESTRUCTOR(obj) /* nothing */
#endif

#endif // #include guard

