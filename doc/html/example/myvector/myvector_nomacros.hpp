// Copyright (C) 2009-2010 Lorenzo Caminiti.
// Use, modification, and distribution is subject to the
// Contract++ Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt.)

// Main documentation example that illustrates contracts without the macros.

#ifndef MYVECTOR_NOMACROS_HPP_
#define MYVECTOR_NOMACROS_HPP_

//[ myvector_nomacros_cpp

#include "pushable.hpp" // Base class for subcontracting.
#include <contract.hpp> // This library.
#include <vector> // STL vector.

// Wrapper that adds simple (not complete) contracts to C++ STL
// without using the library contract macros.
template<typename T>
class myvector: public pushable<T> {

#if defined CONTRACT_CHECK_CLASS_INVARIANT ||  /* Allow for         */ \
        defined CONTRACT_CHECK_PRECONDITION || /* optional contract */ \
        defined CONTRACT_CHECK_POSTCONDITION   /* compilation.      */
    // Augmented state.
    friend class contract::state;
    mutable contract::state contract_state_;
#endif // contracts

#if defined CONTRACT_CHECK_CLASS_INVARIANT
    // Static class invariants
    static void contract_static_invariant_(void) {
        // Assert nothing in this case.
    }
    // Class invariants.
    void contract_invariant_(void) const {
        if (!((size() == 0) == empty()))
            throw contract::failure(__FILE__, __LINE__);
        // More invariants here...
    }
#endif // invariants

public:
    typedef typename std::vector<T>::size_type size_type;
    typedef typename std::vector<T>::const_reference const_reference;
    typedef typename std::vector<T>::const_iterator const_iterator;
    
    // Contract for constructor.
    explicit myvector(size_type count): vector_(count)
#if defined CONTRACT_CHECK_CLASS_INVARIANT || \
        defined CONTRACT_CHECK_PRECONDITION || \
        defined CONTRACT_CHECK_POSTCONDITION
    {
        contract_contract_constructor_count_<0>().call(this, count);
    }
private:
#if defined CONTRACT_CHECK_PRECONDITION
    // Static preconditions (i.e., no object).
    static void contract_precondition_contract_constructor_count_(
            const size_type& count) /* no `const` (it is `static`) */ { 
    }
#endif // preconditions
#if defined CONTRACT_CHECK_POSTCONDITION
    void contract_postcondition_contract_constructor_count_(
            contract::noold, // Always `noold` for old object.
            const size_type& count, contract::noold) const {
        if (!(size() == count))
            throw contract::failure(__FILE__, __LINE__);
    }
#endif // postconditions
protected:
    void contract_body_contract_constructor_(size_type count)
#endif // contracts
    {
        // Do nothing in this case
    }
#if defined CONTRACT_CHECK_CLASS_INVARIANT || \
        defined CONTRACT_CHECK_PRECONDITION || \
        defined CONTRACT_CHECK_POSTCONDITION
    template<int ZERO>
    struct contract_contract_constructor_count_:
            contract::constructor< // Use `constructor` (not `function`).
            // Class type can never be tagged `copyable`.
            void (myvector*, size_type)> {
        contract_contract_constructor_count_(): contract::constructor <
                void (myvector*, size_type)
                >(    &myvector::contract_body_contract_constructor_
                    , &myvector::contract_precondition_contract_constructor_count_
                    , &myvector::contract_postcondition_contract_constructor_count_
                ) {}
    };
public:
#endif // contracts
    
    // Contract for destructor.
    virtual ~myvector(void)
    // Destructors only check invariants.
#if defined CONTRACT_CHECK_CLASS_INVARIANT
    {
        contract_contract_destructor_<0>().call(this);
    }
protected:
    // No precondition and no postcondition functions.
    virtual void contract_body_contract_destructor_(void)
#endif // invariant
    {
        // Do nothing in this case.
    }
#if defined CONTRACT_CHECK_CLASS_INVARIANT
    template<int ZERO>
    struct contract_contract_destructor_:
            contract::destructor< // Use `destructor` (not `function`).
            // Class type can never be tagged `copyable`.
            void (myvector*)> {
        contract_contract_destructor_(): contract::destructor<
                void (myvector*)
                >(&myvector::contract_body_contract_destructor_ ) {}
        };
public: 
#endif // invariant

    // Contract for non-static member functions.
    void push_back(const T& element)
#if defined CONTRACT_CHECK_CLASS_INVARIANT || \
        defined CONTRACT_CHECK_PRECONDITION || \
        defined CONTRACT_CHECK_POSTCONDITION
    // Contracted function.
    {
        contract_push_back_element_<0>().call(this , element);
    }
private: // Private so not to alter user call public API.
#if defined CONTRACT_CHECK_PRECONDITION
    void contract_precondition_push_back_element_(const T& element) const {
        if (!(size() < max_size())) 
            throw contract::failure(__FILE__, __LINE__);
        // More preconditions here...
    }
#endif // preconditions
#if defined CONTRACT_CHECK_POSTCONDITION
    void contract_postcondition_push_back_element_(
            const myvector* contract_old_this_, // Old value for object.
            const T& element, contract::noold   // No old for element argument.
            ) const {
        if (!(size() == (contract_old_this_->size() + 1)))
            throw contract::failure(__FILE__, __LINE__);
        // More postconditions here...
    }
#endif // postconditions
protected: // Must be protected (not private) to allow subcontracting.
    void contract_body_push_back_(const T& element)
#endif // contracts
    // Original function definition (the body).
    {
        vector_.push_back(element);
    } 
#if defined CONTRACT_CHECK_CLASS_INVARIANT || \
        defined CONTRACT_CHECK_PRECONDITION || \
        defined CONTRACT_CHECK_POSTCONDITION
    // Contract class.
    template<int ZERO>
    struct contract_push_back_element_: contract::nonstatic_member_function<
            // Function type with class type pointer as 1st argument.
            // Copyable class type for old object value in postconditions.
            // For constant members, change `myvector` to `myvector const`.
            void (contract::copyable<myvector>*, const T&),
            // Base contract class for subcontracting.
            typename pushable<T>::template contract_push_back_element_<0>
            > {
        // Constructor specifies body, preconditions, and postconditions.
        contract_push_back_element_(): contract::nonstatic_member_function<
                void (contract::copyable<myvector>*, const T&),
                typename pushable<T>::template contract_push_back_element_<0>
                >(    &myvector::contract_body_push_back_
#if defined CONTRACT_CHECK_PRECONDITION
                    , &myvector::contract_precondition_push_back_element_
#endif // preconditions
#if defined CONTRACT_CHECK_POSTCONDITION
                    , &myvector::contract_postcondition_push_back_element_
#endif // postconditions
                ) {} 
    };
public: // Restore original access level.
#endif // contracts

    // Contract for template plus static member function.
    template<class Iter>
    static bool all_equals(Iter first, Iter last, const T& element)
    // Static members also check (static) class invariants.
#if defined CONTRACT_CHECK_CLASS_INVARIANT || \
        defined CONTRACT_CHECK_PRECONDITION || \
        defined CONTRACT_CHECK_POSTCONDITION
    {
        return contract_all_equals_first_last_element_<Iter>().call(
                first, last, element);
    }
private:
    // Static template precondition and postcondition functions.
#if defined CONTRACT_CHECK_PRECONDITION
    template<class Iter>
    static void contract_precondition_all_equals_first_last_element_(
            const Iter& first, const Iter& last, const T& element)
            /* no `const` */ {
        if (!(first < last))
            throw contract::failure(__FILE__, __LINE__);
    }
#endif // preconditions
#if defined CONTRACT_CHECK_POSTCONDITION
    template<class Iter>
    static void contract_postcondition_all_equals_first_last_element_(
            const Iter& first, contract::noold,
            const Iter& last, contract::noold,
            const T& element, contract::noold,
            const bool& result ) // Result value.
            /* no `const` */ {
    }
#endif // postconditions
protected:
    template<class Iter>
    static bool contract_body_all_equals_(
            Iter first, Iter last, const T& element)
#endif // contracts
    {
        for (Iter i = first; i < last; ++i) {
            if (*i != element) return false;
        } 
        return true;
    }
#if defined CONTRACT_CHECK_CLASS_INVARIANT || \
        defined CONTRACT_CHECK_PRECONDITION || \
        defined CONTRACT_CHECK_POSTCONDITION
    // Function template parameter `class Iter` already present so
    // no artificial `int ZERO` parameter.
    template<class Iter>
    struct contract_all_equals_first_last_element_: contract::static_member_function<
            bool (myvector*, Iter, Iter, const T&)
            > {
        contract_all_equals_first_last_element_(): contract:: static_member_function<
                bool (myvector*, Iter, Iter, const T&)
                >(    &myvector::template contract_body_all_equals_<Iter>
#if defined CONTRACT_CHECK_PRECONDITION
                    , &myvector::template contract_precondition_all_equals_first_last_element_<Iter>
#endif // preconditions
#if defined CONTRACT_CHECK_POSTCONDITION
                    , &myvector::template contract_postcondition_all_equals_first_last_element_<Iter>
#endif // postconditions
                ) {}
    };
public:
#endif // contracts

    // Similarly, complete contracts sketched here and add contracts
    // for all other functions (see [Crowl2006] vector example).
    size_type size(void) const { return vector_.size(); }
    size_type max_size(void) const { return vector_.max_size(); }
    bool empty(void) const { return vector_.empty(); }
    const_reference back(void) const { return vector_.back(); }
    const_iterator begin(void) const { return vector_.begin(); }
    const_iterator end(void) const { return vector_.end(); }
    const_reference operator[](size_type index) const
        { return vector_[index]; }
    
private:
    std::vector<T> vector_;
};

// Contract for non-member function.
double abs_total(const myvector<double>& vector)
// Non-member members do not check invariants.
#if defined CONTRACT_CHECK_PRECONDITION || \
        defined CONTRACT_CHECK_POSTCONDITION
;
void contract_precondition_abs_total_vector_(
        const myvector<double>& vector ) {
}
void contract_postcondition_abs_total_vector_(
        const myvector<double>& vector, contract::noold,
        const double& total) {
    if (!(total >= 0.0))
        throw contract::failure(__FILE__, __LINE__);
}
double contract_body_abs_total_(const myvector<double>& vector)
#endif // preconditions or postconditions
{
    double total = 0.0;
    CONTRACT_ASSERT_BLOCK_INVARIANT( total == 0.0 );
    {
        CONTRACT_INIT_LOOP_VARIANT;
        for (size_t i = 0; i < vector.size(); ++i) {
            CONTRACT_ASSERT_BLOCK_INVARIANT( i < vector.size() );
            CONTRACT_ASSERT_LOOP_VARIANT( vector.size() - i );

            total += vector[i];
        } 
    }
    return total < 0.0 ? -total : total;
}
#if defined CONTRACT_CHECK_PRECONDITION || \
        defined CONTRACT_CHECK_POSTCONDITION
template<int ZERO>
struct contract_abs_total_vector_: contract::nonmember_function<
        // Still use `function` but no class type pointer as 1st argument.
        double (const myvector<double>&)
        > {
    contract_abs_total_vector_(): contract::nonmember_function<
            double (const myvector<double>&)>
            (     &contract_body_abs_total_
                , &contract_precondition_abs_total_vector_
                , &contract_postcondition_abs_total_vector_
            ) {}
};
// Contracted function defined last and always `inline`.
inline double abs_total(const myvector<double>& vector) {
    return contract_abs_total_vector_<0>().call(vector);
}
#endif // preconditions or postconditions

//]

#endif // #include guard

