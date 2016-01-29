#pragma once

#include <stack>
#include <math.h>
#include <stdexcept>
#include "IGraph.h"
#include "States.h"

//checks if CNF is satisfiableS


inline void StupidIsSatisfiable(const std::vector<Conjunct>& conjunctions, std::vector<bool>& value, 
                            	    int number_of_variables_to_set, bool &is_satisfiable);
