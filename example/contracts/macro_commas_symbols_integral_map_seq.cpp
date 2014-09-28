
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

//[macro_commas_symbols_integral_map_seq
CONTRACT_CLASS(
    template(
        (typename Key)
        (typename T)
        (class Allocator)
                (default comma(1)(::std::allocator<std::pair<Key const, T> >))
        (comma(1)(typename ::std::map<int, T>::key_type) default_key)
                (default (-1))
    ) requires( (comma(1)(boost::Convertible<Key, int>)) )
    class (integral_map)
        extends( (public comma(1)(::sizeable<Key, T>)) )
) {
    CONTRACT_CLASS_INVARIANT_TPL(
        (((::sizeable<Key, T>::max_size)) >= size())
    )

    public: typedef typename std::map<Key, T, std::less<Key>, Allocator>::
            iterator iterator;

    CONTRACT_FUNCTION_TPL(
        public template( (typename OtherKey) (typename OtherT) )
            requires(
                (comma(1)(::boost::Convertible<OtherKey, Key>))
                (comma(1)(::boost::Convertible<OtherT, T>))
            )
        comma(1)(::std::pair<iterator, bool>) (insert) (
                (comma(1)(::std::pair<OtherKey, OtherT> const&) other_value)
                        (default comma(1)(::std::pair<Key,T>(default_key, T())))
            ) throw( (comma(1)(::std::pair<Key, T>)) )
            precondition(
                ((!full()))
            )
            postcondition(
                (auto result = return)
                (comma(1)(typename sizeable<OtherKey, OtherT>::size_type)
                        old_other_size = CONTRACT_OLDOF
                                (size<OtherKey, OtherT>()))
                (((::sizeable<Key, T>::max_size)) >= size())
                (size() == old_other_size + (result.second ? 1 : 0))
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
    return boost::report_errors();
}

