#include <iostream>
#include <vector>
#include <queue>
#include <boost/tuple/tuple.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/successive_shortest_path_nonnegative_weights.hpp>
#include <boost/graph/find_flow_cost.hpp>

using namespace std;
using namespace boost;

typedef adjacency_list_traits<vecS, vecS, directedS> Traits;
typedef adjacency_list<vecS, vecS, directedS, no_property,
    property<edge_capacity_t, long,
        property<edge_residual_capacity_t, long,
            property<edge_reverse_t, Traits::edge_descriptor,
            	property<edge_weight_t, long> > > > > Graph;
typedef property_map<Graph, edge_capacity_t>::type EdgeCapacityMap;
typedef property_map<Graph, edge_weight_t>::type EdgeWeightMap;
typedef property_map<Graph, edge_residual_capacity_t>::type ResidualCapacityMap;
typedef property_map<Graph, edge_reverse_t>::type ReverseEdgeMap;
typedef graph_traits<Graph>::out_edge_iterator OutEdgeIt;

typedef graph_traits<Graph>::vertex_descriptor	Vertex;
typedef graph_traits<Graph>::edge_descriptor	Edge;   // Edge type
typedef graph_traits<Graph>::edge_iterator		EdgeIt; // Iterator


void addEdge(int from, int to, long c, long w,
             EdgeCapacityMap &capacity, ReverseEdgeMap &rev_edge,
             EdgeWeightMap weight, Graph &G) {
     Edge e, reverseE;
     tie(e, tuples::ignore) = add_edge(from, to, G);
     tie(reverseE, tuples::ignore) = add_edge(to, from, G);
     capacity[e] = c;
     weight[e] = w;
     capacity[reverseE] = 0;
     weight[reverseE] = -w; // note the minus!
     rev_edge[e] = reverseE;
     rev_edge[reverseE] = e;
}

int main() {

	cout << "BGL MIN COST MAX FLOW" << endl;

	const int NVERTICES=7;
	const int v_source=0;
	const int v_farm1=1;
	const int v_farm2=2;
	const int v_farm3=3;
	const int v_shop1=4;
	const int v_shop2=5;
	const int v_target=6;


	Graph G(NVERTICES);
	EdgeWeightMap weight = get(edge_weight, G);
	EdgeCapacityMap capacity = get(edge_capacity, G);
	ReverseEdgeMap rev_edge = get(edge_reverse, G);
	ResidualCapacityMap res_capacity = get(edge_residual_capacity, G);

	addEdge(v_source, v_farm1, 3, 0, capacity, rev_edge, weight, G);
	addEdge(v_source, v_farm2, 1, 0, capacity, rev_edge, weight, G);
	addEdge(v_source, v_farm3, 2, 0, capacity, rev_edge, weight, G);

	addEdge(v_farm1, v_shop1, 1, 1, capacity, rev_edge, weight, G);
	addEdge(v_farm1, v_shop2, 1, 5, capacity, rev_edge, weight, G);
	addEdge(v_farm2, v_shop1, 1, 2, capacity, rev_edge, weight, G);
	addEdge(v_farm2, v_shop2, 1, 2, capacity, rev_edge, weight, G);
	addEdge(v_farm3, v_shop1, 1, 3, capacity, rev_edge, weight, G);
	addEdge(v_farm3, v_shop2, 2, 2, capacity, rev_edge, weight, G);

	addEdge(v_shop1, v_target, 3, 0, capacity, rev_edge, weight, G);
	addEdge(v_shop2, v_target, 3, 0, capacity, rev_edge, weight, G);

	successive_shortest_path_nonnegative_weights(G, v_source, v_target);

	int flow = 0;
	OutEdgeIt eit, eend;
	for(tie(eit, eend)=out_edges(vertex(v_source, G), G); eit != eend; ++eit) {
		flow += capacity[*eit] - res_capacity[*eit];
	}

	int cost = find_flow_cost(G);
	cout << "cost is " << cost << endl;
	cout << "flow is " << flow << endl;

	// Print all edges with weights
	/*cout << "All edges (without reverse edges):" << endl;
	EdgeIt eit, eend;
	for(tie(eit, eend) = edges(G); eit != eend; ++eit) {
		cout << source(*eit, G) << "->" << target(*eit, G);
		cout << "\tresidual: " << res_capacity[*eit] << "\ttotal: " << capacity[*eit] << endl; 
	}*/

	return 0;
}
