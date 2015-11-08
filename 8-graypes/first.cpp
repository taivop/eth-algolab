#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

void test_case(int n) {

	cout << "---- " << n << " ----" << endl;

	vector<int> x = vector<int>(n, 0);
	vector<int> y = vector<int>(n, 0);

	for(int i=0; i<n; i++) {
		cin >> x[i] >> y[i];
	}

	double min_dist = -1;
	for(int i=0; i<n; i++) {
		for(int j=i+1; j<n; j++) {
			if(i != j) {
				int dx = x[i] - x[j];
				int dy = y[i] - y[j];
				double dist = sqrt(dx * dx + dy * dy);
				cout << dx * dx << endl;
				if(min_dist == -1 || min_dist > dist) {
					min_dist = dist;
				}
			}
		}
	}

	cout << ceil(min_dist * 50) << endl;
	
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