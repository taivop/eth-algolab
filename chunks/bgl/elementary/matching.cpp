#include <iostream>
#include <vector>
#include <boost/tuple/tuple.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/max_cardinality_matching.hpp>

using namespace std;
using namespace boost;

typedef adjacency_list<vecS, vecS, undirectedS>	Graph;
typedef graph_traits<Graph>::vertex_descriptor	Vertex;
typedef graph_traits<Graph>::edge_descriptor	Edge;   // Edge type
typedef graph_traits<Graph>::edge_iterator		EdgeIt; // Iterator

int main() {

	cout << "BGL ELEMENTARY GRAPH ALGORITHMS" << endl;

	const int NVERTICES = 8;
	const int NEDGES = 10;
	const int EDGES[NEDGES][2] = {{0, 1}, {0, 7}, {1, 2}, {2, 3}, {2, 7},
									{3, 4}, {3, 5}, {4, 5}, {6, 7}};

	Graph G(NVERTICES);
	for(int i = 0; i < NEDGES; ++i) {
		Edge e;
		boost::tie(e, tuples::ignore) = add_edge(EDGES[i][0], EDGES[i][1], G);
	}

	vector<Vertex> mate(NVERTICES);
	edmonds_maximum_cardinality_matching(G, &mate[0]);

	for(int i=0; i<NVERTICES; i++) {
		cout << "node " << i << ", mate " << mate[i] << endl;
	}




	// Print all edges with weights
	cout << "All edges:" << endl;
	EdgeIt eit, eend;
	for(tie(eit, eend) = edges(G); eit != eend; ++eit) {
		cout << source(*eit, G) << "--" << target(*eit, G) << endl; 
	}

	return 0;
}
