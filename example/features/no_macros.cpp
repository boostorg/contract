
//[no_oldof_macro
template<typename T>
class vector {
public:
    void push_back(T const& value, boost::contract::virtual_* v = 0)
        // Program old-value without macros (pass extra `v` if virtual).
        boost::shared_ptr<int const> old_size =
                boost::contract::copy_old() ? size() : boost::contract::old();

        auto c = boost::contract::public_function(this)
            .postcondition([&] {
                BOOST_CONTRACT_ASSERT(size() == *old_size + 1);
            })
        ;

        vect_.push_back(id); // Function body.
    }

    /* ... */

    //]
    
    void invariant() const {
        BOOST_CONTRACT_ASSERT(size() >= 0);
    }
    
private:
    std::vector<int> vect_;
};

//[no_virtual_oldof_macro
class identifiers {
public:
    virtual void push_back(int id, boost::contract::virtual_* v = 0)
        // Program old-value without macros with extra `v`.
        boost::shared_ptr<int const> old_size =
                boost::contract::copy_old(v) ? size() : boost::contract::old();

        auto c = boost::contract::public_function(this)
            .postcondition([&] {
                BOOST_CONTRACT_ASSERT(size() == *old_size + 1);
            })
        ;

        vect_.push_back(id); // Function body.
    }

    /* ... */

    //]
    
    void invariant() const {
        BOOST_CONTRACT_ASSERT(size() >= 0);
    }
    
private:
    std::vector<int> vect_;
};


//[no_base_types_macro
#include <boost/mpl/vector.hpp>

class multi_identifiers :
    private boost::contract::constructor_precondition<multi_identifiers>,
    public identifiers, public virtual pushable,
    protected sizer, private capacitor
{
public:
    // Program `base_types` without macros (list only public bases).
    typedef boost::mpl::vector<identifiers, pushable> base_types;

    /* ... */
//]
};

