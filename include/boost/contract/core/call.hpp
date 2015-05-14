
#ifndef BOOST_CONTRACT_CALL_HPP_
#define BOOST_CONTRACT_CALL_HPP_

/** @file */

#include <boost/contract/aux_/call.hpp>
/** @cond */
#include <boost/shared_ptr.hpp>
/** @endcond */

namespace boost {
    namespace contract {
        class set_precondition_postcondition;
        class set_postcondition;

        namespace aux {
            template<typename, typename, typename>
            class bind;

            template<class, class, typename>
            class check_subcontracted_pre_post_inv;
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

    template<class C>
    friend boost::contract::set_postcondition constructor(
            call const&, C const*);
    
    template<class C>
    friend boost::contract::set_postcondition destructor(
            call const&, C const*);
    
    template<class C>
    friend boost::contract::set_precondition_postcondition public_member(
            call const&, C const*);
    
    friend boost::contract::set_precondition_postcondition protected_member(
            call const&);
    
    friend boost::contract::set_precondition_postcondition private_member(
            call const&);
    
    friend boost::contract::set_precondition_postcondition free_function(
            call const&);

    template<typename, typename, typename>
    friend class boost::contract::aux::bind;
            
    template<class, class, typename>
    friend class boost::contract::aux::check_subcontracted_pre_post_inv;

    explicit call(boost::shared_ptr<boost::contract::aux::call> _call) :
            call_(_call) {}
    
    call(call const& other) : call_(other.call_) {} // Shallow ptr copy.
    call& operator=(call const&); // No copy operator.

    boost::shared_ptr<boost::contract::aux::call> call_;
};

} } // namespace

#endif // #include guard

