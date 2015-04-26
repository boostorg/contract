
#ifndef BOOST_CONTRACT_SET_PRECONDITION_POSTCONDITION_HPP_
#define BOOST_CONTRACT_SET_PRECONDITION_POSTCONDITION_HPP_

#include <boost/contract/set/precondition_only.hpp>
#include <boost/contract/set/postcondition_only.hpp>
#include <boost/contract/aux_/check/pre_post.hpp>
#include <boost/shared_ptr.hpp>

namespace boost {
    namespace contract {
        class scoped;
        class virtual_body;

        template<class Itrospection, class Class, typename Function,
                typename Argument0>
        boost::contract::set::precondition_postcondition public_member(
            boost::contract::virtual_body const, Class* const, Function const&,
            Argument0
        );
        
        template<class Introspection, class Class, typename Function,
                typename Argument0>
        boost::contract::set::precondition_postcondition public_member(
                Class* const, Function const&, Argument0);
    
        template<class Class>
        boost::contract::set::precondition_postcondition public_member(
                boost::contract::virtual_body const, Class* const);
    
        template<class Class>
        boost::contract::set::precondition_postcondition public_member(
                Class* const);
    
        template<class Class>
        boost::contract::set::precondition_postcondition public_member();

        boost::contract::set::precondition_postcondition protected_member();
        boost::contract::set::precondition_postcondition private_member();
        boost::contract::set::precondition_postcondition free_function();
    }
}

namespace boost { namespace contract { namespace set {

class precondition_postcondition { // Allow (shallow ptr) copy for auto c = ...
public:
    template<typename Precondition>
    boost::contract::set::postcondition_only precondition(
            Precondition const& f) {
        contract_->set_pre(f);
        return boost::contract::set::postcondition_only(contract_);
    }
    
    template<typename Postcondition>
    boost::contract::set::precondition_only postcondition(
            Postcondition const& f) {
        contract_->set_post(f);
        return boost::contract::set::precondition_only(contract_);
    }

private:
    // Use friendship and deleted constructors to limit public API.
    friend class boost::contract::scoped;

    template<class Itrospection, class Class, typename Function,
            typename Argument0>
    friend precondition_postcondition boost::contract::public_member(
        boost::contract::virtual_body const, Class* const, Function const&,
        Argument0
    );
        
    template<class Introspection, class Class, typename Function,
            typename Argument0>
    friend precondition_postcondition boost::contract::public_member(
            Class* const, Function const&, Argument0);
        
    template<class Class>
    friend precondition_postcondition boost::contract::public_member(
            boost::contract::virtual_body const, Class* const);
        
    template<class Class>
    friend precondition_postcondition boost::contract::public_member(
            Class* const);
        
    template<class Class>
    friend precondition_postcondition boost::contract::public_member();
    
    friend precondition_postcondition boost::contract::protected_member();
    friend precondition_postcondition boost::contract::private_member();
    friend precondition_postcondition boost::contract::free_function();

    explicit precondition_postcondition(boost::shared_ptr<boost::contract::aux::
            check::pre_post> const contract) : contract_(contract) {}

    boost::shared_ptr<boost::contract::aux::check::pre_post> contract_;
};

} } } // namespace

#endif // #include guard

