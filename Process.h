#ifndef PROCESS_H
#define PROCESS_H

#include <set>
#include "Path.h"
#include "Scanner.h"
#include "Links.h"

using namespace std;
namespace fs = std::filesystem;

//Set file extensions from which to read.
set<string> EXTENSIONSTOREAD({".js", ".css", ".htm", ".html"});

//Set default file name to search for within all directories
string DEFAULTFILENAME = "index";

set<fs::path> filesVisited;
set<fs::path> pathsMade;

void AddToMap (vector<Path> Paths) {
    for (Path pa : Paths) {
        pathsMade.insert(pa.GetAbsolutePath());
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

    cout << "\nREADING FROM " << file.GetAbsolutePath() << endl;

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
            if (EXTENSIONSTOREAD.find(extension) != EXTENSIONSTOREAD.end()) {
                ReadFromFile(pa);
            }
        }
        else {
            //Code to look for an index file in this directory
            fs::path absPath = pa.GetAbsolutePath();
            string tempString = absPath.string();
            if (tempString.at(tempString.length() - 1) == '.') {
                tempString.erase(tempString.length() - 1, 1);
                absPath = tempString;
            }
            if (tempString.at(tempString.length() - 1) == '/' || tempString.at(tempString.length() - 1) == '\\') {
                absPath += DEFAULTFILENAME;
            }
            else {
                string defaultWithSlash = "/" + DEFAULTFILENAME;
                absPath += defaultWithSlash;
            }
            for (string extension : EXTENSIONSTOREAD) {
                fs::path temp = absPath;
                temp += extension;
                if (fs::exists(temp)) {
                    Path tempPath(temp);
                    pathsMade.insert(tempPath.GetAbsolutePath());
                    tempPath.AddPathToMap();
                    ReadFromFile(tempPath);
                    break;
                }
            }
        }
    }

    return;
}











#endif