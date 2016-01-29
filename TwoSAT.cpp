#include "TwoSAT.h"



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
