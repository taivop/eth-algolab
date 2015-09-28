#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct boat {
	int length;
	int position;

	boat(int l, int p) : length(l), position(p) {}

	bool operator<(const boat& rhs) const { return position < rhs.position; }
};

void test_case() {

	int N;
	cin >> N;

	vector<int> length;
	vector<int> position;
	length.reserve(N);
	position.reserve(N);

	vector<boat> boats;

	for(int i=0; i<N; i++) {
		cin >> length[i];
		cin >> position[i];

		boat new_boat = boat(length[i], position[i]);
		boats.push_back(new_boat);
	}

	// Sort boats by position
	sort(boats.begin(), boats.end());

	for(int i=0; i<boats.size(); i++) {
		printf("boat at position %d length %d\n", boats[i].position, boats[i].length);
	}

	int boat_counter = 0;

	// Add boat at leftmost ring
	boat leftmost = boats[0];
	boat_counter++;
	int left_limit = leftmost.position;

	int i=1;
	// Iterate over all boats
	while(i < N) {
		boat current = boats[i];

		// Also need to check whether it would fit if we moved the boat a bit to the right.
		if(current.position - current.length >= left_limit) {
			left_limit = current.position;
			boat_counter++;
		}

		i++;
	}

	cout << boat_counter << endl;

}

int main(void) {
	std::ios_base::sync_with_stdio(false);
	
	int t;
	cin >> t;

	for(int i=0; i<t; i++)
		test_case();

	return 0;
}