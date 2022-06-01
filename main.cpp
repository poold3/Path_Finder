#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <filesystem>

#include "Path.h"
#include "Scanner.h"
#include "Links.h"
#include "Process.h"

using namespace std;
namespace fs = std::filesystem;

int main(int argc, char* argv[]) {
    //Make sure path is specified
    if (argc != 2) {
        cout << "Incorrect number of command line arguments." << endl;
        return 0;
    }

    //Declare variables
    ifstream inFile;
    ofstream outFile;
    fs::path currentPath = fs::current_path();
    Path startFile(argv[1]);

    //Remove previous path map
    fs::remove_all("Map");

    //Create new Map directory
    fs::create_directories("Map");

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
    return 0;
}