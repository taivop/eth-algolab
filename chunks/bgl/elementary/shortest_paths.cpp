#include <iostream>
#include <vector>
#include <limits.h>
#include <boost/tuple/tuple.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <boost/graph/johnson_all_pairs_shortest.hpp>

using namespace std;
using namespace boost;

typedef adjacency_list<vecS, vecS, directedS,
						no_property, property<edge_weight_t, int> >	Graph;
typedef property_map<Graph, edge_weight_t>::type WeightMap;
typedef graph_traits<Graph>::vertex_descriptor	Vertex;
typedef graph_traits<Graph>::edge_descriptor	Edge;   // Edge type
typedef graph_traits<Graph>::edge_iterator		EdgeIt; // Iterator

int main() {

	cout << "BGL ELEMENTARY GRAPH ALGORITHMS" << endl;

	const int NVERTICES = 8;
	const int NEDGES = 10;
	const int EDGES[NEDGES][2] = {{0, 1}, {0, 7}, {1, 2}, {2, 3}, {2, 7},
									{3, 4}, {3, 5}, {4, 5}, {6, 7}, {7, 6}};

	WeightMap wm;

	Graph G(NVERTICES);
	for(int i = 0; i < NEDGES; ++i) {
		Edge e;
		boost::tie(e, tuples::ignore) = add_edge(EDGES[i][0], EDGES[i][1], G);
		wm[e] = i % 4;
	}

	// Dijkstra

	int start_node = 0;
	vector<Vertex> predecessors(num_vertices(G));
	vector<int> distances(num_vertices(G));
	dijkstra_shortest_paths(G, start_node,
		predecessor_map(make_iterator_property_map(predecessors.begin(), get(vertex_index, G))).
  		distance_map(make_iterator_property_map(distances.begin(), get(vertex_index, G))));

	cout << "Dijkstra results:" << endl;
	for(int i=0; i<distances.size(); i++) {
		cout << "node " << i << " at distance " << distances[i] << endl;
	}
	cout << endl;


	// All pairs of shortest paths
	int johnson_distances[NVERTICES][NVERTICES] = {0};
	johnson_all_pairs_shortest_paths(G, johnson_distances);

	cout << "Distance matrix:" << endl;
	for(int i=0; i<NVERTICES; i++) {
		for(int j=0; j<NVERTICES; j++) {
			if(johnson_distances[i][j] == INT_MAX)
				cout << "- ";
			else
				cout << johnson_distances[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;





	// Print all edges with weights
	cout << "All edges with weights:" << endl;
	EdgeIt eit, eend;
	for(tie(eit, eend) = edges(G); eit != eend; ++eit) {
		cout << source(*eit, G) << "--" << target(*eit, G) << ":\t" << wm[*eit] << endl; 
	}

	return 0;
}
