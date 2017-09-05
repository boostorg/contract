// Copyright (C) 2009-2010 Lorenzo Caminiti.
// Use, modification, and distribution is subject to the
// Contract++ Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt.)

/** @file
Context from which the contract failure was generated.
*/

namespace contract {

/**
Source that found the contract condition failure.

For example, this is used in the Throw on Failure annex to ensure that destructors never throw to comply with C++ STL exception safety requirements.

These failure sources are identified separately because they all have different contract checking semantics with respect to each other (see the Tutorial section).

@Warning You must not assume any specific integer value for these enumerated values.
Only use the enumerated values because the integer values they map to are library implementation specific and they could change in future revisions of the library.

@See @c contract::contract_failed_handler
*/
typedef enum {
    /** Contract condition failed from a constructor. */
    FROM_CONSTRUCTOR,
    /** Contract condition failed from a destructor. */
    FROM_DESTRUCTOR,
    /** Contract condition failed from a non-static member function. */
    FROM_NON_STATIC_MEMBER_FUNCTION,
    /** Contract condition failed from a static member function. */
    FORM_STATIC_MEMBER_FUNCTION,
    /** Contract condition failed from a non-member function. */
    FROM_NON_MEMBER_FUNCTION,
    /** Contract condition failed from a code block. */
    FROM_BLOCK,
} from;

} // namespace

