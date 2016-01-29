#pragma once

#include <stack>
#include <math.h>
#include <stdexcept>
#include "IGraph.h"
#include "States.h"
#include "TopologicalSort.h"
#include "Tarjan.h"
#include "DFS.h"


struct Conjunct {
    int variable_[2];
    bool is_positive_[2];
    
    Conjunct(int variable_1, int variable_2, bool is_positive_1, bool is_positive_2) :
		variable_{variable_1, variable_2}, is_positive_{is_positive_1, is_positive_2} {}
};



inline std::unique_ptr<IGraph> GetCondensationGraph(const IGraph& graph, 
				const std::vector< std::set<int> >& components);

inline std::unique_ptr<IGraph> MakeGraphForTwoSAT(const std::vector<Conjunct>& conjunctions, 
					int variables_amount);

inline bool TwoSAT(const std::vector<Conjunct>& conjunctions, std::vector<bool>& values_of_variables);


