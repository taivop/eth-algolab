#include <iostream>
#include <vector>
#include <queue>

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
	vector<node> visited;
	queue<node> Q;

	node start = node(start_x, start_y, 0, 0, 0);
	Q.push(start);

	while(!Q.empty()) {
		// Take a node and mark as visited
		node current = Q.front();
		Q.pop();

		// Check if node was already visited
		bool already_visited = false;
		for(int i=0; i<visited.size(); i++) {
			if(visited[i] == current) {
				already_visited = true;
				break;
			}
		}
		if(already_visited)
			continue;
		else
			visited.push_back(current);

		// Check if we are at the end
		if(current.x == finish_x && current.y == finish_y) {
			printf("Optimal solution takes %d hops.\n", current.num_hops);
			return;
		}

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
		}*/

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
						node new_node = node(new_x, new_y, new_v_x, new_v_y, current.num_hops+1);
						Q.push(new_node);
					}
				}
			}
		}

		/*printf("Queue size %ld.\n", Q.size());
		cout << "-----" << endl;*/

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