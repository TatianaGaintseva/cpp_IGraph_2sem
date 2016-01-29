#include "TestDFS.h"

void FirstSearchTester::StartProcessingVertex(int vertex) {
	if (vertices_processed_.find(vertex) != vertices_processed_.end()) throw std::logic_error("FAIL");
        vertices_processed_.insert(vertex);
}

void FirstSearchTester::ProcessingEdge(int vertex, int incident_vertex) {
    edges_processed_.insert(Edge(vertex, incident_vertex));
}

void FirstSearchTester::LeaveVertex(int vertex) {}

std::set<int> FirstSearchTester::GetVerticesProcessed() { return  vertices_processed_;}

std::set<Edge> FirstSearchTester::GetEdgesProcessed() { return edges_processed_;}


inline void OneFirstSearchTest(const std::vector<Edge> &list_of_edges, int vertices_amount, FirstSearchTester& tester) {
    std::set<int> vertices_set;
    for (int vertex = 0; vertex < vertices_amount; ++vertex) vertices_set.insert(vertex);

    if (tester.GetVerticesProcessed() != vertices_set) throw std::logic_error("FAIL");

    std::set<Edge> set_of_edges(list_of_edges.begin(), list_of_edges.end());
    if (tester.GetEdgesProcessed() != set_of_edges) throw std::logic_error("FAIL");
}

inline void FirstSearchTests(const std::vector<Edge> &list_of_edges, int vertices_amount) {
        auto graph = MakeCompactGraph(list_of_edges, vertices_amount);

    try {
        FirstSearchTester dfs_tester;
        DFS(*graph, dfs_tester);
        OneFirstSearchTest(list_of_edges, vertices_amount, dfs_tester);
    } catch (const std::exception& ex) {
        throw std::logic_error("TestDFS: " + std::string(ex.what()));
    }
}

