#include <iostream>
#include <vector>
#include <cmath>

#include <CGAL/Exact_predicates_exact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>

typedef CGAL::Exact_predicates_exact_constructions_kernel K;
typedef CGAL::Delaunay_triangulation_2<K>  Triangulation;
typedef Triangulation::Finite_edges_iterator  Edge_iterator;
typedef Triangulation::Face  Face;
typedef Triangulation::Face_handle  Face_handle;
typedef Triangulation::Face_circulator  Face_circulator;
typedef Triangulation::Edge  Edge;
typedef Triangulation::Vertex  Vertex;


using namespace std;

void test_case(int n) {

	// cout << "---- " << n << " ----" << endl;

	// Read all infected people
	std::vector<K::Point_2> infected;
	infected.reserve(n);

	for(int i=0; i<n; i++) {
		// cin >> x[i] >> y[i];
		K::Point_2 p;
		cin >> p;
		infected.push_back(p);
	}

	// Construct Delauney triangulation
	Triangulation t;
	t.insert(infected.begin(), infected.end());

	// Read all healthy people
	int m;
	cin >> m;

	for(int i=0; i<m; i++) {
		K::Point_2 escaper;
		int c;
		cin >> escaper >> c;

		// --- Find an escape path for this person ---
		// Find out at which face we are
		Face_handle current_face = t.locate(escaper);

		// Check if we are already outside
		if(t.is_infinite(current_face)) {
			cout << "y";
			continue;
		}
		// TODO check if we are already getting infected

		// Check all incident faces if we could possibly go there
		Triangulation::Face_circulator c = t.incident_faces(current_face); // TODO can't use face here -- what can we use? https://judge.inf.ethz.ch/doc/cgal/doc_html/Triangulation_2/classCGAL_1_1Triangulation__2.html#a0cf72d2b0a303f23c5bc46aacc4d5fa4
		do {
		  if (t.is_infinite(c)) { ... }
		  ...
		} while (++c != t.incident_edges(v));

		// Move to nearest Voronoi point
		K::Point_2 nearest_voronoi = t.dual(current_face);
		cout << nearest_voronoi << endl;


	}

}

int main(void) {
	std::ios_base::sync_with_stdio(false);
	
	int n;
	cin >> n;

	while(n > 0) {
		test_case(n);
		cin >> n;
	}

	return 0;
}