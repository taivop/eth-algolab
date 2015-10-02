#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct boat {
	int id;
	int length;
	int ring;

	boat(int i, int l, int p) : id(i), length(l), ring(p) {}

	bool operator<(const boat& rhs) const {
		/*if((x + length) == (rhs.x + rhs.length))
			return length < rhs.length;
		else*/
			return (ring + length) < (rhs.ring + rhs.length);
	}
};

void print_boat(boat b) {
	printf("boat ID=%d at ring=%d\n and length", b.id, b.ring, b.length);
}

void test_case() {

	int N;
	cin >> N;

	vector<int> length;
	vector<int> ring_position;
	length.reserve(N);
	ring_position.reserve(N);

	vector<boat> boats;

	for(int i=0; i<N; i++) {
		cin >> length[i];
		cin >> ring_position[i];

		boat new_boat = boat(i, length[i], ring_position[i]);
		boats.push_back(new_boat);

	}

	int counter = 0;

	// Add boat at leftmost ring
	boat leftmost = boats[0];
	counter++;
	int left_limit = leftmost.ring;
	//print_boat(leftmost);

	while(true) {
		int left_limit = -1;
		for(int i=0; i<boats.size(); i++) {
			if(boats[i].ring)
		}

	}


	cout << counter << endl;

}

int main(void) {
	std::ios_base::sync_with_stdio(false);
	
	int t;
	cin >> t;

	for(int i=0; i<t; i++)
		test_case();

	return 0;
}