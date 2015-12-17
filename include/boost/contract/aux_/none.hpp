
#ifndef BOOST_CONTRACT_AUX_NONE_HPP_
#define BOOST_CONTRACT_AUX_NONE_HPP_

namespace boost { namespace contract { namespace aux {

// Tag for "no type".
class none {}; // Empty so trivial ctor, copy, etc. but cannot use by mistake.

// Transform `void` to `none` type (for convenience, instead of using MPL).
template<typename T> struct none_if_void { typedef T type; };
template<> struct none_if_void<void> { typedef none type; };

} } } // namespace

#endif // #include guard

