// Copyright (C) 2009-2010 Lorenzo Caminiti.
// Use, modification, and distribution is subject to the
// Contract++ Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt.)

#ifndef CONTRACT_FOM_HPP_
#define CONTRACT_FOM_HPP_

namespace contract {

// This type has to be defined in a separate header in order to avoid
// duplicate definition errors because it is used by both contract
// and contract::aux and C++ does not support forward declarations
// for enumerative types.
typedef enum {
    FROM_CONSTRUCTOR,
    FROM_DESTRUCTOR,
    FROM_NONSTATIC_MEMBER_FUNCTION,
    FROM_STATIC_MEMBER_FUNCTION,
    FROM_NONMEMBER_FUNCTION,
    FROM_BLOCK,
} from;

} // namespace

#endif // #include guard

