#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct boat {
	int id;
	int length;
	int x;

	boat(int i, int l, int p) : id(i), length(l), x(p) {}

	bool operator<(const boat& rhs) const {
		/*if((x + length) == (rhs.x + rhs.length))
			return length < rhs.length;
		else*/
			return (x + length) < (rhs.x + rhs.length);
	}
};

void print_boat(boat b) {
	printf("boat ID=%d at x=%d:%d\n", b.id, b.x, b.x+b.length);
}

void test_case() {

	int N;
	cin >> N;

	vector<int> length;
	vector<int> ring_position;
	length.reserve(N);
	ring_position.reserve(N);

	vector<boat> boats;
	vector<bool> parked;
	parked.reserve(N);

	for(int i=0; i<N; i++) {
		cin >> length[i];
		cin >> ring_position[i];

		for(int dpos=-length[i]; dpos<=0; dpos++) {
			boat new_boat = boat(i, length[i], ring_position[i]+dpos);
			boats.push_back(new_boat);
		}

		parked[i] = false;
	}

	// Sort boats by rightmost position
	sort(boats.begin(), boats.end());



	int counter = 0;

	// Add boat at leftmost ring
	boat leftmost = boats[0];
	parked[leftmost.id] = true;
	counter++;
	int left_limit = leftmost.x + leftmost.length;
	print_boat(leftmost);

	for(int i=1; i<boats.size(); i++) {

		boat current_boat = boats[i];

		if(parked[current_boat.id])
			continue;

		if(left_limit <= current_boat.x) {
			left_limit = current_boat.x + current_boat.length;
			parked[current_boat.id] = true;
			counter++;
			print_boat(current_boat);
		}
	}



	cout << counter << endl;
	cout << 2;

}

int main(void) {
	std::ios_base::sync_with_stdio(false);
	
	int t;
	cin >> t;

	for(int i=0; i<t; i++)
		test_case();

	return 0;
}