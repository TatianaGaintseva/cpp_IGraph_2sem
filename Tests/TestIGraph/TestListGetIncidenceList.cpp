#include "TestListGetIncidenceList.h"

inline void TestListGetIncidenceList(const std::vector<Edge> &list_of_edges, int vertices_amount) {
    try {
	for (int vertex = 0; vertex < vertices_amount; ++vertex)
            TestIGraphGetIncidenceList (IncidenceListGraph(list_of_edges, vertices_amount), 
			list_of_edges, vertex);
    } catch (const std::exception& ex) {
        throw std::logic_error("ListGetIncidenceList: " + std::string(ex.what()));
    }
}

