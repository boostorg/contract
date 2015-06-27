
//[countdown
template<typename T = int>
class countdwon {
public:
    explicit countdown(T n) : n_(n) {}

    /* ... */

protected:
    T get() const { // Protected function (like free functions).
        int result;
        auto c = boost::contract::function()
            .postcondition([&] {
                BOOST_CONTRACT_ASSERT(result == n_);
            })
        ;

        return result = n_; // Function body.
    }

private:
    void dec() { // Private function (like free functions).
        auto old_n = BOOST_CONTRACT_OLDOF(n_);
        auto c = boost::contract::function()
            .precondition([&] {
                BOOST_CONTRACT_ASSERT(n_ > std::numeric_limit<T>::min());
            })
            .postcondition([&] {
                BOOST_CONTRACT_ASSERT(n_ == *old_n - 1);
            })
        ;

        --n_; // Function body.
    }

    T n_;
};
//]

