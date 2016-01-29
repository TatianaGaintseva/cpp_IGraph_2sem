#include <unordered_set>
#include <ctime>
#include "Algo.h"
#include "MakeGraphAndCnf.h"
#include "StupidAlgo.h"
#include "TestsAlgo.h"

const int TESTS_ALGO_MAXN = INT_MAX / (1024 * 1024 * 4);

class FirstSearchTester {
public:

    void StartProcessingVertex(int vertex) {
	if (vertices_processed_.find(vertex) != vertices_processed_.end()) throw std::logic_error("FAIL");
        vertices_processed_.insert(vertex);
    }

    void ProcessingEdge(int vertex, int incident_vertex) {
        edges_processed_.insert(Edge(vertex, incident_vertex));
    }

    void LeaveVertex(int vertex) {}

    std::set<int> GetVerticesProcessed() { return  vertices_processed_;}

    std::set<Edge> GetEdgesProcessed() { return edges_processed_;}

private:
    std::set<int> vertices_processed_;
    std::set<Edge> edges_processed_;
};


inline void OneFirstSearchTest(const std::vector<Edge> &list_of_edges, int vertices_amount, FirstSearchTester& tester) {
    std::set<int> vertices_set;
    for (int vertex = 0; vertex < vertices_amount; ++vertex) vertices_set.insert(vertex);

    if (tester.GetVerticesProcessed() != vertices_set) throw std::logic_error("FAIL");

    std::set<Edge> set_of_edges(list_of_edges.begin(), list_of_edges.end());
    if (tester.GetEdgesProcessed() != set_of_edges) throw std::logic_error("FAIL");
}


inline void FirstSearchTests(const std::vector<Edge> &list_of_edges, int vertices_amount) {
        auto graph = MakeCompactGraph(list_of_edges, vertices_amount);

    try {
        FirstSearchTester dfs_tester;
        DFS(*graph, dfs_tester);
        OneFirstSearchTest(list_of_edges, vertices_amount, dfs_tester);
    } catch (const std::exception& ex) {
        throw std::logic_error("TestDFS: " + std::string(ex.what()));
    }

    try {
        FirstSearchTester bfs_tester;
        DFS(*graph, bfs_tester);
        OneFirstSearchTest(list_of_edges, vertices_amount, bfs_tester);
    } catch (const std::exception& ex) {
         throw std::logic_error("TestBFS: " + std::string(ex.what()));
    }
}




inline void StressTestTopologicalSort(const std::vector<Edge> &list_of_edges, int vertices_amount) {

    try {
        if (StupidIsSircle(vertices_amount, list_of_edges)) return;

        std::vector<int> topologically_ordered_vertices = GetTopologicallyOrderedVerties(list_of_edges, vertices_amount);
        if (topologically_ordered_vertices.size() != vertices_amount) throw std::logic_error("FAIL");

	auto graph = MakeCompactGraph(list_of_edges, vertices_amount);
        for (int i = 0; i < topologically_ordered_vertices.size() - 1; ++i) {
            for (int j = i + 1; j < topologically_ordered_vertices.size(); ++j) {
                if (graph->HasEdge(topologically_ordered_vertices[j], topologically_ordered_vertices[i]))
                     throw std::logic_error("FAIL");
            }
        } 
    } catch (const std::exception& ex) {
        throw std::logic_error("TestTopologicalSort: " + std::string(ex.what()));
    }
}


inline void StressTestTarjan(const std::vector<Edge> &list_of_edges, int vertices_amount) {
    try {
        std::vector< std::set<int> > strong_components = GetStrongComponents(list_of_edges, vertices_amount);
        std::set< std::set<int> > strong_components_set(strong_components.begin(), strong_components.end());
        std::set< std::set<int> > right_strong_components = StupidTarjan(list_of_edges, vertices_amount);
        
        if (strong_components_set != right_strong_components) throw std::logic_error("FAIL"); 
    } catch (const std::exception& ex) {
        throw std::logic_error("TestTarjan: " + std::string(ex.what()));
    }
}


inline void TestGetCondensationGraph(const std::vector<Edge> list_of_edges, int vertices_amount, 
                const std::vector< std::set<int> >& components) {
    try {
	auto graph = MakeCompactGraph(list_of_edges, vertices_amount);
        std::vector<int> vertex_component_number(graph->GetNumberOfVertices());

        for (size_t component_index = 0; component_index < components.size(); ++component_index) {   
            for (const auto& vertex : components[component_index]) {
                vertex_component_number[vertex] = component_index;
            }
        }
  
        std::set<Edge> right_set_of_condensation_graph_edges;
        for (int vertex = 0; vertex < graph->GetNumberOfVertices(); ++vertex) {
            std::vector<int> vertex_incidences = graph->GetIncidenceList(vertex);

            for (size_t i = 0; i < vertex_incidences.size(); ++i) {
                int incident_vertex = vertex_incidences[i];

                if (vertex_component_number[incident_vertex] != vertex_component_number[vertex]) 
                    right_set_of_condensation_graph_edges.insert(Edge(vertex_component_number[vertex], 
                            vertex_component_number[incident_vertex]));
            }
        }

        auto condensation_graph = GetCondensationGraph(*graph, components);
        if (condensation_graph->GetNumberOfVertices() != components.size()) throw std::logic_error("FAIL");
        std::set<Edge> algo_set_of_condensation_graph_edges;
        for (int vertex = 0; vertex < condensation_graph->GetNumberOfVertices(); ++vertex) {
            std::vector<int> vertex_incidences = condensation_graph->GetIncidenceList(vertex);
        
            for (size_t i = 0; i < vertex_incidences.size(); ++i) {
                int incident_vertex = vertex_incidences[i];
                algo_set_of_condensation_graph_edges.insert(Edge(vertex, incident_vertex));
            }
        }

        if (right_set_of_condensation_graph_edges != algo_set_of_condensation_graph_edges) 
            throw std::logic_error("FAIL");
    } catch (const std::exception& ex) {
        throw std::logic_error("TestGetCondensationGraph: " + std::string(ex.what()));
    }
} 


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


class AllSmallListOfEdgesGenerator {
public:

    AllSmallListOfEdgesGenerator(int vertices_amount) : vertices_amount_(vertices_amount), next_list_of_edges_number_(0) {}

    std::vector<Edge> NextSmallListOfEdges() {
        try {

	    if (next_list_of_edges_number_ >= (1 << (vertices_amount_ * vertices_amount_)) )
		throw std::logic_error("FAIL in generating graph");

            std::vector<Edge> next_list_of_edges;

	    for (int i = 0; i < vertices_amount_ * vertices_amount_; ++i) {
	        if ((next_list_of_edges_number_ & (1 << i)) != 0) 
	       	    next_list_of_edges.push_back(Edge(i / vertices_amount_, i % vertices_amount_));
	    }

	    next_list_of_edges_number_++;

	    return next_list_of_edges;       
        } catch (const std::exception& ex) {
            throw std::logic_error(std::string(ex.what()));
        }
    }

private:
    int vertices_amount_;
    int next_list_of_edges_number_;
};


class AllSmallCNFsGenerator {
public:
    AllSmallCNFsGenerator(int variables_amount) : variables_amount_(variables_amount), list_of_edges_generator_(variables_amount * 2) {}

    std::vector<Conjunct> NextSmallCnf() {
	try {
	    if (next_cnf_number_ >= (1 << (4 * variables_amount_ * variables_amount_)) )
		throw std::logic_error("FAIL in generating cnf");

	    std::vector<Conjunct> next_cnf;
	    std::vector<Edge> next_list_of_edges = list_of_edges_generator_.NextSmallListOfEdges();
	    for (int i = 0; i < next_list_of_edges.size(); ++i) {
	        next_cnf.push_back(Conjunct(next_list_of_edges[i].begin_ / 2, next_list_of_edges[i].end_ / 2, 
						next_list_of_edges[i].begin_ % 2, next_list_of_edges[i].end_ % 2));
	    }
	    next_cnf_number_++;
	    return next_cnf;;
        } catch (const std::exception& ex) {
            throw std::logic_error(std::string(ex.what()));
        }
    }

private:
    int variables_amount_;
    int next_cnf_number_;
    AllSmallListOfEdgesGenerator list_of_edges_generator_;
};


// tests of Algos on all small graphs with vertices amount <= 4
inline void TestAlgoOnSmallGraphs() {
    try {
        for (int vertices_amount = 1; vertices_amount < 5; ++vertices_amount) {
	    AllSmallListOfEdgesGenerator small_list_of_edges_generator(vertices_amount);

            for (int list_of_edges_number = 0; list_of_edges_number < 
			(1 << (vertices_amount * vertices_amount)); ++list_of_edges_number) {

		std::vector<Edge> next_list_of_edges = small_list_of_edges_generator.NextSmallListOfEdges();
		
		FirstSearchTests(next_list_of_edges, vertices_amount);
		StressTestTopologicalSort(next_list_of_edges, vertices_amount);
		StressTestTarjan(next_list_of_edges, vertices_amount);

		// as there all graphs with vertices amount <= 4 are generated, so
		// putting all this graphs into tarjan algo all partitions into components by vertices
		// will be generated, so TestGetCondensationGraph will be tested on all possible kinds of partitions.
		Tarjan tarjan(vertices_amount);
		std::vector< std::set<int> > strong_components = tarjan.GetComponents();
		TestGetCondensationGraph(next_list_of_edges, vertices_amount, strong_components);
 	    } 
        }

	for (int variables_amount = 0; variables_amount < 4; ++variables_amount) {
	    AllSmallCNFsGenerator small_cnfs_generator(variables_amount);
	    for (int cnf_number = 0; cnf_number < (1 << (4 * variables_amount * variables_amount)); ++cnf_number) {
		std::vector<Conjunct> next_cnf = small_cnfs_generator.NextSmallCnf();
		TestMakeGraphForTwoSAT(next_cnf, variables_amount);
		StressTestTwoSAT(next_cnf, variables_amount);
	    }
	}
    } catch (const std::exception& ex) {
        throw std::logic_error("TestAlgoOnSmallGraphs: " + std::string(ex.what()));
    }
}
 

void TestTopologicalSortOnBigAcyclicGraphs(const std::vector<Edge> &list_of_edges, int vertices_amount) {
    try {
	std::vector<Edge> copy_list_of_edges = list_of_edges;  
        std::vector<int> topologically_ordered_vertices = GetTopologicallyOrderedVerties(copy_list_of_edges, vertices_amount);

	random_shuffle(copy_list_of_edges.begin(), copy_list_of_edges.end());
        std::vector<int> topologically_ordered_vertices_after_shuffle = GetTopologicallyOrderedVerties(copy_list_of_edges, vertices_amount);

	if (topologically_ordered_vertices_after_shuffle != topologically_ordered_vertices) throw std::logic_error("FAIL");
    } catch (const std::exception& ex) {
        throw std::logic_error("TestTopologicalSortOnBigAcyclicGraphs : " + std::string(ex.what()));
    }
}


void TestTarjanOnBigGraphs(const std::vector<Edge> &list_of_edges, int vertices_amount) {
    try {
        std::vector<Edge> copy_list_of_edges = list_of_edges;
        std::vector< std::set<int> > strong_components = GetStrongComponents(list_of_edges, vertices_amount);

        random_shuffle(copy_list_of_edges.begin(), copy_list_of_edges.end());
        std::vector< std::set<int> > strong_components_after_shuffle = GetStrongComponents(list_of_edges, vertices_amount);

	if (strong_components_after_shuffle != strong_components) throw std::logic_error("FAIL");
    } catch (const std::exception& ex) {
        throw std::logic_error("TestTarjanOnBigGraphs : " + std::string(ex.what()));
    }
}


void Test2SATOnBigCNFs(const std::vector<Conjunct> &conjunctions, int variables_amount) {
    try {
        std::vector<Conjunct> conjunctions_copy = conjunctions;
        random_shuffle(conjunctions_copy.begin(), conjunctions_copy.end());

        std::vector<bool> values_of_variables(variables_amount);
        if (TwoSAT(conjunctions, values_of_variables) != TwoSAT(conjunctions_copy, values_of_variables)) 
	    throw std::logic_error("FAIL");
    } catch (const std::exception& ex) {
        throw std::logic_error("Test2SATOnBigGraphs : " + std::string(ex.what()));
    }
}




void TestAlgo() {

    TestAlgoOnSmallGraphs();

    // Stress tests of algos on small random graphs
    for (int i = 0; i < TESTS_ALGO_MAXN; ++i) {
    
        std::pair<std::vector<Edge>, int> new_graph = CreateSmallRandomListOfEdges();
        std::vector<Edge> list_of_edges = new_graph.first;
        int vertices_amount = new_graph.second;

	FirstSearchTests(list_of_edges, vertices_amount);
	std::cout<<"FirstSearchTests : OK\n";

	StressTestTopologicalSort(list_of_edges, vertices_amount);
	std::cout<<"StressTestTopologicalSort : OK\n";

        StressTestTarjan(list_of_edges, vertices_amount);
        std::cout<<"StressTestTarjan : OK\n";


	new_graph = CreateSmallRandomAsyclicListOfEdges();
        list_of_edges = new_graph.first;
        vertices_amount = new_graph.second;

	StressTestTopologicalSort(list_of_edges, vertices_amount);
        std::cout<<"StressTestTopologicalSort on asyclic graph: OK\n";

        
        std::pair<std::vector<Conjunct>, int> new_cnf = CreateSmallRandomCNF();
        std::vector<Conjunct> conjunctions = new_cnf.first;
        int variables_amount = new_cnf.second;

	TestMakeGraphForTwoSAT(conjunctions, variables_amount);
	std::cout<<"TestMakeGraphForTwoSAT : OK\n";

	//75 % of all cnfs generated in this circle are satisfiable(382 of 512)
        StressTestTwoSAT(conjunctions, variables_amount);
        std::cout<<"StressTestTwoSAT : OK\n";
    }

    // Tests of algos on big random graphs
    for (int i = 0; i < TESTS_ALGO_MAXN; ++i) {
    
        std::pair< std::vector<Edge>, int > new_graph = CreateBigRandomListOfEdges();
        std::vector<Edge> list_of_edges = new_graph.first;
        int vertices_amount = new_graph.second;

        TestTarjanOnBigGraphs(list_of_edges, vertices_amount);
        std::cout<<"TestTarjanOnBigGraphs : OK\n";


	new_graph = CreateBigRandomAsyclicListOfEdges();
        list_of_edges = new_graph.first;
        vertices_amount = new_graph.second;

	TestTopologicalSortOnBigAcyclicGraphs(list_of_edges, vertices_amount);
        std::cout<<"TestTopologicalSortOnBigAcyclicGraphs : OK\n";

        
        std::pair<std::vector<Conjunct>, int> new_cnf = CreateBigRandomCNF();
        std::vector<Conjunct> conjunctions = new_cnf.first;
        int variables_amount = new_cnf.second;

	TestMakeGraphForTwoSAT(conjunctions, variables_amount);
	std::cout<<"TestMakeGraphForTwoSAT : OK\n";

	// 58 % of all cnfs generated in this sircle satisfiable (299 of 512)
        Test2SATOnBigCNFs(conjunctions, variables_amount);
        std::cout<<"Test2SATOnBigCNFs : OK\n";
    }
}

