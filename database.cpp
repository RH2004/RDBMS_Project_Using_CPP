#include "database.h"

void Database::createTable(const string & tableName) {
    Table* table = findTable(tableName);
    if (table!=NULL) {
        throw runtime_error("Error: Table already exists.");
    }
    Table newtable(tableName);
    tables.push_back(newtable);
}

void Database::addColumnToTable(const string & tableName, const Column & column) {
    Table* table = findTable(tableName);
    if (!table) {
        throw runtime_error("Error: Table not found.");
    }
    table->addColumn(column);
}

void Database::addRowToTable(const string & tableName, const Row & row) {
    Table* table = findTable(tableName);
    if (!table) {
        throw runtime_error("Error: Table not found.");
    }
    table->addRow(row);
}

void Database::print() const {
    cout << "Database Structure:"<<endl;
    for (int i = 0; i < tables.size(); i++) {
    	tables[i].print();
    }
}

void Database::saveToBinaryFile(const string& filename) const {
    std::ofstream outFile(filename, std::ios::binary);
    if (!outFile) {
        throw std::runtime_error("Error: Could not open file for writing.");
    }
    // Write the number of tables
    size_t numTables = tables.size();
    outFile.write(reinterpret_cast<const char*>(&numTables), sizeof(numTables));

    // Write each table's name and its data
    for (const auto& table : tables) {
        // Write the table's name length and the name itself
        size_t tableNameLength = table.getName().size();
        outFile.write(reinterpret_cast<const char*>(&tableNameLength), sizeof(tableNameLength));
        outFile.write(table.getName().c_str(), tableNameLength);

        // Write columns count
        size_t numColumns = table.getColumns().size();
        outFile.write(reinterpret_cast<const char*>(&numColumns), sizeof(numColumns));

        // Write column details (name and type) for each column
        for (const auto& column : table.getColumns()) {
    size_t columnNameLength = column.getName().size();
    outFile.write(reinterpret_cast<const char*>(&columnNameLength), sizeof(columnNameLength));
    outFile.write(column.getName().c_str(), columnNameLength);

    // Get the string representing the column type
    std::string columnType = column.getDataType();

    // Write the length of the column type string (so we can read it back later)
    size_t columnTypeLength = columnType.size();
    outFile.write(reinterpret_cast<const char*>(&columnTypeLength), sizeof(columnTypeLength));

    // Write the actual string representing the column type
    outFile.write(columnType.c_str(), columnTypeLength);
}

        // Write rows count
        size_t numRows = table.getRows().size();
        outFile.write(reinterpret_cast<const char*>(&numRows), sizeof(numRows));

        // Write each row's data
        for (const auto& row : table.getRows()) {
            for (const auto& value : row.getValues()) {
                // Assuming values are strings, adjust accordingly if needed
                size_t valueLength = value.size();
                outFile.write(reinterpret_cast<const char*>(&valueLength), sizeof(valueLength));
                outFile.write(value.c_str(), valueLength);
            }
        }
    }

    outFile.close();
}





void Database::loadFromBinaryFile(const std::string& filename) {
    std::ifstream inFile(filename, std::ios::binary);
    if (!inFile) {
        throw std::runtime_error("Error: Could not open file for reading.");
    }
    // Read the number of tables
    size_t numTables;
    inFile.read(reinterpret_cast<char*>(&numTables), sizeof(numTables));
    // Read each table's data
    for (size_t i = 0; i < numTables; ++i) {
        // Read table name length and name
        size_t tableNameLength;
        inFile.read(reinterpret_cast<char*>(&tableNameLength), sizeof(tableNameLength));
        std::string tableName(tableNameLength, '\0');
        inFile.read(&tableName[0], tableNameLength);
        Table newTable(tableName);  // Create a new table object with the read name
        // Read the number of columns for the table
        size_t numColumns;
        inFile.read(reinterpret_cast<char*>(&numColumns), sizeof(numColumns));
        // Read column data (name and type)
        for (size_t j = 0; j < numColumns; ++j) {
            size_t columnNameLength;
            inFile.read(reinterpret_cast<char*>(&columnNameLength), sizeof(columnNameLength));
            std::string columnName(columnNameLength, '\0');
            inFile.read(&columnName[0], columnNameLength);
            // Read column type (a string)
            size_t columnTypeLength;
            inFile.read(reinterpret_cast<char*>(&columnTypeLength), sizeof(columnTypeLength));
            std::string columnType(columnTypeLength, '\0');
            inFile.read(&columnType[0], columnTypeLength);
            // Create the column and add it to the table
            Column newColumn(columnName, columnType);  // Assuming Column constructor exists that takes name and type
            newTable.addColumn(newColumn);
        }

        // Read the number of rows for the table
        size_t numRows;
        inFile.read(reinterpret_cast<char*>(&numRows), sizeof(numRows));

        // Read row data
        for (size_t k = 0; k < numRows; ++k) {
            Row newRow;  // Assuming a Row constructor that can take data
            for (size_t l = 0; l < numColumns; ++l) {
                size_t valueLength;
                inFile.read(reinterpret_cast<char*>(&valueLength), sizeof(valueLength));

                std::string value(valueLength, '\0');
                inFile.read(&value[0], valueLength);

                newRow.addValue(value);  // Assuming Row has a method to add values
            }
            newTable.addRow(newRow);  // Add the row to the table
        }

        // Add the table to the database
        tables.push_back(newTable);
    }

    inFile.close();
}



Table* Database::findTable(const string& tableName) {
    for(int i = 0; i < tables.size(); i++) {
        if (tables[i].getName() == tableName) {
            return &tables[i];
        }
    }
    return NULL;
}