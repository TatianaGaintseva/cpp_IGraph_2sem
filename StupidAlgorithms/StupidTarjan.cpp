#include "StupidTarjan.h"

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
