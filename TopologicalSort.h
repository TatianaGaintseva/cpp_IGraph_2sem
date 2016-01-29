#pragma once

#include <stack>
#include <math.h>
#include <stdexcept>
#include "IGraph.h"
#include "States.h"
#include "DFS.h"

class TopologicalSort {
public:
    TopologicalSort(int vertices_amount);

    void StartProcessingVertex(int vertex);
    void ProcessingEdge(int vertex, int incident_vertex);
    void LeaveVertex(int vertex);
    std::vector<int> GetTopologicalOrder() const;


private:
    std::vector<int> reversed_topological_order_;
    std::vector<state> vertex_condition_;
};

std::vector<int> GetTopologicallyOrderedVerties(const std::vector<Edge> &list_of_edges, int vertices_amount);
