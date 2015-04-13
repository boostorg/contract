
#ifndef BOOST_CONTRACT_EXT_SFINAE_HPP_
#define BOOST_CONTRACT_EXT_SFINAE_HPP_

#include <boost/mpl/bool.hpp>

// NOTE: Unfortunately, it is not possible to use Boost.TTI because it not
// always works on MSVC (e.g., when the introspecting meta-function is invoked
// multiple times, MSVC 2010 gives an internal compiler error). This is a
// simpler implementation of SFINAE that can be used to program introspecing
// meta-functions that seem to work better with MSVC.

namespace boost { namespace contract { namespace ext { namespace sfinae {

typedef struct {} yes;
typedef yes no[2];

template<typename T, class Check>
class check : private Check {
    using Check::apply;
    template<typename> static no& apply(...);

public:
    static bool const value = sizeof(apply<T>(0)) == sizeof(yes);
    typedef boost::mpl::bool_<value> type;
};

template< typename F, F >
struct function_exists;

} } } } // namespace

#endif // #include guard

