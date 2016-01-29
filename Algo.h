#pragma once

#include <stack>
#include <math.h>
#include <stdexcept>
#include "IGraph.h"

typedef enum {
    NOT_PROCESSED = 0,
    IN_PROCESSING,
    PROCESSED,
} state ;


struct Conjunct {
    int variable_[2];
    bool is_positive_[2];
    
    Conjunct(int variable_1, int variable_2, bool is_positive_1, bool is_positive_2) :
		variable_{variable_1, variable_2}, is_positive_{is_positive_1, is_positive_2} {}
};


class TopologicalSort {
public:
    TopologicalSort(int vertices_amount) : vertex_condition_(vertices_amount, NOT_PROCESSED) {}

    void StartProcessingVertex(int vertex) {
	vertex_condition_[vertex] = IN_PROCESSING;
    }

    void ProcessingEdge(int vertex, int incident_vertex) {
	try {
	    if (vertex_condition_[incident_vertex] == IN_PROCESSING) 
		throw std::logic_error("Error:: There is a circle");
        } catch (const std::exception& ex) {
            throw std::logic_error(std::string(ex.what()));
        }
    }

    void LeaveVertex(int vertex) {
	if (vertex_condition_[vertex] == PROCESSED) return;
	vertex_condition_[vertex] = PROCESSED;
	reversed_topological_order_.push_back(vertex);
    }

    std::vector<int> GetTopologicalOrder() const {
	std::vector<int> topological_order(reversed_topological_order_.begin(), reversed_topological_order_.end());
	reverse(topological_order.begin(), topological_order.end());
	return topological_order;
    }


private:
    std::vector<int> reversed_topological_order_;
    std::vector<state> vertex_condition_;
};



class Tarjan {
public:
    Tarjan(int vertices_amount) : parent_(vertices_amount), time_(0), is_root_(vertices_amount, true), 
		 vertex_condition_(vertices_amount, NOT_PROCESSED), vertex_time_(vertices_amount, 0),
			vertex_is_in_component_(vertices_amount, 0) {}
    
    void StartProcessingVertex(int vertex) {
	vertex_time_[vertex] = ++time_;
	vertices_stack_.push(vertex);
	vertex_condition_[vertex] = IN_PROCESSING;
    }

    void ProcessingEdge(int vertex, int incident_vertex) {
	if (vertex_condition_[incident_vertex] == IN_PROCESSING) {
	    if (incident_vertex == vertex) return;
	    vertex_time_[vertex] = std::min(vertex_time_[incident_vertex], vertex_time_[vertex]);
	    is_root_[vertex] = false;
	} 

	if (vertex_condition_[incident_vertex] == NOT_PROCESSED) {
	    parent_[incident_vertex] = vertex;
	}

	if (vertex_condition_[incident_vertex] == PROCESSED) {
	    if (vertex_is_in_component_[incident_vertex] ||
			vertex_time_[vertex] <= vertex_time_[incident_vertex]) return;

	    vertex_time_[vertex] = vertex_time_[incident_vertex];
	    is_root_[vertex] = false;
	    
	}
    }

    void LeaveVertex(int vertex) {
	if (vertex_condition_[vertex] == PROCESSED) return;

	vertex_condition_[vertex] = PROCESSED;
	if (vertex_time_[parent_[vertex]] > vertex_time_[vertex]) {
	    vertex_time_[parent_[vertex]] = vertex_time_[vertex];
	    is_root_[parent_[vertex]] = false;
	}

	if (is_root_[vertex]) {
	    NewComponent(vertex);    
	}
    }

    std::vector< std::set<int> > GetComponents() const {
	return components_;
    }

private:
    int time_;
    std::vector<state> vertex_condition_;
    std::vector< std::set<int> > components_;
    std::stack<int> vertices_stack_;
    std::vector<int> vertex_time_;
    std::vector<int> parent_;
    std::vector<bool> is_root_;
    std::vector<bool> vertex_is_in_component_;



    void NewComponent(int vertex) {
        std::set<int> new_component;
	int current_vertex;

	while (true) {

	    current_vertex = vertices_stack_.top();
	    vertices_stack_.pop();
	    vertex_is_in_component_[current_vertex] = true;
	    new_component.insert(current_vertex);
	    if (current_vertex == vertex) {	
		break;
	    }
    	}
	components_.push_back(new_component);
    }
};


template <class Visitor>
void DFS (const IGraph& graph, Visitor& visitor) {
    std::vector<bool> visited(graph.GetNumberOfVertices(), false);
    for (int vertex = 0; vertex < graph.GetNumberOfVertices(); ++vertex) 
        if (!visited[vertex]) DFSImplementation(graph, visitor, visited, vertex);
}


template <class Visitor>
void DFSImplementation (const IGraph& graph, Visitor& visitor, std::vector<bool>& visited, int vertex_start) {
    std::stack <int> vertices_stack;
    vertices_stack.push(vertex_start);
    
    while (!vertices_stack.empty()) {
        int current_vertex = vertices_stack.top();
	
	if (!visited[current_vertex]) {
	    visited[current_vertex] = true;
	    visitor.StartProcessingVertex(current_vertex);

            std::vector<int> current_vertex_incidences = graph.GetIncidenceList(current_vertex);

            for (int i = 0; i < current_vertex_incidences.size(); ++i) {
                int next_incident_vertex = current_vertex_incidences[i];
	        visitor.ProcessingEdge(current_vertex, next_incident_vertex);
	        if (!visited[next_incident_vertex]) vertices_stack.push(next_incident_vertex);     
            }
	}
	else {
	    visitor.LeaveVertex(current_vertex);
	    vertices_stack.pop();
	}
    }
}


std::vector<int> GetTopologicallyOrderedVerties(const std::vector<Edge> &list_of_edges, int vertices_amount) {
    auto graph = MakeCompactGraph(list_of_edges, vertices_amount);
    TopologicalSort topological_sort(vertices_amount);
    DFS(*graph, topological_sort);

    return topological_sort.GetTopologicalOrder();
}


std::vector< std::set<int> > GetStrongComponents(const std::vector<Edge> &list_of_edges, int vertices_amount) {
    auto graph = MakeCompactGraph(list_of_edges, vertices_amount);
    Tarjan tarjan_algo(vertices_amount);
    DFS(*graph, tarjan_algo);

    return tarjan_algo.GetComponents();
}


inline std::unique_ptr<IGraph> GetCondensationGraph(const IGraph& graph, 
				const std::vector< std::set<int> >& components) {

    std::vector<int> vertex_component_number(graph.GetNumberOfVertices());
    for (size_t component_index = 0; component_index < components.size(); ++component_index) {   
        for (const auto& vertex : components[component_index]) {
            vertex_component_number[vertex] = component_index;
        }
    }

    std::set<Edge> set_of_condensation_graph_edges;
    for (int vertex = 0; vertex < graph.GetNumberOfVertices(); ++vertex) {
	std::vector<int> vertex_incidences = graph.GetIncidenceList(vertex);

	for (size_t i = 0; i < vertex_incidences.size(); ++i) {
	    int incident_vertex = vertex_incidences[i];

	    if (vertex_component_number[incident_vertex] != vertex_component_number[vertex]) 
		set_of_condensation_graph_edges.insert(Edge(vertex_component_number[vertex], 
			vertex_component_number[incident_vertex]));
	}
    }
    std::vector<Edge> list_of_condensation_graph_edges;
    list_of_condensation_graph_edges.insert(list_of_condensation_graph_edges.end(),
		 set_of_condensation_graph_edges.begin(), set_of_condensation_graph_edges.end());

    return MakeCompactGraph(list_of_condensation_graph_edges, components.size());
}


inline std::unique_ptr<IGraph> MakeGraphForTwoSAT(const std::vector<Conjunct>& conjunctions, 
					int variables_amount) {
    std::vector<Edge> list_of_edges;
    
    for (size_t i = 0; i < conjunctions.size() ; ++i) {
	
	// let (x + amount_of_variables) be negative of variable x

	int positive_of_conjunct_1 = conjunctions[i].is_positive_[0] ? 
			conjunctions[i].variable_[0] : variables_amount + conjunctions[i].variable_[0];
	int positive_of_conjunct_2 = conjunctions[i].is_positive_[1] ?  
			conjunctions[i].variable_[1] : variables_amount + conjunctions[i].variable_[1];
	
	int negative_of_conjunct_1 = conjunctions[i].is_positive_[0] ? variables_amount + 
			conjunctions[i].variable_[0] : conjunctions[i].variable_[0];
	int negative_of_conjunct_2 = conjunctions[i].is_positive_[1] ? variables_amount + 
			conjunctions[i].variable_[1] : conjunctions[i].variable_[1];

	list_of_edges.push_back(Edge(negative_of_conjunct_1, positive_of_conjunct_2));
	list_of_edges.push_back(Edge(negative_of_conjunct_2, positive_of_conjunct_1));
    }
    return MakeCompactGraph(list_of_edges, variables_amount * 2);
}


inline bool TwoSAT(const std::vector<Conjunct>& conjunctions, std::vector<bool>& values_of_variables) {
    auto graph = MakeGraphForTwoSAT(conjunctions, values_of_variables.size());
    size_t variables_amount = values_of_variables.size();

    Tarjan tarjan(variables_amount * 2);
    DFS(*graph, tarjan);
    std::vector<int> vertices_component_numbers(variables_amount * 2, -1);
    std::vector< std::set<int> > condensation_graph_vertices = tarjan.GetComponents();

    for (int component_index = 0; component_index < condensation_graph_vertices.size(); ++component_index) {
	std::set<int>::iterator vertex_index;
	for (vertex_index = condensation_graph_vertices[component_index].begin(); 
		vertex_index != condensation_graph_vertices[component_index].end(); ++vertex_index) {
	    vertices_component_numbers[*vertex_index] = component_index;
	}
    }

    for (int variable = 0; variable < variables_amount; ++variable) {
	if (vertices_component_numbers[variable] == vertices_component_numbers[variables_amount + variable]) {
		return false;
	}
    }

    auto condensation_graph = GetCondensationGraph(*graph, condensation_graph_vertices);

    // tarjan algorythm returnes vertices of condensation graph in reversed topological order.
    // so we can just reverse vector condensation_graph_vertices and get vector 
    // topological_condensation_graph_vertices 
    std::vector< std::set<int> > topological_condensation_graph_vertices = condensation_graph_vertices;
    reverse(topological_condensation_graph_vertices.begin(), topological_condensation_graph_vertices.end());
    
    std::vector<bool> values_of_vertices(variables_amount * 2, 0);
    for (size_t component_index = 0; component_index < topological_condensation_graph_vertices.size();
					 ++component_index) {
	for (const auto& vertex : topological_condensation_graph_vertices[component_index]) {
	    if (values_of_vertices[vertex] == 1) continue;

	    values_of_vertices[(vertex + variables_amount) % (variables_amount * 2)] = 1;
	    values_of_variables[vertex % variables_amount] = vertex % variables_amount == vertex ? 0 : 1;
	}
    }

    return true;
}
