#include <iostream>
#include <fstream>
#include <cassert>
#include <list>
#include <vector>

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_3.h>
#include <CGAL/Triangulation_vertex_base_with_info_3.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Triangulation_vertex_base_with_info_3<CGAL::Color,K> Vb;
typedef CGAL::Triangulation_data_structure_3<Vb> Tds;
typedef CGAL::Delaunay_triangulation_3<K, Tds> Delaunay;
typedef Delaunay::Edge Delaunay_edge;
typedef Delaunay::Point Point;

typedef Delaunay::Point   Point;

int main()
{
    std::ofstream oFileT("output.txt",std::ios::out);

    // Points that are evenly distributed in cuboid space
    std::list<Point> L;
    for (int x = 0; x <5 ; x ++) {
        for (int y = 0; y < 5; y ++) {
            for (int z = 0; z < 5; z ++) {
                L.push_front(Point(x, y, z));
            }
        }
    }

    // Do delaunay triangulation
    Delaunay T(L.begin(), L.end());;
    
    Delaunay::Triangulation_3::Finite_edges_iterator eit = T.finite_edges_begin(); 
    Delaunay::Triangulation_3::Finite_edges_iterator end = T.finite_edges_end(); 

    Point p;
    Point q;    
    ++eit;

    // Get the line segment(from point p to point q)
    // Save the data and we will plot with Matlab
    for(;eit != end; ++eit) 
    { 
        Delaunay_edge edge = *eit;   
        q = edge.first->vertex(edge.third)->point();
        p = edge.first->vertex(edge.second)->point();

        oFileT << p << '\n' << q << std::endl;
    }

    return 0;
}