#pragma once

#include <unordered_set>
#include <ctime>
#include "Algo.h"
#include "MakeGraphAndCnf.h"
#include "StupidAlgo.h"

class FirstSearchTester {
public:

    void StartProcessingVertex(int vertex);

    void ProcessingEdge(int vertex, int incident_vertex);

    void LeaveVertex(int vertex);

    std::set<int> GetVerticesProcessed();

    std::set<Edge> GetEdgesProcessed();

private:
    std::set<int> vertices_processed_;
    std::set<Edge> edges_processed_;
};


inline void OneFirstSearchTest(const std::vector<Edge> &list_of_edges, int vertices_amount, FirstSearchTester& tester);

inline void FirstSearchTests(const std::vector<Edge> &list_of_edges, int vertices_amount);

