#include "TestMakeGraphForTwoSAT.h"

inline void TestMakeGraphForTwoSAT(const std::vector<Conjunct>& conjunctions, int variables_amount) {
    try {
        auto graph = MakeGraphForTwoSAT(conjunctions, variables_amount);
        for (int i = 0; i < conjunctions.size(); ++i) {

            int positive_of_conjunct_1 = conjunctions[i].is_positive_[0] ? 
                        conjunctions[i].variable_[0] : variables_amount + conjunctions[i].variable_[0];
            int positive_of_conjunct_2 = conjunctions[i].is_positive_[1] ?  
                        conjunctions[i].variable_[1] : variables_amount + conjunctions[i].variable_[1];
        
            int negative_of_conjunct_1 = conjunctions[i].is_positive_[0] ? variables_amount + 
                        conjunctions[i].variable_[0] : conjunctions[i].variable_[0];
            int negative_of_conjunct_2 = conjunctions[i].is_positive_[1] ? variables_amount + 
                        conjunctions[i].variable_[1] : conjunctions[i].variable_[1];

            bool edge_not_1_to_2 = graph->HasEdge(negative_of_conjunct_1, positive_of_conjunct_2);
            bool edge_not_2_to_1 = graph->HasEdge(negative_of_conjunct_2, positive_of_conjunct_1);
        
            if(!(edge_not_1_to_2 && edge_not_2_to_1)) throw std::logic_error("FAIL");
        }
    } catch (const std::exception& ex) {
        throw std::logic_error("TestTarjan: " + std::string(ex.what()));
    }
}
