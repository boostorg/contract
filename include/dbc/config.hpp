/**
 * @file
 * @author Copyright (C) 2009 Lorenzo Caminiti.
 *  Distributed under DBC++ Software License (see file LICENSE_1_0.txt).
 */

#ifndef DBC_CONFIG_HPP_
#define DBC_CONFIG_HPP_

#include "detail/pp/defines.hpp" // Must be 1st include.
#include <iostream>

// Assertion //

/** Whether assertions that throw are checked or not (default: true). */
#ifndef DBC_CONFIG_ENABLE_THROWING_ASSERTIONS
#   define DBC_CONFIG_ENABLE_THROWING_ASSERTIONS true
#endif

/** Whether assertions that exit are checked or not (default: true). */
#ifndef DBC_CONFIG_ENABLE_EXITING_ASSERTIONS
#   define DBC_CONFIG_ENABLE_EXITING_ASSERTIONS true
#endif

/** Whether assertions that terminate are checked or not (default: true). */
#ifndef DBC_CONFIG_ENABLE_TERMINATING_ASSERTIONS
#   define DBC_CONFIG_ENABLE_TERMINATING_ASSERTIONS true
#endif

/** Default action on assertion violation: raise(), exit(1), or terminate(). */
#define DBC_DEFAULT_RAISE_ON_ASSERTION_VIOLATION     0
#define DBC_DEFAULT_EXIT_ON_ASSERTION_VIOLATION      1
#define DBC_DEFAULT_TERMINATE_ON_ASSERTION_VIOLATION 2
#ifndef DBC_CONFIG_DEFAULT_ON_ASSERTION_VIOLATION
#   define DBC_CONFIG_DEFAULT_ON_ASSERTION_VIOLATION \
            DBC_DEFAULT_RAISE_ON_ASSERTION_VIOLATION
#endif
#ifdef DBC // Validate macro value only if DBC.
#   if      DBC_CONFIG_DEFAULT_ON_ASSERTION_VIOLATION != \
                DBC_DEFAULT_RAISE_ON_ASSERTION_VIOLATION && \
            DBC_CONFIG_DEFAULT_ON_ASSERTION_VIOLATION != \
                DBC_DEFAULT_EXIT_ON_ASSERTION_VIOLATION && \
            DBC_CONFIG_DEFAULT_ON_ASSERTION_VIOLATION != \
                DBC_DEFAULT_TERMINATE_ON_ASSERTION_VIOLATION 
#       error "invalid DBC default action on assertion violation DBC_CONFIG_DEFAULT_ON_ASSERTION_VIOLATION"
#   endif
#endif //DBC

// Logging //

/** Log level NONE, VIOLATION (default), DEBUG, ALL. */
#define DBC_LOG_LEVEL_NONE       0
#define DBC_LOG_LEVEL_VIOLATION  1
#define DBC_LOG_LEVEL_DEBUG      2
#define DBC_LOG_LEVEL_ALL        3
#ifndef DBC_CONFIG_LOG_LEVEL
#   define DBC_CONFIG_LOG_LEVEL DBC_LOG_LEVEL_VIOLATION
#endif
#ifdef DBC // Validate macro value only if DBC.
#   if DBC_CONFIG_LOG_LEVEL != DBC_LOG_LEVEL_NONE && \
            DBC_CONFIG_LOG_LEVEL != DBC_LOG_LEVEL_VIOLATION && \
            DBC_CONFIG_LOG_LEVEL != DBC_LOG_LEVEL_DEBUG && \
            DBC_CONFIG_LOG_LEVEL != DBC_LOG_LEVEL_ALL
#       error "invalid DBC log level DBC_CONFIG_LOG_LEVEL"
#   endif
#endif //DBC

/**
 * Print to log specified debug message (default to std::clog).
 * @param[in] message C-style null-terminated message string.
 */
#ifndef DBC_CONFIG_LOG_DEBUG
#   define DBC_CONFIG_LOG_DEBUG(message) \
            { std::clog << "dbc: " << message << std::endl; }
#endif

/**
 * Print to log specified assertion violation message (default to std::cerr).
 * @param[in] message C-style null-terminated message string.
 */
#ifndef DBC_CONFIG_LOG_VIOLATION
#   define DBC_CONFIG_LOG_VIOLATION(message) \
            { std::cerr << "dbc: " << message << std::endl; }
#endif

// Documentation //

/** Document comment for assertion. */
#ifndef DBC_CONFIG_DOC_ASSERTION
    // The comment "/*label*/" below prints label in Doxygen (don't change it).
#   define DBC_CONFIG_DOC_ASSERTION(condition, label) condition/*label*/
#endif

/** Documentation comment for precoditions code block. */
#ifndef DBC_CONFIG_DOC_REQUIRE
#   define DBC_CONFIG_DOC_REQUIRE(require_code) /** \pre \code require_code \endcode */
#endif

/** Documentation comment for postcondition code block. */
#ifndef DBC_CONFIG_DOC_ENSURE
#   define DBC_CONFIG_DOC_ENSURE(ensure_code) /** \post \code ensure_code \endcode */
#endif

/** Documentation comment for class invariant code block. */
#ifndef DBC_CONFIG_DOC_INVARIANT
#   define DBC_CONFIG_DOC_INVARIANT(full_class_type, invariant_code) \
    /** <table border="0" cellpadding="0" cellspacing="0"><tr><td><b>Precondition/Postcondition/Invariant Parameters:</b></td></tr><tr><td><table border="0" cellspacing="0"><tr><td></td>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<td><tt>[in]</tt></td><td><em>self</em></td><td>Constant reference to this object (similar to \c *this in \c const context).</td></tr><tr><td></td><td><tt>[in]</tt></td><td><em>entity.old</em></td><td>Value \e entity had when preconditions were evaluated (in postcondition and for copiable \e entity only).</td></tr><tr><td></td><td><tt>[in]</tt></td><td><em>entity.now</em></td><td>Value \e entity has when postconditions are evaluated (in postcondition only).</td></tr><tr><td></td><td><tt>[in]</tt></td><td><em>result</em></td><td>Value being returned (in postcondition of non-void functions only).</td></tr></table></td></tr></table> */ \
    /** \invariant */ \
    /** \code invariant_code \endcode */ \
    /** \class full_class_type */
#endif

// Library Compilation //

/** Maximum number of argument supported for contract function (5 default). 
 * Increasing this number will significantly increase compilation time! */
#ifndef DBC_CONFIG_MAX_ARGC
#    define DBC_CONFIG_MAX_ARGC 3 // default max arg count
#endif
#ifdef DBC // Validate macro value only if DBC.
#   if DBC_CONFIG_MAX_ARGC < 0
#       error "DBC argument count DBC_CONFIG_MAX_ARGC count be negative"
#   endif
#   include <boost/preprocessor.hpp> // Included only if DBC.
#   if DBC_CONFIG_MAX_ARGS > BOOST_PP_LIMIT_MAG
#       error "DBC argument count DBC_CONFIG_MAX_ARGC cannot be greater then BOOST_PP_LIMIT_MAG"
#   endif
#endif // DBC

/** This files path must exist within your include path settings (-I). */
#ifndef DBC_CONFIG_FUN_HPP_FILE_PATH
#   define DBC_CONFIG_FUN_HPP_FILE_PATH "dbc/fun.hpp"
#endif

#ifndef DBC_CONFIG_FUNCTOR_HPP_FILE_PATH
#   define DBC_CONFIG_FUNCTOR_HPP_FILE_PATH "dbc/detail/separating/functor.hpp"
#endif

#ifndef DBC_CONFIG_VARIATOR_HPP_FILE_PATH
#   define DBC_CONFIG_VARIATOR_HPP_FILE_PATH \
            "dbc/detail/separating/variator.hpp"
#endif

#endif // DBC_CONFIG_HPP_

