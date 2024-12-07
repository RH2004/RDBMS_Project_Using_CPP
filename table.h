#ifndef TABLE_H
#define TABLE_H

#include <string>
#include <vector>
#include <stdexcept>
#include <iostream>

using namespace std;

#include "column.h"
#include "row.h"

class Table {
private:
    string name;
    vector<Column> columns;
    vector<Row> rows;

public:
    Table(const string & name);
    const string& getName() const;
    void addColumn(const Column & column);
    void addRow(const Row & row);
    const vector<Column> & getColumns() const;
    const vector<Row>& getRows() const;
    void print() const;
};

#endif

