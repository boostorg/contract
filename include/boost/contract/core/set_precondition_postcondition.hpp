
#ifndef BOOST_CONTRACT_SET_PRECONDITION_POSTCONDITION_HPP_
#define BOOST_CONTRACT_SET_PRECONDITION_POSTCONDITION_HPP_

#include <boost/contract/core/set_precondition_only.hpp>
#include <boost/contract/core/set_postcondition_only.hpp>
#include <boost/contract/core/virtual.hpp>
#include <boost/contract/aux_/check/pre_post.hpp>
#include <boost/shared_ptr.hpp>

namespace boost { namespace contract {

// This type allows (shallow ptr) copies for `auto c = ...`.
class set_precondition_postcondition {
public:
    template<typename Precondition>
    boost::contract::set_postcondition_only precondition(
            Precondition const& f) {
        contract_->set_pre(f);
        return boost::contract::set_postcondition_only(contract_);
    }
    
    template<typename Postcondition>
    boost::contract::set_precondition_only postcondition(
            Postcondition const& f) {
        contract_->set_post(f);
        return boost::contract::set_precondition_only(contract_);
    }

private:
    // Use friendship and deleted constructors to limit public API.
    friend class var;

    template<class Itrospection, class Class, typename Argument0>
    friend set_precondition_postcondition public_member(boost::contract::
            virtual_* const, Class* const, Argument0&);
        
    template<class Introspection, class Class, typename Argument0>
    friend set_precondition_postcondition public_member(Class *const,
            Argument0&);
        
    template<class Class>
    friend set_precondition_postcondition public_member(boost::contract::
            virtual_* const, Class* const);
        
    template<class Class>
    friend set_precondition_postcondition public_member(Class* const);
        
    template<class Class>
    friend set_precondition_postcondition public_member();
    
    friend set_precondition_postcondition protected_member();
    friend set_precondition_postcondition private_member();
    friend set_precondition_postcondition free_function();

    explicit set_precondition_postcondition(boost::shared_ptr<boost::contract::
            aux::check::pre_post> const contract) : contract_(contract) {}

    boost::shared_ptr<boost::contract::aux::check::pre_post> contract_;
};

} } // namespace

#endif // #include guard

