#pragma once

#include <stack>
#include <math.h>
#include <stdexcept>
#include "IGraph.h"
#include "States.h"


inline std::set< std::set<int> > StupidTarjan(const std::vector<Edge> &list_of_edges, int vertices_amount);
