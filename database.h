#ifndef DATABASE_H
#define DATABASE_H

#include <iostream>
#include <vector>

#include <stdexcept>
#include <fstream>
#include <string>

using namespace std;

#include "table.h"

class Database {
private:
    vector<Table> tables;
public:
    void createTable(const string & tableName);
    void addColumnToTable(const string & tableName, const Column & column);
	void addRowToTable(const string & tableName, const Row & row);
	void print() const;
    Table* findTable(const string & tableName);
    void Database::saveToBinaryFile(const string& filename) const;
    void Database::loadFromBinaryFile(const std::string& filename) ;
};

#endif

