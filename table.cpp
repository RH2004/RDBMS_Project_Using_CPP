#include "table.h"

Table::Table(const string & name){
	this->name = name;
}

const string & Table::getName() const {
    return name;
}

void Table::addColumn(const Column & column) {
	columns.push_back(column);
}

void Table::addRow(const Row & row){
	if (row.getValues().size() != columns.size()) {
        throw runtime_error("Error: Column count mismatch.");
    }
    rows.push_back(row);
}

const vector<Column> & Table::getColumns() const {
    return columns;
}

const vector<Row> & Table::getRows() const {
    return rows;
}

void Table::print() const{
	cout << "Table: " << getName()<<endl;
	cout << "Columns:"<<endl;
    vector<Column> columns = getColumns();
    for (int j = 0; j < columns.size(); j++) {
        columns[j].print();
    }
    cout << "Rows:"<<endl;
    for (int j = 0; j < columns.size(); j++) {
        columns[j].printHeader();    cout << "\t";
    }
    cout<< endl << endl;
    vector<Row> rows = getRows();
    for (int k = 0; k < rows.size(); k++) {
    	rows[k].print();
    }
}

