#include "TestGetCondensationGraph.h"

inline void TestGetCondensationGraph(const std::vector<Edge> list_of_edges, int vertices_amount, 
                const std::vector< std::set<int> >& components) {
    try {
	auto graph = MakeCompactGraph(list_of_edges, vertices_amount);
        std::vector<int> vertex_component_number(graph->GetNumberOfVertices());

        for (size_t component_index = 0; component_index < components.size(); ++component_index) {   
            for (const auto& vertex : components[component_index]) {
                vertex_component_number[vertex] = component_index;
            }
        }
  
        std::set<Edge> right_set_of_condensation_graph_edges;
        for (int vertex = 0; vertex < graph->GetNumberOfVertices(); ++vertex) {
            std::vector<int> vertex_incidences = graph->GetIncidenceList(vertex);

            for (size_t i = 0; i < vertex_incidences.size(); ++i) {
                int incident_vertex = vertex_incidences[i];

                if (vertex_component_number[incident_vertex] != vertex_component_number[vertex]) 
                    right_set_of_condensation_graph_edges.insert(Edge(vertex_component_number[vertex], 
                            vertex_component_number[incident_vertex]));
            }
        }

        auto condensation_graph = GetCondensationGraph(*graph, components);
        if (condensation_graph->GetNumberOfVertices() != components.size()) throw std::logic_error("FAIL");
        std::set<Edge> algo_set_of_condensation_graph_edges;
        for (int vertex = 0; vertex < condensation_graph->GetNumberOfVertices(); ++vertex) {
            std::vector<int> vertex_incidences = condensation_graph->GetIncidenceList(vertex);
        
            for (size_t i = 0; i < vertex_incidences.size(); ++i) {
                int incident_vertex = vertex_incidences[i];
                algo_set_of_condensation_graph_edges.insert(Edge(vertex, incident_vertex));
            }
        }

        if (right_set_of_condensation_graph_edges != algo_set_of_condensation_graph_edges) 
            throw std::logic_error("FAIL");
    } catch (const std::exception& ex) {
        throw std::logic_error("TestGetCondensationGraph: " + std::string(ex.what()));
    }
} 
