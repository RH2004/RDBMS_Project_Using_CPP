#include "row.h"

Row::Row(){ }

Row::Row(const vector<string> & values){
	this->values = values;
}

Row& Row::addValue(string value) {
    this->values.push_back(value);
    return *this; // Correctly return a reference to the object
}


const vector<string> & Row::getValues() const {
    return values;
}

void Row::print() const {
    for (int i = 0; i < values.size(); i++) {
        cout << values[i] << "\t";
    }
    cout << endl;
}

