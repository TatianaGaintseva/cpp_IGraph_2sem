#include "StupidIsSatisfiable.h"


inline void StupidIsSatisfiable(const std::vector<Conjunct>& conjunctions, std::vector<bool>& value, 
                            	    int number_of_variables_to_set, bool &is_satisfiable) {

    if (number_of_variables_to_set >= conjunctions.size()) {
        is_satisfiable = true;
        return;
    }

    Conjunct variables_to_set = conjunctions[number_of_variables_to_set];

    if (value[variables_to_set.variable_[0]] != -1 && value[variables_to_set.variable_[1]] != -1) {
        bool conjunct_1 = variables_to_set.is_positive_[0] ? value[variables_to_set.variable_[0]] : 
                !value[variables_to_set.variable_[0]];
        bool conjunct_2 = variables_to_set.is_positive_[1] ? value[variables_to_set.variable_[1]] : 
                !value[variables_to_set.variable_[1]];

        if (conjunct_1 || conjunct_2) 
            StupidIsSatisfiable(conjunctions, value, number_of_variables_to_set + 1, is_satisfiable);

    }

    if (value[variables_to_set.variable_[0]] != -1 && value[variables_to_set.variable_[1]] == -1) {
        bool conjunct_1 = variables_to_set.is_positive_[0] ? value[variables_to_set.variable_[0]] : 
                !value[variables_to_set.variable_[0]];
        if (conjunct_1) {
            StupidIsSatisfiable(conjunctions, value, number_of_variables_to_set + 1, is_satisfiable);
            return;
        }
      
        value[variables_to_set.variable_[1]] = variables_to_set.is_positive_[1];
        StupidIsSatisfiable(conjunctions, value, number_of_variables_to_set + 1, is_satisfiable);
        value[variables_to_set.variable_[1]] = -1;
    }

    if (value[variables_to_set.variable_[0]] == -1 && value[variables_to_set.variable_[1]] != -1) {
        bool conjunct_2 = variables_to_set.is_positive_[1] ? value[variables_to_set.variable_[1]] : 
                !value[variables_to_set.variable_[1]];
        if (conjunct_2) {
            StupidIsSatisfiable(conjunctions, value, number_of_variables_to_set + 1, is_satisfiable);
            return;
        }
      
        value[variables_to_set.variable_[0]] = variables_to_set.is_positive_[0];
        StupidIsSatisfiable(conjunctions, value, number_of_variables_to_set + 1, is_satisfiable);
        value[variables_to_set.variable_[0]] = -1;
    }

    if (value[variables_to_set.variable_[0]] == -1 && value[variables_to_set.variable_[1]] == -1) {
        value[variables_to_set.variable_[0]] = variables_to_set.is_positive_[0];
        StupidIsSatisfiable(conjunctions, value, number_of_variables_to_set + 1, is_satisfiable);
        value[variables_to_set.variable_[0]] = -1;

        
        value[variables_to_set.variable_[1]] = variables_to_set.is_positive_[1];
        StupidIsSatisfiable(conjunctions, value, number_of_variables_to_set + 1, is_satisfiable);
        value[variables_to_set.variable_[1]] = -1;
    }
}

