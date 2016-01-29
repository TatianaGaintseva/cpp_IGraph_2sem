#pragma once

#include <ctime>
#include "IGraph.h"
#include "DFS.h"
#include "Tarjan.h"
#include "TopologicalSort.h"
#include "TwoSAT.h"
#include "Constants.h"
#include "RandomCNF.h"


inline std::pair<std::vector<Conjunct>, int> CreateSmallRandomCNF();
