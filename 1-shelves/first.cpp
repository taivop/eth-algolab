#include <iostream>
#include <vector>
#include <string>

using namespace std;

vector<int> recurse(vector<int> v, int l, int m, int n) {
	int current_len = v[0];

	int tabs_count = current_len / 100;
	string tabs = string(tabs_count, ' ');
	printf("%s| %d %d %d\n", tabs.c_str(), v[0], v[1], v[2]);

	// check if conditions are satisfied
	if(current_len == l) {
		return v;
	}
	else if(current_len > l) {
		return vector<int> (3, 0);
	}
	else {
		// put in n and recurse
		vector<int> added_n = v;
		added_n[2] += 1;
		added_n[0] = current_len + n;
		vector<int> result_n = recurse(added_n, l, m, n);
		if(result_n[0] == l) // prune
			return result_n;

		// put in m and recurse
		vector<int> added_m = v;
		added_m[1] += 1;
		added_m[0] = current_len + m;
		vector<int> result_m = recurse(added_m, l, m, n);
		if(result_m[0] == l) // prune
			return result_m;

		//printf("\tn: %d %d %d\n", result_n[0], result_n[1], result_n[2]);
		//printf("\tm: %d %d %d\n", result_m[0], result_m[1], result_m[2]);

		// if both failed, return current one
		if(result_n[0] == 0 && result_m[0] == 0)
			return v;
		// of the two results, pick one with higher length
		else if(result_n[0] >= result_m[0])
			return result_n;
		else
			return result_m;
	}
}

void test_case() {
	int l, m, n;
	cin >> l;
	cin >> m;
	cin >> n;

	// start from n=0, m=0
	vector<int> v (3, 0);

	vector<int> result = recurse(v, l, m, n);
	//vector<int> result = v;

	printf("%d %d %d\n", result[1], result[2], l-result[0]);
}

int main(void) {
	std::ios_base::sync_with_stdio(false);
	
	int N;
	cin >> N;

	for(int i=0; i<N; i++)
		test_case();

	return 0;
}
