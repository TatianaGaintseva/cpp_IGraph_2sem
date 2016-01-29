#include "TestMatrixGetIncidenceList.h"

inline void TestMatrixGetIncidenceList(const std::vector<Edge> &list_of_edges, int vertices_amount) {
    try {
	for (int vertex = 0; vertex < vertices_amount; ++vertex)
	    TestIGraphGetIncidenceList (IncidenceMatrixGraph(list_of_edges, vertices_amount), 
			list_of_edges, vertex);
    } catch (const std::exception& ex) {
        throw std::logic_error("MatrixGetIncidenceList: " + std::string(ex.what()));
    }
}
