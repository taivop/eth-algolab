#include <iostream>
#include <vector>
#include <queue>
#include <unordered_set>

using namespace std;

struct node {
	int x;
	int y;
	int v_x;
	int v_y;
	int num_hops;

	node(int init_x, int init_y, int init_v_x, int init_v_y, int init_num_hops) {
		x = init_x;
		y = init_y;
		v_x = init_v_x;
		v_y = init_v_y;
		num_hops = init_num_hops;
	}
};

bool operator==(const node& lhs, const node& rhs) {
	    return lhs.x == rhs.x && lhs.y == rhs.y && lhs.v_x == rhs.v_x && lhs.v_y == rhs.v_y;
};

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
	/*for(int a=0; a<X; a++) {
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
	}*/



	// ---- Actual solution part ----
	queue<node> Q;
	bool visited[X][Y][7][7];

	for(int a=0; a<X; a++)
		for(int b=0; b<Y; b++)
			for(int c=0; c<7; c++)
				for(int d=0; d<7; d++)
					visited[a][b][c][d] = false;

	node start = node(start_x, start_y, 0, 0, 0);
	Q.push(start);

	while(!Q.empty()) {
		// Take a node
		node current = Q.front();
		Q.pop();

		// Check if node was already visited
		if(visited[current.x][current.y][current.v_x+3][current.v_y+3])
			continue;
		else
			visited[current.x][current.y][current.v_x+3][current.v_y+3] = true;

		// Print board
		/*for(int a=0; a<X; a++) {
			for(int b=0; b<Y; b++) {
				if(a == current.x && b == current.y)
					cout << "O";
				else if(a == start_x && b == start_y)
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
		printf("Speed (%d, %d). Done %d hops. Queue size %ld.\n", current.v_x, current.v_y, current.num_hops, Q.size());
		cout << "-----" << endl;*/

		// Check if we are at the end
		if(current.x == finish_x && current.y == finish_y) {
			//printf("Optimal solution takes %d hops.", current.num_hops);
			cout << "Optimal solution takes " << current.num_hops << " hops." << endl;
			return;
		}

		// Add all legal changes of velocity into the queue
		for(int d_v_x=-1; d_v_x<=1; d_v_x++) {
			int new_v_x = current.v_x + d_v_x;
			int new_x = current.x + new_v_x;
			if(0 <= new_x && new_x < X && -3 <= new_v_x && new_v_x <= 3) {
				for(int d_v_y=-1; d_v_y<=1; d_v_y++) {
					int new_v_y = current.v_y + d_v_y;
					int new_y  = current.y + new_v_y;
					// Don't push into queue if new node would be in an obstacle
					if(obstacle[new_x][new_y])
						continue;
					if(0 <= new_y && new_y < Y && -3 <= new_v_y && new_v_y <= 3) {
						int new_num_hops = current.num_hops + 1;
						if(new_v_x == 0 && new_v_y == 0)
							new_num_hops -= 1;
						node new_node = node(new_x, new_y, new_v_x, new_v_y, new_num_hops);
						Q.push(new_node);
					}
				}
			}
		}

	}

	cout << "No solution." << endl;

}

int main(void) {
	std::ios_base::sync_with_stdio(false);
	
	int N;
	cin >> N;

	for(int i=0; i<N; i++)
		test_case();

	return 0;
}