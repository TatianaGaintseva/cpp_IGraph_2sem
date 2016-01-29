#pragma once

#include "Algo.h"


inline void StupidFindSircle(const std::vector<Edge>& list_of_edges, int vertex, std::vector<state>& processed, 
			   bool &is_sircle) {
    processed[vertex] = IN_PROCESSING;

    for (int edge_index = 0; edge_index < list_of_edges.size(); ++edge_index) {
	if (list_of_edges[edge_index].begin_ != vertex) continue;

	if (processed[list_of_edges[edge_index].end_] == IN_PROCESSING) { 
	    is_sircle = true;
	    return;
	}

	if (processed[list_of_edges[edge_index].end_] == NOT_PROCESSED) { 
	    StupidFindSircle(list_of_edges, list_of_edges[edge_index].end_, processed, is_sircle); 
	    if (is_sircle) return;
	}
    }
    processed[vertex] = PROCESSED;
}

inline bool StupidIsSircle(int vertices_amount, const std::vector<Edge>& list_of_edges) {
    				std::vector<state> processed(vertices_amount, NOT_PROCESSED);
    bool is_sircle = false;

    for (int vertex = 0; vertex < vertices_amount; ++vertex) {
	if (!processed[vertex]) {
	    StupidFindSircle(list_of_edges, vertex, processed, is_sircle);
	    if (is_sircle) return true;
	}
    }
    return false;
}



inline bool StupidAreConnected(const std::vector<Edge> &list_of_edges, int vertex_a, int vertex_b, int vertices_amount) {
    std::stack<int> vertices_stack;
    vertices_stack.push(vertex_a); 
    std::vector<bool> visited (vertices_amount, 0);

    while (!vertices_stack.empty()) {
        int vertex = vertices_stack.top();
        vertices_stack.pop();
        if (visited[vertex]) continue;
        visited[vertex] = true;
        
        for (int edge_index = 0; edge_index < list_of_edges.size(); ++edge_index) {
            if (list_of_edges[edge_index].begin_ == vertex && list_of_edges[edge_index].end_ == vertex_b)
                 return true;
            if (list_of_edges[edge_index].begin_ == vertex && !visited[list_of_edges[edge_index].end_])
                 vertices_stack.push(list_of_edges[edge_index].end_);
        }
    }
    return false;
}


inline std::set< std::set<int> > StupidTarjan(const std::vector<Edge> &list_of_edges, int vertices_amount) {
    std::set< std::set<int> > answer;
    std::vector<bool> is_in_component(vertices_amount, 0);

    for (int vertex = 0; vertex < vertices_amount; ++vertex) {
        if (is_in_component[vertex]) continue;

        is_in_component[vertex] = true;
        std::set<int> new_component;
        new_component.insert(vertex);
        for (int next_vertex = 0; next_vertex < vertices_amount; ++next_vertex) {
            if (is_in_component[next_vertex]) continue;
            if (StupidAreConnected(list_of_edges, vertex, next_vertex, vertices_amount) && 
                        StupidAreConnected(list_of_edges, next_vertex, vertex, vertices_amount)) {
                new_component.insert(next_vertex);
                is_in_component[next_vertex] = true;
            }
        }
        answer.insert(new_component);
    }
    return answer;
}



inline void StupidIsSatisfiable(const std::vector<Conjunct>& conjunctions, std::vector<bool>& value, 
                            	    int number_of_variables_to_set, bool &is_satisfiable) {

    if (number_of_variables_to_set >= conjunctions.size()) {
        is_satisfiable = true;
        return;
    }

    Conjunct variables_to_set = conjunctions[number_of_variables_to_set];

    if (value[variables_to_set.variable_[0]] != -1 && value[variables_to_set.variable_[1]] != -1) {
        bool conjunct_1 = variables_to_set.is_positive_[0] ? value[variables_to_set.variable_[0]] : 
                !value[variables_to_set.variable_[0]];
        bool conjunct_2 = variables_to_set.is_positive_[1] ? value[variables_to_set.variable_[1]] : 
                !value[variables_to_set.variable_[1]];

        if (conjunct_1 || conjunct_2) 
            StupidIsSatisfiable(conjunctions, value, number_of_variables_to_set + 1, is_satisfiable);

    }

    if (value[variables_to_set.variable_[0]] != -1 && value[variables_to_set.variable_[1]] == -1) {
        bool conjunct_1 = variables_to_set.is_positive_[0] ? value[variables_to_set.variable_[0]] : 
                !value[variables_to_set.variable_[0]];
        if (conjunct_1) {
            StupidIsSatisfiable(conjunctions, value, number_of_variables_to_set + 1, is_satisfiable);
            return;
        }
      
        value[variables_to_set.variable_[1]] = variables_to_set.is_positive_[1];
        StupidIsSatisfiable(conjunctions, value, number_of_variables_to_set + 1, is_satisfiable);
        value[variables_to_set.variable_[1]] = -1;
    }

    if (value[variables_to_set.variable_[0]] == -1 && value[variables_to_set.variable_[1]] != -1) {
        bool conjunct_2 = variables_to_set.is_positive_[1] ? value[variables_to_set.variable_[1]] : 
                !value[variables_to_set.variable_[1]];
        if (conjunct_2) {
            StupidIsSatisfiable(conjunctions, value, number_of_variables_to_set + 1, is_satisfiable);
            return;
        }
      
        value[variables_to_set.variable_[0]] = variables_to_set.is_positive_[0];
        StupidIsSatisfiable(conjunctions, value, number_of_variables_to_set + 1, is_satisfiable);
        value[variables_to_set.variable_[0]] = -1;
    }

    if (value[variables_to_set.variable_[0]] == -1 && value[variables_to_set.variable_[1]] == -1) {
        value[variables_to_set.variable_[0]] = variables_to_set.is_positive_[0];
        StupidIsSatisfiable(conjunctions, value, number_of_variables_to_set + 1, is_satisfiable);
        value[variables_to_set.variable_[0]] = -1;

        
        value[variables_to_set.variable_[1]] = variables_to_set.is_positive_[1];
        StupidIsSatisfiable(conjunctions, value, number_of_variables_to_set + 1, is_satisfiable);
        value[variables_to_set.variable_[1]] = -1;
    }
}

