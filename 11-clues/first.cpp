#include <iostream>
#include <vector>
#include <queue>
#include <limits>

#include <boost/graph/connected_components.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/tuple/tuple.hpp>	// tuples::ignore

using namespace std;
using namespace boost;


// Undirected graph with long weights on edges.
typedef	adjacency_list<vecS, vecS, undirectedS,
		no_property,
		property<edge_weight_t, long> >	Graph;

typedef	graph_traits<Graph>::vertex_descriptor	Vertex;	// Edge type
typedef	graph_traits<Graph>::edge_descriptor	Edge;	// Edge type
typedef graph_traits<Graph>::edge_iterator		EdgeIt;		// Iterator
typedef graph_traits<Graph>::out_edge_iterator	OutEdgeIt;		// Iterator

// Map edge -> weight.
typedef	property_map<Graph, edge_weight_t>::type	WeightMap;


bool bfs_path_exists(int v_start, int v_goal, int n, Graph &G) {

	//cout << "start from " << v_start << ", goal " << v_goal << endl;

	vector<int> visited(n, false);
	queue<int> Q;
	Q.push(v_start);

	while(!Q.empty()) {
		int current_node = Q.front();
		Q.pop();
		visited[current_node] = true;

		//cout << "\t currently at node " << current_node << endl;

		if(current_node == v_goal) {
			return true;
		} else {
			OutEdgeIt eit, eend;
			for(tie(eit, eend) = out_edges(current_node, G); eit != eend; ++eit) {
				int tgt = target(*eit, G);

				if(!visited[tgt])
					Q.push(tgt);
			}
		}
	}

	return false;
}

void test_case() {
	int n, m, r;
	cin >> n >> m >> r;				// <number_of_nodes> <number_of_edges>
	// cout << n << endl << m << endl << r << endl;
	long rsq = r * r;

	Graph G(n);
	WeightMap wm = get(edge_weight, G);

	vector<int> node_x(n);
	vector<int> node_y(n);

	for(int i=0; i<n; i++) {
		int x, y;
		cin >> x >> y;

		node_x[i] = x;
		node_y[i] = y;
	}

	for(int i=0; i<n; i++) {
		for(int j=i+1; j<n; j++) {
			int dx = node_x[i] - node_x[j];
			int dy = node_y[i] - node_y[j];
			long dsq = dx * dx + dy * dy;

			if(dsq <= rsq) {
				Edge e;
				tie(e, tuples::ignore) = add_edge(i, j, G);
				wm[e] = dsq;
			}
		}
	}

	// Coloring graph
	vector<bool> green_allowed(n, true);
	vector<bool> purple_allowed(n, true);
	vector<bool> visited(n, false);

	queue<int> Q;

	// Find connected components
	vector<int> component(n);
	int num_components = connected_components(G, &component[0]);

	// Add one node from each connected component
	vector<bool> added(num_components, false);
	for(int i=0; i<n; i++) {
		int comp = component[i];
		if(!added[comp]) {
			Q.push(i);
			purple_allowed[i] = false;	// color first node green
			added[comp] = true;
		}
	}

	bool interference_exists = false;

	// TODO handle connected components
	while(!Q.empty()) {
		int current_node = Q.front();
		Q.pop();
		visited[current_node] = true;

		/*cout << "node " << current_node << ": ";
		if(green_allowed[current_node])
			cout << "green allowed | ";
		if(purple_allowed[current_node])
			cout << "purple allowed";
		cout << endl;*/

		if(!green_allowed[current_node] && !purple_allowed[current_node]) {
			interference_exists = true;
			break;
		} else {
			if(green_allowed[current_node])
				purple_allowed[current_node] = false;	// color current node green
			else
				green_allowed[current_node] = false;	// color current node purple

			// Add all neighbors to queue
			OutEdgeIt eit, eend;
			for(tie(eit, eend) = out_edges(current_node, G); eit != eend; ++eit) {
				int tgt = target(*eit, G);

				if(!visited[tgt])
					Q.push(tgt);

				if(green_allowed[current_node]) {// current node is green
					green_allowed[tgt] = false;
					//cout << "\t" << tgt << " can't be green" << endl;
				}
				if(purple_allowed[current_node]) {
					purple_allowed[tgt] = false;
					//cout << "\t" << tgt << " can't be purple" << endl;
				}
			}
		}
	}

	// Answer queries about clues
	for(int c=0; c<m; c++) {

		int sx, sy, wx, wy;	// sherlock and watson coordinates
		cin >> sx >> sy >> wx >> wy;

		// If there is interferene
		if(interference_exists) {
			cout << "n";//INTERFERENCE";
		} else {
			// If Sherlock and Watson are within range of each other
			int dx = sx - wx;
			int dy = sy - wy;
			long separation_sq = dx * dx + dy * dy;
			if(separation_sq <= rsq) {
				cout << "y";//RANGE";
			} else {
				// ---- Find closest nodes to sherlock and watson
				int s_nearest = -1;
				int w_nearest = -1;
				long s_distsq = LONG_MAX;
				long w_distsq = LONG_MAX;

				for(int i=0; i<n; i++) {
					// sherlock
					int dxs = sx - node_x[i];
					int dys = sy - node_y[i];
					long dsqs = dxs * dxs + dys * dys;
					if(dsqs < s_distsq) { // todo what if equal distances?
						s_nearest = i;
						s_distsq = dsqs;
					}
					// watson
					int dxw = wx - node_x[i];
					int dyw = wy - node_y[i];
					long dsqw = dxw * dxw + dyw * dyw;
					if(dsqw < w_distsq) { // todo what if equal distances?
						w_nearest = i;
						w_distsq = dsqw;
					}
				}

				// If sherlock or watson can't reach network
				if(s_distsq > rsq || w_distsq > rsq) {
					//cout << "sherlock nearest " << s_nearest << " [" << s_distsq << "], watson nearest " << w_nearest << "[" << w_distsq << "]" << endl;
					cout << "n";//NETWORK REACH";
					continue;
				}
				// Find if path exists in graph
				else if(bfs_path_exists(s_nearest, w_nearest, n, G))
					cout << "y";//BFS PATH";
				else
					cout << "n";//BFS PATH";

				//cout << endl << "nearest to sherlock " << s_nearest << endl;
				//cout << endl << "nearest to watson " << w_nearest << endl;
			}
		}
	}


	cout << endl;

	/*EdgeIt eit, eend;
	for(tie(eit, eend) = edges(G); eit != eend; ++eit) {
		cout << source(*eit, G) << "--" << target(*eit, G) << ", dsq=" << wm[*eit] << endl;
	}
	cout << "rsq=" << rsq << endl;*/

	/*Edge e;
		tie(e, tuples::ignore) = add_edge(n1, n2, G);
		wm[e] = w;*/

	// Print node colors
	/*for(int i=0; i<n; i++) {
		cout << "node " << i << " color: ";
		if(purple_allowed[i])
			cout << "purple ";
		else
			cout << "green";
		cout << endl;
	}*/
}

int main(void) {
	std::ios_base::sync_with_stdio(false);
	
	int t;
	cin >> t;

	for(int i=0; i<t; i++)
		test_case();

	return 0;
}