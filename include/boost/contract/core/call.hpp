
#ifndef BOOST_CONTRACT_CALL_HPP_
#define BOOST_CONTRACT_CALL_HPP_

#include <boost/contract/aux_/call.hpp>
#include <boost/shared_ptr.hpp>

namespace boost {
    namespace contract {
        class set_precondition_postcondition;

        namespace aux {
            template<typename, typename, typename>
            class bind;
        }
    }
}

namespace boost { namespace contract {

class call {
public:
    // Nothing here (opaque object that users cannot directly use or create).

private: // Friendship to minimize lib's public API.
    friend bool copy_oldof(call const&);
    friend class oldof;
    
    template<typename, typename, typename>
    friend class boost::contract::aux::bind;

    friend boost::contract::set_precondition_postcondition free_function(
            call const&);

    template<class C>
    friend boost::contract::set_precondition_postcondition public_member(
            boost::contract::call const&, C const*);

    explicit call(boost::shared_ptr<boost::contract::aux::call> _call) :
            call_(_call) {}
    
    call(call const& other) : call_(other.call_) {} // Shallow ptr copy.
    call& operator=(call const&); // No copy operator.

    boost::shared_ptr<boost::contract::aux::call> call_;
};

} } // namespace

#endif // #include guard

