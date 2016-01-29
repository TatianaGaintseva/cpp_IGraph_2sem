#include "BigRandomListOfEdges.h"

inline std::pair<std::vector<Edge>, int> CreateBigRandomListOfEdges() {
    int vertices_amount = rand() % BIG_MAX_VERTICES_AMOUNT;
    vertices_amount = vertices_amount > 0 ? vertices_amount : 1;
    int edges_amount = rand() % BIG_MAX_EDGES_AMOUNT;

    return CreateRandomListOfEdges(vertices_amount, edges_amount);
}
