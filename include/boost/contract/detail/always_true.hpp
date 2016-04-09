
#ifndef BOOST_CONTRACT_DETAIL_ALWAYS_TRUE_HPP_
#define BOOST_CONTRACT_DETAIL_ALWAYS_TRUE_HPP_

namespace boost { namespace contract { namespace detail {

struct always_true {
    template<class> struct result; // To support boost::result_of.
    template<class F> struct result<F()> { typedef bool type; };

    bool operator()() { return true; }
};

} } } // namespace

#endif // #include guard

