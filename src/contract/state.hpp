// Copyright (C) 2009-2010 Lorenzo Caminiti.
// Use, modification, and distribution is subject to the
// Contract++ Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt.)

#ifndef CONTRACT_STATE_HPP_
#define CONTRACT_STATE_HPP_

#include "aux_/sync.hpp"

namespace contract {

// Contracted class (ClassType) must declare this class a friend and 
// it must declare a mutable (private) member variable of type
// `state` with name `contract_state_`.
class state {
public:
    state(): object_checking_contract_(false) {}
    
    // WARNING: All contents of this class are library implementation
    // specific -- that is why they are all postfixed with "_".
    // !!!THEY MUST NOT BE USED DIRECTLY IN USER CODE!!!
    
    // If threading, this should be sync'd (use sync<>).
    aux::sync<bool, false> object_checking_contract_;

    // WORKAROUND: Duplicate Friend Warning
    // The following functions are used to access object private or
    // protected components because this state class is made friend
    // of the class type. This way, only one friendship is required.
    // (The alternative would have been to declare function::member 
    // class friend but that would have required to repeat the 
    // friendship multiple times because for all the different used 
    // template instantiations of function::member causing warnings 
    // on some compilers.)

    template<class ClassType>
    static state& get_state_(ClassType const* const object) {
        // contract_state_ mutable so non-const state& can be
        // returned here from const object.
        return object->CONTRACT_CONFIG_STATE_VARIABLE_;
    }
    
    template<class ClassType>
    static void call_static_invariant_() {
        // Static invariant function is static so no object.
        ClassType::CONTRACT_CONFIG_STATIC_INVARIANT_FUNCTION_();
    }
    
    template<class ClassType>
    static void call_invariant_(ClassType const* const object) {
        // Invariant function must be const-member (object is const).
        object->CONTRACT_CONFIG_INVARIANT_FUNCTION_();
    }

    template<class ClassType, class BaseClassType>
    static void to_base_(ClassType const* const object,
            BaseClassType const*& base_object) {
        // This is not a cast! It will correctly generate a
        // compile-time error if the library miss uses it when
        // BaseClassType is not a base type of ClassType.
        base_object = object;
    }
};

} // namespace

#endif // #include guard

