#include "FullListOfEdges.h"

inline std::vector<Edge> CreateFullListOfEdges(int vertices_amount) {

    std::vector<Edge> list_of_edges;

    for (int vertex_a = 0; vertex_a < vertices_amount; ++vertex_a) 
	for (int vertex_b = 0; vertex_b < vertices_amount; ++vertex_b)
	     list_of_edges.push_back(Edge(vertex_a, vertex_b));

    return list_of_edges;
}
