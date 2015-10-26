#include <iostream>
#include <algorithm>
#include <vector>

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/edmonds_karp_max_flow.hpp>
#include <boost/tuple/tuple.hpp>

using namespace std;
using namespace boost;

typedef	adjacency_list_traits<vecS, vecS, directedS> Traits;
typedef adjacency_list<vecS, vecS, directedS, no_property,
	property<edge_capacity_t, long,
		property<edge_residual_capacity_t, long,
			property<edge_reverse_t, Traits::edge_descriptor> > > >	Graph;
typedef	property_map<Graph, edge_capacity_t>::type		EdgeCapacityMap;
typedef	property_map<Graph, edge_residual_capacity_t>::type	ResidualCapacityMap;
typedef	property_map<Graph, edge_reverse_t>::type		ReverseEdgeMap;
typedef	graph_traits<Graph>::vertex_descriptor			Vertex;
typedef	graph_traits<Graph>::edge_descriptor			Edge;
typedef graph_traits<Graph>::edge_iterator	EdgeIt;	// Iterator

// Custom EdgeAdder that encapsulates the references to the graph and its
// property maps and always creates reverse edges with corresponding capacities.
struct EdgeAdder {
	EdgeAdder(Graph & G, EdgeCapacityMap &capacity, ReverseEdgeMap &rev_edge) 
		: G(G), capacity(capacity), rev_edge(rev_edge) {}

	void addEdge(int u, int v, long c) {
		Edge e, reverseE;
		tie(e, tuples::ignore) = add_edge(u, v, G);
		tie(reverseE, tuples::ignore) = add_edge(v, u, G);
		capacity[e] = c;
		capacity[reverseE] = 0;
		rev_edge[e] = reverseE;
		rev_edge[reverseE] = e;
	}
	Graph &G;
	EdgeCapacityMap	&capacity;
	ReverseEdgeMap	&rev_edge;
};

int main() {
	// Create Graph and Maps
	Graph G(4);
	EdgeCapacityMap	capacity = get(edge_capacity, G);
	ReverseEdgeMap	rev_edge = get(edge_reverse, G);
	ResidualCapacityMap	res_capacity = get(edge_residual_capacity, G);
	EdgeAdder ea(G,capacity, rev_edge);

	// Add edges
	ea.addEdge(0, 1, 1);
	ea.addEdge(0, 3, 1);
	ea.addEdge(2, 1, 1);
	ea.addEdge(2, 3, 1);

	// Add source and sink
	Vertex _source = add_vertex(G);
	Vertex sink = add_vertex(G);
	ea.addEdge(_source, 0, 2);
	ea.addEdge(_source, 2, 1);
	ea.addEdge(1, sink, 2);
	ea.addEdge(3, sink, 1);

	// Calculate flow
	long flow1 = edmonds_karp_max_flow(G, _source, sink);
	cout << "Maximum Flow with the Edmonds-Karp Algorihtm: " << flow1 << endl;
	long flow2 = push_relabel_max_flow(G, _source, sink);
	cout << "Maximum Flow with the Push-Relabel Algorihtm: " << flow2 << endl;

	// Iterate over all edges and output the residual flow.
	EdgeIt e, eend;
	for (tie(e, eend) = edges(G); e != eend; ++e) {
		// e is an iterator, *e is a descriptor.
		Vertex u = source(*e, G), v = target(*e, G);
		cout << "Edge (" << u << "," << v << ") has residual capacity " 
			 << res_capacity[*e] << " and initial capacity "
			 << capacity[*e] << "." << endl;
	}
	return 0;
}
