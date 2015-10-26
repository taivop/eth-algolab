#include <iostream>
#include <vector>

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/push_relabel_max_flow.hpp>
#include <boost/tuple/tuple.hpp>	// tuples::ignore

using namespace std;
using namespace boost;


// Undirected graph with int weights on edges.
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

void test_case() {
	int n, m;
	cin >> n >> m;				// <number_of_nodes> <number_of_edges>

	//cout << "---- n=" << n << ", m=" << m << " ----" << endl;

	Graph G(n);
	EdgeCapacityMap	capacity = get(edge_capacity, G);
	ReverseEdgeMap	rev_edge = get(edge_reverse, G);
	ResidualCapacityMap	res_capacity = get(edge_residual_capacity, G);
	EdgeAdder ea(G,capacity, rev_edge);

	// Create existing point counts for players
	vector<int> score = vector<int>(n, 0);

	// Create all players
	vector<Vertex> player;
	for(int i=0; i<n; i++) {
		Vertex p = add_vertex(G);
		player.push_back(p);
	}

	// Create source and sink
	Vertex v_source = add_vertex(G);
	Vertex v_sink = add_vertex(G);

	for(int i=0; i<m; i++) { // Read all matches
		int a, b, c;
		cin >> a >> b >> c;

		if(c == 0) { // If result is not known
			Vertex p_a = player[a];
			Vertex p_b = player[b];

			Vertex match = add_vertex(G);

			// Source -> match
			ea.addEdge(v_source, match, 1);

			// Match -> players
			ea.addEdge(match, p_a, 1);
			ea.addEdge(match, p_b, 1);

		} else if(c == 1) {
			score[a] += 1;
		} else if(c == 2) {
			score[b] += 1;
		}
		

	}
	
	bool has_negative = false;
	long subtracting = 0;
	long sum_of_points = 0;

	for(int i=0; i<n; i++) { // Read all point counts
		int s;
		cin >> s;

		Vertex p = player[i];

		// Player -> sink
		ea.addEdge(p, v_sink, s - score[i]);
		subtracting += score[i];
		sum_of_points += s;

		// cout << "s=" << s << ", score=" << score[i] << endl;
		if(s - score[i] < 0) {
			has_negative = true;
		}
	}

	if(has_negative || sum_of_points != m) {
		cout << "no" << endl;
		return;
	}

	long flow = push_relabel_max_flow(G, v_source, v_sink);
	//cout << "Max flow found: " << flow << "+" << subtracting << "=" << flow+subtracting << ", number of matches=" << m << endl;

	if(flow + subtracting == m)
		cout << "yes" << endl;
	else
		cout << "no" << endl;

/*
	EdgeIt e, eend;
	for (tie(e, eend) = edges(G); e != eend; ++e) {
		// e is an iterator, *e is a descriptor.
		Vertex u = source(*e, G), v = target(*e, G);
		cout << "Edge (" << u << "," << v << ") has residual capacity " 
			 << res_capacity[*e] << " and initial capacity "
			 << capacity[*e] << "." << endl;
	}*/

	return;
}

int main(void) {
	std::ios_base::sync_with_stdio(false);
	
	int t;
	cin >> t;

	for(int i=0; i<t; i++)
		test_case();

	return 0;
}