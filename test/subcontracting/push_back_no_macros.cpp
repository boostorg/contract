
#include <boost/contract.hpp>
#include <boost/tti/has_member_function.hpp>
#include <vector>
#include <iostream>
#include <cassert>

template< typename T, class Alloc >
struct pushable {
    void invariant ( ) const {
        std::cout << "pushable::invariant" << std::endl;
    }

    virtual ~pushable ( ) { }
    
    virtual void push_back ( T const& value, boost::contract::control c = 0 )
            = 0 {
        std::cout << "pushable::push_back" << std::endl;
        /*
        boost::contract::function<> contract(this
            , [&] ( ) {
                std::cout << "pushable::push_back::precondition" << std::endl;
//                assert(false); // Failure to check overriding preconditions.
            }
            , [&] ( ) {
                assert(back() == value); // Should use static-if (C++14).
            }
        );*/
    }

    virtual T const& back ( ) const = 0;
};

struct sizeable {
    virtual unsigned size ( ) const = 0;
    virtual unsigned max_size ( ) const = 0;
};
    
#define BASES (public pushable<T, Alloc>) (public sizeable)
template< typename T, class Alloc = std::allocator<T> >
class vector : BOOST_CONTRACT_BASE_ENUM(BASES) {
public:
    void invariant ( ) const {
        std::cout << "vector::invariant" << std::endl;
        assert(empty() == (size() == 0));
    }

    void push_back ( T const& value, boost::contract::control c = 0 ) {
        std::cout << "vector::push_back" << std::endl;

        auto old_size = size();
        boost::contract::function<has_member_function_push_back,
                BOOST_CONTRACT_BASE_TYPES(BASES)> contract(c
            , &vector::push_back, this
            , [&] ( ) {
                std::cout << "vector::push_back::precondition" << std::endl;
                assert(this->size() < this->max_size());
            }
            , [&] ( ) {
                std::cout << "vector::push_back::postcondition" << std::endl;
                assert(this->size() == old_size + 1);
            }
        );

        std::cout << "vector::push_back::body " << value << std::endl;
        vector_.push_back(value);
    }
    
    bool empty ( ) const { return vector_.empty(); }
    unsigned size ( ) const { return vector_.size(); }
    unsigned max_size () const { return vector_.max_size(); }
    T const& back ( ) const { return vector_.back(); }

private:
    BOOST_TTI_HAS_MEMBER_FUNCTION(push_back)
    
    std::vector<T, Alloc> vector_;
};
#undef BASES

// NOTE: Invariant function must be a public member.

// NOTE: contract must be declared at the very top of the function, before the
// function body instructions.

// NOTE: For convenience, preconditions and postconditions usually capture by
// reference so they must avoid modifying program's state (read-only).
// Furthermore, preconditions should not use old-values, not even read-only
// (even if they implicitly capture those using `&`).

// NOTE: C++14 is required in order to program static-if without the macros.
    
// TODO: Allow to name pre/post-condition functor parameter using
// `boost::contract::pre/post-condition = ...` to support case when only
// postconditions are specified. These could always be used to improve
// readability...

// TODO: Could wrap inv, pre, post above with
// #ifdef BOOST_CONTRACT_INVARIANT/PRECONDITON/POSTCONDITION ... #endif
// to not compile contract when they are disable (but not running contracts
// when they are disabled might be enough). Also old-value declarations could
// be wrapped y #ifdef BOOST_CONTRACT_POSTCONDITION ... #endif.

int main ( ) {
    vector<int> v;
    v.push_back(123);
    return 0;
}

