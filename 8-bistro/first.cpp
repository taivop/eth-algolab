#include <iostream>
#include <vector>
#include <cmath>

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Delaunay_triangulation_2<K>  Triangulation;
typedef Triangulation::Finite_edges_iterator  Edge_iterator;
typedef Triangulation::Edge  Edge;
typedef Triangulation::Vertex  Vertex;


using namespace std;

void test_case(int n) {

	// cout << "---- " << n << " ----" << endl;

	// Read all existing locations
	std::vector<K::Point_2> existing;
	existing.reserve(n);

	for(int i=0; i<n; i++) {
		// cin >> x[i] >> y[i];
		K::Point_2 p;
		cin >> p;
		existing.push_back(p);
	}

	// Construct Delauney triangulation
	Triangulation t;
	t.insert(existing.begin(), existing.end());

	// Read all proposed locations
	int m;
	cin >> m;

	std::vector<K::Point_2> proposed;
	proposed.reserve(m);

	for(int i=0; i<m; i++) {
		K::Point_2 p;
		cin >> p;
		proposed.push_back(p);

		Vertex nearest = *(t.nearest_vertex(p));

		long long dx = nearest.point().x() - p.x();
		long long dy = nearest.point().y() - p.y();
		long long sqd = dx * dx + dy * dy;

		cout << sqd << endl;
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