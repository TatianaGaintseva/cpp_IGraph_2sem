#pragma once

#include <ctime>
#include "IGraph.h"
#include "Algo.h"

const int BIG_MAX_VERTICES_AMOUNT = INT_MAX / (1024 * 1024);
const int BIG_MAX_EDGES_AMOUNT = INT_MAX / (1024 * 1024);

const int SMALL_MAX_VERTICES_AMOUNT = INT_MAX / (1024 * 1024 * 64);
const int SMALL_MAX_EDGES_AMOUNT = INT_MAX / (1024 * 1024 * 64);


inline std::pair<std::vector<Edge>, int> CreateRandomListOfEdges(int vertices_amount, int edges_amount) {
    std::vector<Edge> list_of_edges;
    for (int i = 0; i < edges_amount; ++i) {
	int begin  = rand() % vertices_amount;
	int end = rand() % vertices_amount;
	list_of_edges.push_back( Edge(begin, end) );
    }
    return std::pair<std::vector<Edge>, int >(list_of_edges, vertices_amount);
}


inline std::pair<std::vector<Edge>, int> CreateSmallRandomListOfEdges() {
    int vertices_amount = rand() % SMALL_MAX_VERTICES_AMOUNT;
    vertices_amount = vertices_amount > 0 ? vertices_amount : 1;
    int edges_amount = rand() % SMALL_MAX_EDGES_AMOUNT;

    return CreateRandomListOfEdges(vertices_amount, edges_amount);
}


inline std::pair<std::vector<Edge>, int> CreateBigRandomListOfEdges() {
    int vertices_amount = rand() % BIG_MAX_VERTICES_AMOUNT;
    vertices_amount = vertices_amount > 0 ? vertices_amount : 1;
    int edges_amount = rand() % BIG_MAX_EDGES_AMOUNT;

    return CreateRandomListOfEdges(vertices_amount, edges_amount);
}

inline std::pair<std::vector<Edge>, int> CreateRandomAsyclicListOfEdges(int vertices_amount, int edges_amount) {
    std::vector<int> vertices;
    for (int i = 0; i < vertices_amount; ++i) vertices.push_back(i);
    std::random_shuffle(vertices.begin(), vertices.end());

    std::vector<Edge> list_of_edges;
    for (int i = 0; i < edges_amount; ++i) {
	int begin_index = rand() % (vertices_amount - 1);
	int end_index = begin_index + rand() % (vertices_amount - begin_index);
	end_index = ((end_index == begin_index) ? begin_index + 1 : end_index);

	int begin  = vertices[begin_index];
	int end = vertices[end_index];
       
	list_of_edges.push_back( Edge(begin, end) );
    }

    return std::pair<std::vector<Edge>, int>(list_of_edges, vertices_amount);
}  


inline std::pair<std::vector<Edge>, int> CreateSmallRandomAsyclicListOfEdges() {
    int vertices_amount = rand() % SMALL_MAX_VERTICES_AMOUNT;
    vertices_amount = vertices_amount > 1 ? vertices_amount : 2;
    int edges_amount = rand() % SMALL_MAX_EDGES_AMOUNT;

    return CreateRandomAsyclicListOfEdges(vertices_amount, edges_amount);
}


inline std::pair<std::vector<Edge>, int> CreateBigRandomAsyclicListOfEdges() {
    int vertices_amount = rand() % BIG_MAX_VERTICES_AMOUNT;
    vertices_amount = vertices_amount > 1 ? vertices_amount : 2;
    int edges_amount = rand() % BIG_MAX_EDGES_AMOUNT;

    return CreateRandomAsyclicListOfEdges(vertices_amount, edges_amount);
}


inline std::vector<Edge> CreateFullListOfEdges(int vertices_amount) {

    std::vector<Edge> list_of_edges;

    for (int vertex_a = 0; vertex_a < vertices_amount; ++vertex_a) 
	for (int vertex_b = 0; vertex_b < vertices_amount; ++vertex_b)
	     list_of_edges.push_back(Edge(vertex_a, vertex_b));

    return list_of_edges;
}


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


inline std::pair<std::vector<Conjunct>, int> CreateSmallRandomCNF() {
    int variables_amount = rand() % SMALL_MAX_VERTICES_AMOUNT;
    variables_amount = variables_amount > 0 ? variables_amount : 1;
    int conjunctions_amount = rand() % SMALL_MAX_EDGES_AMOUNT;

    return CreateRandomCNF(variables_amount, conjunctions_amount);
}


inline std::pair<std::vector<Conjunct>, int> CreateBigRandomCNF() {
    int variables_amount = rand() % BIG_MAX_VERTICES_AMOUNT;
    variables_amount = variables_amount > 0 ? variables_amount : 1;
    int conjunctions_amount = rand() % BIG_MAX_EDGES_AMOUNT;

    return CreateRandomCNF(variables_amount, conjunctions_amount);
}


