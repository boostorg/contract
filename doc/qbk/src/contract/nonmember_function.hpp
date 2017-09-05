// Copyright (C) 2009-2010 Lorenzo Caminiti.
// Use, modification, and distribution is subject to the
// Contract++ Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt.)

/**
@file
Class template used to write contracts non-member functions.
*/

namespace contract {

/**
Class template used to write contracts for non-member functions.

@Note Only the differences between this class and the @c contract::nonstatic_member_function class are documented here.
Read the @c contract::nonstatic_member_function documentation first.

The @c CONTRACT_FUNCTION() macro expands to code that uses this class template (when no <c>(class)</c> is specified in the function signature sequence, see the Without the Macros section) -- whenever possible, use the macro instead of using this class template directly.
Rarely, it might be needed to use this template class directly to implement workarounds for compilers that do not fully comply with the ISO C++ standard.

@Params
@Param{F, The function type of the non-member function being contracted.}
@EndParams

The function type @c F must be specified as follows:
@code
    ResultType (ArgumentType1, ..., ArgumentTypeN)
@endcode



@See Without the Macros section, @c contract::nonstatic_member_function
*/
template<typename F>
class nonmember_function {
public:

    /**
    Construct this contract object using the specified body, preconditions, and postconditions functions.
    
    @Params
    @Param{body_function, A pointer to the function executing the body.}
    @Param{precondition_function, A pointer to the function asserting the preconditions.}
    @Param{postcondition_function, A pointer to the function asserting the postconditions.}
    @EndParams

    Refer to the @c contract::nonstatic_member_function documentation for the definition of metaprogramming constructs used below (@c __IfCopyable__, etc).

    Note the followings for the function pointer types defined below:
    @li They are non-member functions.
    @li There is no old object value in postconditions, not even @c contract::noold (because non-member functions have no object).
    
    The body function pointer type is defined as follows:
    @code
        typedef ResultType (* __BodyFunctionPointer__)
                (   __RemoveCopyable__< ArgumentType1 >,
                    ..., 
                    __RemoveCopyable__< ArgumentTypeN >
                );
    @endcode
    
    The precondition function pointer type is defined as follows:
    @code     
        typedef ResultType (* __PreconditionFunctionPointer__)
                (   boost::add_reference<boost::add_const<
                            __RemoveCopyable__< ArgumentType1 > >::type>::type,
                    ..., 
                    boost::add_reference<boost::add_const<
                            __RemoveCopyable__< ArgumentTypeN > >::type>::type
                );
    @endcode

    The postcondition function pointer type is defined as follows:    
    @code                        
        typedef ResultType (* __PreconditionFunctionPointer__)
                (   boost::add_reference<boost::add_const<
                            __RemoveCopyable< ArgumentType1 > >::type>::type,
                    __IfCopyable__< ArgumentType1,
                            boost::add_reference<boost::add_const<
                            __RemoveCopyable__< ArgumentType1 > >::type>::type >,
                    ..., 
                    boost::add_reference<boost::add_const<
                            __RemoveCopyable__< ArgumentTypeN > >::type>::type,
                    __IfCopyable__< ArgumentTypeN,
                            boost::add_reference<boost::add_const<
                            __RemoveCopyable< ArgumentTypeN > >::type>::type >,
                    __IfNonVoid__< boost::add_reference<boost::add_const<
                            ResultType>::type>::type >
                ) const;
    @endcode
    */
    nonmember_function(__BodyFunctionPointer__ body_function,
            __PreconditionFunctionPointer__ precondition_function,
            __PostconditionFunctionPointer__ postcondition_function);
    
    
    /** Destroy this contract object. */
    virtual ~nonmember_function();
    
    /**
    Check the contract and executes the member function body.

    Refer to the @c contract::nonstatic_member_function documentation.
    
    The @c call() function takes no object (because the contracted function is not a member).
    */
    virtual ResultType call(
            ArgumentType1 argument1, ..., ArgumetnTypeN argumentN);

};

} // namespace

