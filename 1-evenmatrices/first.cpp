#include <iostream>

using namespace std;

bool combine(bool a, bool b) {
	return a != b;
}

bool combine3(bool a, bool b, bool c) {
	return combine(combine(a, b), c);
}

bool combine4(bool a, bool b, bool c, bool d) {
	return combine(combine3(a, b, c), d);
}

void test_case() {
	int n;
	cin >> n;

	// Read all numbers into a matrix
	bool bits[n][n];
	for(int i=0; i<n; i++) {
		for(int j=0; j<n; j++) {
			cin >> bits[i][j];
		}
	}
	
	// Construct sums matrix
	bool sums[n][n];
	for(int i=0; i<n; i++) {
		for(int j=0; j<n; j++) {

			// First row or column are special cases
			if(j == 0) {

				if(i == 0)
					sums[i][j] = bits[i][j];
				else 
					sums[i][j] = combine(sums[i-1][j], bits[i][j]);

			} else {

				if(i == 0)
					sums[i][j] = combine(sums[i][j-1], bits[i][j]);
				else {
					bool excluding_current = combine3(sums[i-1][j-1], sums[i-1][j], sums[i][j-1]);
					sums[i][j] = combine(excluding_current, bits[i][j]);
				}

			}

		}
	}

	/*
	for (int r = 0; r < n; ++r) {
		for (int c = 0; c < n; ++c) {
			std::cout << sums[r][c] << " ";
		}
		std::cout << std::endl;
	}
	*/

	// Count number of even matrices
	int num_even_pairs = 0;
	for(int i1=0; i1<n; i1++) {
		for(int i2=i1; i2<n; i2++) {
			for(int j1=0; j1<n; j1++) {
				for(int j2=j1; j2<n; j2++) {

					bool parity;

					if(i1 == 0) {
						if(j1 == 0) {
							parity = sums[i2][j2];
						} else {
							parity = combine(sums[i2][j2], sums[i2][j1-1]);
						}
					} else {
						if(j1 == 0) {
							parity = combine(sums[i2][j2], sums[i1-1][j2]);
						} else {
							parity = combine4(sums[i2][j2], sums[i1-1][j2],
								sums[i2][j1-1], sums[i1-1][j1-1]);
						}
					}

					// Matrix is even if parity is 0
					if(!parity)
						num_even_pairs += 1;

				}
			}
		}
	}

	cout << num_even_pairs << endl;

}

int main(void) {
	std::ios_base::sync_with_stdio(false);
	
	int N;
	cin >> N;

	for(int i=0; i<N; i++)
		test_case();

	return 0;
}