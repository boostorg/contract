// Copyright (C) 2009-2010 Lorenzo Caminiti.
// Use, modification, and distribution is subject to the
// Contract++ Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt.)

/**
@file
Class template used to write contracts for destructors.
*/

namespace contract {

/**
Class template used to write contracts for destructors.

@Note Only the differences between this class and the @c contract::nonstatic_member_function class are documented here.
Read the @c contract::nonstatic_member_function documentation first.

The @c CONTRACT_DESTRUCTOR() macro expands to code that uses this class template (see the Without the Macros section) -- whenever possible, use the macro instead of using this class template directly.
Rarely, it might be needed to use this class template directly to implement workarounds for compilers that do not fully comply with the ISO C++ standard.

@Params
@Param{F, The function type for the destructor being contracted.}
@EndParams

Base contract classes cannot be specified because destructors do not directly subcontract (C++ object destruction mechanism will automatically invoke base class contracts when they are present).

The function type @c F must be specified as follows:
@code
    void (ClassType::*)()
@endcode
Note:
@li The result type is always @c void because destructors return no value.
@li @c ClassType is never @c const because destructors can never be constant members (as they modify the object by destructing it).
@li @c ClassType cannot be tagged @c contract::copyable because there is no object before destructor body execution (it has not been destructed yet) -- the library will generate a compile-time error otherwise.
@li There is no function argument type because destructors take no argument.

@See Without the Macros section, @c contract::nonstatic_member_function
*/
template<typename F>
class destructor: public nonstatic_member_function<F> {
public:

    /**
    Construct this contract object using the specified body.

    No precondition and no postcondition function is specified (destructors only check class invariants).
    This is because destructors have no arguments so there are no preconditions, in addition there is no object after destructor body execution so there are no postconditions (see Tutorial section for more information).
    
    @Params
    @Param{body_function, A pointer to the function executing the body.}
    @EndParams
    
    The body function pointer type is defined as follows:
    @code
        typedef void (ClassType::* __BodyFunctionPointer__)();
    @endcode
    @li Destructor body takes no argument.
    
    */
    destructor(__BodyFunctionPointer__ body_function);
    
    
    /** Destroy this contract object. */
    virtual ~destructor();
    
    /**
    Check the contract and executes the member function body.
    
    Refer to the @c contract::nonstatic_member_function documentation.
    
    Accordingly with @c F, the @c call() function always returns void and it takes no argument.
    */
    virtual void call(__MaybeConstClassPointer__ object);
};

} // namespace

