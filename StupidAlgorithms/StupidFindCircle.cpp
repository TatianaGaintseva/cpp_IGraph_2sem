#include "StupidFindCircle.h"

inline void StupidFindSircle(const std::vector<Edge>& list_of_edges, int vertex, std::vector<state>& processed, 
			   bool &is_sircle) {
    processed[vertex] = IN_PROCESSING;

    for (int edge_index = 0; edge_index < list_of_edges.size(); ++edge_index) {
	if (list_of_edges[edge_index].begin_ != vertex) continue;

	if (processed[list_of_edges[edge_index].end_] == IN_PROCESSING) { 
	    is_sircle = true;
	    return;
	}

	if (processed[list_of_edges[edge_index].end_] == NOT_PROCESSED) { 
	    StupidFindSircle(list_of_edges, list_of_edges[edge_index].end_, processed, is_sircle); 
	    if (is_sircle) return;
	}
    }
    processed[vertex] = PROCESSED;
}
