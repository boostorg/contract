
#ifndef BOOST_CONTRACT_AUX_NONE_HPP_
#define BOOST_CONTRACT_AUX_NONE_HPP_

namespace boost { namespace contract { namespace aux {

struct none { // Tag for "no type".
    // Empty so trivially constructible, copyable, cannot used by mistake, etc.
};

// Transform `void` to `none` type.
template<typename T> struct none_if_void { typedef T type; };
template<> struct none_if_void<void> { typedef none type; };

} } } // namespace

#endif // #include guard

