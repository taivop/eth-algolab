#include <iostream>
#include <vector>

#include <boost/graph/adjacency_list.hpp>
#include <boost/tuple/tuple.hpp>	// tuples::ignore

using namespace std;
using namespace boost;


// Undirected graph with int weights on edges.
typedef	adjacency_list_traits<vecS, vecS, directedS> Traits;
typedef adjacency_list<vecS, vecS, directedS, no_property,
	property<edge_weight_t, long> >						Graph;
typedef	property_map<Graph, edge_capacity_t>::type		WeightMap;
typedef	graph_traits<Graph>::vertex_descriptor			Vertex;
typedef	graph_traits<Graph>::edge_descriptor			Edge;
typedef graph_traits<Graph>::edge_iterator	EdgeIt;	// Iterator

void test_case() {
	int n, i;
	cin >> n >> i;

	//cout << "---- n=" << n << ", m=" << m << ", s=" << s << " ----" << endl;

	Graph G(n);
	WeightMap	wm = get(edge_weight, G);



	EdgeIt e, eend;
	/*for (tie(e, eend) = edges(G); e != eend; ++e) {
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