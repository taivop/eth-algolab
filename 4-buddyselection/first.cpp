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
typedef graph_traits<Graph>::edge_iterator		EdgeIt;		// Iterator
typedef graph_traits<Graph>::vertex_descriptor	Vertex;		// Iterator

// Map edge -> weight.
typedef	property_map<Graph, edge_weight_t>::type	WeightMap;

int match_count(vector<string> a, vector<string> b) {
	set<string> set_a = set<string>(a.begin(), a.end());
	set<string> set_b = set<string>(b.begin(), b.end());

	vector<string> result;
	set_intersection(a.begin(), a.end(),
					 b.begin(), b.end(),
					 back_inserter(result));

	// TODO
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
			cout << i << "," << j << ": " << wm[e] << endl;
		}
	}
}

int main(void) {
	std::ios_base::sync_with_stdio(false);
	
	int t;
	cin >> t;

	for(int i=0; i<t; i++)
		test_case();

	return 0;
}