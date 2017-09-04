
#ifndef DBC_PP_DEFINE_HPP_
#define DBC_PP_DEFINE_HPP_

// Compilation Symbols (must #include before any other library #include.

// Only very basic consistency checking on control macro #definition is done 
// here -- the rest is left up to the user. E.g., probably makes no sense to
// #define DBC_CHECK_REQUIRE without #defining also DBC but this is not 
// enforced here.

#if defined DBC_DOC && defined DBC_ALL
#   error "DBC_DOC cannot be #defined at the same time with DBC and/or DBC_ALL"
#endif

#ifdef DBC_NO // Shortcut for all DBC_CHECK off.
#   ifdef DBC_ALL
#       error "DBC_NO and DBC_ALL cannot be #defined at the same time"
#   endif
#   undef DBC_CHECK_REQUIRE
#   undef DBC_CHECK_ENSURE
#   undef DBC_CHECK_INVARIANT
#   undef DBC_CHECK_LOOP
#endif

#ifdef DBC_ALL // Shortcut for all DBC_CHECK on.
#   ifdef DBC_NO
#       error "DBC_ALL and DBC_NO cannot be #defined at the same time"
#   endif
#   define DBC_CHECK_REQUIRE
#   define DBC_CHECK_ENSURE
#   define DBC_CHECK_INVARIANT
#   define DBC_CHECK_LOOP
#endif

#ifdef DBC // DBC symbol controls user's code compilation.
#   error "DBC is #defined internally and it should not be #defined by the user -- use DBC_ALL, DBC_NO, DBC_CHECK_REQUIRE, DBC_CHECK_ENSURE, and/or DBC_CHECK_INVARIANT instead"
#elif defined DBC_CHECK_REQUIRE || defined DBC_CHECK_ENSURE \
        || defined DBC_CHECK_INVARIANT // DBC_CHECK_LOOP must be separate!
#   define DBC
#else
#   undef DBC
#endif

// Make sure checks #defined as 0/1 (to use them with Boost.Preprocessor if).

#ifdef DBC_CHECK_REQUIRE
#   undef DBC_CHECK_REQUIRE
#   define DBC_CHECK_REQUIRE 1
#else
#   define DBC_CHECK_REQUIRE 0
#endif

#ifdef DBC_CHECK_ENSURE
#   undef DBC_CHECK_ENSURE
#   define DBC_CHECK_ENSURE 1
#else
#   define DBC_CHECK_ENSURE 0
#endif

#ifdef DBC_CHECK_INVARIANT
#   undef DBC_CHECK_INVARIANT
#   define DBC_CHECK_INVARIANT 1
#else
#   define DBC_CHECK_INVARIANT 0
#endif

#ifdef DBC_CHECK_LOOP
#   undef DBC_CHECK_LOOP
#   define DBC_CHECK_LOOP 1
#else
#   define DBC_CHECK_LOOP 0
#endif

#endif // DBC_PP_DEFINE_HPP_

