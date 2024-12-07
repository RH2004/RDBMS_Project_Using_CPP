#include "compiler.h"

Compiler::Compiler(Database & database) : database(database) {

}

void Compiler::compile(const string & query) {
    Lexer lexer(query);
    Parser parser(lexer, database);
    parser.parseStatement();
}
