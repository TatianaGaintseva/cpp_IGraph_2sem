#include "TestMakeCompactGraph.h"

inline void TestMakeCompactGraph(const std::vector<Edge> &list_of_edges, int vertices_amount) {

    try {
	auto graph = MakeCompactGraph(list_of_edges, vertices_amount);

	if (IncidenceMatrixGraph::ByteSize(vertices_amount, list_of_edges.size()) >
                 IncidenceListGraph::ByteSize(vertices_amount, list_of_edges.size())) {

	    if (typeid(*graph) != typeid(IncidenceListGraph)) 
		throw std::logic_error("FAIL");
	}
	else if (typeid(*graph) != typeid(IncidenceMatrixGraph)) 
	    throw std::logic_error("FAIL");
    } catch (const std::exception& ex) {
        throw std::logic_error("TestMakeCompactGraph: " + std::string(ex.what()));
    }
}
