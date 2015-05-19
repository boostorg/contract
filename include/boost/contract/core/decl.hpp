
#ifndef BOOST_CONTRACT_DECL_HPP_
#define BOOST_CONTRACT_DECL_HPP_

/** @file */

#include <boost/contract/aux_/call.hpp>
/** @cond */
#include <boost/shared_ptr.hpp>
/** @endcond */

namespace boost {
    namespace contract {
        class set_precondition_postcondition;
        class set_postcondition_only;

        namespace aux {
            template<class, class, typename>
            class check_subcontracted_pre_post_inv;

            template<typename, typename, typename>
            class decl_free_function;
            
            template<typename, class, typename, typename>
            class decl_member_function;
        }
    }
}

namespace boost { namespace contract {

class decl {
public:
    // Nothing here (opaque object that users cannot directly use or create).

private:
    explicit decl(boost::shared_ptr<boost::contract::aux::call> call) :
            call_(call) {}
    
    // TODO: DO I need the copy ctor?
    decl(decl const& other) : call_(other.call_) {} // Shallow ptr copy.
    decl& operator=(decl const&); // No copy operator.

    boost::shared_ptr<aux::call> call_;
    
    // Friendship used to limit lib's public API.

    friend bool copy_old(decl const&);
    friend class old;

    template<class C>
    friend set_postcondition_only constructor(decl const&, C const*);
    
    template<class C>
    friend set_postcondition_only destructor(decl const&, C const*);
    
    template<class C>
    friend set_precondition_postcondition public_member(decl const&, C const*);
    
    template<class, class C, typename A0>
    friend set_precondition_postcondition public_member(decl const&, C const*,
            A0 const&);
    
    friend set_precondition_postcondition protected_member(decl const&);
    
    friend set_precondition_postcondition private_member(decl const&);
    
    friend set_precondition_postcondition free_function(decl const&);

    template<class, class, typename>
    friend class boost::contract::aux::check_subcontracted_pre_post_inv;
    
    template<typename, typename, typename>
    friend class boost::contract::aux::decl_free_function;

    template<typename, class, typename, typename>
    friend class boost::contract::aux::decl_member_function;
};

} } // namespace

#endif // #include guard

