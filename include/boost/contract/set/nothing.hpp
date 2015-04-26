
#ifndef BOOST_CONTRACT_SET_NOTHING_HPP_
#define BOOST_CONTRACT_SET_NOTHING_HPP_

#include <boost/contract/aux_/check/pre_post.hpp>
#include <boost/shared_ptr.hpp>

namespace boost {
    namespace contract {
        class type;

        namespace set {
            class precondition_only;
            class postcondition_only;
        }
    }
}

namespace boost { namespace contract { namespace set {

class nothing { // Allow (shallow ptr) copy for `auto c = ...`.
public:
    // Allow to set nothing (neither precondition, nor postcondition).

private:
    // Use friendship and deleted constructors to limit public API.
    friend class boost::contract::type;
    friend class boost::contract::set::precondition_only;
    friend class boost::contract::set::postcondition_only;
    
    explicit nothing(boost::shared_ptr<boost::contract::aux::check::pre_post>
            const contract) : contract_(contract) {}

    boost::shared_ptr<boost::contract::aux::check::pre_post> contract_;
};

} } } // namespace

#endif // #include guard

