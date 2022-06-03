#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <set>
#include <filesystem>

#include "Path.h"
#include "Scanner.h"
#include "Links.h"
#include "Process.h"

using namespace std;
namespace fs = std::filesystem;

int main(int argc, char const * argv[]) {
    //Make sure path is specified
    if (argc < 2) {
        cout << "Incorrect number of command line arguments." << endl;
        return 0;
    }

    //Declare variables
    ifstream inFile;
    ofstream outFile;
    fs::path currentPath = fs::current_path();
    Path startFile;

    if (argc == 2) {
        cout << "Starting new map!" << endl;

        startFile = Path(argv[1]);

        //Remove previous path map
        fs::remove_all("Map");

        //Create new Map directory
        fs::create_directories("Map");
    }
    else if (argc == 3 && (string)argv[1] == "-c") {
        cout << "Continuing on existing map!" << endl;

        startFile = Path(argv[2]);

        //Load FilesVisited.txt into filesVisited
        inFile.open("FilesVisited.txt");
        if (inFile.is_open()) {
            string inputLine;
            while (getline(inFile, inputLine)) {
                filesVisited.insert(inputLine);
            }
        }
        inFile.close();
    }
    else {
        cout << "Incorrect command line argument." << endl;
        return 0;
    }
    

    //Verify startFile
    inFile.open(startFile.GetAbsolutePath());
    if (!inFile.is_open() || startFile.IsDirectory()) {
        cout << "No file found at " << startFile.GetAbsolutePath() << "." << endl;
        return 0;
    }
    inFile.close();

    //Add startFile to Map
    startFile.AddPathToMap();

    //Send startFile to Scanner
    ReadFromFile(startFile);

    cout << "\n\nPath-Finder Mapping Complete!" << endl;
    cout << filesVisited.size() << " files read!" << endl;
    outFile.open("FilesVisited.txt");
    if (outFile.is_open()) {
        for (fs::path pa : filesVisited) {
            outFile << pa << endl;
        }
    }
    outFile.close();
    cout << pathsMade.size() << " paths/files made!" << endl;
    return 0;
}