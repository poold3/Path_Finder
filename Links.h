#ifndef LINKS_H
#define LINKS_H

using namespace std;
namespace fs = std::filesystem;

bool IsValidDirectoryCharacter (char c) {
    if (c == '/' || c == '\\' || c == ':' || c == '*' || c == '?' || c == '"' || c == '<' || c == '>' || c == '|') {
        return false;
    }
    return true;
}

int FindDirectorySize(string inputLine) {
    int size = 0;
    while (inputLine.length() > 0 && IsValidDirectoryCharacter(inputLine.at(0))) {
        ++size;
        inputLine = inputLine.substr(1);
    }
    return size;
}

bool CombinePaths(string str, fs::path currentPath) {
    //This function needs to combine the str path to the current path
    bool exists = false;
    string strCopy = str;
    if (strCopy.at(0) == '/' || strCopy.at(0) == '\\') {
        exists = fs::exists(strCopy);
        return exists;
    }
    else if (strCopy.substr(0, 2) == "./" || strCopy.substr(0, 2) == ".\\") {
        strCopy = strCopy.substr(2);
        fs::path temp = strCopy;
        fs::path temp2 = currentPath;
        temp2 += temp;
        exists = fs::exists(temp2);
        return exists;
    }
    else {
        string newPath = "";
        int size = 1;
        for (int i = 0; i < (int)strCopy.length(); ++i) {
            if (IsValidDirectoryCharacter(strCopy.at(0))) {
                size = FindDirectorySize(strCopy);
                newPath += strCopy.substr(0, size);
            }
            if (strCopy.at(0) == '/' || strCopy.at(0) == '\\') {
                newPath += "/";
                size = 1;
            }
            strCopy = strCopy.substr(size);
        }
    }
    
}


string FilterString (string str, fs::path currentPath) {
    //This function will look for additions (https, ?, etc.) to file paths that we need to remove
    //before we can map out the path
    if (str.length() <= 0) {
        return str;
    }
    if (str.at(0) == '\'' || str.at(0) == '\"') {
        str.erase(0, 1);
    }
    if (str.at(str.length() - 1) == '\'' || str.at(str.length() - 1) == '\"') {
        str.erase(str.length() - 1, 1);
    }
    for (int i = 0; i < (int)str.length(); ++i) {
        str.at(i) = tolower(str.at(i));
    }


    bool changes = true;

    while (changes == true && str.length() > 0 && CombinePaths(str, currentPath) == false) {
        changes = false;
        size_t position = str.find("https://");
        if (position != string::npos && position == 0) {
            str.erase(position, 8);
            changes = true;
        }
        position = str.find("http://");
        if (position != string::npos && position == 0) {
            str.erase(position, 7);
            changes = true;
        }
        position = str.find("www.");
        if (position != string::npos && position == 0) {
            str.erase(position, 4);
            changes = true;
        }
        position = str.find("url");
        if (position != string::npos) {
            str.erase(position, 4);
            changes = true;
        }
    }
    

    return str;
}

vector<fs::path> FindLinks(vector<string> strings, fs::path currentPath) {
    vector<fs::path> links;
    for (string str : strings) {
        fs::path testPath = currentPath;
        //"/mnt/v/alumni3.byu.eduCopy/index.cfm";
        //cout << fs::exists(testing) << endl;
        //cout << fs::is_directory(testing) << endl;

        //Send string to filtering station.
        string filteredString = FilterString(str, currentPath);
        
    }



    return links;
}


#endif