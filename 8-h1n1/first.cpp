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
typedef Triangulation::Vertex_handle  Vertex_handle;


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
		long d;
		cin >> escaper >> d;

		// --- Find an escape path for this person ---
		// Find out at which face we are
		Face_handle current_face = t.locate(escaper);
		K::Point_2 current_voronoi = t.dual(current_face);

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

		// Check all incident faces if we could possibly go there

		vector<Face_handle> visited_faces;
		visited_faces.push_back(current_face);

		for(int neighbor_num=0; neighbor_num<3; neighbor_num++) {
			Vertex_handle opposite_vertex  = current_face->vertex(neighbor_num);
			Vertex_handle border_endpoint1 = current_face->vertex((neighbor_num + 1) % 3);
			Vertex_handle border_endpoint2 = current_face->vertex((neighbor_num + 2) % 3);
			Edge border = pair<Face_handle, int>(current_face, neighbor_num);
			Face_handle neighbor_face = current_face->neighbor(neighbor_num);
			K::Point_2 neighbor_voronoi = t.dual(neighbor_face);
		}


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