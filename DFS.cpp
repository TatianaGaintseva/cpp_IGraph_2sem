#include "DFS.h"

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
}     if (!visited[vertex]) DFSImplementation(graph, visitor, visited, vertex);
}


