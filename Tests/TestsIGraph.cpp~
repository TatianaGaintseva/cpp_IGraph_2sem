#include <unordered_set>
#include <stdexcept>
#include <typeinfo>
#include "IGraph.h"
#include "Algo.h"
#include "MakeGraphAndCnf.h"
#include "TestsIGraph.h"

const int IGRAPH_TESTS_NUMBER = INT_MAX / (1024 * 1024 * 4);


inline void TestIGraphGetNumberOfVertices (const IGraph& graph, int vertices_amount) {
    if (graph.GetNumberOfVertices() != vertices_amount) {
	throw std::logic_error("IGraph::GetNumberOfVertices: FAIL");
    } 
}

inline void TestMatrixGetNumberOfVertices (std::vector<Edge> &list_of_edges, 
					int vertices_amount) {
    try {
	TestIGraphGetNumberOfVertices (IncidenceMatrixGraph(list_of_edges, vertices_amount), vertices_amount);
    } catch (const std::exception& ex) {
        throw std::logic_error("MatrixGetNumberOfVertices: " + std::string(ex.what()));
    }
}

inline void TestListGetNumberOfVertices (std::vector<Edge> &list_of_edges, int vertices_amount) {
    try {
	TestIGraphGetNumberOfVertices (IncidenceMatrixGraph(list_of_edges, vertices_amount), vertices_amount);
    } catch (const std::exception& ex) {
        throw std::logic_error("MatrixGetNumberOfVertices: " + std::string(ex.what()));
    }
}


inline void TestIGraphGetIncidenceList(const IGraph& graph, const std::vector<Edge> &list_of_edges, int vertex) {

    std::unordered_set<int> right_insidence_vertices_set;


    std::vector<int> incidence_list = graph.GetIncidenceList(vertex);
    std::unordered_set<int> incidence_vertices_set(incidence_list.begin(), incidence_list.end());

    for (int edge_index = 0; edge_index < list_of_edges.size(); ++edge_index) {
	if (list_of_edges[edge_index].begin_ == vertex) {
	    right_insidence_vertices_set.insert(list_of_edges[edge_index].end_);
	}
    }

    if (incidence_vertices_set != right_insidence_vertices_set) {
	throw std::logic_error("IGraph::GetIncidenceList : FAIL");
    } 
	
}

inline void TestMatrixGetIncidenceList(const std::vector<Edge> &list_of_edges, int vertices_amount) {
    try {
	for (int vertex = 0; vertex < vertices_amount; ++vertex)
	    TestIGraphGetIncidenceList (IncidenceMatrixGraph(list_of_edges, vertices_amount), 
			list_of_edges, vertex);
    } catch (const std::exception& ex) {
        throw std::logic_error("MatrixGetIncidenceList: " + std::string(ex.what()));
    }
}

inline void TestListGetIncidenceList(const std::vector<Edge> &list_of_edges, int vertices_amount) {
    try {
	for (int vertex = 0; vertex < vertices_amount; ++vertex)
            TestIGraphGetIncidenceList (IncidenceListGraph(list_of_edges, vertices_amount), 
			list_of_edges, vertex);
    } catch (const std::exception& ex) {
        throw std::logic_error("ListGetIncidenceList: " + std::string(ex.what()));
    }
}


inline void TestIGraphHasEdge(const IGraph& graph, const std::vector<Edge> &list_of_edges, 
			int vertex_a, int vertex_b) {
	
    bool has_edge_between_a_and_b = graph.HasEdge(vertex_a, vertex_b);
    bool right_has_edge_between_a_and_b = false;

    for (int edge_index = 0; edge_index < list_of_edges.size(); ++edge_index) {
	if (list_of_edges[edge_index].begin_ == vertex_a && list_of_edges[edge_index].end_ == vertex_b) {
	    right_has_edge_between_a_and_b = true;
	    break;
	}
    } 

    if (right_has_edge_between_a_and_b != has_edge_between_a_and_b) {
	throw std::logic_error("TestIGraphHasEdge: FAIL");
    } 
}

inline void TestMatrixHasEdge(const std::vector<Edge> &list_of_edges, int vertices_amount) {
    try {
	IncidenceMatrixGraph graph(list_of_edges, vertices_amount);
	for (int vertex_a = 0; vertex_a < vertices_amount; ++vertex_a) {
	    for (int vertex_b = 0; vertex_b < vertices_amount; ++vertex_b) {
		TestIGraphHasEdge(graph, list_of_edges, vertex_a,  vertex_b);
	    }
	}
    } catch (const std::exception& ex) {
        throw std::logic_error("TestMatrixHasEdge: " + std::string(ex.what()));
    }
}

inline void TestListHasEdge(const std::vector<Edge> &list_of_edges, int vertices_amount) {
    try {
	IncidenceListGraph graph(list_of_edges, vertices_amount);
	for (int vertex_a = 0; vertex_a < vertices_amount; ++vertex_a) {
	    for (int vertex_b = 0; vertex_b < vertices_amount; ++vertex_b) {
		TestIGraphHasEdge(graph, list_of_edges, vertex_a,  vertex_b);
	    }
	}
    } catch (const std::exception& ex) {
        throw std::logic_error("TestListHasEdge: " + std::string(ex.what()));
    }
}


inline void TestMakeCompactGraph(const std::vector<Edge> &list_of_edges, int vertices_amount) {

    try {
	auto graph = MakeCompactGraph(list_of_edges, vertices_amount);

	if (IncidenceMatrixGraph::ByteSize(vertices_amount, list_of_edges.size()) >
                 IncidenceListGraph::ByteSize(vertices_amount, list_of_edges.size())) {

	    if (typeid(*graph) != typeid(IncidenceListGraph)) 
		throw std::logic_error("FAIL");
	}
	else if (typeid(*graph) != typeid(IncidenceMatrixGraph)) 
	    throw std::logic_error("FAIL");
    } catch (const std::exception& ex) {
        throw std::logic_error("TestMakeCompactGraph: " + std::string(ex.what()));
    }
}



inline void TestIGraph() {

    std::cout << "Test : MakeCompactGraphOnFullGraphs\n";
    for (int vertices_amount = 0; vertices_amount < IGRAPH_TESTS_NUMBER; ++vertices_amount) {
	TestMakeCompactGraph(CreateFullListOfEdges(vertices_amount), vertices_amount);
    }
    std::cout << "Ok\n";

    std::cout << "Test : MakeCompactGraphOnEmptyGraphs\n";
    for (int vertices_amount = 0; vertices_amount < IGRAPH_TESTS_NUMBER; ++vertices_amount) {
	std::vector<Edge> empty_list_of_edges;
	TestMakeCompactGraph(empty_list_of_edges, vertices_amount);
    }
    std::cout << "Ok\n";

    for (int i = 0; i < IGRAPH_TESTS_NUMBER; ++i) {

	std::pair<std::vector<Edge>, int> new_graph = CreateBigRandomListOfEdges();
	std::vector<Edge> list_of_edges = new_graph.first;
	int vertices_amount = new_graph.second;

        std::cout << "Test : MatrixGetNumberOfVertices\n";
        TestMatrixGetNumberOfVertices(list_of_edges, vertices_amount);
	std::cout << "Ok\n";

        std::cout << "Test : ListGetNumberOfVertices\n";
        TestListGetNumberOfVertices(list_of_edges, vertices_amount);
        std::cout << "Ok\n";

        std::cout << "Test : MatrixGetIncidenceList\n";
        TestMatrixGetIncidenceList(list_of_edges, vertices_amount);
	std::cout << "Ok\n";

        std::cout << "Test : ListGetIncidenceList\n";
        TestListGetIncidenceList(list_of_edges, vertices_amount);
        std::cout << "Ok\n";

        std::cout << "Test : MatrixHasEdge:\n";
        TestMatrixHasEdge(list_of_edges, vertices_amount);
        std::cout << "Ok\n";

        std::cout << "Test : ListHasEdge\n";
        TestListHasEdge(list_of_edges, vertices_amount);
        std::cout << "Ok\n";

	// 25% of all random graphs generated in this circle are ment to be IncidenceListGraphs 
	//and 75% are ment to be IncidenceMatrixGraphs, so both of them are checked by this tests.
	std::cout << "Test : MakeCompactGraph\n";
        TestMakeCompactGraph(list_of_edges, vertices_amount);
        std::cout << "Ok\n";
	
    }

}

