#include "column.h"

Column::Column(const string & name, const string & dataType) {
    this->name = name;    this->dataType = dataType; 
}
string Column::getName() const {
    return name;
}
string Column::getDataType() const {
    return dataType;
}

void Column::print() const{
	cout << "\t" << getName() << " (" << getDataType() << ")" << endl;
}

void Column::printHeader() const{
	cout << getName();
}
