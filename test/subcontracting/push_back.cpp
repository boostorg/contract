
#include <boost/contract.hpp>
#include <vector>

template< typename T, class Alloc >
struct pushable {
    virtual ~pushable ( ) { }
    virtual void push_back ( T const& value ) = 0;
};

BOOST_CONTRACT_CLASS(
    template( typename T, class Alloc, default std::allocator<T> )
    class (vector) extends( public (pushable<T, Alloc>) )
) {
    BOOST_CONTRACT_CLASS_INVARIANT_TPL()

    BOOST_CONTRACT_FUNCTION_TPL(
        public void (push_back) ( (T const&) value )
    ) {
        vector_.push_back(value);
    }

private:
    std::vector<T, Alloc> vector_;
}

int main ( ) {
    return 0;
}

