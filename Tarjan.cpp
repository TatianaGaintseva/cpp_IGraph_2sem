#include "Tarjan.h"

Tarjan::Tarjan(int vertices_amount) : parent_(vertices_amount), time_(0), is_root_(vertices_amount, true), 
		 vertex_condition_(vertices_amount, NOT_PROCESSED), vertex_time_(vertices_amount, 0),
			vertex_is_in_component_(vertices_amount, 0) {}

void Tarjan::StartProcessingVertex(int vertex) {
	vertex_time_[vertex] = ++time_;
	vertices_stack_.push(vertex);
	vertex_condition_[vertex] = IN_PROCESSING;
}

void Tarjan::ProcessingEdge(int vertex, int incident_vertex) {
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

void Tarjan::LeaveVertex(int vertex) {
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

std::vector< std::set<int> > Tarjan::GetComponents() const {
	return components_;
}


void Tarjan::NewComponent(int vertex) {
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



std::vector< std::set<int> > GetStrongComponents(const std::vector<Edge> &list_of_edges, int vertices_amount) {
    auto graph = MakeCompactGraph(list_of_edges, vertices_amount);
    Tarjan tarjan_algo(vertices_amount);
    DFS(*graph, tarjan_algo);

    return tarjan_algo.GetComponents();
}
