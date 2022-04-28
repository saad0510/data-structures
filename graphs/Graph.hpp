#ifndef GRAPH_LIST_HPP
#define GRAPH_LIST_HPP

#include "Vertex.hpp"
#include <iostream>
#include <list>
#include <queue>

// a general template class for any undirected graph
template <typename type>
class Graph
{
    // type-aliases for readability
    using VType = Vertex<type>;
    using iterator = Vertex<type> *;
    using visiter = void (*)(VType &);

private:
    std::list<VType> adj_list; // adjacency list

public:
    // constructors:
    Graph() = default;
    Graph(const type &vertex) { add_vertex(vertex); }

    // inserts a new vertex of given key
    // RECEIVES: vertex = the key of vertext
    // RETURNS: nothing
    void add_vertex(const type &vertex)
    {
        for (const auto &v : adj_list)
            if (v.key == vertex)
                return;
        adj_list.push_back(VType(vertex));
    }

    // creates a bi-directional edge between given vertices
    // RECEIVES: v1 = key of vertex1
    //           v2 = key of vertex2
    //           weight = weight of the edge [by default 1]
    // RETURNS: nothing
    void add_edge(const type &v1, const type &v2, const int &weight = 1)
    {
        // pointers to the vertices:
        iterator v1_ptr = nullptr,
                 v2_ptr = nullptr;
        // find vertices in graph:
        for (auto &e : adj_list)
        {
            if (e.key == v1) // vertex1 is found?
                v1_ptr = &e;
            if (e.key == v2) // vertex2 is found?
                v2_ptr = &e;
            if (v1_ptr && v2_ptr) // both vertices are found?
            {                     // connect them & exit:
                v1_ptr->edges.push_back(Edge<type>(v2_ptr, weight));
                v2_ptr->edges.push_back(Edge<type>(v1_ptr, weight));
                break;
            }
        }
    }

    // accesses all vertices in BFS order
    // RECEIVES: start = key of the source vertex
    //           visit = a callback function that receives each vertex
    // RETURNS: nothing
    void bfs(const type &start, const visiter &visit)
    {
        iterator start_ptr = nullptr; // pointer to source vertex
        // mark all vertices as unvisited:
        for (auto &v : adj_list)
        {
            v.visited = false;
            if (v.key == start) // find the source vertex:
                start_ptr = &v;
        }
        if (!start_ptr) // source vertex was not found?
            return;

        std::queue<iterator> q;
        q.push(start_ptr);
        start_ptr->visited = true;

        while (!q.empty())
        {
            iterator v = q.front();
            q.pop();
            visit(*v);

            for (auto &child : v->edges)
                if (child.neighbour->visited == false)
                {
                    child.neighbour->visited = true;
                    q.push(child.neighbour);
                }
        }
    }

    // accesses all vertices in DFS order
    // RECEIVES: start = key of the source vertex
    //           visit = a callback function that receives each vertex
    // RETURNS: nothing
    void dfs(const type &start, const visiter &visit)
    {
        iterator start_ptr = nullptr; // pointer to source vertex
        // mark all vertices as unvisited:
        for (auto &v : adj_list)
        {
            v.visited = false;
            if (v.key == start) // find the source vertex:
                start_ptr = &v;
        }
        if (start_ptr)             // source vertex was found?
            dfs(start_ptr, visit); // pass control to utility function
    }

    // prints all vertices with their edges on console
    // RECEIVES: nothing
    // RETURNS: nothing
    void display() const
    {
        for (const auto &vertex : adj_list)
        {
            std::cout << vertex.key << " = ";
            for (const auto &n : vertex.edges)
                std::cout << n.neighbour->key << " ";
            puts("");
        }
        puts("");
    }

private:
    void dfs(iterator vertex, const visiter &visit)
    {
        vertex->visited = true;
        for (auto &child : vertex->edges)
        {
            if (child.neighbour->visited)
                continue;
            dfs(child.neighbour, visit);
        }
        visit(*vertex);
    }
};

#endif