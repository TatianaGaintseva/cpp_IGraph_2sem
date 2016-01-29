#include "RandomAsyclicListOfEdges.h"

inline std::pair<std::vector<Edge>, int> CreateRandomAsyclicListOfEdges(int vertices_amount, int edges_amount) {
    std::vector<int> vertices;
    for (int i = 0; i < vertices_amount; ++i) vertices.push_back(i);
    std::random_shuffle(vertices.begin(), vertices.end());

    std::vector<Edge> list_of_edges;
    for (int i = 0; i < edges_amount; ++i) {
	int begin_index = rand() % (vertices_amount - 1);
	int end_index = begin_index + rand() % (vertices_amount - begin_index);
	end_index = ((end_index == begin_index) ? begin_index + 1 : end_index);

	int begin  = vertices[begin_index];
	int end = vertices[end_index];
       
	list_of_edges.push_back( Edge(begin, end) );
    }

    return std::pair<std::vector<Edge>, int>(list_of_edges, vertices_amount);
} 
