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

bool CombinePaths(string str, fs::path currentPath, fs::path &newPath, vector<string> oldPathSegments) {
    //This function needs to combine the str path to the current path
    bool exists = false;
    string strCopy = str;

    vector<string> newPathSegments;
    int size;
    //Get segments of new path
    while (strCopy.length() > 0) {
        if (IsValidDirectoryCharacter(strCopy.at(0))) {
            size = FindDirectorySize(strCopy);
            string newSegement = strCopy.substr(0, size);
            if (newSegement == "alumni3.byu.edu") {
                newSegement = "alumni3.byu.eduCopy";
            }
            if (newPathSegments.size() != 0 || (newSegement != "alumni3" && newSegement != "alumni3.byu.eduCopy")) {
                newPathSegments.push_back(strCopy.substr(0, size));
            }
        }
        else if (strCopy.at(0) == '/' || strCopy.at(0) == '\\') {
            size = 1;
        }
        else {
            return false;
        }
        strCopy = strCopy.substr(size);
    }

    strCopy = str;
    if (strCopy.length() == 0) {
        return false;
    }
    else if (strCopy.at(0) == '/' || strCopy.at(0) == '\\') {
        string newString = "/mnt/v/alumni3.byu.eduCopy/";
        for (int i = 0; i < (int)newPathSegments.size(); ++i) {
            newString += newPathSegments.at(i);
            if (i != (int)(newPathSegments.size() - 1)) {
                newString += "/";
            }
        }
        exists = fs::exists(newString);
        newPath = newString;
        return exists;
    }
    else if (strCopy.substr(0, 2) == "./" || strCopy.substr(0, 2) == ".\\") {
        strCopy = strCopy.substr(2);
        fs::path temp = strCopy;
        newPath = currentPath;
        newPath += temp;
        exists = fs::exists(newPath);
        return exists;
    }
    else {
        vector<string> finalSegments = oldPathSegments;
        //Using the newPath segments, create the finalSegments
        for (int i = 0; i < (int)newPathSegments.size(); ++i) {
            if (newPathSegments.at(i) == "..") {
                finalSegments.pop_back();
            }
            else {
                finalSegments.push_back(newPathSegments.at(i));
            }
        }

        //Build newPath
        string newString = "/";
        for (int i = 0; i < (int)finalSegments.size(); ++i) {
            newString += finalSegments.at(i);
            if (i != (int)(finalSegments.size() - 1)) {
                newString += "/";
            }
        }

        exists = fs::exists(newString);
        newPath = newString;
        return exists;

    }
    
}


string FilterString (string str) {
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

    while (changes == true && str.length() > 0) {
        changes = false;
        size_t position = str.find("https://");
        if (position != string::npos && position == 0) {
            str.erase(position, 7);
            changes = true;
        }
        position = str.find("http://");
        if (position != string::npos && position == 0) {
            str.erase(position, 6);
            changes = true;
        }
        position = str.find("www.");
        if (position != string::npos && position == 0) {
            str.erase(position, 4);
            string temp = "/";
            str = temp + str;
            changes = true;
        }
        position = str.find("url(");
        if (position != string::npos) {
            str.erase(0, position + 4);
            str.erase(str.length() - 1, 1);
            changes = true;
        }
        position = str.find("?");
        if (position != string::npos) {
            str.erase(position, str.length() - position);
            changes = true;
        }
        position = str.find("#");
        if (position != string::npos) {
            size_t nextPosition = str.find("#", position + 1);
            if (nextPosition != string::npos) {
                str.erase(position, str.length() - position);
                changes = true;
            }
        }
    }
    

    return str;
}

vector<fs::path> FindLinks(vector<string> strings, fs::path currentPath) {
    vector<fs::path> links;
    vector<string> oldPathSegments;
    string oldPath = currentPath.string();
    
    int size = 1;
    while (oldPath.length() > 0) {
        if (IsValidDirectoryCharacter(oldPath.at(0))) {
            size = FindDirectorySize(oldPath);
            oldPathSegments.push_back(oldPath.substr(0, size));
        }
        else if (oldPath.at(0) == '/' || oldPath.at(0) == '\\') {
            size = 1;
        }
        oldPath = oldPath.substr(size);
    }



    int counter = 0;
    for (string str : strings) {
        try {
            ++counter;
            fs::path testPath = currentPath;

            //Send string to filtering station.
            string filteredString = FilterString(str);
            fs::path newPath;
            bool exists = CombinePaths(filteredString, currentPath, newPath, oldPathSegments);

            if (exists) {
                cout << "\t" << counter << ": " << newPath << endl;
                links.push_back(newPath);
            }
        }
        
        catch(exception& e) {
            cout << endl << e.what() << endl << endl;
        }
    
    }
    


    return links;
}


#endif