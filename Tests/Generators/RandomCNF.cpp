#include "RandomCNF.h"

inline std::pair<std::vector<Conjunct>, int> CreateRandomCNF(int variables_amount, int conjunctions_amount) {
    std::vector<Conjunct> conjunctions;

    for (int i = 0; i < conjunctions_amount; ++i) {
        int conjunct_1  = rand() % variables_amount;
        int conjunct_2 = rand() % variables_amount;
        bool conjunct_1_state = rand() % 2;
        bool conjunct_2_state = rand() % 2;
        conjunctions.push_back(Conjunct(conjunct_1, conjunct_2, conjunct_1_state, conjunct_2_state));
    }
    return std::pair<std::vector<Conjunct>, int >(conjunctions, variables_amount);
}
