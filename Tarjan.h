#pragma once

#include <stack>
#include <math.h>
#include <stdexcept>
#include "IGraph.h"
#include "States.h"
#include "TopologicalSort.h"
#include "DFS.h"

class Tarjan {
public:
    Tarjan(int vertices_amount);   
    void StartProcessingVertex(int vertex);
    void ProcessingEdge(int vertex, int incident_vertex);
    void LeaveVertex(int vertex);
    std::vector< std::set<int> > GetComponents() const;

private:
    int time_;
    std::vector<state> vertex_condition_;
    std::vector< std::set<int> > components_;
    std::stack<int> vertices_stack_;
    std::vector<int> vertex_time_;
    std::vector<int> parent_;
    std::vector<bool> is_root_;
    std::vector<bool> vertex_is_in_component_;

    void NewComponent(int vertex);
};



std::vector< std::set<int> > GetStrongComponents(const std::vector<Edge> &list_of_edges, int vertices_amount);

