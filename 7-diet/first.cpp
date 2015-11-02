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

void test_case(int n, int m) {

	// n is # nutrients, m is # foods

	Solution s;

	// --- NUTRIENTS ---
	vector<int> min_amount = vector<int>(n, 0);
	vector<int> max_amount = vector<int>(n, 0);

	// Read data about nutrients
	for(int i=0; i<n; i++) {
		cin >> min_amount[i];
		cin >> max_amount[i];
	}

	// --- FOODS ---

	vector<vector<int> > nutrition_value;
	vector<int> price = vector<int>(m, 0);
	vector<int> AMOUNT = vector<int>(m, 0);		// identity vector [0, 1, ...], holds the variable corresponding to the variable showing the amount of the j-th food
	nutrition_value.reserve(m);

	// Read data about foods
	for(int j=0; j<m; j++) {
		AMOUNT[j] = j;
		cin >> price[j];
		vector<int> food = vector<int>(n, 0);

		for(int i=0; i<n; i++) {
			cin >> food[i];
		}

		nutrition_value.push_back(food);
	}

	// cout << "n=" << min_amount.size() << ", m=" << nutrition_value.size() << endl;


	// --- CONSTRUCT PROGRAM ---
	Program qp (CGAL::SMALLER, true, 0, false, 0);

	// Cost function
	for(int j=0; j<m; j++) {
		qp.set_c(AMOUNT[j], price[j]);
	}

	// Constraints: for each nutrient
	for(int i=0; i<n; i++) {
		int constraint_id;

		// --- Add min constraint ---
		constraint_id = 2 * i;
		for(int j=0; j<m; j++) {
			qp.set_a(AMOUNT[j], constraint_id, nutrition_value[j][i]);
			// Lower bound: amount of food cannot be 0
			// qp.set_l(AMOUNT[j], true, 0); // don't need because already set in qp initialisation
		}
		qp.set_b(constraint_id, min_amount[i]); // Min amount
		qp.set_r(constraint_id, CGAL::LARGER);

		// --- Add max constraint ---
		constraint_id = 2 * i + 1;
		for(int j=0; j<m; j++) {
			qp.set_a(AMOUNT[j], constraint_id, nutrition_value[j][i]);
		}
		qp.set_b(constraint_id, max_amount[i]); // Max amount
		qp.set_r(constraint_id, CGAL::SMALLER);
	}


	// --- SOLVE ---
	s = CGAL::solve_quadratic_program(qp, ET());

	// Output
	if(s.status() == CGAL::QP_OPTIMAL) {
		cout << (int) CGAL::to_double(s.objective_value()) << endl; // Careful: possibility for WA here.
		// cout << s << endl;
	} else {
		cout << "No such diet." << endl;
	}

}

int main(void) {
	std::ios_base::sync_with_stdio(false);
	
	int n, m;
	cin >> n >> m;

	while(n != 0) {
		test_case(n, m);
		cin >> n >> m;
	}

	return 0;
}