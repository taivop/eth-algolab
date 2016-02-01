#include <iostream>
#include <vector>
#include <queue>
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
typedef graph_traits<Graph>::out_edge_iterator OutEdgeIterator;

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

	const int NVERTICES = 6;

	Graph G(NVERTICES);
	EdgeCapacityMap capacity = get(edge_capacity, G);
	ReverseEdgeMap rev_edge = get(edge_reverse, G);
	ResidualCapacityMap res_capacity = get(edge_residual_capacity, G);

	int flow_source = 0;
	int flow_sink = 5;

	addEdge(flow_source, 1, 5, capacity, rev_edge, G);
	addEdge(1, 2, 3, capacity, rev_edge, G);
	addEdge(1, 3, 2, capacity, rev_edge, G);
	addEdge(2, 3, 1, capacity, rev_edge, G);
	addEdge(2, 4, 2, capacity, rev_edge, G);
	addEdge(3, 4, 2, capacity, rev_edge, G);
	addEdge(4, flow_sink, 4, capacity, rev_edge, G);


	long flow = push_relabel_max_flow(G, flow_source, flow_sink);

	cout << "Flow through graph with " << NVERTICES << " nodes: " << flow << endl;

	cout << "Now finding minimum cut." << endl;
	vector<bool> visited(NVERTICES, false);
	std::queue<int> Q;
	Q.push(flow_source);

	while(!Q.empty()) {

		int current_node = Q.front();
		Q.pop();
		visited[current_node] = true;
		cout << "currently at node " << current_node << endl;

		// Iterate over all outgoing edges
		OutEdgeIterator eit, eend;
		for (tie(eit, eend) = out_edges(current_node, G); eit != eend; ++eit) {
			int tgt = target(*eit, G);
			if(res_capacity[*eit] <= 0) {
				cout << "\t" << tgt << " residual capacity is " << res_capacity[*eit] << ", not visiting" << endl;
			}
			else if(!visited[tgt] && res_capacity[*eit] > 0) {
				Q.push(tgt);
				cout << "\t" << tgt << " unvisited, adding to queue" << endl;
			} else {
				cout << "\t" << tgt << " already visited" << endl;
			}
		}
	}

	cout << "Visited nodes: ";
	for(int i=0; i<NVERTICES; i++) {
		if(visited[i])
			cout << i << " ";
	}
	cout << endl;



	// Print all edges with weights
	/*cout << "All edges (without reverse edges):" << endl;
	EdgeIt eit, eend;
	for(tie(eit, eend) = edges(G); eit != eend; ++eit) {
		cout << source(*eit, G) << "->" << target(*eit, G);
		cout << "\tresidual: " << res_capacity[*eit] << "\ttotal: " << capacity[*eit] << endl; 
	}*/

	return 0;
}
