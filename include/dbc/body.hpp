
#ifndef DBC_BODY_HPP_
#define DBC_BODY_HPP_

#ifndef DBC

#define DBC_BODY(fun_name) fun_name
#define DBC_OPERATOR_BODY(operator_symbol, operator_name) operator_symbol
#define DBC_DESTRUCTOR_BODY(class_type) class_type :: ~class_type

#else // DBC

#include <boost/preprocessor.hpp>

#define DBC_BODY(fun_name) BOOST_PP_CAT(BOOST_PP_CAT(dbc_body_, fun_name), _)

/** Needed because operator_symbol cannot in token concatenation when creating
 * contract name. */
#define DBC_OPERATOR_BODY(operator_symbol, operator_name) \
    DBC_BODY(operator_name)

// Unfortunately, it is not possible to implement a macro 
// DBC_CONSTRUCTOR_BODY() (similar to the destructor macro below) that can deal
// with base initializers in a reasonable way. Such a constructor body macro
// would need the full function signature as specified to DBC_CONSTRUCTOR() in
// the constructor contract specification. It would be too inconvenient for the
// user to specify such complex signature twice. Furthermore, templates present
// another major issue as it seems that a constructor body macro would require
// the full template signature... If C++ suppoerted delegating constructors, 
// there could have been a way around these issues.
// To split constructor implementation from declaration, simply use init(). 

#define DBC_DESTRUCTOR_BODY(class_type) void class_type :: DBC_BODY(del)

#endif // DBC

#endif // DBC_BODY_HPP_

