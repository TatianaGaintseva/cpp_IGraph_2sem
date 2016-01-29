#pragma once

#include <stack>
#include <math.h>
#include <stdexcept>
#include "IGraph.h"
#include "States.h"

template <class Visitor>
void DFS (const IGraph& graph, Visitor& visitor);

template <class Visitor>
void DFSImplementation (const IGraph& graph, Visitor& visitor, std::vector<bool>& visited, int vertex_start);
