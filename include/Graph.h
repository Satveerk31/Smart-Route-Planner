#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <string>
#include <deque>

using namespace std;

struct Edge{
    string destination;
    int distance;
};

class Graph{
    friend class FileManager;
private:
    unordered_map<string, vector<Edge>> adjacencyList;

    void DFSUtil(const string& city, unordered_set<string>& visited);
    deque<string> routeHistory;
public:
    Graph();

    void displayGraph() const;

    void findShortestPath(const string& source,
                          const string& destination);

    void removeCity(const string& city);

    void removeRoute(const string& source,
                     const string& destination);

    void BFS(const string& startCity);
    bool searchCity(const string& city) const;

    void DFS(const string& startCity);

    void updateRoute(const string& source,const string& destination,int newDistance);

    void graphStatistics() const;

    void showRouteHistory();

    void addCity(const string& city, bool showMessage = true);
    void addRoute(const string& source,
              const string& destination,
              int distance,
              bool showMessage = true);
};

#endif