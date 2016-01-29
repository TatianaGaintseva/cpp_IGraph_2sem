#pragma once;

#include <unordered_set>
#include <stdexcept>
#include <typeinfo>
#include "IGraph.h"


inline void TestIGraphHasEdge(const IGraph& graph, const std::vector<Edge> &list_of_edges, 
			int vertex_a, int vertex_b);
