#ifndef PROCESS_H
#define PROCESS_H

#include <set>
#include "Path.h"
#include "Scanner.h"
#include "Links.h"

using namespace std;
namespace fs = std::filesystem;

set<fs::path> filesVisited;

void AddToMap (vector<Path> Paths) {
    for (Path pa : Paths) {
        pa.AddPathToMap();
    }

    return;
}

void ReadFromFile(Path file) {
    ofstream outFile;
    ifstream inFile;

    if (filesVisited.find(file.GetAbsolutePath()) != filesVisited.end()) {
        return;
    }

    filesVisited.insert(file.GetAbsolutePath());

    cout << "READING FROM " << file.GetAbsolutePath() << endl;

    Scanner scanner(file.GetAbsolutePath());
    scanner.RunScan();

    //Get strings from file
    vector<string> strings = scanner.GetStrings();
    /*
    outFile.open("strings.txt");
    if (outFile.is_open()) {
        for (string str : strings) {
            outFile << str << endl;
        }
    }
    outFile.close();
    */

    //Get links from strings
    vector<fs::path> links = FindLinks(strings, file.GetDirectory());
    vector<Path> newPaths;
    for (fs::path link : links) {
        Path temp(link);
        newPaths.push_back(temp);
    }
    //Add all links to map
    AddToMap(newPaths);

    //Send every code file to ReadFromFile()
    for (Path pa : newPaths) {
        if (!pa.IsDirectory()) {
            string extension = pa.GetExtension();
            if (extension == ".cfm" || extension == ".cfc" || extension == ".js" || extension == ".css") {
                ReadFromFile(pa);
            }
        }
    }

    return;
}











#endif