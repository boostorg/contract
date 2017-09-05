
// Copyright (C) 2008-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://sourceforge.net/projects/contractpp

#include <contract.hpp>
#include <boost/graph/adjacency_list.hpp> 
#include <boost/graph/depth_first_search.hpp>
#include <boost/graph/graph_traits.hpp> 
#include <boost/range/irange.hpp> 
#include <boost/pending/indirect_cmp.hpp> 
#include <boost/type_traits/is_convertible.hpp>
#include <boost/type_traits/is_integral.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/property_map/property_map.hpp>
#include <boost/property_map/shared_array_property_map.hpp>
#include <boost/mpl/and.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/detail/lightweight_test.hpp>

namespace graphs {

// Helpers.

template< typename G >
struct vertex_descriptor
{
    typedef typename boost::graph_traits<G>::vertex_descriptor type;
};

template< typename T >
struct is_incidence_and_vertex_list_graph :
    boost::mpl::and_<
          boost::is_convertible<
              typename boost::graph_traits<T>::traversal_category
            , boost::incidence_graph_tag
          >
        , boost::is_convertible<
              typename boost::graph_traits<T>::traversal_category
            , boost::vertex_list_graph_tag
          >
    >
{};

template< typename T, typename Key >
struct is_property_map_of_key :
    boost::is_same<Key, typename boost::property_traits<T>::key_type>
{};

template< typename T, typename Key >
struct is_integral_property_map_of_key :
    boost::mpl::and_<
          boost::is_integral<typename boost::property_traits<T>::value_type>
        , is_property_map_of_key<T, typename Key::type>
    >
{};

template< typename Size, typename IndexMap >
boost::shared_array_property_map<boost::default_color_type, IndexMap>
default_color_map ( Size const& num_vertices, IndexMap const& index_map )
{
    return boost::make_shared_array_property_map(num_vertices,
            boost::default_color_type(), index_map);
}

} // namespace

// Function with named parameters.

//[named_params_dfs_keywords
namespace graphs {

CONTRACT_PARAMETER(graph)
CONTRACT_PARAMETER(visitor)
CONTRACT_PARAMETER(root_vertex)
CONTRACT_PARAMETER(index_map)
CONTRACT_PARAMETER(color_map)

} // namespace
//]

//[named_params_dfs_decl
namespace graphs {

CONTRACT_FUNCTION(
    void (depth_first_search) (
            // Required parameter (no default value) with requirement predicate.
            in requires(is_incidence_and_vertex_list_graph<boost::mpl::_>)
                    graph,
            // Optional (default value) of any type (auto).
            in auto visitor, default boost::dfs_visitor<>(),
            // Exact type specified.
            in (vertex_descriptor<CONTRACT_PARAMETER_TYPEOF(graph)>)
                    root_vertex, default (*boost::vertices(graph).first),
            // Any type matching requirement predicate (unary meta-function).
            in requires(
                is_integral_property_map_of_key<
                      boost::mpl::_
                    , vertex_descriptor<CONTRACT_PARAMETER_TYPEOF(graph)>
                >
            ) index_map, default boost::get(boost::vertex_index, graph),
            // In-out parameter.
            in out requires(
                is_property_map_of_key<
                      boost::mpl::_
                    , vertex_descriptor<CONTRACT_PARAMETER_TYPEOF(graph)>
                >
            ) color_map, default default_color_map(boost::num_vertices(graph),
                    index_map)
        )
        // No `precondition(...)` or `postcondition(...)` in this example.
) {
    // Also function definition can use `PARAMETER_TYPEOF`.
    typedef CONTRACT_PARAMETER_TYPEOF(graph)& graph_ref; // Unused by example.
    boost::depth_first_search(graph, boost::visitor(visitor).
            color_map(color_map).root_vertex(root_vertex).
            vertex_index_map(index_map));
}  

} // namespace
//]

// Main program.

template< typename TimeMap >
class dfs_time_visitor : public boost::default_dfs_visitor
{
public:
    typedef typename boost::property_traits<TimeMap>::value_type T;

    dfs_time_visitor ( TimeMap dmap, TimeMap fmap, T& t )
        : dmap_(dmap), fmap_(fmap), time_(t)
    {}
    
    template< typename V, typename G >
    void discover_vertex ( V u, G const& g ) const { put(dmap_, u, time_++); }
    
    template< typename V, typename G >
    void finish_vertex ( V u, G const& g ) const { put(fmap_, u, time_++); }

private:
    TimeMap dmap_;
    TimeMap fmap_;
    T& time_;
};

int main ( void )
{ 
    typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS> G;
    typedef boost::graph_traits<G>::vertices_size_type size_type;

    enum {u, v, w, x, y, z, N};
    char names[] = {'u', 'v', 'w', 'x', 'y', 'z'};
    typedef std::pair<int, int> E;
    E edges[] = {E(u, v), E(u, x), E(x, v), E(y, x), E(v, y), E(w, y), E(w, z),
            E(z, z)};
    G g(edges, edges + sizeof(edges) / sizeof(E), N);

    std::vector<size_type> dtime(boost::num_vertices(g));
    std::vector<size_type> ftime(boost::num_vertices(g));
    size_type t = 0;
    dfs_time_visitor<size_type*> vis(&dtime[0], &ftime[0], t);

    //[named_params_dfs_call
    graphs::depth_first_search(graphs::visitor_ = vis, graphs::graph_ = g);
    //]

    std::vector<size_type> dorder(N);
    boost::integer_range<size_type> r(0, N);
    std::copy(r.begin(), r.end(), dorder.begin());
    std::sort(dorder.begin(), dorder.end(),
            boost::indirect_cmp<size_type*, std::less<size_type> >(&dtime[0]));
    BOOST_TEST(names[dorder[0]] == 'u');
    BOOST_TEST(names[dorder[1]] == 'v');
    BOOST_TEST(names[dorder[2]] == 'y');
    BOOST_TEST(names[dorder[3]] == 'x');
    BOOST_TEST(names[dorder[4]] == 'w');
    BOOST_TEST(names[dorder[5]] == 'z');

    std::vector<size_type> forder(N);
    std::copy(r.begin(), r.end(), forder.begin());
    std::sort(forder.begin(), forder.end(),
            boost::indirect_cmp<size_type*, std::less<size_type> >(&ftime[0]));
    BOOST_TEST(names[forder[0]] == 'x');
    BOOST_TEST(names[forder[1]] == 'y');
    BOOST_TEST(names[forder[2]] == 'v');
    BOOST_TEST(names[forder[3]] == 'u');
    BOOST_TEST(names[forder[4]] == 'z');
    BOOST_TEST(names[forder[5]] == 'w');
    return boost::report_errors();
} 
//]

