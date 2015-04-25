
#ifndef BOOST_CONTRACT_SET_PRECONDITION_POSTCONDITION_HPP_
#define BOOST_CONTRACT_SET_PRECONDITION_POSTCONDITION_HPP_

#include <boost/contract/set/precondition_only.hpp>
#include <boost/contract/set/postcondition_only.hpp>
#include <boost/contract/aux_/check/pre_post.hpp>
#include <boost/shared_ptr.hpp>

namespace boost {
    namespace contract {
        class type;
        class virtual_body;

        template<class Itrospection, class Class, typename Function,
                typename Argument0>
        boost::contract::set::precondition_postcondition public_member(
            Class* const, Function const&, Argument0,
            boost::contract::virtual_body const
        );
        
        template<class Introspection, class Class, typename Function,
                typename Argument0>
        boost::contract::set::precondition_postcondition public_member(
                Class* const, Function const&, Argument0);
    
        template<class Class>
        boost::contract::set::precondition_postcondition public_member(
                Class* const, boost::contract::virtual_body const);
    
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

class precondition_postcondition {
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
    explicit precondition_postcondition(boost::shared_ptr<boost::contract::aux::
            check::pre_post> const contract) : contract_(contract) {}

    /* implicit */ precondition_postcondition(precondition_postcondition const&
            other) : contract_(other.contract_) {}
    precondition_postcondition& operator=(precondition_postcondition const&)
            /* = delete */;
    precondition_postcondition() /* = delete */;

    boost::shared_ptr<boost::contract::aux::check::pre_post> contract_;
    
    // Use friendship and deleted constructors to limit public API.

    friend class boost::contract::type;

    template<class Itrospection, class Class, typename Function,
            typename Argument0>
    friend precondition_postcondition boost::contract::public_member(
        Class* const, Function const&, Argument0,
        boost::contract::virtual_body const
    );
        
    template<class Introspection, class Class, typename Function,
            typename Argument0>
    friend precondition_postcondition boost::contract::public_member(
            Class* const, Function const&, Argument0);
        
    template<class Class>
    friend precondition_postcondition boost::contract::public_member(
            Class* const, boost::contract::virtual_body const);
        
    template<class Class>
    friend precondition_postcondition boost::contract::public_member(
            Class* const);
        
    template<class Class>
    friend precondition_postcondition boost::contract::public_member();
    
    friend precondition_postcondition boost::contract::protected_member();
    friend precondition_postcondition boost::contract::private_member();
    friend precondition_postcondition boost::contract::free_function();
};

} } } // namespace

#endif // #include guard

