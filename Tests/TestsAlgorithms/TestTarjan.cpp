#include "TestTarjan"

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
