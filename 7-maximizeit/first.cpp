// example: decide whether there exists a disk that covers a given set
// of points R in the plane and is disjoint from another set of points B
#include <iostream>
#include <cassert>
#include <CGAL/basic.h>
#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>

// choose exact integral type
#ifdef CGAL_USE_GMP
#include <CGAL/Gmpz.h>
typedef CGAL::Gmpz ET;
#else
#include <CGAL/MP_Float.h>
typedef CGAL::MP_Float ET;
#endif

// program and solution types
typedef CGAL::Quadratic_program<int> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;

using namespace std;

void test_case(int p) {
	Program qp (CGAL::SMALLER, true, 0, false, 0);

	int a, b;
	cin >> a >> b;

	if(p == 1) {
		const int X = 0;
		const int Y = 1;

		// x + y <= 4
		qp.set_a(X, 0, 1);
		qp.set_a(Y, 0, 1);
		qp.set_b(	0, 4);

		// 4x + 2y <= ab
		qp.set_a(X, 1, 4);
		qp.set_a(Y, 1, 2);
		qp.set_b(	1, a * b);

		// -x + y <= 1
		qp.set_a(X, 2, -1);
		qp.set_a(Y, 2, 1);
		qp.set_b(	2, 1);

		// x, y >= 0 are set in the initialisation of qp

		//cout << "a=" << a << ", b=" << b << ", a*b" << a*b << endl;
		// Cost function: ax^2 - by
		qp.set_d(X, X, 2 * a);
		qp.set_d(X, Y, 0);
		qp.set_d(Y, Y, 0);
		qp.set_c(X, 0);
		qp.set_c(Y, -b);
		qp.set_c0(0);

		// Solve
		Solution s = CGAL::solve_quadratic_program(qp, ET());

		// Output
		if(s.status() == CGAL::QP_OPTIMAL) {
			cout << (int) CGAL::to_double(-s.objective_value()) << endl; // Careful: possibility for WA here.
			//cout << s << endl;
		} else {
			cout << "no" << endl;
		}


	} else {
		cout << "" << endl;
	}
}

int main(void) {
	std::ios_base::sync_with_stdio(false);
	
	int p;
	cin >> p;

	while(p != 0) {
		test_case(p);
		cin >> p;
	}

	return 0;
}