#include <iostream>
#include <vector>
#include <algorithm>
#include <CGAL/Exact_predicates_exact_constructions_kernel_with_sqrt.h>
#include <CGAL/Min_circle_2.h>
#include <CGAL/Min_circle_2_traits_2.h>

typedef CGAL::Exact_predicates_exact_constructions_kernel_with_sqrt K;
typedef CGAL::Min_circle_2_traits_2<K>  Traits;
typedef CGAL::Min_circle_2<Traits>      Min_circle;
typedef CGAL::Min_circle_2< Traits >::Support_point_iterator Support_point_iterator;


using namespace std;

double ceil_to_double(const K::FT& x)
{
  double a = std::ceil(CGAL::to_double(x));
  while (a < x) a += 1;
  while (a-1 >= x) a -= 1;
  return a;
}

void test_case(int n) {
	//cout << "n == " << n << endl;

	vector<K::Point_2> points;
	points.reserve(n);

	for(int i=0; i<n; i++) {
		long x, y;
		cin >> x >> y;
		//cout << x << ", " << y << endl;

		K::Point_2 p(x, y);
		points.push_back(p);
	}

	Min_circle mc(points.begin(), points.end(), true);

	// Remove points one by one and find minimum radius
	K::FT min_r_squared = mc.circle().squared_radius();

	for(int i=0; i<mc.number_of_support_points(); i++) {
		vector<K::Point_2> points_new = points;

		Support_point_iterator to_erase = find(points_new.begin(), points_new.end(), mc.support_point(i));

		if(to_erase != points_new.end())
			points_new.erase(to_erase);

		Min_circle mc_new(points_new.begin(), points_new.end(), true);
		K::FT r_squared = mc_new.circle().squared_radius();

		if(r_squared < min_r_squared)
			min_r_squared = r_squared;
	}

	cout << (long) ceil_to_double(sqrt(min_r_squared)) << endl;
	
	return;
}

int main(void) {
	std::ios_base::sync_with_stdio(false);
	
	int n;
	
	cin >> n;

	while(n != 0) {
		test_case(n);
		cin >> n;
	}

	return 0;
}