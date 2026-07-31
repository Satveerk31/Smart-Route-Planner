#include "../include/FileManager.h"
#include "../include/Graph.h"

#include <fstream>
#include <set>

using namespace std;

// Save graph data
void FileManager::saveData(Graph &graph)
{
    ofstream cityFile("data/cities.txt");
    ofstream routeFile("data/routes.txt");

    if (!cityFile || !routeFile)
    {
        cout << "Error opening file!\n";
        return;
    }

    // Save Cities
    for (const auto &city : graph.adjacencyList)
    {
        cityFile << city.first << endl;
    }

    // Save Routes
    set<pair<string, string>> savedRoutes;

    for (const auto &city : graph.adjacencyList)
    {
        for (const Edge &road : city.second)
        {
            string city1 = city.first;
            string city2 = road.destination;

            // Avoid duplicate routes
            if (city1 > city2)
                swap(city1, city2);

            if (savedRoutes.find({city1, city2}) == savedRoutes.end())
            {
                routeFile << city1 << " "
                          << city2 << " "
                          << road.distance << endl;

                savedRoutes.insert({city1, city2});
            }
        }
    }

    cityFile.close();
    routeFile.close();

    cout << "Data saved successfully!\n";
}
void FileManager::loadData(Graph &graph)
{
    ifstream cityFile("data/cities.txt");
    ifstream routeFile("data/routes.txt");

    if (!cityFile || !routeFile)
    {
        cout << "No saved data found.\n";
        return;
    }

    string city;

    // Load Cities
    while (cityFile >> city)
    {
        graph.addCity(city);
    }

    string source, destination;
    int distance;

    // Load Routes
    while (routeFile >> source >> destination >> distance)
    {
        graph.addRoute(source, destination, distance);
    }

    cityFile.close();
    routeFile.close();

    cout << "Data loaded successfully!\n";
}