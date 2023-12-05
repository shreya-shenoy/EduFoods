/*#include "DataExtract.h"
#include "Tree.h"
int main() {
    string filename = "FoodProducts2.csv";
    //DataExtract sheet;
    //vector<vector<string>> data = sheet.extractData(filename);

    std::ifstream file(filename);

    // std::ifstream file(filename);

    if(!file.is_open())
        cout << "CLOSED";
    // Vector to store rows
    std::vector<std::vector<std::string>> data;

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
        data.push_back(row);
    }
    // Close the file
    file.close();



    Tree tree;
    for(int i = 1; i < 50; i++) // upper bound set to 15 (instead of data.size()) for debugging
    {
        if(data.at(i).size() >= 12) // make sure the row size is at least 12, gets rid of data points w/ missing entries
        {
            string date = data.at(i).at(0);
            string product = data.at(i).at(4);
            string category = data.at(i).at(6);
            string symptoms = "";
            for(int j = 10; j < data.at(i).size(); j++){
                if(j != 10 && data.at(i).at(j).front() == '"')
                    break;
                symptoms += data.at(i).at(j) + " ";
            }
            tree.insert(date, product, category, symptoms); // insert into tree
        }
    }
    cout << data.at(0).at(0) << endl; // date
    cout << data.at(0).at(4) << endl; // product name
    cout << data.at(0).at(6) << endl; // product category
    cout << data.at(0).at(10) << endl; // symptoms
    cout << data.at(0).at(11) << endl; // outcome

    cout << tree.getSize() << endl; // print current tree size

    //for(int i = 0; i < data.at(3).size(); i++){
    // cout << data.at(3).at(i) << endl;
    // }

    //cout << data.at(7).at(10) << endl;
    //cout << data.at(16).at(10) << endl;
    // cout << data.at(25).at(10) << endl;
    //cout << data.at(38).at(10) << endl;

    tree.search("2023"); // search for 2023



}*/