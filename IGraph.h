#pragma once

#include <iostream>
#include <vector>
#include <stdio.h>
#include <set>
#include <climits>
#include <algorithm>
#include <functional>
#include <memory>


struct Edge {
    int begin_;
    int end_;

    Edge(int begin, int end) : begin_(begin), end_(end) {}

    // for using set<Edge>
    bool operator < (const Edge edge) const {
	return (edge.begin_ > begin_  || (edge.begin_ == begin_ && edge.end_ > end_));
    }

    bool operator == (const Edge edge) const {
	return (edge.begin_ == begin_  && edge.end_ == end_);
    }
};


class IGraph {
public:
    virtual int GetNumberOfVertices() const = 0;
    virtual std::vector<int> GetIncidenceList(int vertex) const = 0;
    virtual bool HasEdge(int vertex_a, int vertex_b) const = 0;
    virtual ~IGraph() {};
};


class IncidenceMatrixGraph : public IGraph {
public:

    IncidenceMatrixGraph(const std::vector<Edge> &list_of_edges, int vertices_amount) :
				vertices_amount_(vertices_amount), edges_amount_(list_of_edges.size()), 
				matrix_graph_(vertices_amount, std::vector<bool>(vertices_amount, 0)) {


    for (int i = 0; i < list_of_edges.size(); ++i) {
        if (!matrix_graph_[list_of_edges[i].begin_][list_of_edges[i].end_])
            matrix_graph_[list_of_edges[i].begin_][list_of_edges[i].end_] = 1;
	else edges_amount_--;
        }
    }

    int GetNumberOfVertices() const {
	return vertices_amount_;
    }

    std::vector<int> GetIncidenceList(int vertex) const {
	std::vector<int> answer;
        for (int i = 0; i < matrix_graph_[vertex].size(); ++i) {
        	if (matrix_graph_[vertex][i]) answer.push_back(i);
        }
        return answer;
    } 


    bool HasEdge(int vertex_a, int vertex_b) const {
	return matrix_graph_[vertex_a][vertex_b];
    }

    static size_t ByteSize(int vertices_amount, int edges_amount)  {
	return static_cast<size_t> (vertices_amount * vertices_amount * sizeof(bool) / CHAR_BIT);
    }

private:
    int vertices_amount_;
    int edges_amount_;
    std::vector< std::vector<bool> > matrix_graph_;
};



class IncidenceListGraph : public IGraph {
public:

    IncidenceListGraph(const std::vector<Edge> &list_of_edges, int vertices_amount) :
    	vertices_amount_(vertices_amount), edges_amount_(list_of_edges.size()),
      			beginnings_of_edges_(vertices_amount + 1, 0) {
	
	// in case if there're some similar edges in list_of_edges
	std::set<Edge> set_of_edges;

    	for (int i = 0; i < list_of_edges.size(); ++i) 
	set_of_edges.insert(list_of_edges[i]);

	for (const auto& edge: set_of_edges) {
	    std::vector<int> :: iterator end_of_edge_begin = ends_of_edges_.begin() +
		     beginnings_of_edges_[edge.begin_];
	    ends_of_edges_.insert(end_of_edge_begin, edge.end_);
	    for (int j = edge.begin_ + 1; j < beginnings_of_edges_.size(); ++j) beginnings_of_edges_[j]++;
	}

	edges_amount_ = set_of_edges.size();
        beginnings_of_edges_[vertices_amount] = edges_amount_;
    }

    int GetNumberOfVertices() const {
        return vertices_amount_;
    }


    std::vector<int> GetIncidenceList(int vertex) const {
	std::vector<int> :: const_iterator ends_of_edges_begin = 
		ends_of_edges_.begin() +  beginnings_of_edges_[vertex];

        std::vector<int> :: const_iterator ends_of_edges_end = ends_of_edges_.begin() + 
		beginnings_of_edges_[vertex + 1];

        return std::vector<int>(ends_of_edges_begin, ends_of_edges_end);
    }

    bool HasEdge(int vertex_a, int vertex_b) const {
	for (int i = beginnings_of_edges_[vertex_a]; i < beginnings_of_edges_[vertex_a + 1]; ++i) {
            if (ends_of_edges_[i] == vertex_b) return true;
    	}
        return false;
    }

    static size_t ByteSize(int vertices_amount, int edges_amount) {
	return ((vertices_amount + edges_amount) * sizeof(int));
    }

private:
    int vertices_amount_;
    int edges_amount_;
    std::vector<int> ends_of_edges_;
    std::vector<int> beginnings_of_edges_;
};


inline std::unique_ptr<IGraph> MakeCompactGraph (const std::vector<Edge> &list_of_edges, int vertices_amount) {
 
    if(IncidenceMatrixGraph::ByteSize(vertices_amount, list_of_edges.size()) >
		 IncidenceListGraph::ByteSize(vertices_amount, list_of_edges.size())) {

	 std::unique_ptr<IGraph> incidence_list_graph (new IncidenceListGraph(list_of_edges, 
						vertices_amount));
        return std::move(incidence_list_graph);
    } else {
	std::unique_ptr<IGraph> incidence_matrix_graph (new IncidenceMatrixGraph(list_of_edges, 
						vertices_amount));
        return std::move(incidence_matrix_graph);
    }
}

