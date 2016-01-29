#pragma once

#include <stack>
#include <math.h>
#include <stdexcept>
#include "IGraph.h"
#include "States.h"


inline void StupidFindSircle(const std::vector<Edge>& list_of_edges, int vertex, std::vector<state>& processed, 
			   bool &is_sircle);
