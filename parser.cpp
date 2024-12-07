#include "parser.h"
#include <stdexcept>

Parser::Parser(Lexer & lexer, Database & database) : lexer(lexer), database(database) {
    currentToken = lexer.getNextToken();
}

void Parser::match(TokenType expected) {
    if (currentToken.type == expected) {
        currentToken = lexer.getNextToken();
    } else {
        throw runtime_error("Syntax Error: Unexpected token " + currentToken.value);
    }
}

void Parser::parseCreateStatement() {
    match(CREATE);
    match(TABLE);

    string tableName = currentToken.value;
    match(IDENTIFIER);

    database.createTable(tableName);

    match(LPAREN);
    do {
        string columnName = currentToken.value;
        match(IDENTIFIER);

        string dataType;
        if (currentToken.type == INTEGER) {
            dataType = "INTEGER";
            match(INTEGER);
        } else if (currentToken.type == VARCHAR) {
            dataType = "VARCHAR";
            match(VARCHAR);
            match(LPAREN);
            match(NUMBER);
            match(RPAREN);
        } else if (currentToken.type == DATE) {
            dataType = "DATE";
            match(DATE);
        } else {
            throw runtime_error("Syntax Error: Invalid data type.");
        }
		
		Column column(columnName, dataType);
        database.addColumnToTable(tableName, column);

        if (currentToken.type == COMMA) {
            match(COMMA);
        } else {
            break;
        }
    } while (true);
    match(RPAREN);
    match(SEMICOLON);
}

void Parser::parseInsertStatement() {
    match(INSERT);
    match(INTO);

    string tableName = currentToken.value;
    match(IDENTIFIER);

    match(VALUES);
    match(LPAREN);

    vector<string> values;
    do {
        if (currentToken.type == NUMBER || currentToken.type == STRING) {
            values.push_back(currentToken.value);
            match(currentToken.type);
        } else {
            throw runtime_error("Syntax Error: Invalid value.");
        }

        if (currentToken.type == COMMA) {
            match(COMMA);
        } else {
            break;
        }
    } while (true);
    match(RPAREN);
    match(SEMICOLON);
	Row row(values);
    database.addRowToTable(tableName, row);
}

void Parser::parseSelectStatement() {
    match(SELECT);

    if (currentToken.type == STAR) {
        match(STAR);
    } else {
        do {
            match(IDENTIFIER);
            if (currentToken.type == COMMA) {
                match(COMMA);
            } else {
                break;
            }
        } while (true);
    }

    match(FROM);

    string tableName = currentToken.value;
    match(IDENTIFIER);

    if (currentToken.type == WHERE) {
        match(WHERE);
        match(IDENTIFIER); // Column name
        match(EQUALS);     // Operator
        match(NUMBER);     // Value
    }

    match(SEMICOLON);
	
	Table * table = database.findTable(tableName);
	//table->print();
}

void Parser::parseStatement() {
    if (currentToken.type == CREATE) {
        parseCreateStatement();
    } else if (currentToken.type == INSERT) {
        parseInsertStatement();
    } else if (currentToken.type == SELECT) {
        parseSelectStatement();
    } else {
        throw runtime_error("Syntax Error: Invalid statement.");
    }
}

