#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class Graph;

class FileManager
{
public:

    // Save complete graph
    static void saveData(Graph &graph);

    // Load complete graph
    static void loadData(Graph &graph);
};

#endif