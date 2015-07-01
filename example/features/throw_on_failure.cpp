
#include <boost/contract.hpp>
#include <boost/detail/lightweight_test.hpp>
#include <cstring>
#include <iostream>

//[throw_on_failure_cstring
struct too_large_error {};

template<std::size_t MaxSize>
class cstring
    #define BASES private boost::contract::constructor_precondition< \
            cstring<T, MaxSize> >
    : BASES
{
public:
    typedef BOOST_CONTRACT_BASE_TYPES(BASES) base_types;
    #undef BASES

    /* implicit */ cstring(char const* chars) :
        boost::contract::constructor_precondition<cstring>([&] {
            BOOST_CONTRACT_ASSERT(chars); // Throw `assertion_failure`.
            if(std::strlen(chars) > MaxSize) {
                throw too_large_error(); // Also throw user-defined exception.
            }
        })
    {
        auto c = boost::contract::constructor(this)
            .postcondition([&] {
                BOOST_CONTRACT_ASSERT(size() == std::strlen(chars));
            })
        ;

        size_ = std::strlen(chars);
        for(int i = 0; i < size_; ++i) chars_[i] = chars[i];
        chars_[size_] = '\0';
    }

    /* ... */
//]

    ~string() {
        auto c = boost::contract::destructor(this); // Check invariants.
        delete[] chars_;
    }
    
    int size() const {
        auto c = boost::contract::public_function(this); // Check invariants.
        return size_;
    }
    
    void invariant() const {
        BOOST_CONTRACT_ASSERT(size() < MaxSize);
        BOOST_CONTRACT_ASSERT(chars_);
        BOOST_CONTRACT_ASSERT(chars_[size()] == '\0');
    }

private:
    char[MaxSize] chars_;
    std::size_t size_;
};

//[throw_on_failure_handler
void throwing_handler(boost::contract::from context) {
    if(context == boost::contract::from_destructor) {
        // Ignore exception because destructors should never throw.
        std::cerr << "destructor contract failed (ignored)" << std::endl;
    } else {
        throw; // Re-throw (assertion_failure, too_large_error, etc.).
    }
}

int main() {
    boost::contract::set_precondition_failed(&throwing_handler);
    boost::contract::set_postcondition_failed(&throwing_handler);
    boost::contract::set_invariant_failed(&throwing_handler);

    /* ... */
//]

    string s("abc");
    BOOST_TEST_EQ(s[0], 'a');

    bool pass = false;
    try {
        std::cout << "1" << std::endl;
        s[3];
        std::cout << "2" << std::endl;
    } // Out of range.
    catch(string::range_error const&) {
        std::cout << "3" << std::endl;
        pass = true;
    }
    std::cout << "4" << std::endl;
    BOOST_TEST(pass);

    return boost::report_errors();
}

