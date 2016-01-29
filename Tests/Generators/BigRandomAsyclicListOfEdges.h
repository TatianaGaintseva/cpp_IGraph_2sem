#pragma once

#include <ctime>
#include "IGraph.h"
#include "DFS.h"
#include "Tarjan.h"
#include "TopologicalSort.h"
#include "TwoSAT.h"
#include "Constants.h"
#include "RandomAsyclicListOfEdges.h"

inline std::pair<std::vector<Edge>, int> CreateBigRandomAsyclicListOfEdges();
