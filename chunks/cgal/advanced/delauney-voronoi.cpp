#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <iostream>

using namespace std;

typedef CGAL::Exact_predicates_inexact_constructions_kernel		K;
typedef CGAL::Delaunay_triangulation_2<K>						Triangulation;
typedef Triangulation::Finite_faces_iterator					Face_iterator;
typedef Triangulation::All_faces_iterator						All_faces_iterator;
typedef Triangulation::Face_handle								Face_handle;
typedef Triangulation::Point									TP;
typedef Triangulation::Vertex_handle							Vertex_handle;

int main() {

	cout << "CGAL DELAUNEY TRIANGULATIONS" << endl;

	Triangulation t;

	// Insert points. Note that triangulation has its own point class.
	t.insert(TP(1, 1));
	t.insert(TP(3, 3));
	t.insert(TP(4, 1));
	t.insert(TP(5, 3));
	t.insert(TP(7, 2));
	t.insert(TP(7, 4));


	cout << "finite faces:" << endl;
	for (Face_iterator f = t.finite_faces_begin(); f != t.finite_faces_end(); ++f)
 		std::cout << t.triangle(f) << endl;

	cout << "infinite faces:" << endl;
 	// https://judge.inf.ethz.ch/doc/cgal/doc_html/Triangulation/classCGAL_1_1Triangulation.html
 	for (All_faces_iterator f = t.all_faces_begin(); f != t.all_faces_end(); ++f)
 		if(t.is_infinite(f))
 			std::cout << t.triangle(f) << endl;

 	cout << endl;

 	K::Point_2 p1(3, 2);
 	Face_handle f1 = t.locate(p1);

 	cout << "Point p1=(" << p1 << ") is located on face f1=(" << t.triangle(f1) << ")" << endl;
 	Vertex_handle v1 = t.nearest_vertex(p1);

 	cout << "Neighbours of face f1:" << endl;
 	for(int i=0; i<3; i++) {
 		Face_handle neighbor = f1->neighbor(i);
 		if(t.is_infinite(neighbor)) {
		  	cout << "INFINITE";
		  } else {
		  	cout << "FINITE  ";
		  }
 		cout << " " << t.triangle(neighbor) << endl;
 	}

 	cout << "Voronoi vertex on face f1: ";
 	cout << t.dual(f1) << " [WARNING: uses construction]" << endl << endl;

 	// TODO get edges of f1 and print both endpoints of each edge

 	cout << "Nearest vertex to point p1=(" << p1 << ") is v1=(" << v1->point() << ")" << endl;

 	cout << "The neighboring faces of v1 are:" << endl;
 	Triangulation::Face_circulator c = t.incident_faces(v1);
	do {
	  if(t.is_infinite(c)) {
	  	cout << "INFINITE";
	  } else {
	  	cout << "FINITE  ";
	  }

	  cout << " " << t.triangle(c) << endl;
	  
	} while (++c != t.incident_faces(v1));





	return 0;
}
