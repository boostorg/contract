
// Copyright (C) 2008-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://sourceforge.net/projects/contractpp

#include <contract.hpp>
#include <boost/concept_check.hpp>
#include <boost/detail/lightweight_test.hpp>
#include <map>
#include <utility>

template< typename Key, typename T >
struct sizeable
{
    public: typedef typename std::map<Key, T>::size_type size_type;
    public: static size_type const max_size = 100;
    public: virtual size_type size( void ) const = 0;
};

//[macro_commas_symbols_integral_map
CONTRACT_CLASS(
    template(
        typename Key,
        typename T, // Commas in following template params.
        class Allocator,
                default (::std::allocator<std::pair<Key const, T> >),
        (typename ::std::map<int, T>::key_type) default_key,
                default (-1)
    ) requires( (boost::Convertible<Key, int>) ) // Commas in concepts.
    class (integral_map)
        extends( public (::sizeable<Key, T>) ) // Commas in bases.
) {
    CONTRACT_CLASS_INVARIANT_TPL( // Commas in class invariants.
        (::sizeable<Key, T>::max_size) >= size()
    )

    public: typedef typename std::map<Key, T, std::less<Key>, Allocator>::
            iterator iterator;

    CONTRACT_FUNCTION_TPL(
        public template( typename OtherKey, typename OtherT )
            requires(
                (::boost::Convertible<OtherKey, Key>),
                (::boost::Convertible<OtherT, T>)
            )
        (::std::pair<iterator, bool>) (insert) ( // Commas in result and params.
                (::std::pair<OtherKey, OtherT> const&) other_value,
                        default (::std::pair<Key, T>(default_key, T()))
            ) throw( (::std::pair<Key, T>) ) // Commas in exception specs.
            precondition( // Leading symbols in preconditions (same for commas).
                ((!full())) // LIMITATION: Two sets `((...))` (otherwise seq.).
            )
            postcondition( // Commas in postconditions.
                auto result = return,
                (typename sizeable<OtherKey, OtherT>::size_type)
                        old_other_size = CONTRACT_OLDOF
                                (size<OtherKey, OtherT>()),
                (::sizeable<Key, T>::max_size) >= size(),
                size() == old_other_size + (result.second ? 1 : 0)
            )
    ) {
        // ...
//]
        std::pair<Key, T> value(other_value.first, other_value.second);
        std::pair<iterator, bool> result = map_.insert(value);
        if(size() > sizeable<Key, T>::max_size) throw value;
        return result;
    }
                
    public: bool full ( void ) const
        { return size() == sizeable<Key, T>::max_size; }
    
    public: typename sizeable<Key, T>::size_type size ( void ) const
        { return map_.size(); }
    
    public: template< typename OtherKey, typename OtherT >
    typename sizeable<OtherKey, OtherT>::size_type size ( void ) const
        { return map_.size(); }
    
    public: T& operator[] ( Key const& key ) { return map_[key]; }

    private: std::map<Key, T, std::less<Key>, Allocator> map_;
};

int main ( void )
{
    integral_map<char, int> m;
    m.insert(std::make_pair(123, 'a'));
    BOOST_TEST(m[char(123)] == int('a'));
    m.insert<char, int>();
    BOOST_TEST(m[char(-1)] == int());
    
    // Test an implementation detail.
    BOOST_TEST(CONTRACT_DETAIL_PP_IS_VARIADIC( (std::pair<char, int>) ) == 1);
    BOOST_TEST(CONTRACT_DETAIL_PP_IS_VARIADIC( (std::pair<char, int>) p) == 1);
    BOOST_TEST(CONTRACT_DETAIL_PP_IS_VARIADIC( false ) == 1);
    BOOST_TEST(CONTRACT_DETAIL_PP_IS_VARIADIC( (!false) ) == 0); // Sequence.
    
    return boost::report_errors();
}

