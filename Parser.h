#ifndef PARSER_H
#define PARSER_H

#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <fstream>
#include <sstream>

#include "Token.h"
using namespace std;

class Parser {
    private:
        vector<Token> tokens;
        queue<TokenType> commands;
        queue<Circle> circles;
        queue<Color> colors;
        queue<Rect> rects;
        queue<MoveTo> moveTos;
        queue<DrawTo> drawTos;

        // '(' = ++ | ')' = --. If parenCounter != 0 at the end, ERROR!
        int parenCounter = 0;

    public:
        Parser(vector<Token> tokens) {
            this->tokens = tokens;
        }

        Parser() {

        }

        void ThrowError(string error) {
            throw std::invalid_argument(error);
        }

        queue<TokenType> GetCommands() {
            return commands;
        }

        Circle GetNextCircle() {
            Circle circle = circles.front();
            circles.pop();
            return circle;
        }

        Color GetNextColor() {
            Color color = colors.front();
            colors.pop();
            return color;
        }

        Rect GetNextRect() {
            Rect rect = rects.front();
            rects.pop();
            return rect;
        }

        MoveTo GetNextMoveTo() {
            MoveTo moveTo = moveTos.front();
            moveTos.pop();
            return moveTo;
        }

        DrawTo GetNextDrawTo() {
            DrawTo drawTo = drawTos.front();
            drawTos.pop();
            return drawTo;
        }

        void advanceToken() {
            tokens.erase(tokens.begin());
        }

        TokenType tokenType() const {
            return tokens.at(0).getType();
        }

        Token match(TokenType t) {
            Token token = tokens.at(0);
            if (token.getType() == t) {
                advanceToken();
            }
            else {
                stringstream error;
                error << "Invalid Order of Tokens: " << tokens.at(0).toString();
                ThrowError(error.str());
            }
            return token;
        }

        vector<Token> matchColor(TokenType endOfColor) {
            //int parenthesis = 0;
            vector<Token> color;



            return color;
        }

        //This function can handle all order of operations that can be input as a number
        vector<Token> matchNumber(TokenType endOfNumber) {
            int parenthesis = 0;
            vector<Token> number;
            while (tokenType() != endOfNumber) {
                if (tokenType() == LEFT_PAREN) {
                    ++parenthesis;
                    number.push_back(match(LEFT_PAREN));
                }
                else if (tokenType() == RIGHT_PAREN) {
                    --parenthesis;
                    number.push_back(match(RIGHT_PAREN));
                }
                else if (tokenType() == NUMBER && (number.size() == 0 || (number.at(number.size() - 1).getType() != NUMBER && number.at(number.size() - 1).getType() != RIGHT_PAREN))) {
                    number.push_back(match(NUMBER));
                }
                else if (tokenType() != NUMBER && number.size() > 0 && (number.at(number.size() - 1).getType() == NUMBER || number.at(number.size() - 1).getType() == RIGHT_PAREN)) {
                    if (tokenType() == ADD) {
                        number.push_back(match(ADD));
                    }
                    else if (tokenType() == SUBTRACT) {
                        number.push_back(match(SUBTRACT));
                    }
                    else if (tokenType() == MULTIPLY) {
                        number.push_back(match(MULTIPLY));
                    }
                    else if (tokenType() == DIVIDE) {
                        number.push_back(match(DIVIDE));
                    }
                }
                else {
                    stringstream error;
                    error << "Invalid Order of Tokens: " << tokens.at(0).toString();
                    ThrowError(error.str());
                }

            }
            if (parenthesis != 0) {
                stringstream error;
                error << "Error concerning parenthesis on line " << number.at(0).getLine();
                ThrowError(error.str());
            }
            return number;
        }

        void RunScan() {
            while (tokens.size() > 0) {
                if (tokenType() == CIRCLE) {
                    //Match all tokens and store neccessary tokens.
                    match(CIRCLE);
                    match(LEFT_PAREN);
                    vector<Token> xPosition = matchNumber(COMMA);
                    match(COMMA);
                    vector<Token> yPosition = matchNumber(COMMA);
                    match(COMMA);
                    vector<Token> radius = matchNumber(COMMA);
                    match(COMMA);
                    Token fill;
                    if (tokenType() == TRUE) {
                        fill = match(TRUE);
                    }
                    else {
                        fill = match(FALSE);
                    }
                    match(RIGHT_PAREN);
                    match(SEMI_COLON);

                    //Create new object
                    Circle circle(xPosition, yPosition, radius, fill);
                    circles.push(circle);
                    commands.push(CIRCLE);

                }
                else if (tokenType() == COLOR) {
                    match(COLOR);
                    match(LEFT_PAREN);
                    vector<Token> value;
                    if (tokenType() == ID) {
                        value.push_back(match(ID));
                    }
                    else if (tokenType() == RGB) {
                        value.push_back(match(RGB));
                        value.push_back(match(LEFT_PAREN));
                        vector<Token> rValue = matchNumber(COMMA);
                        value.reserve(value.size() + rValue.size());
                        value.insert(value.end(), rValue.begin(), rValue.end());
                        value.push_back(match(COMMA));
                        vector<Token> gValue = matchNumber(COMMA);
                        value.reserve(value.size() + gValue.size());
                        value.insert(value.end(), gValue.begin(), gValue.end());
                        value.push_back(match(COMMA));
                        vector<Token> bValue = matchNumber(RIGHT_PAREN);
                        value.reserve(value.size() + bValue.size());
                        value.insert(value.end(), bValue.begin(), bValue.end());
                        value.push_back(match(RIGHT_PAREN));
                    }
                    else if (tokenType() == HEXCODE) {
                        value.push_back(match(HEXCODE));
                    }
                    match(RIGHT_PAREN);
                    match(SEMI_COLON);

                    Color color(value);
                    colors.push(color);
                    commands.push(COLOR);
                }
                else if (tokenType() == RECT) {
                    match(RECT);
                    match(LEFT_PAREN);
                    vector<Token> xPosition = matchNumber(COMMA);
                    match(COMMA);
                    vector<Token> yPosition = matchNumber(COMMA);
                    match(COMMA);
                    vector<Token> width = matchNumber(COMMA);
                    match(COMMA);
                    vector<Token> height = matchNumber(COMMA);
                    match(COMMA);
                    Token fill;
                    if (tokenType() == TRUE) {
                        fill = match(TRUE);
                    }
                    else {
                        fill = match(FALSE);
                    }
                    match(RIGHT_PAREN);
                    match(SEMI_COLON);

                    Rect rect(xPosition, yPosition, width, height, fill);
                    rects.push(rect);
                    commands.push(RECT);
                }
                else if (tokenType() == MOVETO) {
                    match(MOVETO);
                    match(LEFT_PAREN);
                    vector<Token> xPosition = matchNumber(COMMA);
                    match(COMMA);
                    vector<Token> yPosition = matchNumber(RIGHT_PAREN);
                    match(RIGHT_PAREN);
                    match(SEMI_COLON);

                    MoveTo moveTo(xPosition, yPosition);
                    moveTos.push(moveTo);
                    commands.push(MOVETO);
                }
                else if (tokenType() == DRAWTO) {
                    match(DRAWTO);
                    match(LEFT_PAREN);
                    vector<Token> xPosition = matchNumber(COMMA);
                    match(COMMA);
                    vector<Token> yPosition = matchNumber(RIGHT_PAREN);
                    match(RIGHT_PAREN);
                    match(SEMI_COLON);

                    DrawTo drawTo(xPosition, yPosition);
                    drawTos.push(drawTo);
                    commands.push(DRAWTO);
                }
            }
        }
};

#endif