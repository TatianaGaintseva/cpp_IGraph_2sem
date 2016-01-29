#pragma once

#include <unordered_set>
#include <ctime>
#include "Algo.h"
#include "MakeGraphAndCnf.h"
#include "StupidAlgo.h"
#include "TestsAlgo.h"

inline void StressTestTwoSAT(const std::vector<Conjunct>& conjunctions, int variables_amount);
