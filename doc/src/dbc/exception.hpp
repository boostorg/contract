/**
 * @file
 * Header file to only include exception facilities.
 */

namespace dbc {

/**
 * Base class for all contract violation exceptions.
 * If this exception is thrown while checking preconditions, postconditions,
 * or invariants then it is automatically re-thrown by the library as either
 * @c dbc::precondition_violation, @c dbc::postcondition_violation, or
 * @c dbc::invariant_violation respectively.
 */
class condition_violation: public std::exception {
public:
    /**
     * Construct this exception with the specified description.
     * @param[in] what Exception description.
     *
     */
    explicit condition_violation(const std::string& what);
};

/** Exception thrown by default on precondition failure. */
class precondition_violation: public condition_violation {
public:
    /**
     * Construct this exception with the specified description.
     * @param[in] what Exception description.
     *
     */
    explicit precondition_violation(const std::string& what);
};

/** Exception thrown by default on postcondition failure. */
class postcondition_violation: public condition_violation {
public:
    /**
     * Construct this exception with the specified description.
     * @param[in] what Exception description.
     *
     */
    explicit postcondition_violation(const std::string& what);
};

/** Exception thrown by default on invariant failure. */
class invariat_violation: public conditions_violation {
public:
    /**
     * Construct this exception with the specified description.
     * @param[in] what Exception description.
     *
     */
    explicit invariant_violation(const std::string& what);
};

/**
 * Pointer type for the user function that can be registered to handle
 * destructor contract failures that attempt to throw an exception.
 * To comply with C++ STL requirements, exception should never be thrown from
 * destructor. If a contract violation in a destructor attempt to throw, the
 * library will call instead the user handler function registered with
 * @c set_broken_destructor_invariant(). If the user has not registered any
 * function, @c broken_destructor_invariant() will be called by default.
 */
typedef void (*broken_destructor_invariant_handler)();

/**
 * Register user defined function to handle attempt to throw exception on
 * destructor contract violation.
 * If no user define handler is registered,
 * @c dbc::broken_destructor_invariant() is called by default.
 * @param handler A function pointer to the user defined handler.
 */
inline broken_destructor_invariant_handler set_broken_destructor_invariant(
        broken_destructor_invariant_handler handler);

/**
 * The default handler called if destructor contract violation attempts to
 * throw an exception and no user handler has been registered.
 * This default handler will:
 * -#   Log a message and terminate the program (@c std::terminate())
 *      if @c DBC_CONFIG_ENABLE_TERMINATING_ASSERTIONS is defined.
 * -#   Or else, log a message and exit the program with code 1 (@c ::exit(1))
 *      if @c DBC_CONFIG_ENABLE_EXITING_ASSERTIONS is defined.
 * -#   Or else, just log a message and continue the execution.
 *
 * But it never throws an exception.
 * Use @c dbc::set_broken_destructor_invariant() to register a user defined
 * handler.
 */
inline void broken_destructor_invariant();

} // namespace dbc

