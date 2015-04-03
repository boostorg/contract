
#include <boost/contract.hpp>
#include <boost/tti/has_member_function.hpp>
#include <boost/mpl/vector.hpp>
#include <vector>
#include <iostream>

template< typename T, class Alloc >
struct pushable {
    void invariant ( ) const { // Must not be virtual.
        std::cout << "pushable invariants" << std::endl;
    }

    virtual ~pushable ( ) { }
    
    // Must not be virtual.
    void push_back ( T const& value, boost::contract::control c = 0 ) {
        std::cout << "pushable push_back: " << value << std::endl;

        boost::contract::function<> contract(this, c
            , [&] ( ) {
                std::cout << "pushable push_back preconditions" << std::endl;
                //BOOST_CONTRACT_ASSERT(false); // force check derived pre...
            }
            , [&] ( ) {
                std::cout << "pushable push_back postconditions" << std::endl;
                BOOST_CONTRACT_ASSERT(this->back() == value); // static-if...
            }
        );
        //push_back_body(value);
    }
    //virtual void push_back_body ( T const& value ) = 0;

    virtual T const& back ( ) const = 0;
};

struct sizeable {
    virtual unsigned size ( ) const = 0;
    virtual unsigned max_size ( ) const = 0;
};
        
template< typename T, class Alloc = std::allocator<T> >
class vector : public pushable<T, Alloc>, public sizeable {
public:
    void invariant ( ) const {
        std::cout << "vector invariants" << std::endl;
        BOOST_CONTRACT_ASSERT(empty() == (size() == 0));
    }

    struct push_back_traits {
        // Using Boost.TTI here makes MSVC crash if called more than once... :(
        //BOOST_TTI_HAS_MEMBER_FUNCTION(push_back)

        template< class CC, typename RR, class AA >
        class has_member_function {
            typedef struct {} yes;
            typedef yes no[2];

            template< typename FF, FF > struct check_func;
            template< typename TT >
            static yes& check (
                check_func<
                    typename boost::contract::ext::function_types::
                            member_function_pointer<RR, TT, AA>::type,
                    &TT::push_back
                >*
            );
            template< typename >
            static no& check ( ... );

        public:
            static bool const value = sizeof(check<CC>(0)) == sizeof(yes);
        };

        template< class CC, typename FF >
        static FF member_function_ptr ( ) { return &CC::push_back; }
    };

    void push_back ( T const& value, boost::contract::control c = 0 ) {
        std::cout << "vector push_back: " << value << std::endl;

        auto old_size = c.oldof_(size());
        boost::contract::function<
            push_back_traits,
            boost::mpl::vector<
                  pushable<T, Alloc>*
                , sizeable*
            >
        > contract(&vector::push_back, this, value, c
            , [&] ( ) {
                std::cout << "vector push_back preconditions" << std::endl;
                BOOST_CONTRACT_ASSERT(this->size() < this->max_size());
            }
            , [&] ( ) {
                std::cout << "vector push_back postconditions" << std::endl;
                BOOST_CONTRACT_ASSERT(this->size() == old_size + 1);
            }
        );
        push_back_body(value);
    }
    void push_back_body ( T const& value ) {
        std::cout << "vector push_back body " << std::endl;
        vector_.push_back(value);
    }
    
    bool empty ( ) const { return vector_.empty(); }
    unsigned size ( ) const { return vector_.size(); }
    unsigned max_size () const { return vector_.max_size(); }
    T const& back ( ) const { return vector_.back(); }

private:
    std::vector<T, Alloc> vector_;
};
        
int main ( ) {
    vector<int> v;
    v.push_back(123);
    return 0;
}

