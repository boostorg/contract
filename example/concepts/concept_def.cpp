
// Copyright (C) 2008-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://sourceforge.net/projects/contractpp

//[concept_def
CONTRACT_CONCEPT(
    concept (ArithmeticLike) ( typename T )
        extends(
            Regular<T>,
            LessThanComparable<T>,
            HasUnaryPlus<T>,
            HasNegate<T>,
            (HasPlus<T, T>),
            (HasMinus<T, T>)
            // ...
        )
    (
        explicit constructor(T, T) ( intmax_t),
        explicit constructor(T, T) ( uintmax_t ),
        explicit constructor(T, T) ( long double ),

        requires (Convertible<typename HasUnaryPlus<T>::result_type, T>)
        // ...
    )
)

CONTRACT_CONCEPT(
    auto concept (HasFind) ( typename T )
    (
        typename key_type, as typename T::key_type,
        typename mapped_type,

        (std::pair<key_type, mapped_type>) (find) ( T const&, key_type const& )
    )
)

CONTRACT_CONCEPT(
    auto concept (HasDereference) ( typename T )
    (
        typename result_type,

        (result_type) operator(*)(deref) ( T& ),
        (result_type) operator(*)(deref) ( T&& )
    )
)

CONTRACT_CONCEPT(
    auto concept (IdentityOf) ( typename T )
    (
        typename type, as T,
        requires (SameType<type, T>)
    )
)

CONTRACT_CONCEPT(
    auto concept (MemberFunctionRequirements) ( typename T )
    (
        constructor(T, T) ( int a, float b ),
        destructor(T, ~T) ( void ),
        void member(T, f) ( void ) const
    )
)

CONTRACT_CONCEPT(
    auto concept (HasEqualTo) ( typename T, typename U )
    (
        bool operator(==)(equal) ( T const&, U const& )
    )
)

CONTRACT_CONCEPT(
    auto concept (ExplicitlyConvertible) ( typename T, typename U )
    (
        explicit operator(U)(U_type) ( T const& )
    )
)

CONTRACT_CONCEPT(
    auto concept (Convertible) ( typename T, typename U )
        extends( (ExplicitlyConvetible<T, U>) )
    (
        operator(U)(U_type) ( T const& )
    )
)

CONTRACT_CONCEPT(
    concept (True) ( bool Value )
    (
        void // Empty concept definition.
    )
)

CONTRACT_CONCEPT(
    concept_map (True) ( true )
    (
        void // Empty concept definition.
    )
)

CONTRACT_CONCEPT(
    auto concept (IsEven) ( intmax_t Value )
    (
        requires True<V % 2 == 0>
    )
)

CONTRACT_CONCEPT(
    auto concept (CopyConstructible) ( typename T )
        extends( MoveConstructible<T>, (Constructible<T, T const&>) )
    (
        axiom (CopyPreservation) ( (T) x )
        (
            T(x) == x;
        )
    )
)

CONTRACT_CONCEPT(
    concept (Iterator) ( typename X ) extends( Semiregular<X> )
    (
        typename(MoveConstructible) reference, as typename X::reference,
        typename(MoveConstructible) postinc_result,
        requires HasDereference<postinc_result>,

        (reference) operator(*)(deref) ( X& ),
        (reference) operator(*)(deref) ( X&& ),
        (X&) operator(++)(preinc) ( X& ),
        (postinc_result) operator(++)(postinc) ( X&, int )
    )
)

CONTRACT_CONCEPT(
    concept (RandomAccessIterator) ( typename X )
        extends( BidirectionalIterator<X>, LessThanComparable<X> )
    (
        typename(MoveConstructible) reference,
        requires (Convertible<reference, value_type const&>),

        (X&) operator(+=)(inc) ( X&, difference_type ),

        (X) operator(+)(add) ( (X const&) x, (difference_type) n )
        (
            X y(x);
            y += n;
            return y;
        ),

        (X) operator(+)(add) ( (difference_type) n, (X const&) x )
        (
            X y(x);
            y += n;
            return y;
        ),

        (X) operator(-=)(dec) ( X&, difference_type ),

        (X) operator(-)(sub) ( (X const&) x, (difference_type) n )
        (
            X y(x);
            y -= n;
            return y;
        ),

        (difference_type) operator(-)(sub) ( X const&, X const& ),

        (reference) operator([])(at) ( X const&, difference_type )
    )
)

CONTRACT_CONCEPT(
    template( typename(ObjectType) T )
    concept_map (RandomAccessIterator) ( T* )
    (
        typedef (T) value_type,
        typedef ptrdiff_t difference_type,
        typedef (T&) reference,
        typedef (T*) pointer
    )
)
//]

