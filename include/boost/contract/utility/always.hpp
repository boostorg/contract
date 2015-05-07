
#ifndef BOOST_CONTRACT_ALWAYS_HPP_
#define BOOST_CONTRACT_ALWAYS_HPP_

#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>

namespace boost { namespace contract {

// Result must be copy constructible (always true for func. result types).
template< typename Result >
struct always {
    typedef Result result_type;

    explicit always ( Result const& result ) :
            result_(boost::make_shared<Result>(result)) {}

    // No matter if functor called with 0 to n args, it always returns result.
    Result operator() ( ... ) const { return *result_; }

private:
    // Pointer so copies of this object do not keep copying result (above
    // operator() already returns new copies for result to users).
    boost::shared_ptr<Result> const result_;
};

} } // namespace

#endif // #include guard

