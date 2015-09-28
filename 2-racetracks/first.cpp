#include <iostream>
#include <vector>

using namespace std;


void test_case() {
	int X, Y, start_x, start_y, finish_x, finish_y, num_obstacles;
	cin >> X;
	cin >> Y;
	cin >> start_x;
	cin >> start_y;
	cin >> finish_x;
	cin >> finish_y;
	cin >> num_obstacles;

	// Create obstacles matrix
	bool obstacle[X][Y];
	for(int a=0; a<X; a++)
		for(int b=0; b<Y; b++)
			obstacle[a][b] = false;
	for(int i=0; i<num_obstacles; i++) {
		int x1, y1, x2, y2;
		cin >> x1;
		cin >> y1;
		cin >> x2;
		cin >> y2;

		for(int a=x1; a<=x2; a++) {
			for(int b=y1; b<=y2; b++)
				obstacle[a][b] = true;
		}
	}

	// Print board
	for(int a=0; a<X; a++) {
		for(int b=0; b<Y; b++) {
			if(a == start_x && b == start_y)
				cout << "S";
			else if(a == finish_x && b == finish_y)
				cout << "F";
			else if(obstacle[a][b])
				cout << "x";
			else
				cout << ".";
		}
		cout << endl;
	}
}

int main(void) {
	std::ios_base::sync_with_stdio(false);
	
	int N;
	cin >> N;

	for(int i=0; i<N; i++)
		test_case();

	return 0;
}