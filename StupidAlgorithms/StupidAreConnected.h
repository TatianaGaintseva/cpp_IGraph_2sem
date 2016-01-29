#pragma once

#include <stack>
#include <math.h>
#include <stdexcept>
#include "IGraph.h"
#include "States.h"


inline bool StupidAreConnected(const std::vector<Edge> &list_of_edges, int vertex_a, int vertex_b, int vertices_amount);
