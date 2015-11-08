#include <iostream>
#include <vector>
#include <cmath>

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Delaunay_triangulation_2<K>  Triangulation;
typedef Triangulation::Finite_edges_iterator  Edge_iterator;
typedef Triangulation::Edge  Edge;


using namespace std;

void test_case(int n) {

	// cout << "---- " << n << " ----" << endl;

	Triangulation t;

	std::vector<K::Point_2> pts;
	pts.reserve(n);

	// vector<int> x = vector<int>(n, 0);
	// vector<int> y = vector<int>(n, 0);

	for(int i=0; i<n; i++) {
		// cin >> x[i] >> y[i];
		K::Point_2 p;
		cin >> p;
		pts.push_back(p);
	}

	// Construct Delauney triangulation
	t.insert(pts.begin(), pts.end());

	long long min_sqd = -1;

	// Find shortest edge in triangulation
	for (Edge_iterator ei = t.finite_edges_begin(); ei != t.finite_edges_end(); ++ei) {
		Edge e = *ei;
		Triangulation::Vertex_handle v1 = e.first->vertex((e.second + 1) % 3);
		Triangulation::Vertex_handle v2 = e.first->vertex((e.second + 2) % 3);
		long dx = v1->point().x() - v2->point().x();
		long dy = v1->point().y() - v2->point().y();
		long long sqd = dx * dx + dy * dy;
		if(min_sqd == -1 || sqd < min_sqd)
			min_sqd = sqd;
 		//std::cout << "e = " << v1->point() << " <-> " << v2->point() << std::endl;
 		//std::cout << t.segment(e) << endl;
	}

	std::cout << ceil(sqrt(min_sqd) * 50) << endl;
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