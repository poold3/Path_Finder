#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>

#include "Scanner.h"
#include "Parser.h"

using namespace std;

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cout << "Incorrect number of command line arguments." << endl;
        return 0;
    }

    ifstream inFile;
    inFile.open(argv[1]);
    if (!inFile.is_open()) {
        cout << argv[1] << " was not found." << endl;
        return 0;
    }





    return 0;
}