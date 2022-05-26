#ifndef SCANNER_H
#define SCANNER_H

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

#include "Token.h"
using namespace std;

class Scanner {
    private:
    vector<Token> tokens;
    string inputFile;

    public:
    Scanner(string inputFile) {
        this->inputFile = inputFile;
    }
    Scanner() {
        this->inputFile = "";
    }

    vector<Token> GetTokens() {
        return tokens;
    }

    void ThrowError(string error) {
        throw std::invalid_argument(error);
    }

    int FindNumberSize(string inputLine) {
        //We already know the first char is part of the number
        inputLine = inputLine.substr(1);
        int size = 1;

        while (inputLine.length() > 0 && isdigit(inputLine.at(0))) {
            ++size;
            inputLine = inputLine.substr(1);
        }
        if (inputLine.length() > 0 && isalpha(inputLine.at(0))) {
            //Letter directly after a number. This is not a number and an ID cannot start with
            //a number.
            ThrowError("Not a number");
        }
        return size;
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

    bool IsHexCode(string inputLine) {
        inputLine = inputLine.substr(1);
        if (inputLine.length() < 6) {
            return false;
        }
        for (int i = 0; i < 6; ++i) {
            if (!isalnum(inputLine.at(i))) {
                return false;
            }
        }
        return true;
    }

    void RunScan() {
        ifstream inFile;
        string inputLine;
        inFile.open(inputFile);
        if (!inFile.is_open()) {
            ThrowError("Unable to open " + inputFile);
        }
        TokenType type;
        int size;
        int line = 1;
        while (getline(inFile, inputLine)) {
            //Erase all whitespace from the inputLine
            for (unsigned long i = 0; i < inputLine.length(); ++i) {
                if (isspace(inputLine.at(i))) {
                    inputLine.erase(i, 1);
                    --i;
                }
            }
            //cout << inputLine << endl;

            while (inputLine.length() > 0) {
                if (inputLine.at(0) == ',') {
                    type = COMMA;
                    size = 1;
                }
                else if (inputLine.at(0) == '.') {
                    type = PERIOD;
                    size = 1;
                }
                else if (inputLine.at(0) == '#' && IsHexCode(inputLine) == true) {
                    type = HEXCODE;
                    size = 7;
                }
                else if (inputLine.at(0) == 'r' && inputLine.substr(0, 4) == "rgb(") {
                    type = RGB;
                    size = 3;
                }
                else if (inputLine.at(0) == '?') {
                    type = Q_MARK;
                    size = 1;
                }
                else if (inputLine.at(0) == '(') {
                    type = LEFT_PAREN;
                    size = 1;
                }
                else if (inputLine.at(0) == ')') {
                    type = RIGHT_PAREN;
                    size = 1;
                }
                else if (inputLine.at(0) == '[') {
                    type = LEFT_BRACKET;
                    size = 1;
                }
                else if (inputLine.at(0) == ']') {
                    type = RIGHT_BRACKET;
                    size = 1;
                }
                else if (inputLine.at(0) == '{') {
                    type = LEFT_BRACE;
                    size = 1;
                }
                else if (inputLine.at(0) == '}') {
                    type = RIGHT_BRACE;
                    size = 1;
                }
                else if (inputLine.at(0) == ':') {
                    type = COLON;
                    size = 1;
                }
                else if (inputLine.at(0) == ';') {
                    type = SEMI_COLON;
                    size = 1;
                }
                else if (inputLine.at(0) == '*') {
                    type = MULTIPLY;
                    size = 1;
                }
                else if (inputLine.at(0) == '/') {
                    if (inputLine.length() > 1 && inputLine.at(1) == '/') {
                        type = COMMENT;
                        break;
                    }
                    else {
                        type = DIVIDE;
                        size = 1;
                    }
                }
                else if (inputLine.at(0) == '+') {
                    type = ADD;
                    size = 1;
                }
                else if (inputLine.at(0) == '=') {
                    type = EQUALS;
                    size = 1;
                }
                else if (isdigit(inputLine.at(0))) {
                    //Positive NUMBER
                    type = NUMBER;
                    try {
                        size = FindNumberSize(inputLine);
                    }
                    catch (exception& e) {
                        stringstream error;
                        error << "Invalid number on line " << line << ".";
                        ThrowError(error.str());
                    }
                }
                else if (inputLine.at(0) == '-') {
                    //It is a negative NUMBER if the dash does not directly follow a number.
                    if (inputLine.length() > 1 && isdigit(inputLine.at(1)) && (tokens.size() == 0 || tokens.at(tokens.size() - 1).getType() != NUMBER)) {
                        //Negative NUMBER
                        type = NUMBER;
                        try {
                            size = FindNumberSize(inputLine);
                        }
                        catch (exception& e) {
                            stringstream error;
                            error << "Invalid number on line " << line << ".";
                            ThrowError(error.str());
                        }
                    }
                    else {
                        type = SUBTRACT;
                        size = 1;
                    }
                }
                else if (inputLine.at(0) == 'c' && inputLine.substr(0, 7) == "circle(") {
                    type = CIRCLE;
                    size = 6;
                }
                else if (inputLine.at(0) == 'c' && inputLine.substr(0, 6) == "color(") {
                    type = COLOR;
                    size = 5;
                }
                else if (inputLine.at(0) == 'r' && inputLine.substr(0, 5) == "rect(") {
                    type = RECT;
                    size = 4;
                }
                else if (inputLine.at(0) == 'm' && inputLine.substr(0, 7) == "moveTo(") {
                    type = MOVETO;
                    size = 6;
                }
                else if (inputLine.at(0) == 'd' && inputLine.substr(0, 7) == "drawTo(") {
                    type = DRAWTO;
                    size = 6;
                }
                else if (inputLine.at(0) == 't' && inputLine.substr(0, 4) == "true" && (inputLine.length() == 4 || (!isalpha(inputLine.at(4)) && !isdigit(inputLine.at(4))))) {
                    type = TRUE;
                    size = 4;
                }
                else if (inputLine.at(0) == 'f' && inputLine.substr(0, 5) == "false" && (inputLine.length() == 5 || (!isalpha(inputLine.at(5)) && !isdigit(inputLine.at(5))))) {
                    type = FALSE;
                    size = 5;
                }
                else if (inputLine.length() > 2 && (inputLine.at(0) == '\'' || inputLine.at(0) == '\"')) {
                    type = STRING;
                    try {
                        size = FindStringSize(inputLine);
                    }
                    catch (exception& e) {
                        stringstream error;
                        error << "No end to string on line " << line << ".";
                        ThrowError(error.str());
                    }
                }
                else if (isalpha(inputLine.at(0))) {
                    type = ID;
                    try {
                        size = FindIDSize(inputLine);
                    }
                    catch (exception& e) {
                        stringstream error;
                        error << "Invalid ID on line " << line << ".";
                        ThrowError(error.str());
                    }
                    
                }
                else {
                    stringstream error;
                    error << "Invalid token detected on line " << line << ": " << inputLine.at(0) << ".";
                    ThrowError(error.str());
                }
                string value = inputLine.substr(0, size);
                inputLine = inputLine.substr(size);
                Token newToken(type, value, line);
                tokens.push_back(newToken);
            }
            ++line;
        }
    }


};




#endif