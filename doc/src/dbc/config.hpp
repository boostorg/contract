/**
 * @file
 * Header file to only include library configuration symbols.
 * Default values are listed here. If these macros are defined by the user 
 * before the @e first inclusion of this file (or of @c "dbc.hpp" in general),
 * then the user defined values are retained. Otherwise, if no user defined
 * symbol is present for these macros, they are defined to the default values
 * listed here. Essentially, all these macro are defined as follow:
 * @code
 *  #ifndef DBC_CONFIG_<NAME>
 *  #define DBC_CONFIG_<NAME> <DEFAULT-MACRO-VALUE-FOR-NAME>
 *  #endif
 * @endcode
 */

// Assertion //

/**
 * Whether assertions that throw are checked or not (default: true).
 * This only controls assertion checking at run-time but the assertions are
 * compiled into the object code regardless of the definition of this symbol.
 * @see Use the @c DBC_CHECK_... symbols to control contract compilation.
 */
#define DBC_CONFIG_ENABLE_THROWING_ASSERTIONS true

/** Whether assertions that exit are checked or not (default: true).
 * This only controls assertion checking at run-time but the assertions are
 * compiled into the object code regardless of the definition of this symbol.
 * @see Use the @c DBC_CHECK_... symbols to control contract compilation.
 */
#define DBC_CONFIG_ENABLE_EXITING_ASSERTIONS true

/** Whether assertions that terminate are checked or not (default: true).
 * This only controls assertion checking at run-time but the assertions are
 * compiled into the object code regardless of the definition of this symbol.
 * @see Use the @c DBC_CHECK_... symbols to control contract compilation.
 */
#define DBC_CONFIG_ENABLE_TERMINATING_ASSERTIONS true

/** By default, throw exception on assertion violation. */
#define DBC_DEFAULT_THROW_ON_ASSERTION_VIOLATION     0
/** By default, exit the program with code 1 on assertion violation. */
#define DBC_DEFAULT_EXIT_ON_ASSERTION_VIOLATION      1
/** By default, terminate the program on assertion violation. */
#define DBC_DEFAULT_TERMINATE_ON_ASSERTION_VIOLATION 2

/** 
 * Default action to take on assertion violation. 
 * Must be defined to one of the <c>DBC_DEFAULT_..._ON_ASSERTION_VIOLATION</c>
 * symbols.
 */
#define DBC_CONFIG_DEFAULT_ON_ASSERTION_VIOLATION \
            DBC_DEFAULT_THROW_ON_ASSERTION_VIOLATION

// Logging //

/** Never log. */
#define DBC_LOG_LEVEL_NONE       0
/** Only log on assertion violation. */
#define DBC_LOG_LEVEL_VIOLATION  1
/** Log on assertion violation and for debug. */
#define DBC_LOG_LEVEL_DEBUG      2
/** Log on assertion violation, debug, and trace information. */
#define DBC_LOG_LEVEL_ALL        3

/** 
 * Log level to use.
 * Must be defined to one of the @c DBC_LOG_LEVEL_... symbols.
 */
#define DBC_CONFIG_LOG_LEVEL DBC_LOG_LEVEL_VIOLATION

/**
 * Print to log specified debug message (default to std::clog).
 * @param[in] message C-style null-terminated message string.
 */
#define DBC_CONFIG_LOG_DEBUG(message) \
    { std::clog << "dbc: " << message << std::endl; }

/**
 * Print to log specified assertion violation message (default to std::cerr).
 * @param[in] message C-style null-terminated message string.
 */
#define DBC_CONFIG_LOG_VIOLATION(message) \
    { std::cerr << "dbc: " << message << std::endl; }

// Documentation //

/**
 * Documentation comment for assertion.
 * The @c DBC_CONFIG_DOC_... macros automatically document the code only if
 * the code-based API is used and if the documentation tool can be instructed
 * to define the @c DBC_DOC symbol and expand all library macros (for
 * doxygen, specify "MACRO_EXPANSION = YES", add the "dbc.hpp" path to
 * "INCLUDE_PATH", and add DBC_DOC to "PREDEFINED" in the Doxyfile).
 * @see Automatic_Contract_Documentation
 */
#define DBC_CONFIG_DOC_ASSERTION(condition, label) condition/*label*/

/** Documentation comment for precoditions code block. */
#define DBC_CONFIG_DOC_REQUIRE(preconditions) \
    /** \pre \code preconditions \endcode */

/** Documentation comment for postcondition code block. */
#define DBC_CONFIG_DOC_ENSURE(postconditions) \
    /** \post \code postconditions \endcode */

/** Documentation comment for class invariant code block. */
#define DBC_CONFIG_DOC_INVARIANT(full_class_type, invariants) \
    /** <table border="0" cellpadding="0" cellspacing="0"><tr><td><b>Precondition/Postcondition/Invariant Parameters:</b></td></tr><tr><td><table border="0" cellspacing="0"><tr><td></td>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<td><tt>[in]</tt></td><td><em>self</em></td><td>Constant reference to this object (similar to \c *this in \c const context).</td></tr><tr><td></td><td><tt>[in]</tt></td><td><em>entity.old</em></td><td>Value \e entity had when preconditions were evaluated (in postcondition and for copiable \e entity only).</td></tr><tr><td></td><td><tt>[in]</tt></td><td><em>entity.now</em></td><td>Value \e entity has when postconditions are evaluated (in postcondition only).</td></tr><tr><td></td><td><tt>[in]</tt></td><td><em>result</em></td><td>Value being returned (in postcondition of non-void functions only).</td></tr></table></td></tr></table> */ \
    /** \invariant */ \
    /** \code invariants \endcode */ \
    /** \class full_class_type */

// Library Compilation //

/** 
 * Maximum number of argument supported for contract function in
 * <c>[0, 255]</c>.
 * @warning Increasing this number will significantly increase compilation
 *  time!
 */
#define DBC_CONFIG_MAX_ARGC 3

/** 
 * This files path must exist within your include path settings (use @c -I
 * option for @c g++). 
 */
#define DBC_CONFIG_FUN_HPP_FILE_PATH "dbc/fun.hpp"

