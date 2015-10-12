#include <iostream>
#include <vector>

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/kruskal_min_spanning_tree.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <boost/tuple/tuple.hpp>	// tuples::ignore

using namespace std;
using namespace boost;


// Undirected graph with int weights on edges.
typedef	adjacency_list<vecS, vecS, undirectedS,
		no_property,
		property<edge_weight_t, int> >	Graph;

typedef	graph_traits<Graph>::edge_descriptor	Edge;	// Edge type
typedef graph_traits<Graph>::edge_iterator	EdgeIt;		// Iterator

// Map edge -> weight.
typedef	property_map<Graph, edge_weight_t>::type	WeightMap;

void test_case() {
	int n, m;
	cin >> n >> m;				// <number_of_nodes> <number_of_edges>

	Graph G(n);
	WeightMap wm = get(edge_weight, G);

	for(int i=0; i<m; i++) {
		int n1, n2, w;
		cin >> n1 >> n2 >> w;	// <start_node> <end_node> <weight>

		Edge e;
		tie(e, tuples::ignore) = add_edge(n1, n2, G);
		wm[e] = w;
	}

	vector<Edge> mst;			// vector to store MST
	kruskal_minimum_spanning_tree(G, back_inserter(mst));

	int sum = 0;
	// Sum weights of MST
	for(vector<Edge>::iterator it=mst.begin(); it != mst.end(); it++) {
		Edge e = *it;
		sum += wm[e];
	}

	// Maximum distance from node 0
	//Compute shortes t-u path in G_T
	vector<int> dist(n);
	vector<int> pred(n);
	int tgt = 0;
	dijkstra_shortest_paths(G, tgt,
	    predecessor_map(make_iterator_property_map(pred.begin(), get(vertex_index, G))).
	    distance_map(make_iterator_property_map(dist.begin(), get(vertex_index, G))));


	int max_distance = 0;
	for(int i=0; i<n; i++) {
		if(dist[i] > max_distance)
			max_distance = dist[i];
		//cout << pred[i] << " " << dist[i] << endl;
	}

	cout << sum << " " << max_distance << endl;
	
}

int main(void) {
	std::ios_base::sync_with_stdio(false);
	
	int t;
	cin >> t;

	for(int i=0; i<t; i++)
		test_case();

	return 0;
}