#include "TestTopologicalSort.cpp"

inline void StressTestTopologicalSort(const std::vector<Edge> &list_of_edges, int vertices_amount) {

    try {
        if (StupidIsSircle(vertices_amount, list_of_edges)) return;

        std::vector<int> topologically_ordered_vertices = GetTopologicallyOrderedVerties(list_of_edges, vertices_amount);
        if (topologically_ordered_vertices.size() != vertices_amount) throw std::logic_error("FAIL");

	auto graph = MakeCompactGraph(list_of_edges, vertices_amount);
        for (int i = 0; i < topologically_ordered_vertices.size() - 1; ++i) {
            for (int j = i + 1; j < topologically_ordered_vertices.size(); ++j) {
                if (graph->HasEdge(topologically_ordered_vertices[j], topologically_ordered_vertices[i]))
                     throw std::logic_error("FAIL");
            }
        } 
    } catch (const std::exception& ex) {
        throw std::logic_error("TestTopologicalSort: " + std::string(ex.what()));
    }
}
