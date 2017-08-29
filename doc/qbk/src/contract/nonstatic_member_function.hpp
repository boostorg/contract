// Copyright (C) 2009-2010 Lorenzo Caminiti.
// Use, modification, and distribution is subject to the
// Contract++ Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt.)

/**
@file
Class template used to write contracts for non-static member functions.
*/

namespace contract {

/**
Class template used to write contracts for non-static member functions.

@Note This class is used to write contracts for non-static member functions but it cannot be used for static-member functions (see @c contract::static_member), constructors (see @c contract::constructor), destructors (see @c contract::destructor), and non-m
ember functions (see @c contract::nonmember_function) because they have different contract checking semantics.

The @c CONTRACT_FUNCTION() macro expands to code that uses this class template (see the Without the Macros section) -- whenever possible, use the macro instead of using this class template directly.
Rarely, it might be needed to use this class template directly to implement workarounds for compilers that do not fully comply with the ISO C++ standard.

@Params
@Param{F, The function type of the function being contracted.}
@Param{BaseContractClass1\, ...\, BaseContractClassM,
    These are the contracts from which the member function is subcontracting.
    These are all optional\, they are only specified when the member function is subcontracting: no base contract is specified if no subcontracting\, only @c BaseContractClass1 is specified to subcontract from 1 base class only\, and more base contract classes are specified to support subcontracting with multiple inheritance.
    @li Each of these types must inherit from @c contract::nonstatic_member_function (so to be a contract class) and its class type must be a base class of the contracted class (otherwise the library will generate a compile-time error).
    @li When multiple base contract classes are specified\, the overridden contracts are checked following the order of the specified template parameters.
    The derived class contract is checked last.
    @li The maximum number of supported base class contracts @e M is specified by the @c CONTRACT_CONFIG_MAX_MULTIPLE_INHERITANCE configuration macro.
}
@EndParams

The following metaprogramming constructs (e.g., @c __AMetaprogrammingConstruct__) are used in this documentation to define the different types:
- If @c S is @c contract::copyable<T> then <c>__RemoveCopyable__< S ></c> is @c T, otherwise it is @c S (i.e., this removes the eventual @c contract::copyable tag from the specified type).
- If @c F is a member function pointer then @c __UncopyableClassType__ is <c>__RemoveCopyable__< ClassType >::</c> (`::` included), otherwise it is nothing.
- If @c F is a constant member then @c __ConstIfConstantMember__ is @c const, otherwise it is nothing.
- If @c S is tagged @c contract::copyable then <c> __IfCopyable__< S, T ></c> is the @c T, otherwise it is the @c contract::noold.
- If @c F has a non-void @c ResultType then <c>__IfNonVoid__< C ></c> is <c>C</c>, otherwise it is nothing.
- If @c F is a non-constant member functions then @c __MaybeConstClassPointer__ is <c>boost::add_pointer< __UncopyableClassType__ >::type</c>, otherwise is is <c>boost::add_pointer<boost::add_const< __UnopyableClassType__ >::type>:: type</c>.

These metaporgramming constructs are @b not templates.
They are internally implemented by the library using both preprocessor and template metaprogramming (in a way that is intentionally @e not documented here because it is library implementation specific).

The function type template parameter @c F must be specified as follows:
@code
    // For member functions.
    ResultType (ClassType __ConstIfConstantMember__*, ArgumentType1, ..., ArgumentTypeN) 
@endcode
Where:
@li The @c ResultType is the function result type (use @c void for functions that have no return value).
@li The @c ClassType is the type of the class the function is member of.
@li For constant member functions @c const qualifies the class type.
@li The class type @c ClassType (together with its eventual @c const qualifier) can be tagged @c contract::copyable as in <c>contract::copyable<ClassType __ConstIfContractMemeber__>*</c> if the object old value <c>CONTRACT_OLDOF(this)</c> is needed in the postconditions (in this case the class must have an accessible constant-correct copy constructor, see @c contract::copy).
Note that @c contract::copyable does @b not wrap the pointer operator (i.e., <c>contract::copyable<ClassType __ConstIfContractMemeber__*></c> is invalid).
@li The class type must declare a (private) mutable member variable of a friend type @c contract::state with the predefined name @c contract_state_ otherwise the library will generate a compile-time error.
This member variable is mainly used by the library to keep track of when contracts are being checked so to disable assertion checking in nested member function calls that could otherwise result in infinite recursion (see the Without the Macros section).
@code
    class ClassType {
    
    // Optional contract compilation.
    #if defined BOOST_CONTRACT_CHECK_CLASS_INVARIANT || \
            defined BOOST_CONTRACT_CHECK_PRECONDITION || \
            defined BOOST_CONTRACT_CHECK_POSTCONDITION
        // Augmented state.
        friend contract::state;
        mutable contract::state contract_state_;
    #endif
        
        ... // Rest of the class.
    };
@endcode
Whenever possible, use the @c CONTRACT_INVARIANT() macro instead of declaring @c contract_state_ directly.
@li The function argument types @c ArgumentType1, ..., @c ArgumentTypeN are all optional (specify none for a function with no argument, only @c ArgumentType1 is specified for a function with one argument, etc).
@li Any of the argument type can be tagged @c contract::copyable if the old value <c>CONTRACT_OLDOF(argument-name)</c> (before body execution) of the related argument is needed in postconditions.
Types tagged @c contract::copyable must have an accessible constant-correct copy constructor (otherwise the library will generate a compile-time error, see @c contract::copy).
The eventual @c contract::copyable tag must wrap the @b entire argument type (including the pointer operator if present, this is different from the class type).
@li The maximum number of supported function arguments @e N is specified by the @c CONTRACT_CONFIG_MAX_FUNCTION_ARITY configuration macro.

@See Without the Macros section
*/
template<typename F,
        class BaseContractClass1 = void, ..., class BaseContractClassM = void>
class nonstatic_member_function {
public:

    /**
    Construct this contract object using the specified body, preconditions, and postconditions functions.
    
    @Params
    @Param{body_function, A pointer to the function executing the body.}
    @Param{precondition_function, A pointer to the function asserting the preconditions.}
    @Param{postcondition_function, A pointer to the function asserting the postconditions.}
    @EndParams

    The body function pointer type is defined as follows:
    @code
        typedef ResultType (__UncopyableClassType__* __BodyFunctionPointer__)
                (   __RemoveCopyable__< ArgumentType1 >,
                    ..., 
                    __RemoveCopyable__< ArgumentTypeN >
                ) __ConstIfConstantMember__;
    @endcode
    @li The body function pointer type matches the signature of the contracted function.
    @li The @c contract::copyable tag is removed from the class and argument types.
    @li The function type is the @c const only if the contracted function is a constant member.
    
    The precondition function pointer type is defined as follows:
    @code     
        typedef void (__UncopyableClassType__* __PreconditionFunctionPointer__)
                (   boost::add_reference<boost::add_const<
                            __RemoveCopyable__< ArgumentType1 > >::type>::type,
                    ..., 
                    boost::add_reference<boost::add_const<
                            __RemoveCopyable__< ArgumentTypeN > >::type>::type
                ) const;
    @endcode
    @li The precondition function pointer type always has a @c void return type.
    @li The @c contract::copyable tag is removed from the class and argument types.
    @li Each function argument is passed as a contract reference.
    @li The function type is always @c const if the contracted function is a member.

    The postcondition function pointer type is defined as follows:    
    @code                        
        typedef void (__UncopyableClassType__* __PreconditionFunctionPointer__)
                (   __IfCopyable__< ClassType,
                            boost::add_pointer<boost::add_const<
                            ClassType>::type>::type >,
                    boost::add_reference<boost::add_const<
                            __RemoveCopyable__< ArgumentType1 > >::type>::type,
                    __IfCopyable__< ArgumentType1,
                            boost::add_reference<boost::add_const<
                            __RemoveCopyable__< ArgumentType1 > >::type>::type >,
                    ..., 
                    boost::add_reference<boost::add_const<
                            __RemoveCopyable__< ArgumentTypeN > >::type>::type,
                    __I fCopyable__< ArgumentTypeN,
                            boost::add_reference<boost::add_const<
                            __RemoveCopyable__< ArgumentTypeN > >::type>::type >,
                    __IfNonVoid__< boost::add_reference<boost::add_const<
                            ResultType>::type>::type >
                ) const;
    @endcode
    @li The postcondition function pointer type always has a @c void return type.
    @li The @c contract::copyable tag is removed from the class and argument types.
    @li The first argument is a constant pointer to the object old value if the class type was tagged @c contract::copyable, otherwise it is of type @c contract::noold (indicating that no object old value is available because the class type was not tagged @c contract::copyable).
    @li Each function argument is passed as contract reference and it is followed by its old value. Each old value is a constant reference to the argument old value if the argument type was tagged @c contract::copayble, otherwise it is of type @c contract::noold  (indicating that no object old value is available because the argument type was not tagged @c contract::copyable).
    @li The function type is always @c const if the contracted function is a member.
    */
    nonstatic_member_function(__BodyFunctionPointer__ body_function,
            __PreconditionFunctionPointer__ precondition_function,
            __PostconditionFunctionPointer__ postcondition_function);
    
    
    /** Destroy this contract object. */
    virtual ~nonstatic_member_function();
    
    /**
    Check the contract and execute the member function body.
    
    This function implements the correct contract checking semantics for the function call (see the Tutorial section).
    In summary:
    @li It checks class invariants and preconditions (also of overridden contracts when subcontracting), it executes the member function body, then it checks class invariants and postconditions (also of overridden contracts when subcontracting).
    @li If the body throws an exception, only class invariants (and not postconditions) are checked on function exit.
    @li Non-member functions do not check class invariants and they do not subcontract.
    
    
    @Params
    @Param{object, A pointer to the object (present only if @c F is a member function pointer type).
        The object pointer is @c const only if @c F is a constant member function pointer type (to handle constant member functions).}
    @Param{argument1\, ...\, argumentN, The function arguments.}
    @EndParams
    
    @Returns The function return value but only when @c F is a non-void function pointer type.
    
    @Note When @c F is a member function pointer type, the @c call() function checks class invariants by calling a constant member function with the @c contract_invariant_ predefined name and it also checks static class invariants by calling a static member function with the @c contract_static_invariant_ predefined name (see the Without the Macros section for more information):
    @code
        class ClassType {

        #if defined BOOST_CONTRACT_CHECK_INVARIANT
            void contract_static_invariant_(void) {
                ... // Assert static class invariants.
            }
            void contract_invariant_ (void) const {
                ... // Assert class invariants.
            }
        #endif
                    
            ... // Rest of the class.
        };
    @endcode
    Note the \#if guard to declare the function only when invariant compilation and checking is turned on.
    Such function must be defined and accessible otherwise the library will generate a compile-time error.
    Whenever possible, use the @c CONTRACT_INVARIANT() macro instead of programming the @c contract_invariant_ and @c contract_static_invariant_ functions directly.
    */
    virtual ResultType call(__MaybeConstClassPointer__ object,
            ArgumentType1 argument1, ..., ArgumetnTypeN argumentN);

};

} // namespace

