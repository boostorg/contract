
#include <iostream>
#include <boost/contract.hpp>
#include <boost/type_traits/has_equal_to.hpp>
#include <functional>
#include <vector>

template< typename T, class Alloc >
struct pushable {
    void invariant ( ) const { // Must not be virtual.
        std::cout << "pushable invariants" << std::endl;
    }

    virtual ~pushable ( ) { }
    
    // Virtual functions: Must not be virtual, have extra v default param, and
    // have virtual body.
    void push_back ( T const& value, boost::contract::virtual_body v = 0 ) {
        // TODO: old-of here must go via contract extra param...
        boost::contract::type contract = boost::contract::member(this, v)
            .precondition([&] ( ) {
                std::cout << "pushable push_back preconditions" << std::endl;
                //BOOST_CONTRACT_ASSERT(false); // force check derived pre...
            })
            .postcondition([&] ( ) {
                std::cout << "pushable push_back postconditions" << std::endl;
                BOOST_CONTRACT_ASSERT(
                    boost::contract::check_if<boost::has_equal_to<T> >(
                            std::equal_to<T>(), this->back(), value)
                );
            })
        ;
        push_back_body(value);
    }
    virtual void push_back_body ( T const& value ) = 0;

    virtual T const& back ( ) const = 0;
};

struct sizeable {
    virtual unsigned size ( ) const = 0;
    virtual unsigned max_size ( ) const = 0;
};
    
template< typename T, class Alloc = std::allocator<T> >
struct vector : boost::contract::extends<
    boost::contract::public_<pushable<T, Alloc> >,
    boost::contract::protected_virtual<sizeable>
> {
    void invariant ( ) const {
        std::cout << "vector invariants" << std::endl;
        BOOST_CONTRACT_ASSERT(empty() == (size() == 0));
    }
    
    void push_back ( T const& value ) {
        unsigned int const old_size = size();
        // TODO: Enforce "if class has bases, must use this signature".
        boost::contract::type contract = boost::contract::member<
                introspect_push_back>(this, &vector::push_back, value)
            .precondition([&] ( ) {
                std::cout << "vector push_back preconditions" << std::endl;
                BOOST_CONTRACT_ASSERT(this->size() < this->max_size());
            })
            .postcondition([&] ( ) {
                std::cout << "vector push_back postconditions" << std::endl;
                BOOST_CONTRACT_ASSERT(this->size() == old_size + 1);
            })
        ;

        push_back_body(value);
    }
    void push_back_body ( T const& value ) {
        std::cout << std::endl << "vector push_back body " << std::endl;
        vector_.push_back(value);
        std::cout << std::endl;
    }
    
    bool empty ( ) const { return vector_.empty(); }
    unsigned size ( ) const { return vector_.size(); }
    unsigned max_size () const { return vector_.max_size(); }
    T const& back ( ) const { return vector_.back(); }

private:
    BOOST_CONTRACT_INTROSPECT(push_back)

    std::vector<T, Alloc> vector_;
};
        
int main ( ) {
    vector<int> v;
    v.push_back(123);
    return 0;
}

