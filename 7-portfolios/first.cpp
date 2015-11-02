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

	// n is # assets, m is # investors

	vector<int> ALPHA = vector<int>(n, 0);

	// --- ASSETS ---
	vector<int> asset_cost = vector<int>(n, 0);
	vector<int> asset_return = vector<int>(n, 0);

	for(int i=0; i<n; i++) {
		cin >> asset_cost[i];
		cin >> asset_return[i];
		ALPHA[i] = i;
	}

	// cout << asset_cost.size() << " " << asset_return.size() << endl;

	// --- COVARIANCE MATRIX ---
	vector<vector<int> > covariance;

	for(int i=0; i<n; i++) {
		vector<int> row = vector<int>(n, 0);
		for(int j=0; j<n; j++)
			cin >> row[j];
		covariance.push_back(row);
	}


	// --- INVESTORS ---
	vector<int> investor_cost = vector<int>(m, 0);
	vector<int> investor_return = vector<int>(m, 0);
	vector<int> investor_variance = vector<int>(m, 0);

	for(int i=0; i<m; i++) {
		cin >> investor_cost[i];
		cin >> investor_return[i];
		cin >> investor_variance[i];
	}

	for(int investor=0; investor<m; investor++) {
		// --- CONSTRUCT PROGRAM ---
		Program qp (CGAL::LARGER, true, 0, false, 0);

		// Optimisation goal
		for(int i=0; i<n; i++) {
			for(int j=0; j<=i; j++) {	// only below or on the diagonal
				qp.set_d(ALPHA[i], ALPHA[j], 2 * covariance[i][j]);
			}
		}

		// Return constraint
		int constraint_id = 0;
		for(int i=0; i<n; i++) {
			qp.set_a(ALPHA[i], constraint_id, asset_return[i]);
		}
		qp.set_b(constraint_id, investor_return[investor]);
		qp.set_r(constraint_id, CGAL::LARGER);

		// Cost constraint
		constraint_id = 1;
		for(int i=0; i<n; i++) {
			qp.set_a(ALPHA[i], constraint_id, asset_cost[i]);
		}
		qp.set_b(constraint_id, investor_cost[investor]);
		qp.set_r(constraint_id, CGAL::SMALLER);

		// --- SOLVE ---
		Solution s = CGAL::solve_quadratic_program(qp, ET());
		
		if(s.status() == CGAL::QP_OPTIMAL && CGAL::to_double(s.objective_value()) <= investor_variance[investor])
			cout << "Yes.\t" << endl; // << CGAL::to_double(s.objective_value()) << " <= " << investor_variance[investor] << endl;
		else
			cout << "No.\t" << endl; // << CGAL::to_double(s.objective_value()) << " > " << investor_variance[investor] << endl;
		//cout << s << endl;
	}

	/*
	// --- SOLVE ---
	s = CGAL::solve_quadratic_program(qp, ET());

	// Output
	if(s.status() == CGAL::QP_OPTIMAL) {
		cout << (int) CGAL::to_double(s.objective_value()) << endl; // Careful: possibility for WA here.
		// cout << s << endl;
	} else {
		cout << "No such diet." << endl;
	}
	*/

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