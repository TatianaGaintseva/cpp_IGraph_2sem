#include "BigRandomCNF.h"

inline std::pair<std::vector<Conjunct>, int> CreateBigRandomCNF() {
    int variables_amount = rand() % BIG_MAX_VERTICES_AMOUNT;
    variables_amount = variables_amount > 0 ? variables_amount : 1;
    int conjunctions_amount = rand() % BIG_MAX_EDGES_AMOUNT;

    return CreateRandomCNF(variables_amount, conjunctions_amount);
}
