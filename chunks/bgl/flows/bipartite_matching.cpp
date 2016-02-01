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

	const int NVERTICES = 11;

	Graph G(NVERTICES);
	EdgeCapacityMap capacity = get(edge_capacity, G);
	ReverseEdgeMap rev_edge = get(edge_reverse, G);
	ResidualCapacityMap res_capacity = get(edge_residual_capacity, G);

	int flow_source = 0;
	int flow_sink = 10;

	addEdge(flow_source, 1, 1, capacity, rev_edge, G);
	addEdge(flow_source, 2, 1, capacity, rev_edge, G);
	addEdge(flow_source, 3, 1, capacity, rev_edge, G);
	addEdge(flow_source, 4, 1, capacity, rev_edge, G);
	addEdge(flow_source, 5, 1, capacity, rev_edge, G);

	addEdge(1, 6, 1, capacity, rev_edge, G);
	addEdge(2, 7, 1, capacity, rev_edge, G);
	addEdge(3, 7, 1, capacity, rev_edge, G);
	addEdge(4, 8, 1, capacity, rev_edge, G);
	addEdge(5, 8, 1, capacity, rev_edge, G);

	addEdge(6, flow_sink, 1, capacity, rev_edge, G);
	addEdge(7, flow_sink, 1, capacity, rev_edge, G);
	addEdge(8, flow_sink, 1, capacity, rev_edge, G);
	addEdge(9, flow_sink, 1, capacity, rev_edge, G);


	long flow = push_relabel_max_flow(G, flow_source, flow_sink);

	cout << "Flow through graph with " << NVERTICES << " nodes: " << flow << endl;

	cout << "Now finding minimum vertex cover." << endl;
	vector<bool> visited(NVERTICES, false);
	std::queue<int> Q;

	// Find all unmatched vertices in L
	for(int i=1; i<=5; i++) {

		bool matched = false;
		OutEdgeIterator eit, eend;
		for (tie(eit, eend) = out_edges(i, G); eit != eend; ++eit) {
			if(res_capacity[*eit] == 1 && target(*eit, G) >= 6) {
				matched = true;
				break;
			}
		}

		if(matched) {
			Q.push(i);
			cout << i << " unmatched in L, adding to queue" << endl;
		}
	}

	while(!Q.empty()) {

		int current_node = Q.front();
		Q.pop();
		visited[current_node] = true;
		//cout << "currently at node " << current_node << endl;

		// Iterate over all outgoing edges
		OutEdgeIterator eit, eend;
		for (tie(eit, eend) = out_edges(current_node, G); eit != eend; ++eit) {
			int tgt = target(*eit, G);
			//cout << "\t considering target " << tgt << ", visited=" << visited[tgt] << ", res_capacity=" << res_capacity[*eit] << ", capacity=" << capacity[*eit] << endl;
			
			if(tgt >= 6 && tgt < 10 && !visited[tgt] && res_capacity[*eit] == 1) {
				//cout << "\tUsing edge NOT from M: " << current_node << "->" << tgt << endl;
				Q.push(tgt);
			} else if(tgt >= 1 && tgt < 6 && !visited[tgt] && res_capacity[rev_edge[*eit]] == 0) {
				//cout << "\tUsing edge from M: " << current_node << "->" << tgt << endl;
				Q.push(tgt);
			} else if(tgt == flow_source && !visited[tgt] && res_capacity[*eit] == 1) {
				//cout << "\tGoing to flow source." << endl;
				Q.push(tgt);
			}
 		}
	}

	cout << "Visited nodes: " << endl;
	for(int i=0; i<NVERTICES; i++)
		if(visited[i])
			cout << i << " ";
	cout << endl;


	cout << "Minimum vertex cover:" << endl;
	for(int i=0; i<NVERTICES; i++) {
		if(!visited[i] && i >= 1 && i < 6) // unvisited in L
			cout << i << " ";
		else if(visited[i] && i >= 6 && i < 10)
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
