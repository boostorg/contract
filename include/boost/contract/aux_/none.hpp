
#ifndef BOOST_CONTRACT_AUX_NONE_HPP_
#define BOOST_CONTRACT_AUX_NONE_HPP_

namespace boost { namespace contract { namespace aux {

class none { // Tag for "no type".
public:
    static none value; // Tag for "no value" (can take ref, ptr, etc.).

    // Allow default constructor and copy operations.
    
    // Must contain no other member (so it cannot be used by mistake).
};

none none::value;

// Transform `void` to `none` type.
template<typename T> struct none_if_void { typedef T type; };
template<> struct none_if_void<void> { typedef none type; };

} } } // namespace

#endif // #include guard

