#include "TestIGraphGetIncidenceList.h"

inline void TestIGraphGetIncidenceList(const IGraph& graph, const std::vector<Edge> &list_of_edges, int vertex) {

    std::unordered_set<int> right_insidence_vertices_set;


    std::vector<int> incidence_list = graph.GetIncidenceList(vertex);
    std::unordered_set<int> incidence_vertices_set(incidence_list.begin(), incidence_list.end());

    for (int edge_index = 0; edge_index < list_of_edges.size(); ++edge_index) {
	if (list_of_edges[edge_index].begin_ == vertex) {
	    right_insidence_vertices_set.insert(list_of_edges[edge_index].end_);
	}
    }

    if (incidence_vertices_set != right_insidence_vertices_set) {
	throw std::logic_error("IGraph::GetIncidenceList : FAIL");
    } 
	
}
