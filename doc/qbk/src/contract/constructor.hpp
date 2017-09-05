// Copyright (C) 2009-2010 Lorenzo Caminiti.
// Use, modification, and distribution is subject to the
// Contract++ Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt.)

/**
@file
Class template used to write contracts for constructors.
*/

namespace contract {

/**
Class template used to write contracts for constructors.

@Note Only the differences between this class and the @c contract::nonstatic_member_function class are documented here.
Read the @c contract::nonstatic_member_function documentation first.

The @c CONTRACT_CONSTRUCTOR() macro expands to code that uses this class template (see the Without the Macros section) -- whenever possible, use the macro instead of using this class template directly.
Rarely, it might be needed to use this class template directly to implement workarounds for compilers that do not fully comply with the ISO C++ standard.

@Params
@Param{F, The function type of the constructor function being contracted.}
@EndParams

Base contract classes cannot be specified because constructors do not directly subcontract (C++ object construction mechanism will automatically invoke base class contracts when they are present).

The function type @c F must be specified as follows:
@code
    void (ClassType*, ArgumentType1, ..., ArgumentTypeN)
@endcode
Note:
@li The result type is always @c void because constructors return no value.
@li @c ClassType is never @c const because constructors can never be constant members (as they modify the object by constructing it).
@li @c ClassType cannot be tagged @c contract::copyable because there is no object before constructor body execution (it has not been constructed yet) -- the library will generate a compile-time error otherwise.

@See Without the Macros section, @c contract::nonstatic_member_function
*/
template<typename F>
class constructor: public nonstatic_member_function<F> {
public:

    /**
    Construct this contract object using the specified body, preconditions, and postconditions functions.
    
    @Params
    @Param{body_function, A pointer to the function executing the body.}
    @Param{precondition_function, A pointer to the function asserting the preconditions.}
    @Param{postcondition_function, A pointer to the function asserting the postconditions.}
    @EndParams

    Refer to the @c contract::nonstatic_member_function documentation for the definition of metaprogramming constructs used below (@c __IfCopyable__, etc).

    The body function pointer type is defined as follows:
    @code
        typedef void (ClassType::* __BodyFunctionPointer__)
                (   __RemoveCopyable__< ArgumentType1 >,
                    ..., 
                    __RemoveCopyable__< ArgumentTypeN >
                );
    @endcode
    
    The precondition function pointer type is defined as follows:
    @code     
        typedef void (* __PreconditionFunctionPointer__)
                (   boost::add_reference<boost::add_const<
                            __RemoveCopyable__< ArgumentType1 > >::type>::type,
                    ..., 
                    boost::add_reference<boost::add_const<
                            __RemoveCopyable__< ArgumentTypeN > >::type>::type
                );
    @endcode
    @li This is a @b static member function (because is does not specify the class type using <c>(*)</c> instead of <c>(ClassType::*)</c>).
    This ensures that constructor preconditions do not access the object (as before constructor body no object has been constructed yet).
    @li The precondition function is never @c const (because is must be @c static).

    The postcondition function pointer type is defined as follows:    
    @code                        
        typedef void (ClassType::* __PreconditionFunctionPointer__)
                (   contract::noold,
                    boost::add_reference<boost::add_const<
                            __RemoveCopyable__< ArgumentType1 > >::type>::type,
                    __IfCopyable__< ArgumentType1,
                            boost::add_reference<boost::add_const<
                            __RemoveCopyable__< ArgumentType1 > >::type>::type >,
                    ..., 
                    boost::add_reference<boost::add_const<
                            __RemoveCopyable__< ArgumentTypeN > >::type>::type,
                    __IfCopyable__< ArgumentTypeN,
                            boost::add_reference<boost::add_const<
                            __RemoveCopyable__< ArgumentTypeN > >::type>::type >
                ) const;
    @endcode
    @li The old object value is never available (it is always of type @c contract::noold).
    This ensure that constructor postconditions never access the object old value (as there was no object before constructor body execution).
    */
    constructor(__BodyFunctionPointer__ body_function,
            __PreconditionFunctionPointer__ precondition_function,
            __PostconditionFunctionPointer__ postcondition_function);

    /** Destroy this contract object. */
    virtual ~constructor();
    
    /**
    Check the contract and executes the member function body.

    Refer to the @c contract::nonstatic_member_function documentation.

    Accordingly with @c F, the @c call() function always returns @c void.
    */
    virtual void call(__MaybeCvClassPointer__ object,
            ArgumentType1 argument1, ..., ArgumetnTypeN argumentN);
};

} // namespace

