#include "StupidAreConnected.h"

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
