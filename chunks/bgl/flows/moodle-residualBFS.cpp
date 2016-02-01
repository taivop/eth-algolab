#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/push_relabel_max_flow.hpp>
#include <boost/tuple/tuple.hpp>

using namespace std;
using namespace boost;

// Graph typedefs
typedef	adjacency_list_traits<vecS, vecS, directedS>	Traits;
typedef adjacency_list<vecS, vecS, directedS, no_property,
	property<edge_capacity_t, int,
		property<edge_residual_capacity_t, int,
			property<edge_reverse_t, Traits::edge_descriptor> > > >	Graph;
typedef	graph_traits<Graph>::edge_descriptor			Edge;
typedef graph_traits<Graph>::vertex_descriptor			Vertex;
typedef	graph_traits<Graph>::out_edge_iterator			OutEdgeIt;
typedef property_map<Graph, edge_capacity_t>::type		EdgeCapacityMap;
typedef	property_map<Graph, edge_residual_capacity_t>::type	ResidualCapacityMap;
typedef	property_map<Graph, edge_reverse_t>::type		ReverseEdgeMap;

// Custom Add Edge for flow problems
void addEdge(int from, int to, int c, EdgeCapacityMap &capacity, ReverseEdgeMap &rev_edge, Graph &G) {
	Edge e, reverseE;
	tie(e, tuples::ignore)		= add_edge(from, to, G);
	tie(reverseE, tuples::ignore)	= add_edge(to, from, G);
	capacity[e]		= c;
	capacity[reverseE]	= 0;
	rev_edge[e]		= reverseE;
	rev_edge[reverseE]	= e;
}

// Main
int main() {
	// build Graph
	Graph G(6);
	EdgeCapacityMap		capacity = get(edge_capacity, G);
	ReverseEdgeMap		rev_edge = get(edge_reverse, G);
	ResidualCapacityMap	residue = get(edge_residual_capacity, G);

	Vertex source = 0;
	Vertex sink = 5;

	// add edges
	addEdge(source, 1, 5, capacity, rev_edge, G);
	addEdge(1, 2, 3, capacity, rev_edge, G);
	addEdge(1, 3, 2, capacity, rev_edge, G);
	addEdge(2, 3, 1, capacity, rev_edge, G);
	addEdge(2, 4, 2, capacity, rev_edge, G);
	addEdge(3, 4, 2, capacity, rev_edge, G);
	addEdge(4, sink, 4, capacity, rev_edge, G);

	// Find a min cut via maxflow
	push_relabel_max_flow(G, source, sink);
	// BFS to find vertex set S
	vector<int> vis(6, false);
	vis[0] = true;
	std::queue<int> Q;
	Q.push(0);
	while (!Q.empty()) {
		const int u = Q.front();
		Q.pop();
		OutEdgeIt ebeg, eend;
		for (tie(ebeg, eend) = out_edges(u, G); ebeg != eend; ++ebeg) {
			const int v = target(*ebeg, G);
			if (residue[*ebeg] == 0 || vis[v]) continue;
			vis[v] = true;
			Q.push(v);
		}
	}

	// Output S
	for (int i = 0; i < 6; ++i) {
		if (vis[i]) cout << i << " ";
	}
	cout << endl;

	return 0;
}
