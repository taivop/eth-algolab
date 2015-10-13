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
	int t, e, s, a, b;
	cin >> t >> e >> s >> a >> b;				// <number_of_nodes> <number_of_edges>

	Graph G(t);
	WeightMap wm = get(edge_weight, G);

	for(int i=0; i<e; i++) {
		int t1, t2, w;
		cin >> t1 >> t2;	// <start_node> <end_node>

		//cout << "Adding edge: " << t1 << "--" << t2 << ", ";
		int min_weight = 10001;
		for(int j=0; j<s; j++) {
			cin >> w;
			//cout << " " << w;

			if(w < min_weight) {
				//cout << "<" << min_weight;
				min_weight = w;
			}
		}

		//cout << "w=" << min_weight << endl;

		Edge e;
		tie(e, tuples::ignore) = add_edge(t1, t2, G);
		wm[e] = min_weight;
	}

	// Read in hive locations
	int asd;
	for(int i=0; i<s; i++)
		cin >> asd;

	// Get shortest path from start node
	//Compute shortes t-u path in G_T
	vector<int> dist(t);
	vector<int> pred(t);
	int tgt = b;
	dijkstra_shortest_paths(G, tgt,
	    predecessor_map(make_iterator_property_map(pred.begin(), get(vertex_index, G))).
	    distance_map(make_iterator_property_map(dist.begin(), get(vertex_index, G))));

	/*int dst = a;
	int src = pred[a];
	while(dst != b) {
		cout << src << "--" << dst << ", distance " << dist[dst] << endl;
		dst = src;
		src = pred[dst];
	}

	for(int i=0; i<dist.size(); i++) {
		if(pred[i] == a)
			cout << "!!! " << i << ", distance " << dist[i] << endl;
		else
			cout << i << "--" << b << ", distance " << dist[i] << endl;
	}*/

	// Q: Why do we even need the hive locations?
	// A: Because each hive network is an MST of the graph with the limitation that the hive is on this MST.
	

	// Go through each MST and find m, the minimum path on that MST. Then find min(m) which is the answer. Constant time.

	cout << dist[a] << endl;
	
}

int main(void) {
	std::ios_base::sync_with_stdio(false);
	
	int t;
	cin >> t;

	for(int i=0; i<t; i++) {
		//cout << "---- TEST CASE " << i << " ----" << endl;
		test_case();
	}

	return 0;
}