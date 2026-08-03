#include "../include/Menu.h"
#include "../include/FileManager.h"

#include <iostream>
#include <limits>

using namespace std;

void readCityName(string &city){
    getline(cin >> ws, city);
}
void Menu::start(){
    FileManager::loadData(routePlanner);

    int choice;
    string source, destination;
    int distance;

    do{
        cout << "\n=========================================\n";
        cout << "        SMART ROUTE PLANNER\n";
        cout << "=========================================\n";
        cout << "1. Add City\n";
        cout << "2. Add Route\n";
        cout << "3. Display Road Network\n";
        cout << "4. Find Shortest Route\n";
        cout << "5. Remove City\n";
        cout << "6. Remove Route\n";
        cout << "7. BFS Traversal\n";
        cout << "8. Search City\n";
        cout << "9. Update Route Distance\n";
        cout << "10. DFS Traversal\n";
        cout << "11. Graph Statistics\n";
        cout << "12. Recent Route History\n";
        cout << "13. Exit\n";
        cout << "=========================================\n";
        cout << "Enter your choice: ";

        if (!(cin >> choice)){
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            cout << "\nInvalid input! Please enter a number.\n";
            continue;
        }

        switch (choice){
        case 1:

            cout << "Enter City Name: ";
            readCityName(source);

            routePlanner.addCity(source);
            break;

        case 2:

            cout << "Source City: ";
            readCityName(source);

            cout << "Destination City: ";
            readCityName(destination);

            cout << "Distance: ";
            cin >> distance;

            routePlanner.addRoute(source, destination, distance);
            break;

        case 3:

            routePlanner.displayGraph();
            break;

        case 4:

            cout << "Source City: ";
            readCityName(source);

            cout << "Destination City: ";
            readCityName(destination);

            routePlanner.findShortestPath(source, destination);
            break;

        case 5:

            cout << "Enter City Name: ";
            cin >> source;

            routePlanner.removeCity(source);
            break;

        case 6:

            cout << "Source City: ";
            readCityName(source);

            cout << "Destination City: ";
            readCityName(destination);

            routePlanner.removeRoute(source, destination);
            break;

        case 7:

            cout << "Enter Starting City: ";
            readCityName(source);

            routePlanner.BFS(source);
            break;

        case 8:
        {
            cout << "\nEnter City Name: ";
            readCityName(source);
            
            routePlanner.searchCity(source);
            break;
        }

        case 9:
        {
            cout << "\nEnter Source City: ";
            readCityName(source);

            cout << "Enter Destination City: ";
            readCityName(destination);

            cout << "Enter New Distance (km): ";
            cin >> distance;

            routePlanner.updateRoute(source,destination,distance);
            break;
        }

        case 10:
        {
            cout << "\nEnter Starting City: ";
            readCityName(source);

            routePlanner.DFS(source);

            break;
        }

        case 11:
        {
            routePlanner.graphStatistics();
            break;
        }

        case 12:
        {
            routePlanner.showRouteHistory();
            break;
        }

        case 13:
        {
            FileManager::saveData(routePlanner);

            cout << "\nData Saved Successfully!\n";
            cout << "Thank You for using Smart Route Planner!\n";

            break;
        }

        default:

            cout << "\nInvalid Choice!\n";
        }

    } while (choice != 13);
}