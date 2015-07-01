
//[call_if
template<typename T>
class vector {
public:
    void push_back(T const& value) {
        auto old_size = BOOST_CONTRACT_OLDOF(size());
        auto c = boost::contract::public_function(this)
            .precondition([&] {
                BOOST_CONTRACT_ASSERT(this->size() < max_size());
            })
            .postcondition([&] {
                // Check this only if T has operator== (otherwise always true).
                BOOST_CONTRACT_ASSERT(
                    boost::contract::call_if<boost::has_equal_to<T> >(
                        boost::bind(std::equal_to<T>(), boost::cref(back()),
                                boost::cref(value))
                    ).else_([] { return true; })
                );
                
                BOOST_CONTRACT_ASSERT(this->size() == *old_size + 1);
            })
        ;

        vect_.push_back(value);
    }

    /* ... */
//]

    void invariant() const {
        BOOST_CONTRACT_ASSERT(size() <= max_size());
    }

private:
    std::vector<T> vect_;
};

