#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>
#include <fstream>

using namespace std;

#include "compiler.h"
#include "database.h"

void displayMenu() {
    cout << "Database Operations Menu:" << endl;
    cout << "1. Load Database" << endl;
    cout << "2. Display Database" << endl;
    cout << "3. Save Database" << endl;
    cout << "4. Exit" << endl;
}

int main(int argc, char** argv) {
    try {
        Database database;
        Compiler compiler(database);
        string filename = "sample_database.dat";

        // Optionally: Create a sample database (only once, if not loading)
        database.createTable("product");
        database.addColumnToTable("product", Column("id", "INTEGER"));
        database.addColumnToTable("product", Column("name", "VARCHAR(50)"));
        database.addColumnToTable("product", Column("price", "INTEGER"));

        // Add some rows to the table
        database.addRowToTable("product", Row({"11", "Table", "2600"}));
        database.addRowToTable("product", Row({"22", "Chair", "350"}));

        // Save the database to a binary file
        database.saveToBinaryFile(filename);

        bool running = true;
        while (running) {
            displayMenu();
            int choice;
            cout << "Enter your choice: ";
            cin >> choice;

            switch (choice) {
                case 1: {
                    // Load the database from the binary file
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
                case 4:
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
