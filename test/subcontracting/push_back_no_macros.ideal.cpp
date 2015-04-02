
#include <boost/contract.hpp>
#include <vector>
#include <iostream>
#include <cassert>

template< typename T, class Alloc >
struct pushable {
    virtual ~pushable ( ) { }
    
    void push_back ( T const& value, boost::contract contract = 0 ) {
        BOOST_CONTRACT_MEMBER(contract, pushable, public virtual push_back)
            .precondition([&] ( ) {
                BOOST_CONTRACT_ASSERT(false);
            })
            .postcondition([&] ( ) {
                BOOST_CONTRACT_ASSERT(back() == value);
            })
        ;
        push_back_body(value);
    }
    virtual void push_back_body ( T const& value ) = 0;

    virtual T const& back ( ) const = 0;
};

#define BASES (public pushable<T, Alloc>)
template< typename T, class Alloc = std::allocator<T> >
class vector : BOOST_CONTRACT_LIST(BASES) {
public:
    // The name of this function "invariant" can be changed via
    // CONFIG_INVARIANT_FUNCTION_NAME.
    void invariant ( ) const {
        BOOST_CONTRACT_ASSERT(empty() == (size() == 0));
    }

    // This is not needed on C++14 (with generic lambas we can use local structs
    // defined by MEMBER macro to check if has member and access base func ptr).
    BOOST_CONTRACT_MEMBER_TRAITS(push_back)

    void push_back ( T const& value, boost::contract contract = 0 ) {
        auto old_size = contract.oldof_(size());
        // Public not needed on C++14.
        // This macro will error if:
        // * vector is not the class type (using decltype(*this), at least for
        //   non-static members).
        // * "push_back" is not the function name (at least using __func__ at
        //   run-time, but can I check that at compile-time instead?).
        // * any type in BASES is not an actual base (but I can't check if
        //   bases are missing).
        BOOST_CONTRACT_MEMBER(contract, vector, public push_back, BASES)
            .precondition([&] ( ) {
                BOOST_CONTRACT_ASSERT(size() < max_size());
            })
            .postcondition([&] ( ) {
                BOOST_CONTRACT_ASSERT(size() == old_size + 1);
            })
        ;
        push_back_body(value);
    }
    void push_back_body ( T const& value ) { vector_.push_back(value); }
    
    bool empty ( ) const { return vector_.empty(); }
    unsigned int size ( ) const { return vector_.size(); }
    unsigned int max_size () const { return vector_.max_size(); }
    T const& back ( ) const { return vector_.back(); }

private:
    std::vector<T, Alloc> vector_;
};
#undef BASES

int main ( ) {
    vector<int> v;
    v.push_back(123);
    return 0;
}

