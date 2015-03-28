
#ifndef BOOST_CONTRACT_AUX_EVAL_HPP_
#define BOOST_CONTRACT_AUX_EVAL_HPP_

namespace boost { namespace contract { namespace aux {

// Used to force evaluation of expressions before a class is constructed:
//
//  struct x : private eval<x>, ... {
//      x ( ) : eval<x>((expr1, expr2, expr3, ...)), ... { ... }
//      ...
//  };
template< class Derived >
struct eval {
    eval ( ) {}

    template< typename Expr >
    explicit eval ( Expr const& ) {}
};

} } } // namespace

#endif // #include guard

