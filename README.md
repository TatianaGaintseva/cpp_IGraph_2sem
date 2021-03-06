# cpp_IGraph_2sem
Storage for graphs as homework in 2nd term at MIPT


AUTHOR
---------------------------

Tatiana Gaintseva, MIPT-399
email: gaintseva@phystech.edu


WHAT IS DONE
---------------------------

Realization of storage for graphs -- class IGraph, realization of some algorithms (Topoligical sort, Tarjan algorithm, DFS, BFS, 2SAT) that work with IGraph instances and tests for all the realizations.


IGRAPH CLASS
---------------------------

IGraph is a vrtual class and its 2 heirs IncidenceMatrixGraph and IncidenceListGraph are used to store graps in computer memory. There are two different implementations of IGraph and for each particular graph which of instances to use is decided in accordance to memory needed to store it (implementation which uses less memory will be chosen). IncidenceMatrixGraph is a realizationn which stores graph as an incidence matrix and IncidenceListGraph is a realization that storees graph using two lists of vertices -- beginnings and ends of edges. Function MakeCompactGraph is responsible for choosing the best way of storing for each particular graph given.


ALGORITHMS 
---------------------------

There were realized algorithms Topoligical sort, Tarjan algorithm, DFS, BFS, 2SAT that work with IGraph. Descriptions of these algorithms are available at e-maxx.ru


HOW TO USE
---------------------------

To store a particular graph as IGraph, list of its edges and total amount of vertices need to be passed to MakeCompactGraph function. It will choose the best representation.


TESTS
--------------------------

Tests files for all the functions realized are provided in folders TestsIGraph and TestsAlgorithms. To help testing there are stupid (naive) algorithms provided in folder StupidAlgorithms. Also algorithms that generate random graphs and CNFs for testing are provided in folder Generators. There are algorithms that can generate either small or big instances of graphs as it's needed. It is needed to put testing files into project root directory or to link them in order to begin testing.
