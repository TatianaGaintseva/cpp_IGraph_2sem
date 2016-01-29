#include "SmallRandomCNF.h"

inline std::pair<std::vector<Conjunct>, int> CreateSmallRandomCNF() {
    int variables_amount = rand() % SMALL_MAX_VERTICES_AMOUNT;
    variables_amount = variables_amount > 0 ? variables_amount : 1;
    int conjunctions_amount = rand() % SMALL_MAX_EDGES_AMOUNT;

    return CreateRandomCNF(variables_amount, conjunctions_amount);
}
