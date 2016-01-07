#include <boost/graph/graph_traits.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/undirected_graph.hpp>
#include <boost/graph/bellman_ford_shortest_paths.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <boost/graph/astar_search.hpp>
#include <fstream>
#include <iostream>


namespace {
namespace local {

// REF [file] >> ${BOOST_HOME}/libs/graph/example/dijkstra-example.cpp
void dijkstra_example()
{
	typedef boost::adjacency_list<boost::listS, boost::vecS, boost::directedS, boost::no_property, boost::property<boost::edge_weight_t, int> > graph_type;
	typedef boost::graph_traits<graph_type>::vertex_descriptor vertex_descriptor_type;
	typedef boost::graph_traits<graph_type>::edge_descriptor edge_descriptor_type;
	typedef std::pair<int, int> edge_type;

	enum nodes { A, B, C, D, E };

	const int num_nodes = 5;
	const char name[] = "ABCDE";

	const edge_type edge_array[] = { edge_type(A, C), edge_type(B, B), edge_type(B, D), edge_type(B, E), edge_type(C, B), edge_type(C, D), edge_type(D, E), edge_type(E, A), edge_type(E, B) };
	const int edge_weights[] = { 1, 2, 1, 2, 7, 3, 1, 1, 1 };
	const int num_arcs = sizeof(edge_array) / sizeof(edge_type);

#if defined(BOOST_MSVC) && BOOST_MSVC <= 1300
	graph_type g(num_nodes);
	boost::property_map<graph_type, boost::edge_weight_t>::type weightmap = boost::get(boost::edge_weight, g);
	for (std::size_t j = 0; j < num_arcs; ++j)
	{
		edge_descriptor_type e;
		bool inserted;
		boost::tie(e, inserted) = boost::add_edge(edge_array[j].first, edge_array[j].second, g);
		weightmap[e] = edge_weights[j];
	}
#else
	graph_type g(edge_array, edge_array + num_arcs, edge_weights, num_nodes);
	boost::property_map<graph_type, boost::edge_weight_t>::type weightmap = boost::get(boost::edge_weight, g);
#endif

	std::vector<vertex_descriptor_type> p(boost::num_vertices(g));
	std::vector<int> d(boost::num_vertices(g));
	vertex_descriptor_type s = boost::vertex(A, g);

#if defined(BOOST_MSVC) && BOOST_MSVC <= 1300
	// VC++ has trouble with the named parameters mechanism
	boost::property_map<graph_type, boost::vertex_index_t>::type indexmap = boost::get(boost::vertex_index, g);
	boost::dijkstra_shortest_paths(
		g, s, &p[0], &d[0], weightmap, indexmap,
		std::less<int>(), boost::closed_plus<int>(),
		(std::numeric_limits<int>::max)(), 0,
		boost::default_dijkstra_visitor()
	);
#else
	//boost::dijkstra_shortest_paths(g, s, boost::predecessor_map(&p[0]).distance_map(&d[0]));
	boost::dijkstra_shortest_paths(g, s, boost::predecessor_map(boost::make_iterator_property_map(p.begin(), boost::get(boost::vertex_index, g))).distance_map(boost::make_iterator_property_map(d.begin(), boost::get(boost::vertex_index, g))));
#endif

	std::cout << "distances and parents: " << std::endl;
	boost::graph_traits<graph_type>::vertex_iterator vi, vend;
	for (boost::tie(vi, vend) = boost::vertices(g); vi != vend; ++vi)
	{
		std::cout << "distance(" << name[*vi] << ") = " << d[*vi] << ", ";
		std::cout << "parent(" << name[*vi] << ") = " << name[p[*vi]] << std::endl;
	}
	std::cout << std::endl;

	//
	std::ofstream dot_file("data/boost/dijkstra-eg.dot");
	if (dot_file.is_open())
	{
		dot_file << "digraph D {\n"
			<< "  rankdir=LR\n"
			<< "  size=\"4,3\"\n"
			<< "  ratio=\"fill\"\n"
			<< "  edge[style=\"bold\"]\n"
			<< "  node[shape=\"circle\"]\n";

		boost::graph_traits<graph_type>::edge_iterator ei, ei_end;
		for (boost::tie(ei, ei_end) = boost::edges(g); ei != ei_end; ++ei)
		{
			edge_descriptor_type e = *ei;
			vertex_descriptor_type u = boost::source(e, g), v = boost::target(e, g);

			dot_file << "  " << name[u] << " -> " << name[v] << "[label=\"" << boost::get(weightmap, e) << "\"";
			if (p[v] == u)
				dot_file << ", color=\"black\"";
			else
				dot_file << ", color=\"grey\"";
			dot_file << "]" << std::endl;
		}
		dot_file << "}" << std::endl;
	}
}

template<class PredecessorMap>
class record_predecessors : public boost::default_dijkstra_visitor
{
public:
	record_predecessors(PredecessorMap p)
	: predecessor_(p)
	{}

	template<class Edge, class Graph>
	void edge_relaxed(Edge e, Graph &g)
	{
		// set the parent of the target(e) to source(e)
		boost::put(predecessor_, boost::target(e, g), boost::source(e, g));
	}

protected:
	PredecessorMap predecessor_;
};

template<class PredecessorMap>
record_predecessors<PredecessorMap> make_predecessor_recorder(PredecessorMap p)
{
	return record_predecessors<PredecessorMap>(p);
}

class custom_dijkstra_visitor : public boost::default_dijkstra_visitor
{
    template <class Edge, class Graph>
    void edge_relaxed(Edge e, Graph &g)
	{
		// do something
    }

    template <class Edge, class Graph>
    void edge_not_relaxed(Edge e, Graph &g)
	{
		// do something
    }
};

class custom_bellman_visitor : public boost::default_bellman_visitor
{
	template <class Edge, class Graph>
	void examine_edge(Edge u, Graph &g)
	{
		// do something
	}

	template <class Edge, class Graph>
	void edge_relaxed(Edge u, Graph &g)
	{
		// do something
	}

	template <class Edge, class Graph>
	void edge_not_relaxed(Edge u, Graph &g)
	{
		// do something
	}

	template <class Edge, class Graph>
	void edge_minimized(Edge u, Graph &g)
	{
		// do something
	}

	template <class Edge, class Graph>
	void edge_not_minimized(Edge u, Graph &g)
	{
		// do something
	}
};

class custom_astar_visitor : public boost::default_astar_visitor
{
	template <class Edge, class Graph>
	void edge_relaxed(Edge e, const Graph &g)
	{
		// do something
	}

	template <class Edge, class Graph>
	void edge_not_relaxed(Edge e, const Graph &g)
	{
		// do something
	}
};

}  // namespace local
}  // unnamed namespace

namespace boost_graph {

void shortest_paths()
{
	// Dijkstra's algorithm -----------------------------------------
	local::dijkstra_example();

	// Bellman-Ford algorithm -----------------------------------------
	// REF [file] >> ${BOOST_HOME}/libs/graph/example/bellman-example.cpp

	// REF [site] >> http://www.boost.org/doc/libs/1_59_0/libs/graph/doc/quick_tour.html
	// REF [site] >> http://library.developer.nokia.com/index.jsp?topic=/S60_5th_Edition_Cpp_Developers_Library/GUID-02F20077-73B5-4A63-85DB-D909E0ADE01C/html/con_graph_quick_tour.html
	{
		typedef boost::adjacency_list<boost::listS, boost::vecS, boost::directedS, boost::no_property, boost::property<boost::edge_weight_t, int> > graph_type;
		typedef boost::graph_traits<graph_type>::vertex_descriptor vertex_descriptor_type;
		typedef std::pair<int, int> edge_type;

		const int num_nodes = 5;
		const edge_type edges[] = { edge_type(0, 2), edge_type(1, 1), edge_type(1, 3), edge_type(1, 4), edge_type(2, 1), edge_type(2, 3), edge_type(3, 4), edge_type(4, 0), edge_type(4, 1) };
		const int edge_weights[] = { 1, 2, 1, 2, 7, 3, 1, 1, 1 };

		graph_type g(edges, edges + sizeof(edges) / sizeof(edge_type), edge_weights, num_nodes);

		// vector for storing distance property
		std::vector<int> d(boost::num_vertices(g));
		// get the first vertex
		vertex_descriptor_type s = *(boost::vertices(g).first);

		// invoke variant 2 of Dijkstra's algorithm
		//boost::dijkstra_shortest_paths(g, s, boost::distance_map(&d[0]));
		boost::dijkstra_shortest_paths(g, s, boost::distance_map(boost::make_iterator_property_map(d.begin(), boost::get(boost::vertex_index, g))));

		std::cout << "distances from start vertex:" << std::endl;
		boost::graph_traits<graph_type>::vertex_iterator vi;
		for (vi = boost::vertices(g).first; vi != boost::vertices(g).second; ++vi)
			std::cout << "distance(" << *vi << ") = " << d[*vi] << std::endl;
		std::cout << std::endl;

		//
		std::vector<vertex_descriptor_type> p(boost::num_vertices(g), boost::graph_traits<graph_type>::null_vertex());  // the predecessor array
		//boost::dijkstra_shortest_paths(g, s, boost::distance_map(&d[0]).visitor(make_predecessor_recorder(&p[0])));
		boost::dijkstra_shortest_paths(g, s, boost::distance_map(boost::make_iterator_property_map(d.begin(), boost::get(boost::vertex_index, g))).visitor(local::make_predecessor_recorder(&p[0])));

		std::cout << "parents in the tree of shortest paths:" << std::endl;
		for (vi = boost::vertices(g).first; vi != boost::vertices(g).second; ++vi)
		{
			std::cout << "parent(" << *vi;
			//if (p[*vi] == vertex_descriptor_type() && *vi == s)
			if (p[*vi] == boost::graph_traits<graph_type>::null_vertex())  // not working
				std::cout << ") = no parent" << std::endl;
			else
				std::cout << ") = " << p[*vi] << std::endl;
		}
	}
}

}  // namespace boost_graph
