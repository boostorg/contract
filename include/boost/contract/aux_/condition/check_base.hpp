
#ifndef BOOST_CONTRACT_AUX_CHECK_NOTHING_HPP_
#define BOOST_CONTRACT_AUX_CHECK_NOTHING_HPP_

namespace boost { namespace contract { namespace aux {

// Base class for all contracts (used to hold RAII contract object, etc.).
class check_base {
public:
    virtual ~check_base() {}
};

} } } // namespace

#endif // #include guard

