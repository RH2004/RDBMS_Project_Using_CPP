#ifndef ROW_H
#define ROW_H

#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Row {
private:
    vector<string> values;

public:
	Row();
    Row(const vector<string> & values);
    Row & addValue(string value);
    const vector<string> & getValues() const;
    void print() const;
};

#endif

