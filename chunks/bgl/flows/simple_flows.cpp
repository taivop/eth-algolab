#include <iostream>
#include <vector>
#include <boost/tuple/tuple.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/push_relabel_max_flow.hpp>

using namespace std;
using namespace boost;

typedef adjacency_list_traits<vecS, vecS, directedS> Traits;
typedef adjacency_list<vecS, vecS, directedS, no_property,
    property<edge_capacity_t, long,
        property<edge_residual_capacity_t, long,
            property<edge_reverse_t, Traits::edge_descriptor> > > > Graph;
typedef property_map<Graph, edge_capacity_t>::type EdgeCapacityMap;
typedef property_map<Graph, edge_residual_capacity_t>::type ResidualCapacityMap;
typedef property_map<Graph, edge_reverse_t>::type ReverseEdgeMap;

typedef graph_traits<Graph>::vertex_descriptor	Vertex;
typedef graph_traits<Graph>::edge_descriptor	Edge;   // Edge type
typedef graph_traits<Graph>::edge_iterator		EdgeIt; // Iterator


void addEdge(int from, int to, long c,
             EdgeCapacityMap &capacity, ReverseEdgeMap &rev_edge, Graph &G) {
     Edge e, reverseE;
     tie(e, tuples::ignore) = add_edge(from, to, G);
     tie(reverseE, tuples::ignore) = add_edge(to, from, G);
     capacity[e] = c;
     capacity[reverseE] = 0;
     rev_edge[e] = reverseE;
     rev_edge[reverseE] = e;
}

int main() {

	cout << "BGL SIMPLE FLOW ALGORITHMS" << endl;

	const int NVERTICES = 5;

	Graph G(NVERTICES);
	EdgeCapacityMap capacity = get(edge_capacity, G);
	ReverseEdgeMap rev_edge = get(edge_reverse, G);
	ResidualCapacityMap res_capacity = get(edge_residual_capacity, G);

	int flow_source = 0;
	int flow_sink = 1;

	for(int i=2; i<NVERTICES; i++) {
		addEdge(flow_source, i, 1, capacity, rev_edge, G);
		addEdge(i, flow_sink, 1, capacity, rev_edge, G);
	}

	long flow = push_relabel_max_flow(G, flow_source, flow_sink);

	cout << "Flow through graph with " << NVERTICES << " nodes: " << flow << endl;


	// Print all edges with weights
	cout << "All edges (without reverse edges):" << endl;
	EdgeIt eit, eend;
	for(tie(eit, eend) = edges(G); eit != eend; ++eit) {
		if(source(*eit, G) == flow_source || target(*eit, G) == flow_sink) {
			cout << source(*eit, G) << "->" << target(*eit, G);
			cout << "\tresidual: " << res_capacity[*eit] << "\ttotal: " << capacity[*eit] << endl; 
		}
	}

	return 0;
}
