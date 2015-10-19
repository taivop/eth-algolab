#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <algorithm>

#include <boost/graph/adjacency_list.hpp>
#include <boost/tuple/tuple.hpp>	// tuples::ignore

using namespace std;
using namespace boost;


// Undirected graph with int weights on edges.
typedef	adjacency_list<vecS, vecS, undirectedS,
		no_property,
		property<edge_weight_t, int> >	Graph;

typedef	graph_traits<Graph>::edge_descriptor	Edge;	// Edge type
typedef graph_traits<Graph>::edge_iterator		EdgeIterator;		// Iterator
typedef graph_traits<Graph>::vertex_descriptor	Vertex;		// Iterator

// Map edge -> weight.
typedef	property_map<Graph, edge_weight_t>::type	WeightMap;

int match_count(vector<string> a, vector<string> b) {
	set<string> set_a = set<string>(a.begin(), a.end());
	set<string> set_b = set<string>(b.begin(), b.end());

	vector<string> result;
	set_intersection(set_a.begin(), set_a.end(),
					 set_b.begin(), set_b.end(),
					 back_inserter(result));

	return result.size();
}

void test_case() {
	int n, c, f;
	cin >> n >> c >> f;				// <number_of_students> <number_of_characteristics> <min common characteristics to beat>

	Graph G(n);
	WeightMap wm = get(edge_weight, G);

	// Read in students
	vector<vector<string> > students;
	students.reserve(n);
	for(int i=0; i<n; i++) {
		vector<string> student;
		for(int j=0; j<c; j++) {
			string s;
			cin >> s;
			student.push_back(s);
		}
		students.push_back(student);
	}

	// Generate student-student edges into graph
	for(int i=0; i<n; i++) {
		for(int j=i+1; j<n; j++) {
			Edge e;
			tie(e, tuples::ignore) = add_edge(i, j, G);
			wm[e] = match_count(students[i], students[j]);
			//cout << i << "," << j << ": " << wm[e] << endl;
		}
	}


	// Greedily take highest edges first
	vector<pair<int, Edge> > edge_and_weight;
	EdgeIterator eit, eend;
	for (tie(eit, eend) = edges(G); eit != eend; ++eit) {
	   // eit is EdgeIterator, *eit is EdgeDescriptor
	   int u = source(*eit, G), v = target(*eit, G);
	   edge_and_weight.push_back(pair<int, Edge>(wm[*eit], *eit));
	}

	sort(edge_and_weight.begin(), edge_and_weight.end());

	// Keep track of whether nodes are taken
	vector<bool> taken = vector<bool>(n, false);

	// Keep track of how many edges we have taken already
	int num_taken = 0;
	int my_f = 0;
	for(int i=edge_and_weight.size()-1; i>=0; i--) {
		// Take an edge IF neither of its endpoints have been taken yet
		Edge e = edge_and_weight[i].second;
		int u = source(e, G), v = target(e, G);
		int weight = edge_and_weight[i].first;

		cout << "looking at edge " << e << ", weight " << weight << endl;
		if(!taken[u] && !taken[v]) {
			my_f = weight;
			num_taken++;
			taken[u] = true;
			taken[v] = true;
		}

		cout << "so far have taken " << num_taken << " elements" << endl;

		// If enough edges taken
		if(num_taken == n / 2)
			break;
	}

	/*for(int i=edge_and_weight.size()-1; i>=0; i--) {
		cout << edge_and_weight[i].first << ", w=" << edge_and_weight[i].second << endl;
	}*/

	cout << "f=" << f << ", my_f=" << my_f << endl;
	if(my_f == f)
		cout << "optimal" << endl;
	else
		cout << "not optimal" << endl;

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