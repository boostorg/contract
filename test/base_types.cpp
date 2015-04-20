
#include <boost/contract/base_types.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/detail/lightweight_test.hpp>

struct A; struct AA;
struct X; struct XX;
struct U; struct UU;

template<class _1, class _2> struct a2;
template<class _1, class _2> struct x2;
template<class _1, class _2> struct u2;

struct a0;
struct x0;
struct u0;

int main() {
    typedef BOOST_CONTRACT_BASE_TYPES(
          public a2<A, AA>
        , private b2<B, BB>
        , protected c2<C, CC>
        
        , virtual public x2<X, XX>
        , virtual private y2<Y, YY>
        , virtual protected z2<Z, ZZ>
        
        , public virtual u2<U, UU>
        , private virtual v2<V, VV>
        , protected virtual w2<W, WW>
    ) base_types2;
    BOOST_TEST((boost::is_same<base_types2,
        boost::mpl::vector<a2<A, AA>, x2<X, XX>, u2<U, UU> >
    >::value));

    typedef BOOST_CONTRACT_BASE_TYPES(
          private b1<B>
        , protected c1<C>
        
        , virtual private y1<Y>
        , virtual protected z1<Z>
        
        , private virtual v1<V>
        , protected virtual w1<W>
    ) base_types1;
    BOOST_TEST((boost::is_same<base_types1,
        boost::mpl::vector<>
    >::value));

    typedef BOOST_CONTRACT_BASE_TYPES(
          public a0
        , virtual public x0
        , public virtual u0
    ) base_types0;
    BOOST_TEST((boost::is_same<base_types0,
        boost::mpl::vector<a0, x0, u0>
    >::value));

    return boost::report_errors();
}

