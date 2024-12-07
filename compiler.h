#ifndef COMPILER_H
#define COMPILER_H

#include <iostream>
#include <vector>
#include <string>

using namespace std;

#include <stdexcept>
#include "parser.h"

class Compiler {
private:
    Database & database;
public:
    Compiler(Database & database);
    void compile(const string & query);
};

#endif

