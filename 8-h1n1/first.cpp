#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

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
typedef Triangulation::Vertex_handle  Vertex_handle;


using namespace std;

bool recurse(Face_handle current_face, long d, vector<Face_handle>& visited, Triangulation t) {

	// Remember we visited this node
	visited.push_back(current_face);

	cout << "Recursion at: " << t.dual(current_face) << endl;

	// Base of recursion: check if we are free
	if(t.is_infinite(current_face)) {
		cout << "Infinite face!" << endl;
		return true;
	}

	for(int neighbor_num=0; neighbor_num<3; neighbor_num++) {
		Face_handle neighbor_face = current_face->neighbor(neighbor_num);
		//cout << (current_face == neighbor_face) << endl;
		cout << "\tChecking neighbor of vertex " << current_face->vertex(neighbor_num)->point() << endl;

		cout << "\tPoints: ";
		for(int j=0; j<3; j++) {
			cout << neighbor_face->vertex(j)->point() << ", ";
		}
		cout << endl;

		// If we already visited
		if(find(visited.begin(), visited.end(), current_face) != visited.end()) {
			continue;
		}

		Vertex_handle border_endpoint1 = current_face->vertex((neighbor_num + 1) % 3);
		Vertex_handle border_endpoint2 = current_face->vertex((neighbor_num + 2) % 3);
		K::FT border_length_sq = CGAL::squared_distance(border_endpoint1->point(), border_endpoint2->point());

		if(CGAL::to_double(border_length_sq) >= 4 * d) {	// If we can fit through that edge 
			// cout << "can fit through edge " << neighbor_num << endl;

			// New search starting from neighbor
			if(recurse(neighbor_face, d, visited, t)) {
				return true;
			}
		} else {
			cout << "cannot fit through edge :S" << endl;
		}
	}

	return false;
}

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
		cout << "Read in point " << p << endl;
	}

	// Construct Delauney triangulation
	Triangulation t;
	t.insert(infected.begin(), infected.end());

	// Read all healthy people
	int m;
	cin >> m;

	for(int i=0; i<m; i++) {
		K::Point_2 escaper;
		long d;
		cin >> escaper >> d;

		// --- Find an escape path for this person ---
		// Find out at which face we are
		Face_handle current_face = t.locate(escaper);

		// Check if we are already outside
		if(t.is_infinite(current_face)) {
			cout << "y";
			continue;
		}
		// Check if we are already getting infected
		/*K::Point_2 nearest_infected = t.nearest_vertex(escaper, current_face)->point();
		cout << "Nearest infected person: " << nearest_infected << endl;
		int dx = nearest_infected.x() - escaper.x();
		int dy = nearest_infected.y() - escaper.y();
		long nearest_sqd = dx * dx + dy * dy;
		if(nearest_sqd < d) {
			cout << "n";
			continue;
		}*/

		// Recurse
		vector<Face_handle> visited;
		bool result = recurse(current_face, d, visited, t);

		if(result)
			cout << "POSSIBLE TO ESCAPE" << endl;
		else
			cout << "COULDN'T ESCAPE :(" << endl;
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

// https://judge.inf.ethz.ch/doc/cgal/doc_html/Triangulation_2/classCGAL_1_1Triangulation__2.html#a37b3896ab3a416fe4adff475ed625e16
// http://doc.cgal.org/latest/Kernel_23/classCGAL_1_1Point__2.html