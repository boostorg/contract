
#ifndef BOOST_CONTRACT_AUX_SET_NOTHING_HPP_
#define BOOST_CONTRACT_AUX_SET_NOTHING_HPP_

#include <boost/contract/aux_/check/pre_post.hpp>
#include <boost/shared_ptr.hpp>

namespace boost {
    namespace contract {
        class type;
    }
}

namespace boost { namespace contract { namespace aux { namespace set {

class nothing {
public:
    explicit nothing(boost::shared_ptr<boost::contract::aux::check::pre_post>
            const contract) : contract_(contract) {}

    // Allow to set nothing (neither pre, nor post).

private:
    friend class boost::contract::type;
    boost::shared_ptr<boost::contract::aux::check::pre_post> contract_;
};

} } } } // namespace

#endif // #include guard

