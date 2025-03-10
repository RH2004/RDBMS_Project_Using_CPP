﻿# RDBMS_Project_Using_CPP
# Database Management System

## Overview
This project is a lightweight, in-memory **Database Management System (DBMS)** implemented in C++. It allows users to create tables, define columns, insert rows, and perform various operations such as saving and loading the database from a binary file. The system also features a **compiler** that processes and executes queries.

## Features
- **Table Management**: Create and manage multiple tables.
- **Column Definition**: Define columns with specific data types.
- **Row Insertion**: Insert rows with values matching the defined schema.
- **Serialization**: Save and load database data using binary files.
- **Query Compilation**: Process SQL-like queries via a lexer and parser.
- **Error Handling**: Prevents invalid operations such as duplicate table names or mismatched column counts.

## Project Structure
```
├── src/
│   ├── database.h/.cpp       # Manages tables and serialization
│   ├── table.h/.cpp          # Represents a table in the database
│   ├── column.h/.cpp         # Represents columns within tables
│   ├── row.h/.cpp            # Represents rows of data
│   ├── compiler.h/.cpp       # Processes and compiles queries
│   ├── parser.h/.cpp         # Parses SQL-like queries
│   ├── lexer.h/.cpp          # Tokenizes input queries
│   ├── main.cpp              # Entry point of the program
├── data/
│   ├── database.bin          # Binary file for saved database state
├── README.md                 # Project documentation
├── Makefile                  # Compilation script
```

## Installation
### Prerequisites
- **C++ Compiler (g++ or MSVC)**
- **Make (optional, for easy compilation)**

### Compilation
To compile the project, navigate to the root directory and run:
```sh
make
```
Alternatively, you can manually compile using:
```sh
g++ -o dbms main.cpp database.cpp table.cpp column.cpp row.cpp compiler.cpp parser.cpp lexer.cpp
```

## Usage
### Running the Program
Execute the compiled binary:
```sh
./dbms
```

### Sample Operations
#### Creating a Table
```cpp
db.createTable("Students");
```
#### Adding Columns
```cpp
Column nameColumn("Name", "string");
Column ageColumn("Age", "int");
db.addColumnToTable("Students", nameColumn);
db.addColumnToTable("Students", ageColumn);
```
#### Adding Rows
```cpp
Row row1({"Alice", "21"});
db.addRowToTable("Students", row1);
```
#### Saving & Loading Database
```cpp
db.saveToBinaryFile("data/database.bin");
db.loadFromBinaryFile("data/database.bin");
```

## Error Handling
- **Duplicate Tables**: Throws an error if a table with the same name exists.
- **Missing Tables**: Throws an error if a non-existent table is accessed.
- **Column Count Mismatch**: Ensures rows match table schema before insertion.

## Future Enhancements
- **Query Execution Engine**: Implement an execution engine for queries.
- **Indexing**: Add indexing for faster lookups.
- **SQL Parser**: Extend the parser to handle complex SQL queries.
- **Persistence Improvements**: Store data in a structured format like JSON or SQL.

## Contributors
- **Reda HEDDAD**  


---
Feel free to contribute and improve the system!

