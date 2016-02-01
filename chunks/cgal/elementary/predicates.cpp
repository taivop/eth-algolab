#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <iostream>

using namespace std;

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;

int main() {

	cout << "CGAL PREDICATES" << endl;
	// Documentation under 'Global kernel functions': http://doc.cgal.org/latest/Kernel_23/group__kernel__global__function.html

	cout << "---- In-circle test: are points x_i inside the circle defined by {p, q, r}? ----" << endl;
	// http://doc.cgal.org/latest/Kernel_23/group__side__of__bounded__circle__grp.html

	K::Point_2 p(0, 0), q(1,1), r(2,0);

	K::Point_2 x1(-1, -1);
	K::Point_2 x2(0, 0);
	K::Point_2 x3(0, 1);
	K::Point_2 x4(1, 4);
	K::Point_2 x5(1, -1);
	K::Point_2 x6(1, 0);

	cout << "x1 side: " << side_of_bounded_circle(p, q, r, x1) << endl;
	cout << "x2 side: " << side_of_bounded_circle(p, q, r, x2) << endl;
	cout << "x3 side: " << side_of_bounded_circle(p, q, r, x3) << endl;
	cout << "x4 side: " << side_of_bounded_circle(p, q, r, x4) << endl;
	cout << "x5 side: " << side_of_bounded_circle(p, q, r, x5) << endl;
	cout << "x6 side: " << side_of_bounded_circle(p, q, r, x6) << endl;


	cout << "---- Orientation test (left-turn/right-turn/collinear) ----" << endl;
	// http://doc.cgal.org/latest/Kernel_23/group__orientation__grp.html

	K::Point_2 a1(0, 0), a2(1, 1);

	K::Point_2 b1(0, 0);
	K::Point_2 b2(2, 2);
	K::Point_2 b3(-1, -1);
	K::Point_2 b4(-1, 0);
	K::Point_2 b5(1, 0);
	K::Point_2 b6(0, 1);

	cout << "b1 orientation: " << CGAL::orientation(a1, a2, b1) << endl;
	cout << "b2 orientation: " << CGAL::orientation(a1, a2, b2) << endl;
	cout << "b3 orientation: " << CGAL::orientation(a1, a2, b3) << endl;
	cout << "b4 orientation: " << CGAL::orientation(a1, a2, b4) << endl;
	cout << "b5 orientation: " << CGAL::orientation(a1, a2, b5) << endl;
	cout << "b6 orientation: " << CGAL::orientation(a1, a2, b6) << endl;

	cout << "b5 is a right turn (should be!): " << (CGAL::orientation(a1, a2, b5) == CGAL::RIGHT_TURN) << endl;





	return 0;
}
