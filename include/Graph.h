#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <string>
#include <deque>

using namespace std;

// Represents one road from a city to another
struct Edge
{
    string destination;
    int distance;
};

// Graph class
class Graph
{
    friend class FileManager;
private:

    // Adjacency List
    unordered_map<string, vector<Edge>> adjacencyList;

    // Helper function for DFS
    void DFSUtil(const string& city, unordered_set<string>& visited);

    // Store last 5 searched routes
    deque<string> routeHistory;
public:

    // Constructor
    Graph();

    // Add a new city
    void addCity(const string& city);

    // Add a road between two cities
    void addRoute(const string& source,
                  const string& destination,
                  int distance);

    // Display complete graph
    void displayGraph() const;

    // Find shortest path using Dijkstra Algorithm
    void findShortestPath(const string& source,
                          const string& destination);

    // Remove a city
    void removeCity(const string& city);

    // Remove a route
    void removeRoute(const string& source,
                     const string& destination);

    // BFS Traversal
    void BFS(const string& startCity);

    // Search a city
    bool searchCity(const string& city) const;

    // DFS Traversal
    void DFS(const string& startCity);

    // Update distance between two cities
    void updateRoute(const string& source,const string& destination,int newDistance);

    // Display graph statistics
    void graphStatistics() const;

    // Display recent searched routes
    void showRouteHistory();
};

#endif