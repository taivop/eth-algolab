#include <iostream>
#include <vector>
#include <iterator>

#include <boost/config.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/tuple/tuple.hpp>	// tuples::ignore
#include <boost/graph/biconnected_components.hpp>


using namespace std;
using namespace boost;


// Undirected graph with int weights on edges.
typedef	adjacency_list<vecS, vecS, undirectedS,
			property<vertex_degree_t, int>,
			no_property >	Graph;

typedef graph_traits<Graph>::vertex_descriptor Vertex;
typedef	graph_traits<Graph>::edge_descriptor	Edge;	// Edge type
typedef graph_traits<Graph>::edge_iterator	EdgeIt;		// Iterator
typedef property_map<Graph, vertex_degree_t>::type DegreeMap;
typedef graph_traits<Graph>::out_edge_iterator OutEdgeIt;


void test_case() {
	int n, m;
	cin >> n >> m;				// <number_of_nodes> <number_of_edges>

	Graph G(n);
	DegreeMap degree = get(vertex_degree, G);

	for(int i=0; i<m; i++) {
		int n1, n2;
		cin >> n1 >> n2;	// <start_node> <end_node>

		Edge e;
		tie(e, tuples::ignore) = add_edge(n1, n2, G);

		degree[n1] += 1;
		degree[n2] += 1;
	}

	// Find articulation points in graph
	vector<Vertex> art_points;
	articulation_points(G, back_inserter(art_points));

	for(auto u_it=art_points.begin(); u_it != art_points.end(); u_it++) {
		Vertex u = *u_it;
		cout << u << endl;

		// Iterate over all edges of current articulation point
		OutEdgeIt eit, eend;
		for (tie(eit, eend) = out_edges(u, G); eit != eend; ++eit) {
			int v = target(*eit, G);

			// If the other vertex is leaf or an articulation point itself
			if(degree[v] == 1)
				cout << u << " -> "<< v << endl;
		}

	}
	
}

int main(void) {
	std::ios_base::sync_with_stdio(false);
	
	int t;
	cin >> t;

	for(int i=0; i<t; i++)
		test_case();

	return 0;
}