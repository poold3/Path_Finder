#ifndef SCANNER_H
#define SCANNER_H

using namespace std;

class Scanner {
    private:
    vector<string> strings;
    vector<string> ids;
    string inputFile;

    public:
    Scanner(string inputFile) {
        this->inputFile = inputFile;
    }
    Scanner() {
        this->inputFile = "";
    }

    vector<string> GetStrings() {
        return strings;
    }

    vector<string> GetIds() {
        return ids;
    }

    void ThrowError(string error) {
        throw std::invalid_argument(error);
    }

    int FindStringSize(string inputLine) {
        string endOfString = inputLine.substr(0, 1);
        size_t position = inputLine.find(endOfString, 1);
        if (position != string::npos) {
            return static_cast<int>(position + 1);
        }   
        else {
            ThrowError("");
        }
        return 0;
    }

    int FindIDSize(string inputLine) {
        int size = 0;
        while (inputLine.length() > 0 && isalnum(inputLine.at(0))) {
            ++size;
            inputLine = inputLine.substr(1);
        }
        return size;
    }

    void RunScan() {
        cout << inputFile << endl;
        ifstream inFile;
        string inputLine;
        inFile.open(inputFile);
        if (!inFile.is_open()) {
            ThrowError("Unable to open " + inputFile);
        }
        int size;
        int line = 1;
        bool jsComment = false;
        bool cfComment = false;
        while (getline(inFile, inputLine)) {
            while (inputLine.length() > 0) {
                if (jsComment == false && cfComment == false) {
                    if (inputLine.length() > 2 && (inputLine.at(0) == '\'' || inputLine.at(0) == '\"')) {
                        //type = STRING;
                        try {
                            size = FindStringSize(inputLine);
                            string value = inputLine.substr(0, size);
                            strings.push_back(value);
                        }
                        catch (exception& e) {
                            //stringstream error;
                            cout << "No end to string on line " << line << ".";
                            //error << "No end to string on line " << line << ".";
                            //ThrowError(error.str());
                            size = inputLine.length();
                        }
                    }
                    else if (isalpha(inputLine.at(0))) {
                        //type = ID;
                        try {
                            size = FindIDSize(inputLine);
                            string value = inputLine.substr(0, size);
                            ids.push_back(value);
                        }
                        catch (exception& e) {
                            stringstream error;
                            error << "Invalid ID on line " << line << ".";
                            ThrowError(error.str());
                        }
                        
                    }
                    else if (inputLine.substr(0, 2) == "//") {
                        //type = ONE-LINE COMMENT;
                        size = inputLine.length();
                    }
                    else if (inputLine.substr(0, 2) == "/*") {
                        //type = MULTI-LINE COMMENT ON;
                        size = 2;
                        jsComment = true;
                    }
                    else if (inputLine.substr(0, 4) == "<!--") {
                        //type = MULTI-LINE COMMENT ON;
                        size = 4;
                        cfComment = true;
                    }
                    else {
                        size = 1;
                    }
                }
                else if (inputLine.substr(0, 2) == "*/") {
                    //type = MULTI-LINE COMMENT OFF;
                    size = 2;
                    jsComment = false;
                }
                else if (inputLine.substr(0, 3) == "-->") {
                    //type = MULTI-LINE COMMENT OFF;
                    size = 3;
                    cfComment = false;
                }
                else {
                    size = 1;
                }
                inputLine = inputLine.substr(size);
            }
            ++line;
        }
    }


};




#endif