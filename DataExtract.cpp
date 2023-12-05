#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include "DataExtract.h"
using namespace std;
// Reference: https://java2blog.com/read-csv-file-in-cpp/

vector<vector<string>> DataExtract::extractData(string filename){


    std::ifstream file(filename);

    // Vector to store rows
    std::vector<std::vector<std::string>> rows;

    // Read the file line by line
    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string cell;
        std::vector<std::string> row;

        // Read each cell in the line
        while (std::getline(iss, cell, ',')) {
            // Remove leading and trailing whitespaces
            cell.erase(0, cell.find_first_not_of(" \t\r\n"));
            cell.erase(cell.find_last_not_of(" \t\r\n") + 1);

            row.push_back(cell);
        }

        // Add the row to the vector of rows
        rows.push_back(row);
    }
    // Close the file
    file.close();

    return rows;

}