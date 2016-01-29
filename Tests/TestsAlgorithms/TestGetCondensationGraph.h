#pragma once

#include <unordered_set>
#include <ctime>
#include "Algo.h"
#include "MakeGraphAndCnf.h"
#include "StupidAlgo.h"
#include "TestsAlgo.h"

inline void TestGetCondensationGraph(const std::vector<Edge> list_of_edges, int vertices_amount, 
                const std::vector< std::set<int> >& components);
