
#include <boost/contract.hpp>
#include <boost/bind.hpp>
#include <boost/detail/lightweight_test.hpp>
#include <cstring>

// Adapted from an example presented in the book "The C++ Programming Language"
// (Stroustrup, 1997) to illustrate importance of class invariants. Simple
// preconditions were added where it made sense.
// This should be compiled with postconditions checking turned off (define the
// `BOOST_CONTRACT_NO_POSTCONDITIONS` macro) because postconditions are
// deliberately not used here.
// See referenced book for a discussion on the importance of class invariants,
// and on pros and cons of using pre and post conditions.
class string
    #define BASES private boost::contract::constructor_precondition<string>
    : BASES
{
public:
    typedef BOOST_CONTRACT_BASE_TYPES(BASES) base_types;
    #undef BASES

    // Here contracts throw these exceptions instead of terminating on failure.
    struct invariant_error {};
    struct range_error {};
    struct null_error {};
    struct too_large_error {};
    
    enum { too_large = 16000 }; // Length limit.

    void invariant() const {
        if(!chars_) throw invariant_error();
        if(size_ < 0) throw invariant_error();
        if(size_ > too_large) throw invariant_error();
        if(chars_[size_] != '\0') throw invariant_error();
    }

    static void string_precondition(char const* const chars) {
        if(!chars) throw string::null_error();
        if(strlen(chars) > too_large) throw too_large_error();
    }
    /* implicit */ string(char const* chars) :
        boost::contract::constructor_precondition<string>(
                boost::bind(&string_precondition, chars))
    {
        auto c = boost::contract::constructor(this); // Check invariants.
        init(chars);
    }

    /* implicit */ string(string const& other) {
        auto c = boost::contract::constructor(this); // Check invariants.
        init(other.chars_);
    }

    ~string() {
        auto c = boost::contract::destructor(this); // Check invariants.
        delete[] chars_;
    }

    char& operator[](int index) {
        auto c = boost::contract::public_function(this)
            .precondition([&] {
                if(index < 0) throw string::range_error();
                if(index >= size_) throw string::range_error();
            })
        ;

        return chars_[index];
    }

    int size() const {
        auto c = boost::contract::public_function(this); // Check invariants.
        return size_;
    }

private:
    void init(char const* chars) { // Non public so does not check invariants.
        auto c = boost::contract::function()
            .precondition([&] {
                if(!chars) throw string::null_error();
            })
        ;

        size_ = strlen(chars);
        chars_ = new char[size_ + 1];
        for(int i = 0; i < size_; ++i) chars_[i] = chars[i];
        chars_[size_] = '\0';
    }

    int size_;
    char* chars_;
};

void throwing_handler(boost::contract::from context) {
    if(context == boost::contract::from_destructor) {
        // Ignore exception because destructors should never throw.
        std::cerr << "destructor contract failed (ignored)" << std::endl;
    } else {
        throw; // Re-throw active exception throw by the contract.
    }
}

int main() {
    boost::contract::set_precondition_failed(&throwing_handler);
    boost::contract::set_postcondition_failed(&throwing_handler);
    boost::contract::set_invariant_failed(&throwing_handler);

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

