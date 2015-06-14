
#ifndef BOOST_CONTRACT_CALL_IF_HPP_
#define BOOST_CONTRACT_CALL_IF_HPP_

#include <boost/contract/aux_/none.hpp>
#include <boost/make_shared.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/utility/result_of.hpp>
#include <boost/config.hpp>

/* PRIVATE */

// Boost.ResultOf not always able to deduce lambda result type (on MSVC).
#ifndef BOOST_NO_CXX11_DECL_TYPE
#   define BOOST_CONTRACT_CALL_IF_ENABLE_IF_UNARY_RESULT_OF_(F) \
        decltype(boost::declval<F>()())
#else
#   define BOOST_CONTRACT_CALL_IF_ENABLE_IF_UNARY_RESULT_OF_(F) \
        typename boost::result_of<F()>::type
#endif

/* CODE */

namespace boost { namespace contract {

template<bool Cond, typename Then, typename R = boost::contract::aux::none>
struct call_if_statement {}; // Empty so cannot be used.

// Dispatch true condition (then) between non-void and void calls.
// IMPORTANT: result_of<Then()> can be evaluated only when condition is already
// checked to be true (as Then() is required to be valid only in that case) so
// this extra level of dispatching is necessary to avoid compiler errors.
template<typename Then>
struct call_if_statement<true, Then, boost::contract::aux::none> :
    call_if_statement<true, Then,
            BOOST_CONTRACT_CALL_IF_ENABLE_IF_UNARY_RESULT_OF_(Then)>
{
    explicit call_if_statement(Then f) : call_if_statement<true, Then,
            BOOST_CONTRACT_CALL_IF_ENABLE_IF_UNARY_RESULT_OF_(Then)>(f) {}
};

// True condition (then) for non-void call.
template<typename Then, typename R>
struct call_if_statement<true, Then, R> { // Copyable as *.
    explicit call_if_statement(Then f) : r_(boost::make_shared<R>(f())) {}

    operator R() const { return *r_; }

    template<typename Else>
    R else_(Else const&) const { return *r_; }

    template<bool ElseIfCond, typename ElseIfThen>
    call_if_statement<true, Then, R> else_if_c(ElseIfThen const&) {
        return *this;
    }

    template<class ElseIfCond, typename ElseIfThen>
    call_if_statement<true, Then, R> else_if(ElseIfThen const&) {
        return *this;
    }
    
private:
    boost::shared_ptr<R> r_;
};

// True condition (then) for void call.
template<typename Then>
struct call_if_statement<true, Then, void> {
    explicit call_if_statement(Then f) { f(); }
    
    // Cannot provide `operator R()` here, because R is void.

    template<typename Else>
    void else_(Else const&) const {}
    
    template<bool ElseIfCond, typename ElseIfThen>
    call_if_statement<true, Then, void> else_if_c(ElseIfThen const&) {
        return *this;
    }

    template<class ElseIfCond, typename ElseIfThen>
    call_if_statement<true, Then, void> else_if(ElseIfThen const&) {
        return *this;
    }
};

// False condition (else) for both non-void and void calls.
template<typename Then>
struct call_if_statement<false, Then, boost::contract::aux::none> {
    explicit call_if_statement(Then const&) {}

    // Do not provide `operator result_type()` here, require else_ instead.

    // IMPORTANT: result_of<Else()> can be evaluated only when condition is
    // already checked to be false (as Else() is required to be valid only in
    // that case) so this is done lazily only in this template instantiation.
    template<typename Else>
    BOOST_CONTRACT_CALL_IF_ENABLE_IF_UNARY_RESULT_OF_(Else) else_(Else f)
            const {
        return f();
    }
    
    template<bool ElseIfCond, typename ElseIfThen>
    call_if_statement<ElseIfCond, ElseIfThen> else_if_c(ElseIfThen f) {
        return call_if_statement<ElseIfCond, ElseIfThen>(f);
    }
    
    template<class ElseIfCond, typename ElseIfThen>
    call_if_statement<ElseIfCond::value, ElseIfThen> else_if(ElseIfThen f) {
        return call_if_statement<ElseIfCond::value, ElseIfThen>(f);
    }
};

template<bool Cond, typename Then>
call_if_statement<Cond, Then> call_if_c(Then f) {
    return call_if_statement<Cond, Then>(f);
}

template<class Cond, typename Then>
call_if_statement<Cond::value, Then> call_if(Then f) {
    return call_if_statement<Cond::value, Then>(f);
}

} } // namespace

#endif // #include guard

