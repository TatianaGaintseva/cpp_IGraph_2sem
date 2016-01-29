#include "IGraph.h"

inline std::pair<std::vector<Edge>, int> CreateRandomListOfEdges(int vertices_amount, int edges_amount) {
    std::vector<Edge> list_of_edges;
    for (int i = 0; i < edges_amount; ++i) {
	int begin  = rand() % vertices_amount;
	int end = rand() % vertices_amount;
	list_of_edges.push_back( Edge(begin, end) );
    }
    return std::pair<std::vector<Edge>, int >(list_of_edges, vertices_amount);
}
