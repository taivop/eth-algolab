#include <iostream>
#include <vector>
#include <string>

using namespace std;

vector<int> solve(vector<int> v, int l, int m, int n) {

	if(v[0] == 0)
		return v;

	vector<int> best = v;
	// Start removing longs one by one
	for(int i=1; i<=v[2]; i++) {

		vector<int> current = v;

		current[0] += n * i;
		current[2] -= i;
		int num_m_added = current[0] / m;
		current[1] += num_m_added;
		current[0] -= num_m_added * m;

		//printf("%d %d %d\n", current[0], current[1], current[2]);

		if(current[0] < best[0])
			best = current;
	}

	return best;

}

void test_case() {
	int l, m, n;
	cin >> l;
	cin >> m;
	cin >> n;

	// start from n=0, m=0
	vector<int> v (3, 0);
	v[0] = l;

	// Fill with longer one
	v[2] = l / n;
	v[0] -= v[2] * n;

	// Also add as many short ones as possible
	v[1] = v[0] / m;
	v[0] -= v[1] * m;

	vector<int> result = solve(v, l, m, n);
	//vector<int> result = v;

	printf("%d %d %d\n", result[1], result[2], result[0]);
}

int main(void) {
	std::ios_base::sync_with_stdio(false);
	
	int N;
	cin >> N;

	for(int i=0; i<N; i++)
		test_case();

	return 0;
}
