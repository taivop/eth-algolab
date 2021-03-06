#include <iostream>
#include <vector>
#include <iterator>
#include <string>
#include <algorithm>

#include <boost/config.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/tuple/tuple.hpp>	// tuples::ignore
#include <boost/graph/biconnected_components.hpp>


using namespace std;
using namespace boost;

namespace boost
{
  struct edge_component_t
  {
    enum
    { num = 555 };
    typedef edge_property_tag kind;
  }
  edge_component;
}


// Undirected graph with int weights on edges.
typedef	adjacency_list<vecS, vecS, undirectedS,
			property<vertex_degree_t, int>,
			property<edge_component_t, std::size_t > >	Graph;

typedef graph_traits<Graph>::vertex_descriptor Vertex;
typedef	graph_traits<Graph>::edge_descriptor	Edge;	// Edge type
typedef graph_traits<Graph>::edge_iterator	EdgeIt;		// Iterator
typedef property_map<Graph, vertex_degree_t>::type DegreeMap;
typedef graph_traits<Graph>::out_edge_iterator OutEdgeIt;
typedef property_map <Graph, edge_component_t >::type ComponentMap;


void test_case() {
	int n, m;
	cin >> n >> m;				// <number_of_nodes> <number_of_edges>

	Graph G(n);
	DegreeMap degree = get(vertex_degree, G);

	for(int i=0; i<m; i++) {
		int n1, n2;
		cin >> n1 >> n2;	// <start_node> <end_node>

		Edge e;
		tie(e, tuples::ignore) = add_edge(n1, n2, G);

		degree[n1] += 1;
		degree[n2] += 1;
	}

	// Find biconnected components
	
    ComponentMap component = get(edge_component, G);

    std::size_t num_comps = biconnected_components(G, component);


    // Store number of edges in each component
	vector<int> num_edges_in_component(num_comps, 0);
	num_edges_in_component.reserve(num_comps);

	// Iterate over all edges
	EdgeIt eit, eend;
	for (tie(eit, eend) = edges(G); eit != eend; ++eit) {
	   // eit is EdgeIterator, *eit is EdgeDescriptor
	   int u = source(*eit, G), v = target(*eit, G);
	   num_edges_in_component[component[*eit]] += 1;
	   //cout << "component of edge " << *eit << ": " << component[*eit] << endl;
	   //cout << *eit << ": " << component[*eit] << endl
	}

	vector<string> criticals;
	vector<pair<int, int> > criticals2;

	// Do second pass over all edges and get all edges that are in 1-edge components
	for (tie(eit, eend) = edges(G); eit != eend; ++eit) {
	   // eit is EdgeIterator, *eit is EdgeDescriptor
	   	int u = source(*eit, G), v = target(*eit, G);
	   	//cout << "edges in component " << component[*eit] << ": " << num_edges_in_component[component[*eit]] << endl;
		if(num_edges_in_component[component[*eit]] == 1) {
   			criticals2.push_back(pair<int,int>(min(u, v), max(u, v)));
   		}
	}


	sort(criticals2);

	// Print results
	if(criticals2.size() >= 1) {
		cout << criticals2.size() << endl;
		for(int i=0; i<criticals2.size(); i++) {
			cout << criticals2[i].first << " " << criticals2[i].second << endl;
		}
	} else {
		cout << "0" << endl;
	}

}

int main(void) {
	std::ios_base::sync_with_stdio(false);

	int t;
	cin >> t;

	for(int i=0; i<t; i++) {
		//cout << "---- NEW TESTCASE ----" << endl;
		test_case();
	}

	return 0;
}