#include "TestMatrixGetNumberOfVertices.h"

inline void TestMatrixGetNumberOfVertices (std::vector<Edge> &list_of_edges, 
					int vertices_amount) {
    try {
	TestIGraphGetNumberOfVertices (IncidenceMatrixGraph(list_of_edges, vertices_amount), vertices_amount);
    } catch (const std::exception& ex) {
        throw std::logic_error("MatrixGetNumberOfVertices: " + std::string(ex.what()));
    }
}
