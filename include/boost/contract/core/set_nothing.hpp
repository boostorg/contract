
#ifndef BOOST_CONTRACT_SET_NOTHING_HPP_
#define BOOST_CONTRACT_SET_NOTHING_HPP_

#include <boost/contract/aux_/condition/check_nothing.hpp>
#include <boost/shared_ptr.hpp>

namespace boost { namespace contract {

class set_nothing {
public:
    // No set function member here.

private: // Friendship to minimize lib's public API.
    friend class scoped;
    friend class set_precondition;
    friend class set_postcondition;

    template<typename F, typename A0, typename A1>
    friend set_nothing bind(F, A0 const&, A1 const&);

    explicit set_nothing(boost::shared_ptr<boost::contract::
            aux::check_nothing> check) : check_(check) {}

    boost::shared_ptr<boost::contract::aux::check_nothing> check_;
};

} } // namespace

#endif // #include guard

