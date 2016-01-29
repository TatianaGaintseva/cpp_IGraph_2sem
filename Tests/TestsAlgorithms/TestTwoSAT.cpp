#include "TestTwoSat.cpp"

inline void StressTestTwoSAT(const std::vector<Conjunct>& conjunctions, int variables_amount) {
    try {
        std::vector<bool> values_of_variables(variables_amount);
        bool is_satisfiable = TwoSAT(conjunctions, values_of_variables);

        if (!is_satisfiable) {
            bool right_is_satisfiable = false;
            std::vector<bool> value(variables_amount, -1);
            StupidIsSatisfiable(conjunctions, value, 0, right_is_satisfiable);
            if (right_is_satisfiable) throw std::logic_error("FAIL");
            return;
        }
	for (int i = 0; i < conjunctions.size(); ++i) 
        for (int conjunct_index = 0; conjunct_index < conjunctions.size(); ++conjunct_index) {
            Conjunct conjunct = conjunctions[conjunct_index];

            bool conjunct_1 = conjunct.is_positive_[0] ? values_of_variables[conjunct.variable_[0]] :
                                !values_of_variables[conjunct.variable_[0]];
            bool conjunct_2 = conjunct.is_positive_[1] ? values_of_variables[conjunct.variable_[1]] :
                                !values_of_variables[conjunct.variable_[1]];

            if (!(conjunct_1 || conjunct_2)) throw std::logic_error("FAIL"); 
        }
    } catch (const std::exception& ex) {
        throw std::logic_error("TestTwoSAT: " + std::string(ex.what()));
    }
}
