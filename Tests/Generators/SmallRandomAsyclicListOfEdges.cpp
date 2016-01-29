#include "SmallRandomAsyclicListOfEdges.h"

inline std::pair<std::vector<Edge>, int> CreateSmallRandomAsyclicListOfEdges() {
    int vertices_amount = rand() % SMALL_MAX_VERTICES_AMOUNT;
    vertices_amount = vertices_amount > 1 ? vertices_amount : 2;
    int edges_amount = rand() % SMALL_MAX_EDGES_AMOUNT;

    return CreateRandomAsyclicListOfEdges(vertices_amount, edges_amount);
}
