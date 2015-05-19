
#ifndef BOOST_CONTRACT_SET_NOTHING_HPP_
#define BOOST_CONTRACT_SET_NOTHING_HPP_

/** @file */

#include <boost/contract/aux_/condition/check_base.hpp>
/** @cond */
#include <boost/shared_ptr.hpp>
/** @endcond */

namespace boost {
    namespace contract {
        class decl;
    }
}

namespace boost { namespace contract {

// TODO: Make sure all friend declarations are at bottom of public if part of
// public API, or at bottom of private if part of private API.

class set_nothing {
    // Friendship used to limit lib's public API.
    friend class var;
    friend class set_precondition_only;
    friend class set_postcondition_only;

    friend set_nothing decl_function(void (* f)(decl));
    
    template<typename A0>
    friend set_nothing decl_function(A0 const&, void (* f)(A0 const&, decl));

    template<typename A0, typename A1>
    friend set_nothing decl_function(A0 const&, A1 const&,
            void (* f)(A0 const&, A1 const&, decl));

    template<class C>
    friend set_nothing decl_function(C const*, void (C::* f)(decl) const);

    template<class C, typename A0>
    friend set_nothing decl_function(C const*, A0 const&,
            void (C::* f)(A0 const&, decl) const);
    
    template<class C, typename A0, typename A1>
    friend set_nothing bind(C const*, A0 const&, A1 const&,
            void (C::* f)(A0 const&, A1 const&, decl) const);

public:
    // No set function members here.

private:
    explicit set_nothing(boost::shared_ptr<
            boost::contract::aux::check_base> check) : check_(check) {}

    boost::shared_ptr<boost::contract::aux::check_base> check_;
};

} } // namespace

#endif // #include guard

