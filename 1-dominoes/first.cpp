#include <iostream>
#include <vector>

using namespace std;

void test_case() {
	int n;
	cin >> n;

	vector<int> h;

	int a;
	for(int i=0; i<n; i++) {
		cin >> a;
		h.push_back(a);
	}

	int current_pos = 0;
	int max_pos = h[0] - 1;

	while(current_pos <= max_pos) {
		if(current_pos + h[current_pos] - 1 > max_pos) 
			max_pos = current_pos + h[current_pos] - 1;

		//printf("current %d max %d\n", current_pos, max_pos);

		current_pos += 1;
	}

	if(max_pos > n)
		max_pos = n;
	else
		max_pos = max_pos + 1;
	cout << max_pos << endl;
}

int main(void) {
	std::ios_base::sync_with_stdio(false);

	int N;
	cin >> N;

	for(int i=0; i<N; i++) {
		test_case();
	}

	return 0;
}