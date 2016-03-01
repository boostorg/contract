
// Test possible impl. advance() in single function with C++14 generic lambdas.

#include "../detail/oteststream.hpp"
#include <boost/contract/call_if.hpp>
#include <boost/detail/lightweight_test.hpp>
#include <type_traits>
#include <iterator>
#include <functional> // std::bind for generic lambdas.
#include <vector>
#include <list>
#include <sstream>

boost::contract::test::detail::oteststream out;

template<typename Iter>
struct is_random_access_iterator : std::is_same<
    typename std::iterator_traits<Iter>::iterator_category,
    std::random_access_iterator_tag
> {};

template<typename Iter>
struct is_bidirectional_iterator : std::is_same<
    typename std::iterator_traits<Iter>::iterator_category,
    std::bidirectional_iterator_tag
> {};

template<typename Iter>
struct is_input_iterator : std::is_same<
    typename std::iterator_traits<Iter>::iterator_category,
    std::input_iterator_tag
> {};

template<typename Iter, typename Dist>
void myadvance(Iter& i, Dist n) {
    Iter *p = &i; // So captures change actual pointed iterator value.
    boost::contract::call_if<is_random_access_iterator<Iter> >(
        std::bind([] (auto p, auto n) {
            out << "random iterator" << std::endl;
            *p += n;
        }, p, n)
    ).template else_if<is_bidirectional_iterator<Iter> >(
        std::bind([] (auto p, auto n) {
            out << "bidirectional iterator" << std::endl;
            if(n >= 0) while(n--) ++*p;
            else while(n++) --*p;
        }, p, n)
    ).template else_if<is_input_iterator<Iter> >(
        std::bind([] (auto p, auto n) {
            out << "input iterator" << std::endl;
            while(n--) ++*p;
        }, p, n)
    ).else_(
        std::bind([] (auto false_) {
            static_assert(false_, "requires input iter");
        }, std::false_type()) // Use constexpr value.
    );
}

struct x {}; // Test not an iterator (static_assert failure in else_ above).

namespace std {
    template<>
    struct iterator_traits<x> {
        typedef void iterator_category;
    };
}

int main() {
    std::ostringstream ok;

    std::vector<char> v;
    v.push_back('a');
    v.push_back('b');
    v.push_back('c');
    v.push_back('d');
    std::vector<char>::iterator r = v.begin(); // Random iterator.
    out.str("");
    myadvance(r, 1);
    out << *r << std::endl;
    ok.str(""); ok
        << "random iterator" << std::endl
        << "b" << std::endl
    ;
    BOOST_TEST(out.eq(ok.str()));

    std::list<char> l(v.begin(), v.end());
    std::list<char>::iterator b = l.begin(); // Bidirectional iterator.
    out.str("");
    myadvance(b, 2);
    out << *b << std::endl;
    ok.str(""); ok
        << "bidirectional iterator" << std::endl
        << "c" << std::endl
    ;
    BOOST_TEST(out.eq(ok.str()));

    std::istringstream s("a b c d");
    std::istream_iterator<char> i(s);
    out.str("");
    myadvance(i, 3);
    out << *i << std::endl;
    ok.str(""); ok
        << "input iterator" << std::endl
        << "d" << std::endl
    ;
    BOOST_TEST(out.eq(ok.str()));

    // x xx;
    // myadvance(xx, 0); // Error (correctly because x not even input iter).

    return boost::report_errors();
}

