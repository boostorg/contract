
#ifndef BOOST_CONTRACT_CALL_IF_HPP_
#define BOOST_CONTRACT_CALL_IF_HPP_

#include <boost/utility/result_of.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>

// TODO: Once I get this to work 100% right... then consider using it instead
// of the extra mpl::bool_ param inside the lib impl too.

namespace boost { namespace contract {

namespace call_if_ {
    // Result must be copy constructible (always true for func. result types).

    template< bool Cond, typename Result >
    struct call_if_c {
        template< typename Then >
        explicit call_if_c ( Then const& t ) :
                result_(boost::make_shared<Result>(t())) {}

        operator Result ( ) const { return *result_; }

        template< typename Else >
        Result else_ ( Else const& ) const { return *result_; }

    private:
        // Pointer so copies of this object do not keep copying result (above
        // operator() already returns new copies of result to users).
        boost::shared_ptr<Result> const result_;
    };
    
    template< typename Result >
    struct call_if_c<false, Result> {
        template< typename Then >
        explicit call_if_c ( Then const& ) {}

        // Result must be default constructible when else_ is not used.
        operator Result ( ) { return Result(); }

        template< typename Else >
        Result else_ ( Else const& e ) const { return e(); } 
    };

    // Specializations (optimized) for void result type.
    
    template< >
    struct call_if_c<true, void> {
        template< typename Then >
        explicit call_if_c ( Then const& t ) { t(); }

        template< typename Else >
        void else_ ( Else const& ) const {}
    };

    template< >
    struct call_if_c<false, void> {
        template< typename Then >
        explicit call_if_c ( Then const& ) {}

        template< typename Else >
        void else_ ( Else const& e ) const { e(); } 
    };
}

template< bool Cond, typename Result, typename Then >
call_if_::call_if_c<Cond, Result> call_if_c ( Then const& t ) {
    return call_if_::call_if_c<Cond, Result>(t);
}

template< bool Cond, typename Then >
call_if_::call_if_c<Cond, typename boost::result_of<Then>::type> call_if_c (
        Then const& t ) {
    return call_if_::call_if_c<Cond, typename
            boost::result_of<Then>::type>(t);
}

template< class Cond, typename Result, typename Then >
call_if_::call_if_c<Cond::value, Result> call_if ( Then const& t ) {
    return call_if_::call_if_c<Cond::value, Result>(t);
}

template< class Cond, typename Then >
call_if_::call_if_c<Cond::value, typename boost::result_of<Then>::type> call_if(
        Then const& t ) {
    return call_if_::call_if_c<Cond::value,
            typename boost::result_of<Then>::type>(t);
}

} } // namespace

#endif // #include guard

