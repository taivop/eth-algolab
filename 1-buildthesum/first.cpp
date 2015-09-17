#include <iostream>

using namespace std;

void one_case () {
	int num_rows;
	cin >> num_rows;

	float a;
	float sum = 0;

	for(int i=0; i<num_rows; i++) {
		cin >> a;
		sum += a;
	}

	cout << sum << endl;
}

int main(void) {
	int num_test_cases;
	cin >> num_test_cases;

	for(int i=0; i<num_test_cases; i++)
		one_case();

	return 0;
}