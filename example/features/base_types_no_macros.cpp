
#include <boost/contract.hpp>
#include <cassert>

template<typename T>
class pushable {
public:
    void invariant() const {
        BOOST_CONTRACT_ASSERT(capacity() <= max_size());
    }

    virtual void push_back(T x, boost::contract::virtual_* v = 0) = 0;

protected:
    virtual int capacity() const = 0;
    virtual int max_size() const = 0;
};

template<typename T>
void pushable<T>::push_back(T x, boost::contract::virtual_* v) {
    boost::contract::old_ptr<int> old_capacity =
            BOOST_CONTRACT_OLDOF(v, capacity());
    boost::contract::guard c = boost::contract::public_function(v, this)
        .precondition([&] {
            BOOST_CONTRACT_ASSERT(capacity() < max_size());
        })
        .postcondition([&] {
            BOOST_CONTRACT_ASSERT(capacity() >= *old_capacity);
        })
    ;
    assert(false); // Shall never execute this body.
}

struct has_size { virtual int size() const = 0; };
struct has_empty { virtual bool empty() const = 0; };

class unique_chars
    : private boost::contract::constructor_precondition<unique_chars>
{
public:
    void invariant() const {
        BOOST_CONTRACT_ASSERT(size() >= 0);
    }

    unique_chars(char from, char to) :
        boost::contract::constructor_precondition<unique_chars>([&] {
            BOOST_CONTRACT_ASSERT(from <= to);
        })
    {
        boost::contract::guard c = boost::contract::constructor(this)
            .postcondition([&] {
                BOOST_CONTRACT_ASSERT(size() == (to - from + 1));
            })
        ;

        for(char x = from; x <= to; ++x) vect_.push_back(x);
    }

    virtual ~unique_chars() {
        boost::contract::guard c = boost::contract::destructor(this);
    }

    int size() const {
        boost::contract::guard c = boost::contract::public_function(this);
        return vect_.size();
    }

    bool find(char x) const {
        bool result;
        boost::contract::guard c = boost::contract::public_function(this)
            .postcondition([&] {
                if(size() == 0) BOOST_CONTRACT_ASSERT(!result);
            })
        ;

        return result = std::find(vect_.begin(), vect_.end(), x) != vect_.end();
    }

    virtual void push_back(char x, boost::contract::virtual_* v = 0) {
        boost::contract::old_ptr<bool> old_find =
                    BOOST_CONTRACT_OLDOF(v, find(x));
        boost::contract::old_ptr<int> old_size =
                    BOOST_CONTRACT_OLDOF(v, size());
        boost::contract::guard c = boost::contract::public_function(v, this)
            .precondition([&] {
                BOOST_CONTRACT_ASSERT(!find(x));
            })
            .postcondition([&] {
                if(!*old_find) {
                    BOOST_CONTRACT_ASSERT(find(x));
                    BOOST_CONTRACT_ASSERT(size() == *old_size + 1);
                }
            })
        ;

        vect_.push_back(x);
    }

protected:
    unique_chars() {}

    std::vector<int> const& vect() const { return vect_; }

private:
    std::vector<int> vect_;
};

//[base_types_no_macros
#include <boost/mpl/vector.hpp>

class chars :
    private boost::contract::constructor_precondition<chars>,
    public unique_chars,
    public virtual pushable<char>,
    virtual protected has_size,
    private has_empty
{
public:
    // Program `base_types` without macros (list only public bases).
    typedef boost::mpl::vector<unique_chars, pushable<char> > base_types;

    /* ... */
//]
    
    void invariant() const {
        BOOST_CONTRACT_ASSERT(empty() == (size() == 0));
    }
    
    chars(char from, char to) : unique_chars(from, to) {
        boost::contract::guard c = boost::contract::constructor(this);
    }

    chars(char const* const c_str) :
        boost::contract::constructor_precondition<chars>([&] {
            BOOST_CONTRACT_ASSERT(c_str[0] != '\0');
        })
    {
        boost::contract::guard c = boost::contract::constructor(this);

        for(int i = 0; c_str[i] != '\0'; ++i) push_back(c_str[i]);
    }
    
    void push_back(char x, boost::contract::virtual_* v = 0) /* override */ {
        boost::contract::old_ptr<bool> old_find =
                BOOST_CONTRACT_OLDOF(v, find(x));
        boost::contract::old_ptr<int> old_size =
                BOOST_CONTRACT_OLDOF(v, size());
        boost::contract::guard c = boost::contract::public_function<
                override_push_back>(v, &chars::push_back, this, x)
            .precondition([&] {
                BOOST_CONTRACT_ASSERT(find(x));
            })
            .postcondition([&] {
                if(*old_find) BOOST_CONTRACT_ASSERT(size() == *old_size);
            })
        ;

        if(!find(x)) unique_chars::push_back(x);
    }
    BOOST_CONTRACT_OVERRIDE(push_back);

    bool empty() const {
        boost::contract::guard c = boost::contract::public_function(this);
        return size() == 0;
    }

    int size() const { return unique_chars::size(); }

protected:
    int max_size() const { return vect().max_size(); }
    int capacity() const { return vect().capacity(); }
};
    
int main() {
    chars s("abc");
    assert(s.find('a'));
    assert(s.find('b'));
    assert(!s.find('x'));
    return 0;
}

