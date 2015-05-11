
#ifndef BOOST_CONTRACT_AUX_CHECK_NOTHING_HPP_
#define BOOST_CONTRACT_AUX_CHECK_NOTHING_HPP_

namespace boost { namespace contract { namespace aux {

class check_nothing { // Used as base for all contracts (and holder for RAII).
public:
    virtual ~check_nothing() {}
};

} } } // namespace

#endif // #include guard

