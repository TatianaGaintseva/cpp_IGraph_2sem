#pragma once

#include <ctime>
#include "IGraph.h"
#include "DFS.h"
#include "Tarjan.h"
#include "TopologicalSort.h"
#include "TwoSAT.h"
#include "Constants.h"


inline std::pair<std::vector<Conjunct>, int> CreateRandomCNF(int variables_amount, int conjunctions_amount);
