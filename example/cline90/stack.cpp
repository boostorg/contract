
//[cline90_stack
#include <boost/contract.hpp>
#include <boost/detail/lightweight_test.hpp>

template<typename T>
class stack
    #define BASES private boost::contract::constructor_precondition<stack<T> >
    : BASES
{
public:
    typedef BOOST_CONTRACT_BASE_TYPES(BASES) base_types;
    #undef BASES

    // NOTE: Incomplete contract assertions, addressing only `empty` and `full`.

    explicit stack(int capacity) :
        boost::contract::constructor_precondition<stack>([&] {
            BOOST_CONTRACT_ASSERT(capacity >= 0);
        }),
        data_(new T[capacity]), capacity_(capacity), size_(0)
    {
        auto c = boost::contract::constructor(this)
            .postcondition([&] {
                BOOST_CONTRACT_ASSERT(this->empty());
                BOOST_CONTRACT_ASSERT(full() == (capacity == 0));
            })
        ;
        
        for(int i = 0; i < capacity_; ++i) data_[i] = T();
    }

    virtual ~stack() {
        auto c = boost::contract::destructor(this);
        delete[] data_;
    }

    bool empty() const {
        auto c = boost::contract::public_function(this);
        return size_ == 0;
    }

    bool full() const {
        auto c = boost::contract::public_function(this);
        return size_ == capacity_;
    }

    void push(T const& value) {
        auto c = boost::contract::public_function(this)
            .precondition([&] {
                BOOST_CONTRACT_ASSERT(!full());
            })
            .postcondition([&] {
                BOOST_CONTRACT_ASSERT(!empty());
            })
        ;

        data_[size_++] = value;
    }

    T pop() {
        auto c = boost::contract::public_function(this)
            .precondition([&] {
                BOOST_CONTRACT_ASSERT(!empty());
            })
            .postcondition([&] {
                BOOST_CONTRACT_ASSERT(!full());
            })
        ;

        return data_[--size_];
    }

private:
    T* data_;
    int capacity_;
    int size_;
};

int main() {
    stack<int> s(3);
    s.push(123);
    BOOST_TEST_EQ(s.pop(), 123);
    return boost::report_errors();
}
//]

