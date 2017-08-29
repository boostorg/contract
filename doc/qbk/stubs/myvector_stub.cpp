
//[ myvector_stub_cpp

#include "pushable.hpp" // Some base class (for subcontracting).
#include <contract.hpp> // This library.
#include <vector>       // C++ STL vector.

// Wrapper class that adds contracts to std::vector.
template<typename T>
class myvector: public pushable<T> {

    ``*CONTRACT_INVARIANT*``( ({
        CONTRACT_ASSERT( ((size() == 0) == empty() );
        ... // More invariants.
    }) ) /*< No need for "`;`" after the macro closing parenthesis "`)`". >*/
    
public:
    void push_back(const T& element)
    ``*CONTRACT_FUNCTION*``( (class) (copyable)(myvector) /*< The function signature tokens are passed to the __CONTRACT_FUNCTION__() macro in the exact same order as they appear in the function declaration. 
            The parenthesis `()` around the tokens are mandatory (they create a __Boost_Preprocessor__ sequence). >*/ // Function signature.
            (inherit)(pushable<T>) /*< `(inherit)(pushable<T>)` subcontracts from the base contract of `pushable<T>::push_back()`. >*/
            (public) (void) (push_back)( (const T&)(element) )
    (``*precondition*``)({ /*< The precondition section `(precondition) ({...})` and the postcondition section `(postcondition) ({...})` can both be omitted, the body section `(body) ({...})` is mandatory instead. >*/
        CONTRACT_ASSERT( size() < max_size() );
        ... // More preconditions.
    })
    (``*postcondition*``)({
        CONTRACT_ASSERT( size() == (CONTRACT_OLDOF(this)->size() + 1) ); /*< `CONTRACT_OLDOF(this)` is a copy to the object before the body is executed. For it to be available in postconditions, the class type had to be tagged copyable using `(copyable)(myvector)` in the function signature sequence. >*/
        ... // More postconditions.
    })
    (``*body*``)({ /*< The body specifies the original function definition. Instead of `{ vector_.push_back(element); }`, `";"` can be used to separate the function definition from its declaration, or `" = 0;"` can be used to write contracts for pure virtual functions. >*/
        vector_.push_back(element); // Original implementation.
    }) ) /*< Again, no need for "`;`" after macro closing parenthesis "`)`". >*/
    
    ... // Rest of the class.
private:
    std::vector<T> vector_;
};

//]

