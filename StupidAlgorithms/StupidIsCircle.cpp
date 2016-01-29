#include "StupidIsCircle.h"

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
