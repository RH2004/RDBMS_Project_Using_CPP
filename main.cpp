#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>
#include <fstream>
#include <filesystem>  // For file existence check (C++17)

using namespace std;

#include "compiler.h"
#include "database.h"

void displayMenu() {
	cout << "Database Operations Menu:" << endl;
	cout << "1. Load Database" << endl;
	cout << "2. Display Database" << endl;
	cout << "3. Save Database" << endl;
	cout << "4. Add Row to Table" << endl;
	cout << "5. Exit" << endl;
}

int main(int argc, char** argv) {
	try {
		Database database;
		Compiler compiler(database);
		string filename = "sample_database.dat";

		// Check if the binary file exists
		if (std::filesystem::exists(filename)) {
			// If the file exists, load the database from the binary file
			database.loadFromBinaryFile(filename);
			cout << "Database loaded successfully from binary file." << endl;
		} else {
			// If the file doesn't exist, create a new database
			cout << "No existing database file found. Creating a new database." << endl;

			// Create a sample database (this part will only run if the file doesn't exist)
			database.createTable("product");
			database.addColumnToTable("product", Column("id", "INTEGER"));
			database.addColumnToTable("product", Column("name", "VARCHAR(50)"));
			database.addColumnToTable("product", Column("price", "INTEGER"));

			// Add initial rows to the table
			database.addRowToTable("product", Row({"11", "Table", "2600"}));
			database.addRowToTable("product", Row({"22", "Chair", "350"}));

			// Save the database to a binary file
			database.saveToBinaryFile(filename);
			cout << "New database created and saved to binary file." << endl;
		}

		bool running = true;
		while (running) {
			displayMenu();
			int choice;
			cout << "Enter your choice: ";
			cin >> choice;

			switch (choice) {
			case 1: {
				// Load the database from the binary file (this will now only load if the user chooses this option)
				database.loadFromBinaryFile(filename);
				cout << "Database loaded successfully." << endl;
				break;
			}
			case 2: {
				// Display the database structure and data
				database.print();
				break;
			}
			case 3: {
				// Save the current database to the binary file
				database.saveToBinaryFile(filename);
				cout << "Database saved successfully." << endl;
				break;
			}
			case 4: {
				// Add a new row to a table
				string tableName;
				cout << "Enter the table name: ";
				cin >> tableName;

				Table* table = database.findTable(tableName);
				if (!table) {
					cout << "Error: Table not found." << endl;
					break;
				}

				vector<string> newRowValues;
				for (const auto& column : table->getColumns()) {
					string value;
					cout << "Enter value for column '" << column.getName() << "': ";
					cin >> value;
					newRowValues.push_back(value);
				}
				database.addRowToTable(tableName, Row(newRowValues));
				cout << "Row added successfully." << endl;
				break;
			}
			case 5:
				running = false;
				break;
			default:
				cout << "Invalid choice, please try again." << endl;
			}
		}

	} catch (const exception& e) {
		cerr << e.what() << endl;
	}

	return 0;
}
