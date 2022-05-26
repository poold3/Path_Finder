#ifndef TOKEN_H
#define TOKEN_H

#include <iostream>
#include <string>
#include <sstream>
using namespace std;

enum TokenType {
	COMMA, PERIOD, Q_MARK, LEFT_PAREN, RIGHT_PAREN, LEFT_BRACKET, RIGHT_BRACKET, 
    LEFT_BRACE, RIGHT_BRACE, COLON, SEMI_COLON, MULTIPLY, DIVIDE, ADD, SUBTRACT, EQUALS, 
    NUMBER, ID, STRING, COMMENT, TRUE, FALSE, FORWARD_SLASH, BACK_SLASH, DOUBLE_QUOTE,
    SINGLE_QUOTE,
};

class Token {
	private:
		TokenType type;
		string value;
		int line;
	public:
		Token(TokenType type, string value, int line) :
		type(type), value(value), line(line) {}
        Token() {}
		string toString() {
			stringstream out;
            out << "(" << typeName(type) << ",\"" << value << "\"," << line << ")";
			return out.str();
		}
        TokenType getType() const {
            return type;
        }
        string getValue() {
            return value;
        }
        int getLine() {
            return line;
        }
		string typeName(TokenType type) const {
			switch(type) {
                case COMMA:
                    return "COMMA";
                case PERIOD:
                    return "PERIOD";
                case Q_MARK:
                    return "Q_MARK";
                case LEFT_PAREN:
                    return "LEFT_PAREN";
                case RIGHT_PAREN:
                    return "RIGHT_PAREN";
                case LEFT_BRACKET:
                    return "LEFT_PAREN";
                case RIGHT_BRACKET:
                    return "RIGHT_PAREN";
                case LEFT_BRACE:
                    return "LEFT_PAREN";
                case RIGHT_BRACE:
                    return "RIGHT_PAREN";
                case COLON:
                    return "COLON";
                case SEMI_COLON:
                    return "SEMI_COLON";
                case MULTIPLY:
                    return "MULTIPLY";
                case DIVIDE:
                    return "DIVIDE";
                case ADD:
                    return "ADD";
                case SUBTRACT:
                    return "SUBTRACT";
                case EQUALS:
                    return "EQUALS";
                case NUMBER:
                    return "NUMBER";
                case ID:
                    return "ID";
                case TRUE:
                    return "TRUE";
                case FALSE:
                    return "FALSE";
                case FORWARD_SLASH:
                    return "FORWARD_SLASH";
                case BACK_SLASH:
                    return "BACK_SLASH";
                case DOUBLE_QUOTE:
                    return "DOUBLE_QUOTE";
                case SINGLE_QUOTE:
                    return "SINGLE_QUOTE";
            }
            return "";
		}

};
#endif