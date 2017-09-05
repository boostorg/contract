
// Copyright (C) 2008-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://sourceforge.net/projects/contractpp

#ifndef CONTRACT_COPY_HPP_
#define CONTRACT_COPY_HPP_

/** @file
@brief Copy result value and old values for postconditions (this header is
automatically included by <c>contract.hpp</c>).
*/

#include <boost/type_traits/add_const.hpp>
#include <boost/type_traits/add_reference.hpp>
#include <boost/noncopyable.hpp>

namespace contract {

/**
@brief Copy result value and old values for postconditions.

The default implementation of his class template can copy values of any type
that is <c>ConstantCopyConstructible</c> which is of any type <c>T</c> that has
a constant-correct copy constructor of the form:

@code
    T::T( T const& source ) ;
@endcode

@Params
@Param{T,
The type of the value to copy (it is either the result type of the type of an
old-of expression).
}
@EndParams

Programmers can specialize this class template to copy a specific type
differently (and even for types that are not <c>ConstantCopyConstructible</c>,
or not <c>CopyConstructible</c> at all).

@Warning When specializing this class template, programmers must make sure that
their code is constant-correct otherwise the contracts will no longer be
constant-correct.

@SeeAlso @RefSect{advanced_topics, Advanced Topics} section.
*/
template< typename T >
class copy : private boost::noncopyable {
public:
    typedef typename boost::add_reference<typename boost::add_const<
            T>::type>::type const_reference_type;

    /**
    @brief Construct this object copying the specified value assuming <c>T</c>
    has a constant-correct copy constructor.
    */
    explicit copy ( const_reference_type value )
        : value_(value) // Copy here using T's const-correct copy constructor.
    {}

    /**
    @brief Return a constant reference to the copied value.
    */
    const_reference_type value ( void ) const { return value_; }

private:
    // Hold by value (not by reference) to make actual copy.
    typename boost::add_const<T>::type value_;
};

} // namespace contract

#endif // #include guard

