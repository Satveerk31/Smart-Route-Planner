#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class Graph;

class FileManager{
public:
    static void saveData(Graph &graph);
    static void loadData(Graph &graph);
};

#endif