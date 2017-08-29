// Copyright (C) 2009-2010 Lorenzo Caminiti.
// Use, modification, and distribution is subject to the
// Contract++ Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt.)

#ifndef CONTRACT_CONFIG_HPP_
#define CONTRACT_CONFIG_HPP_

// User configs: change them rarely, only if *really* needed.

#ifndef CONTRACT_CONFIG_MAX_FUNCTION_ARITY
#define CONTRACT_CONFIG_MAX_FUNCTION_ARITY 5
#endif // config

#ifndef CONTRACT_CONFIG_MAX_MULTIPLE_INHERITANCE
#define CONTRACT_CONFIG_MAX_MULTIPLE_INHERITANCE 5
#endif // config

// Internal configs: *never* change them (postfixed with `_`).

#ifndef CONTRACT_CONFIG_DEBUG_
#define CONTRACT_CONFIG_DEBUG_ 0
#endif // config

#ifndef CONTRACT_CONFIG_INVARIANT_FUNCTION_
#define CONTRACT_CONFIG_INVARIANT_FUNCTION_ contract_invariant_
#endif // config

#ifndef CONTRACT_CONFIG_STATIC_INVARIANT_FUNCTION_
#define CONTRACT_CONFIG_STATIC_INVARIANT_FUNCTION_ \
        contract_static_invariant_
#endif // config

#ifndef CONTRACT_CONFIG_STATE_VARIABLE_
#define CONTRACT_CONFIG_STATE_VARIABLE_ contract_state_
#endif // config

// This must be `constructor` to allow for member initialization list
// workaround by using a special init function named `constructor`.
#ifndef CONTRACT_CONFIG_CONSTRUCTOR_FUNCTION_NAME_
#define CONTRACT_CONFIG_CONSTRUCTOR_FUNCTION_NAME_ \
        constructor /* trailing _ automatically added */
#endif // config

#ifndef CONTRACT_CONFIG_DESTRUCTOR_FUNCTION_NAME_
#define CONTRACT_CONFIG_DESTRUCTOR_FUNCTION_NAME_ \
        destructor /* trailing _ automatically added */
#endif // config

#ifndef CONTRACT_CONFIG_VARIANT_VARIABLE_
#define CONTRACT_CONFIG_VARIANT_VARIABLE_ contract_variant_
#endif // config

#ifndef CONTRACT_CONFIG_NONMEMBER_FUNCTION_HPP_FILE_PATH_ 
#define CONTRACT_CONFIG_NONMEMBER_FUNCTION_HPP_FILE_PATH_ \
    "contract/nonmember_function.hpp"
#endif // config

#ifndef CONTRACT_CONFIG_NONSTATIC_MEMBER_FUNCTION_HPP_FILE_PATH_ 
#define CONTRACT_CONFIG_NONSTATIC_MEMBER_FUNCTION_HPP_FILE_PATH_ \
    "contract/nonstatic_member_function.hpp"
#endif // config

#ifndef CONTRACT_CONFIG_STATIC_MEMBER_FUNCTION_HPP_FILE_PATH_ 
#define CONTRACT_CONFIG_STATIC_MEMBER_FUNCTION_HPP_FILE_PATH_ \
    "contract/static_member_function.hpp"
#endif // config

#ifndef CONTRACT_CONFIG_CONSTRUCTOR_HPP_FILE_PATH_ 
#define CONTRACT_CONFIG_CONSTRUCTOR_HPP_FILE_PATH_ \
    "contract/constructor.hpp"
#endif // config

#ifndef CONTRACT_CONFIG_AUX_VOID_BASE_CONTRACT_HPP_FILE_PATH_ 
#define CONTRACT_CONFIG_AUX_VOID_BASE_CONTRACT_HPP_FILE_PATH_ \
    "contract/aux_/function/void_base_contract.hpp"
#endif // config

#endif // #include guard

