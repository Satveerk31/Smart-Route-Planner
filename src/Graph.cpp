#include "../include/Graph.h"

#include <queue>
#include <unordered_set>
#include <limits>
#include <algorithm>

// Constructor
Graph::Graph()
{
}

void Graph::addCity(const string& city)
{
    if (adjacencyList.find(city) == adjacencyList.end())
    {
        adjacencyList[city] = vector<Edge>();
        cout << city << " added successfully.\n";
    }
    else
    {
        cout << city << " already exists.\n";
    }
}

void Graph::addRoute(const string& source,
                     const string& destination,
                     int distance)
{
    if (source == destination)
    {
        cout << "Source and Destination cannot be the same.\n";
        return;
    }

    if (distance <= 0)
    {
        cout << "Distance must be greater than 0.\n";
        return;
    }

    addCity(source);
    addCity(destination);

    for (const auto &road : adjacencyList[source])
    {
        if (road.destination == destination)
        {
            cout << "Route already exists!\n";
            return;
        }
    }

    adjacencyList[source].push_back({destination, distance});
    adjacencyList[destination].push_back({source, distance});

    cout << "Route added successfully.\n";
}

void Graph::displayGraph() const
{
    cout << "\n============================================\n";
    cout << "             ROAD NETWORK\n";
    cout << "============================================\n";

    if (adjacencyList.empty())
    {
        cout << "\nNo cities available.\n";
        return;
    }

    for (const auto &city : adjacencyList)
    {
        cout << "\nCity : " << city.first << endl;
        cout << "--------------------------------------------\n";

        if (city.second.empty())
        {
            cout << "   No Connected Routes\n";
        }
        else
        {
            for (const auto &road : city.second)
            {
                cout << "   --> "
                     << road.destination
                     << " ("
                     << road.distance
                     << " km)"
                     << endl;
            }
        }
    }

    cout << "\n============================================\n";
}
void Graph::findShortestPath(const string& source, const string& destination)
{
    if (adjacencyList.find(source) == adjacencyList.end() ||
        adjacencyList.find(destination) == adjacencyList.end())
    {
        cout << "Source or Destination city not found!\n";
        return;
    }

    unordered_map<string, int> distance;
    unordered_map<string, string> parent;

    for (const auto& city : adjacencyList)
    {
        distance[city.first] = numeric_limits<int>::max();
    }

    distance[source] = 0;

    priority_queue<
        pair<int, string>,
        vector<pair<int, string>>,
        greater<pair<int, string>>
    > pq;

    pq.push({0, source});

    while (!pq.empty())
    {
        string currentCity = pq.top().second;
        int currentDistance = pq.top().first;
        pq.pop();

        for (const Edge& road : adjacencyList[currentCity])
        {
            if (currentDistance + road.distance < distance[road.destination])
            {
                distance[road.destination] = currentDistance + road.distance;
                parent[road.destination] = currentCity;

                pq.push({distance[road.destination], road.destination});
            }
        }
    }

    if (distance[destination] == numeric_limits<int>::max())
    {
        cout << "No route exists between "
             << source << " and " << destination << ".\n";
        return;
    }

    // Reconstruct path
    vector<string> path;

    string current = destination;

    while (current != source)
    {
        path.push_back(current);
        current = parent[current];
    }

    path.push_back(source);

    reverse(path.begin(), path.end());

    cout << "\n========== SHORTEST ROUTE ==========\n";

    for (size_t i = 0; i < path.size(); i++)
    {
        cout << path[i];

        if (i != path.size() - 1)
            cout << " -> ";
    }

    cout << "\n\nTotal Distance : "
         << distance[destination]
         << " km\n";
    // Save route history
    string history = source + " -> " + destination;

    routeHistory.push_front(history);

    // Keep only last 5 searches
    if(routeHistory.size() > 5)
    {

        routeHistory.pop_back();
    }
}
void Graph::removeCity(const string& city)
{
    // Check if city exists
    if (adjacencyList.find(city) == adjacencyList.end())
    {
        cout << "City not found!\n";
        return;
    }

    // Remove this city from every other city's route list
    for (auto &entry : adjacencyList)
    {
        auto &roads = entry.second;

        roads.erase(
            remove_if(roads.begin(), roads.end(),
                      [&](const Edge &road)
                      {
                          return road.destination == city;
                      }),
            roads.end());
    }

    // Remove the city itself
    adjacencyList.erase(city);

    cout << city << " removed successfully.\n";
}
void Graph::removeRoute(const string& source, const string& destination)
{
    // Check if both cities exist
    if (adjacencyList.find(source) == adjacencyList.end() ||
        adjacencyList.find(destination) == adjacencyList.end())
    {
        cout << "Source or Destination city not found!\n";
        return;
    }

    // Remove destination from source
    auto &sourceRoads = adjacencyList[source];

    sourceRoads.erase(
        remove_if(sourceRoads.begin(), sourceRoads.end(),
                  [&](const Edge &road)
                  {
                      return road.destination == destination;
                  }),
        sourceRoads.end());

    // Remove source from destination
    auto &destinationRoads = adjacencyList[destination];

    destinationRoads.erase(
        remove_if(destinationRoads.begin(), destinationRoads.end(),
                  [&](const Edge &road)
                  {
                      return road.destination == source;
                  }),
        destinationRoads.end());

    cout << "Route removed successfully.\n";
}
void Graph::updateRoute(const string& source,
                        const string& destination,
                        int newDistance)
{
    // Validation
    if (source == destination)
    {
        cout << "Source and Destination cannot be the same.\n";
        return;
    }

    if (newDistance <= 0)
    {
        cout << "Distance must be greater than 0.\n";
        return;
    }

    // Check if both cities exist
    if (adjacencyList.find(source) == adjacencyList.end() ||
        adjacencyList.find(destination) == adjacencyList.end())
    {
        cout << "Source or Destination city not found!\n";
        return;
    }

    bool found = false;

    // Update source -> destination
    for (auto &road : adjacencyList[source])
    {
        if (road.destination == destination)
        {
            road.distance = newDistance;
            found = true;
            break;
        }
    }

    // Update destination -> source
    for (auto &road : adjacencyList[destination])
    {
        if (road.destination == source)
        {
            road.distance = newDistance;
            break;
        }
    }

    if (found)
    {
        cout << "Route updated successfully!\n";
    }
    else
    {
        cout << "Route not found!\n";
    }
}
void Graph::BFS(const string& startCity)
{
    // Check if city exists
    if (adjacencyList.find(startCity) == adjacencyList.end())
    {
        cout << "City not found!\n";
        return;
    }

    unordered_set<string> visited;
    queue<string> q;

    visited.insert(startCity);
    q.push(startCity);

    cout << "\n========== BFS Traversal ==========\n\n";

    while (!q.empty())
    {
        string current = q.front();
        q.pop();

        cout << current << endl;

        for (const Edge& road : adjacencyList[current])
        {
            if (visited.find(road.destination) == visited.end())
            {
                visited.insert(road.destination);
                q.push(road.destination);
            }
        }
    }

    cout << "\n===================================\n";
}
void Graph::DFSUtil(const string& city,
                    unordered_set<string>& visited)
{
    visited.insert(city);

    cout << city << endl;

    for (const Edge &road : adjacencyList[city])
    {
        if (visited.find(road.destination) == visited.end())
        {
            DFSUtil(road.destination, visited);
        }
    }
}
void Graph::DFS(const string& startCity)
{
    if (adjacencyList.find(startCity) == adjacencyList.end())
    {
        cout << "City not found!\n";
        return;
    }

    unordered_set<string> visited;

    cout << "\n========== DFS Traversal ==========\n\n";

    DFSUtil(startCity, visited);

    cout << "\n===================================\n";
}
bool Graph::searchCity(const string& city) const
{
    if (adjacencyList.find(city) != adjacencyList.end())
    {
        cout << "\nCity Found Successfully!\n";
        return true;
    }

    cout << "\nCity Not Found!\n";
    return false;
}
void Graph::graphStatistics() const
{
    int totalCities = adjacencyList.size();

    int totalRoutes = 0;

    string mostConnectedCity = "";

    int maxConnections = 0;

    for (const auto &city : adjacencyList)
    {
        totalRoutes += city.second.size();

        if ((int)city.second.size() > maxConnections)
        {
            maxConnections = city.second.size();
            mostConnectedCity = city.first;
        }
    }

    // Since each route is stored twice
    totalRoutes /= 2;

    double averageDegree = 0;

    if (totalCities != 0)
        averageDegree = (2.0 * totalRoutes) / totalCities;

    cout << "\n====================================\n";
    cout << "       GRAPH STATISTICS\n";
    cout << "====================================\n\n";

    cout << "Total Cities        : "
         << totalCities << endl;

    cout << "Total Routes        : "
         << totalRoutes << endl;

    cout << "Average Degree      : "
         << averageDegree << endl;

    cout << "Most Connected City : "
         << mostConnectedCity << endl;

    cout << "\n====================================\n";
}
void Graph::showRouteHistory()
{
    cout << "\n====================================\n";
    cout << "       RECENT ROUTE HISTORY\n";
    cout << "====================================\n\n";

    if(routeHistory.empty())
    {
        cout << "No recent searches.\n";
    }
    else
    {
        int count = 1;

        for(const auto &route : routeHistory)
        {
            cout << count << ". " << route << endl;
            count++;
        }
    }

    cout << "\n====================================\n";
}