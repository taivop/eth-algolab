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

	void addSymmetricEdge(int u, int v, long c) {
		Edge e, reverseE;
		tie(e, tuples::ignore) = add_edge(u, v, G);
		tie(reverseE, tuples::ignore) = add_edge(v, u, G);
		capacity[e] = c;
		capacity[reverseE] = c;
		rev_edge[e] = reverseE;
		rev_edge[reverseE] = e;
	}

	Graph &G;
	EdgeCapacityMap	&capacity;
	ReverseEdgeMap	&rev_edge;
};

void test_case() {
	int n, m, s;
	cin >> n >> m >> s;

	cout << "---- n=" << n << ", m=" << m << ", s=" << s << " ----" << endl;

	Graph G(n);
	EdgeCapacityMap	capacity = get(edge_capacity, G);
	ReverseEdgeMap	rev_edge = get(edge_reverse, G);
	ResidualCapacityMap	res_capacity = get(edge_residual_capacity, G);
	EdgeAdder ea(G,capacity, rev_edge);


	// Create all intersections
	vector<Vertex> intersection;
	for(int i=0; i<n; i++) {
		Vertex p = add_vertex(G);
		intersection.push_back(p);
		cout << "Adding intersection " << p << endl;
	}

	cout << "intersection.size() = " << intersection.size() << endl;

	// Create source and sink
	Vertex v_source = intersection[0];
	Vertex v_sink = add_vertex(G);

	// Read all stores
	for(int i=0; i<s; i++) {
		int loc;
		cin >> loc;

		// Store -> sink
		ea.addEdge(intersection[loc], v_sink, 1);
	}

	// Read all streets
	for(int i=0; i<m; i++) {
		int a, b;
		cin >> a >> b;

		cout << "Adding street " << intersection[a] << "->" << intersection[b] << endl;

		Vertex inters_a = intersection[a];
		Vertex inters_b = intersection[b];

		Vertex street = add_vertex(G);

		// Intersections
		ea.addSymmetricEdge(inters_a, inters_b, 1);		

	}

	long flow = push_relabel_max_flow(G, v_source, v_sink);
	cout << "Max flow found: " << flow << endl;

	if(flow == s)
		cout << "yes" << endl;
	else
		cout << "no" << endl;


	EdgeIt e, eend;
	for (tie(e, eend) = edges(G); e != eend; ++e) {
		// e is an iterator, *e is a descriptor.
		Vertex u = source(*e, G), v = target(*e, G);
		cout << "Edge (" << u << "," << v << ") has residual capacity " 
			 << res_capacity[*e] << " and initial capacity "
			 << capacity[*e] << "." << endl;
	}

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