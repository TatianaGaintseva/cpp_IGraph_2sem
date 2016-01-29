#include "TestIGraphGetNumberOfVertices.h"

inline void TestIGraphGetNumberOfVertices (const IGraph& graph, int vertices_amount) {
    if (graph.GetNumberOfVertices() != vertices_amount) {
	throw std::logic_error("IGraph::GetNumberOfVertices: FAIL");
    } 
}
