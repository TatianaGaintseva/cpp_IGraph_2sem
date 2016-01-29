#include "TestListHasEdge.h"


inline void TestListHasEdge(const std::vector<Edge> &list_of_edges, int vertices_amount) {
    try {
	IncidenceListGraph graph(list_of_edges, vertices_amount);
	for (int vertex_a = 0; vertex_a < vertices_amount; ++vertex_a) {
	    for (int vertex_b = 0; vertex_b < vertices_amount; ++vertex_b) {
		TestIGraphHasEdge(graph, list_of_edges, vertex_a,  vertex_b);
	    }
	}
    } catch (const std::exception& ex) {
        throw std::logic_error("TestListHasEdge: " + std::string(ex.what()));
    }
}

