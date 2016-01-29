#pragma once

#include <ctime>
#include "IGraph.h"
#include "DFS.h"
#include "Tarjan.h"
#include "TopologicalSort.h"
#include "TwoSAT.h"
#include "Constants.h"


inline std::pair<std::vector<Edge>, int> CreateRandomListOfEdges(int vertices_amount, int edges_amount);
