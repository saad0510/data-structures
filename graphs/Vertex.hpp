#ifndef VERTEX_HPP
#define VERTEX_HPP

#include <list>

// forward declaration:
template <typename type>
struct Vertex;

// a general template structure for an edge of a directed graph
template <typename type>
struct Edge
{
    int weight;              // the weight of edge
    Vertex<type> *neighbour; // points to vertex at terminal end
    // constructors:
    Edge(Vertex<type> *neighbour)
        : Edge(neighbour, 1) {} // constructor for an unweighted edge
    Edge(Vertex<type> *neighbour, const int &weight)
        : neighbour(neighbour), weight(weight) {}
};

// a general template structure for a vertex of any graph
template <typename type>
struct Vertex
{
    type key;                    // the contents of vertex
    bool visited = false;        // a flag (used in traversing)
    std::list<Edge<type>> edges; // all connected edges
    // constructors:
    Vertex() = default;
    Vertex(const type &key) : key(key) {}
};

#endif