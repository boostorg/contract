// Copyright (C) 2009-2010 Lorenzo Caminiti.
// Use, modification, and distribution is subject to the
// Contract++ Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt.)

/** @file
Macros used to name the body function when separating its definition from the contract declaration.

For example, these macros are used when function body definitions are implemented in a source file ".cpp" while the function and contract declarations are given in separate header file ".hpp".

@See Examples and more information in the Tutorial section.
*/

/**
Macro used to name the constructor body when separating constructor definition from its declaration.

This macro is used when the constructor is defined outside the class declaration (for example in a separate ".cpp" file) to name the constructor body function:
@code    
    BOOST_CONTRACT_CONSTRUCTOR_BODY(class_type, class_name)
            (...) { // Constructor arguments.
        ... // Constructor implementation.
    }
@endcode

@Params
@Param{class_type, The type of the class. For class templates this must also list the template parameters.}
@Param{class_name, The constructor name which is the class type name. For class templates this shall not list the template parameters.}
@EndParams

@Returns This macro expands to code equivalent to the following:
@code
    #if defined CONTRACT_CHECK_CLASS_INVARIANT || \
            defined CONTRACT_CHECK_PRECONDITION || \
            defined CONTRACT_CHECK_POSTCONDITION
        void class_type::contract_body_constructor_ // Constructor body function name.
    #else
        class_type::class_name // Constructor function (contracts off).
    #endif
            (...) { // Constructor arguments.
        ... // Constructor implementation.
    }
@endcode

<b>Member Initialization List</b>

A limitation of this mechanism is that it does not directly support constructor member initialization list.
If a member initialization list is specified then the constructor definition must be provided together with its declaration (for example in the header file).
(This library could overcome this limitation in the future if upcoming C++ standard revisions were to support delegating constructors.)

If the constructor implementation must be separated from its declaration, a possible workaround is to:
-# Delegate the construction job to a special initialization function which must be named "constructor" (and it should be private to avoid other code from messing with the object construction).
-# Program the real constructor to just invoke the initialization function.
-# Write the contract for the initialization function instead that for the real constructor (but using CONTRACT_CONSTRUCTOR() instead of CONTRACT_FUNCTION()).

If this is done then both the constructor and the initialization function body definitions can be separated from the contract declaration.
For example:
@code
    // Declaration.
    
    template<typename T>
    class myvector {
        ... // Invariants.
        
    public:
        typedef typename std::vector<T>::size_type size_type;
        typedef typename std::vector<T>::const_reference const_reference;

        explicit myvector(size_type count); // Separated definition.
        
        ... // Rest of the class.

    private:
        // The initialization function is private and must be named "constructor
".
        void constructor(size_type count)
        // Specify the contract for the initialization function instead of the real constructor.
        CONTRACT_CONSTRUCTOR( (class) (myvector)
                (private) (myvector)( (size_type)(count) ), {
            // Constructor preconditions (none in this case).
        }, {
            // Constructor postconditions.
            CONTRACT_ASSERT(self.now.size() == count.now,
                    "size set to count");
        }, ;) // Now we can separate the body definition using ";".
        
        std::vector<T> vector_;
    };
    
    // Separated definition (possibly in a different file).
    
    template<typename T>
    myvector<T>::myvector(size_type count):
            vector_(count) { // Member initialization list.
        constructor(count); // Just invoke the initialization function.
    }
        
    template<typename T>
    void myvector<T>::CONTRACT_BODY(constructor)(size_type count) {
        // Actual constructor implementation (do nothing in this case).
    }
@endcode

To allow for this workaround, the @c CONTRACT_CONSTRUCTOR() macro can follow a member function but @b only when the member function is named "constructor", it has a @c void return type, and it is not @c const (essentially, only when its signature matches the one of a constructor).
Be aware that for this special "constructor" member function, class invariants will @b not be checked before body execution (because the @c CONTRACT_CONSTRUCTOR() macro implements the Constructor Call Semantics and not the Member Function Call Semantics as explained in the Tutorial section).

@See Tutorial section, @c CONTRACT_CONSTRUCTOR()
*/
#define CONTRACT_CONSTRUCTOR_BODY(class_type, class_name)

/**
Macro used to name the destructor body when separating destructor definition from its declaration.

This macro is used when the destructor is defined outside the class declaration (for example in a separate ".cpp" file) to name the destructor body function:
@code    
    CONTRACT_DESTRUCTOR_BODY(class_type, class_name)
            (void) { // Destructors have no argument.
        ... // Destructor implementation.
    }
@endcode

@Params
@Param{class_type, The type of the class. For class templates this must also list the template parameters.}
@Param{class_name, The constructor name which is the class type name -- do @b not prefixed the class name with "~" (this is the class name and not the destructor name). For class templates this shall not list the template parameters.}
@EndParams

@Returns This macro expands to code equivalent to the following:
@code
    #if defined CONTRACT_CHECK_CLASS_INVARIANT || \
            defined CONTRACT_CHECK_PRECONDITION || \
            defined CONTRACT_CHECK_POSTCONDITION
        void class_type::contract_body_destructor_ // Destructor body function name.
    #else
        class_type::~class_name // Destructor function (contracts off).
    #endif
            (void) { // Destructor have no argument.
        ... // Destructor implementation.
    }
@endcode

@See Tutorial section, @c CONTRACT_DESTRUCTOR()
*/
#define CONTRACT_DESTRUCTOR_BODY(class_type, class_name)

/**
Macro used to name the function body when separating the function definition from its declaration.

This macro is used when the function is defined separately from its declaration (for example in a separate ".cpp" file) to name the body function:
@code    
    ... // Function return type, class-type:: prefix, etc.
    CONTRACT_BODY(function_name)
            (...) { // Function arguments.
        ... // Function implementation.
    }
@endcode

@Params
@Param{function_name, The name of the function. For operators the name must be <c>operator(</c><em>symbol\, word</em><c>)</c> where <em>word</em> must contain no special operator symbol and it must match what specified in the contract declaration (see the Tutorial section).}
@EndParams

@Returns This macro expands to code equivalent to the following:
@code
    ... // Function return type, class-type:: prefix, etc.
    #if defined CONTRACT_CHECK_CLASS_INVARIANT || \
            defined CONTRACT_CHECK_PRECONDITION || \
            defined CONTRACT_CHECK_POSTCONDITION
        contract_body_ ## function_name ## _ // Body function name.
    #else
        function_name // Function name (contracts off).
    #endif
            (...) { // Function arguments.
        ... // Function implementation.
    }
@endcode
(The preprocessor operator @c ## concatenates the specified tokens.)

@See Tutorial section, @c CONTRACT_FUNCTION()
*/
#define CONTRACT_BODY(function_name)

