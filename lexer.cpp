#include "lexer.h"

Lexer::Lexer(const string &input)
{
    this->input = input;
    this->index = 0;
}

Token Lexer::getNextToken()
{
    while (index < input.size() && isspace(input[index]))
        index++;

    if (index >= input.size())
        return (Token){END, ""};

    if (isalpha(input[index]))
    {
        string buffer;
        while (index < input.size() && (isalnum(input[index]) || input[index] == '_'))
        {
            buffer += input[index++];
        }
        if (buffer == "CREATE")
            return (Token){CREATE, buffer};
        if (buffer == "TABLE")
            return (Token){TABLE, buffer};
        if (buffer == "INSERT")
            return (Token){INSERT, buffer};
        if (buffer == "INTO")
            return (Token){INTO, buffer};
        if (buffer == "VALUES")
            return (Token){VALUES, buffer};
        if (buffer == "SELECT")
            return (Token){SELECT, buffer};
        if (buffer == "FROM")
            return (Token){FROM, buffer};
        if (buffer == "WHERE")
            return (Token){WHERE, buffer};
        if (buffer == "INTEGER")
            return (Token){INTEGER, buffer};
        if (buffer == "VARCHAR")
            return (Token){VARCHAR, buffer};
        if (buffer == "DATE")
            return (Token){DATE, buffer};
        return (Token){IDENTIFIER, buffer};
    }

    if (isdigit(input[index]))
    {
        string buffer;
        while (index < input.size() && isdigit(input[index]))
        {
            buffer += input[index++];
        }
        return (Token){NUMBER, buffer};
    }

    if (input[index] == '\'')
    {
        ++index; // Skip opening quote
        string buffer;
        while (index < input.size() && input[index] != '\'')
        {
            buffer += input[index++];
        }
        if (index < input.size() && input[index] == '\'')
            ++index; // Skip closing quote
        return (Token){STRING, buffer};
    }

    switch (input[index++])
    {
    case '*':
        return (Token){STAR, "*"};
    case ',':
        return (Token){COMMA, ","};
    case '(':
        return (Token){LPAREN, "("};
    case ')':
        return (Token){RPAREN, ")"};
    case ';':
        return (Token){SEMICOLON, ";"};
    case '=':
        return (Token){EQUALS, "="};
    case '<':
        if (input[index] == '=')
        {
            ++index;
            return (Token){LESS_EQUALS, "<="};
        }
        return (Token){LESS, "<"};
    case '>':
        if (input[index] == '=')
        {
            ++index;
            return (Token){GREATER_EQUALS, ">="};
        }
        return (Token){GREATER, ">"};
    case '!':
        if (input[index] == '=')
        {
            ++index;
            return (Token){NOT_EQUALS, "!="};
        }
        break;
    }

    return (Token){ERROR, string(1, input[index - 1])};
}
