#include "TestIGraphHasEdge.h"

inline void TestIGraphHasEdge(const IGraph& graph, const std::vector<Edge> &list_of_edges, 
			int vertex_a, int vertex_b) {
	
    bool has_edge_between_a_and_b = graph.HasEdge(vertex_a, vertex_b);
    bool right_has_edge_between_a_and_b = false;

    for (int edge_index = 0; edge_index < list_of_edges.size(); ++edge_index) {
	if (list_of_edges[edge_index].begin_ == vertex_a && list_of_edges[edge_index].end_ == vertex_b) {
	    right_has_edge_between_a_and_b = true;
	    break;
	}
    } 

    if (right_has_edge_between_a_and_b != has_edge_between_a_and_b) {
	throw std::logic_error("TestIGraphHasEdge: FAIL");
    } 
}
