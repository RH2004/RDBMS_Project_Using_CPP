#ifndef COLUMN_H
#define COLUMN_H

#include <iostream>
#include <string>

using namespace std;

class Column {
private:
    string name;
    string dataType;
public:
    Column(const string & name, const string & dataType);
    string getName() const;
    string getDataType() const;
    void print() const;
    void printHeader() const;
};

#endif

