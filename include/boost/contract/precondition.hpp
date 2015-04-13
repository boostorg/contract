
#ifndef BOOST_CONTRACT_PRECONDITION_HPP_
#define BOOST_CONTRACT_PRECONDITION_HPP_

namespace boost { namespace contract {

template<class Class>
struct precondition {
    template<typename Precondition>
    explicit preconfition(Precondition const& f) { f(); }
};

} } // namespace

#endif // #include guard

