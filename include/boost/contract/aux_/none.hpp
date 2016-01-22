
#ifndef BOOST_CONTRACT_AUX_NONE_HPP_
#define BOOST_CONTRACT_AUX_NONE_HPP_

namespace boost { namespace contract { namespace aux {

// Tag for "no type".
class none {
public:
    // Some lib code uses this to avoid unused local var warnings with #if, etc.
    static none& value() {
        static none none_value;
        return none_value;
    }
};

// Transform `void` to `none` type (for convenience, instead of using MPL).
template<typename T> struct none_if_void { typedef T type; };
template<> struct none_if_void<void> { typedef none type; };

} } } // namespace

#endif // #include guard

