#ifndef PARSER_H
#define PARSER_H

#include "lexer.h"
#include "database.h"

class Parser {
private:
    Lexer & lexer;
    Token currentToken;
    Database & database;

    void match(TokenType expected);
    void parseCreateStatement();
    void parseInsertStatement();
    void parseSelectStatement();

public:
    Parser(Lexer & lexer, Database & database);
    void parseStatement();
};

#endif

