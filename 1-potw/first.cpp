#include <iostream>
#include <algorithm>
#include <vector>


using namespace std;

vector<int> read_side(int P_i) {
	vector<int> side;
	for(int j=0; j<P_i; j++) {
		int coin;
		cin >> coin;
		side.push_back(coin);
	}

	return side;
}

vector<int> sunion(vector<int> a, vector<int> b) {
	vector<int> v_union;

	set_union(a.begin(), a.end(),
       b.begin(), b.end(),                  
       back_inserter(v_union));
	return v_union;
}

vector<int> sintersection(vector<int> a, vector<int> b) {
	vector<int> v_intersection;

    set_intersection(a.begin(), a.end(),
    	b.begin(), b.end(),
    	back_inserter(v_intersection));

	return v_intersection;
}

vector<int> sdiff(vector<int> v1, vector<int> v2) {
	vector<int> v_diff;

	set_difference(v1.begin(), v1.end(), v2.begin(), v2.end(), 
                        inserter(v_diff, v_diff.begin()));

	return v_diff;
}

bool sincludes(vector<int> v1, vector<int> v2) {
	return includes(v1.begin(), v1.end(), v2.begin(), v2.end());
}

int sremaining(vector<int> a, int n) {

	if(n == 1)
		return 1;

	if(a[n-1] != n)
		return n;

	for(int i=0; i<a.size(); i++) {
		if(i >= 0) {
			if(a[i] - a[i-1] > 1)
				return a[i-1] + 1;
		}
	}

	return 1337;
}

void test_case() {
	int n, k;

	cin >> n;
	cin >> k;

	vector<int> real;

	vector<int> lighter;
	vector<int> heavier;

	vector<int> hypotheses(n);
	for(int i=0; i<n; i++) {
		hypotheses[i] = i+1;
	}

	//printf("hypotheses %ld\n", hypotheses.size());


	for(int i=0; i<k; i++) {
		int P_i;
		cin >> P_i;

		// Read sides of scale
		vector<int> left = read_side(P_i);
		vector<int> right = read_side(P_i);

		// Read outcome
		char outcome;
		cin >> outcome;

		// If one side contained stuff only in 'real', then the other side must contain crappy coin

		// If sides were equal
		if(outcome == '=') {
			hypotheses = sdiff(hypotheses, left);
			hypotheses = sdiff(hypotheses, right);
		} else if(outcome == '<') {
			lighter = sunion(lighter, left);
			heavier = sunion(heavier, left);

			if(sintersection(hypotheses, left).size() == 0)
				hypotheses = sintersection(hypotheses, right);
			else if(sintersection(hypotheses, right).size() == 0)
				hypotheses = sintersection(hypotheses, left);
		} else if(outcome == '>') {
			lighter = sunion(lighter, right);
			heavier = sunion(heavier, left);

			if(sintersection(hypotheses, left).size() == 0)
				hypotheses = sintersection(hypotheses, right);
			else if(sintersection(hypotheses, right).size() == 0)
				hypotheses = sintersection(hypotheses, left);
		}
	}

	// Anything that was BOTH in heavier and lighter can't be fake
	vector<int> non_fake = sintersection(lighter, heavier);
	hypotheses = sdiff(hypotheses, non_fake);

	printf("nonfake size %ld\n", non_fake.size());

	printf("size(lighter)=%ld, size(heavier)=%ld, size(hypotheses)=%ld, n=%d\n",
		lighter.size(), heavier.size(), hypotheses.size(), n);

	// Only one remaining is fake
	int result;
	if(hypotheses.size() == 1)
		result = hypotheses[0];
	else
		result = 0;

	printf("%d\n", result);
}

int main(void) {
	std::ios_base::sync_with_stdio(false);
	
	int N;
	cin >> N;

	for(int i=0; i<N; i++)
		test_case();

	return 0;
}