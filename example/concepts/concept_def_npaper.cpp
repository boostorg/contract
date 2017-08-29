
// Copyright (C) 2008-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://sourceforge.net/projects/contractpp

//[concept_def_npaper
// Extra spaces, newlines, etc used to align text with this library code.
concept ArithmeticLike < typename T >
    :
        Regular<T>,
        LessThanComparable<T>,
        HasUnaryPlus<T>,
        HasNegate<T>,
        HasPlus<T, T>,
        HasMinus<T, T>
        // ...
    
{
    explicit T::T ( intmax_t ) ;
    explicit T::T ( uintmax_t ) ;
    explicit T::T ( long double ) ;

    requires Convertible<typename HasUnaryPlus<T>::result_type, T> ;
    // ...
}



auto concept HasFind < typename T >
{
    typename key_type = typename T::key_type ;
    typename mapped_type ;

    std::pair<key_type, mapped_type> find ( T const&, key_type const& ) ;
}



auto concept HasDereference < typename T >
{
    typename result_type ;

    result_type operator* ( T& ) ;
    result_type operator* ( T&& ) ;
}



auto concept IdentityOf < typename T >
{
    typename type = T ;
    requires SameType<type, T> ;
}



auto concept MemberFunctionRequirements < typename T >
{
    T::T ( int a, float b ) ;
    T::~T ( void ) ;
    void T::f ( void ) const ;
}



auto concept HasEqualTo < typename T, typename U >
{
    bool operator== ( T const&, U const& ) ;
}



auto concept ExplicitlyConvertible < typename T, typename U >
{
    explicit operator U ( T const& ) ;
}



auto concept Convertible < typename T, typename U >
    : ExplicitlyConvetible<T, U>
{
    operator U ( T const& ) ;
}



concept True < bool Value >
{
    // No operation.
}



concept_map True < true >
{
    // No operation.
}



auto concept IsEven < intmax_t Value >
{
    requires True<V % 2 == 0> ;
}



auto concept CopyConstructible < typename T >
    : MoveConstructible<T>, Constructible<T, T const&>
{
    axiom CopyPreservation ( T x )
    {
        T(x) == x;
    }
}



concept Iterator < typename X > : Semiregular<X>
{
    MoveConstructible reference = typename X::reference ;
    MoveConstructible postinc_result ;
    requires HasDereference<postinc_result> ;

    reference operator* ( X& ) ;
    reference operator* ( X&& ) ;
    X& operator++ ( X& ) ;
    postinc_result operator++ ( X&, int ) ;
}



concept RandomAccessIterator < typename X >
    : BidirectionalIterator<X>, LessThanComparable<X>
{
    MoveConstructible reference ;
    requires Convertible<reference, value_type const&> ;

    X& operator+= ( X&, difference_type ) ;

    X operator+ ( X const& x, difference_type n )
    {
        X y(x);
        y += n;
        return y;
    }

    X operator+ ( difference_type n, X const& x )
    {
        X y(x);
        x += n;
        return y;
    }

    X operator-= ( X&, difference_type ) ;

    X operator- ( X const& x, difference_type n )
    {
        X y(x);
        y -= n;
        return y;
    }

    difference_type operator- ( X const&, X const& ) ;

    reference operator[] ( X const&, difference_type ) ;
}



template< ObjectType T >
concept_map RandomAccessIterator < T* >
{
    typedef T value_type ;
    typedef ptrdiff_t difference_type ;
    typedef T& reference ;
    typedef T* pointer ;
}

//]

