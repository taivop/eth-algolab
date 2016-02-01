#include <iostream>
#include <vector>
#include <boost/tuple/tuple.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/kruskal_min_spanning_tree.hpp>
#include <boost/graph/connected_components.hpp>

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
		wm[e] = 1;		// All weights are equal
	}

	// MST
	vector<Edge> mst;
	kruskal_minimum_spanning_tree(G, back_inserter(mst));

	cout << "All edges of the minimum spanning tree:" << endl;
	for(auto it=mst.begin(); it != mst.end(); it++) {
		cout << *it << endl;
	}
	cout << endl;

	// Connected components
	vector<int> scc(NVERTICES);
	int nscc = connected_components(G, make_iterator_property_map(
		scc.begin(), get(vertex_index, G)));

	cout << "There are " << nscc << " connected components:" << endl;

	for(int i=0; i<scc.size(); i++)
		cout << "node " << i << ": component " << scc[i] << endl;







	// Print all edges
	EdgeIt eit, eend;
	for(tie(eit, eend) = edges(G); eit != eend; ++eit) {
		cout << source(*eit, G) << "--" << target(*eit, G) << endl;
	}

	return 0;
}
