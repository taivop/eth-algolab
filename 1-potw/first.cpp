#include <iostream>
#include <set>
#include <algorithm>

using namespace std;

set<int> read_side(int P_i) {
	set<int> side;
	for(int j=0; j<P_i; j++) {
		int coin;
		cin >> coin;
		side.insert(coin);
	}

	return side;
}

set<int> sunion(set<int> a, set<int> b) {
	set<int> result;

}

set<int> sintersection(set<int> a, set<int> b) {
	set<int> v_intersection;

    set_intersection(a.begin(), a.end(),
    	b.begin(), b.end(),
    	back_inserter(v_intersection));
    
	return v_intersection;
}

int sremaining(set<int> a, int n) {
	return 1337;
}

void test_case() {
	int n, k;

	cin >> n;
	cin >> k;

	set<int> real;

	set<int> lighter;
	set<int> heavier;

	for(int i=0; i<k; i++) {
		int P_i;
		cin >> P_i;

		// Read sides of scale
		set<int> left = read_side(P_i);
		set<int> right = read_side(P_i);

		// Read outcome
		char outcome;
		cin >> outcome;

		// If sides were equal
		if(outcome == '=') {
			real = sunion(real, left);
			real = sunion(real, right);
		} else if(outcome == '<') {
			lighter = sunion(lighter, left);
			heavier = sunion(heavier, left);
		} else if(outcome == '>') {
			lighter = sunion(lighter, right);
			heavier = sunion(heavier, left);
		}
	}

	// Anything that was BOTH in heavier and lighter can't be fake
	set<int> non_fake = sintersection(lighter, heavier);
	real = sunion(real, non_fake);

	// If real.count is n-1 then the only one remaining is fake
	int result;
	if(real.size() == n-1)
		result = sremaining(real, n);
	else
		result = 0;

	printf("%d", result);
}

int main(void) {
	std::ios_base::sync_with_stdio(false);
	
	int N;
	cin >> N;

	for(int i=0; i<N; i++)
		test_case();

	return 0;
}