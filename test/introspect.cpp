
#include <boost/contract/introspect.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/detail/lightweight_test.hpp>

struct w {};

struct z {
    char f(int) { return 'z'; }
};

struct y {
    int f(char) { return -1; }
};

struct x {
    int f(char) {
        BOOST_TEST((introspect_f::has_member_function<y, int,
                boost::mpl::vector<char> >::value));
        BOOST_TEST((!introspect_f::has_member_function<z, int,
                boost::mpl::vector<char> >::value));
        BOOST_TEST((!introspect_f::has_member_function<w, int,
                boost::mpl::vector<char> >::value));
        
        BOOST_TEST((introspect_f::member_function_address<y,
                int (y::*)(char const)>() == &y::f));

        return 'x';
    }
private:
    BOOST_CONTRACT_INTROSPECT(f)
};

int main() {
    x xx;
    xx.f('a');
    return 0;
}

