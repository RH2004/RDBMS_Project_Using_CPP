#ifndef LEXER_H
#define LEXER_H

#include <string>

using namespace std;

// Token types
typedef enum {
    CREATE, TABLE, INSERT, INTO, VALUES, SELECT, FROM, WHERE,
    INTEGER, VARCHAR, DATE, STAR, COMMA, LPAREN, RPAREN, SEMICOLON,
    EQUALS, NOT_EQUALS, LESS, GREATER, LESS_EQUALS, GREATER_EQUALS,
    IDENTIFIER, NUMBER, STRING, END, ERROR
}TokenType;

// Token structure
typedef struct {
    TokenType type;
    string value;
}Token;

class Lexer {
private:
    string input;
    int index;

public:
    Lexer(const string & input);
    Token getNextToken();
};

#endif

