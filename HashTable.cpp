#include <list>
#include <algorithm>
#include <iostream>
#include "HashTable.h"

using namespace std;

HashTable::HashTable(){
    this->max_load_factor = 1.5;
    this->table_size = 5;
    this->load_factor = 0;
    this->curr_size = 0;
    hashTable.resize(table_size);
}


int HashTable::get_size(){
    return curr_size;
}

vector<list<Node*>> HashTable::get_hashTable(){
    return hashTable;
}

size_t HashTable::rehashTable(string& key, int table_size){
    size_t hash = 0;
    for (char ch : key){
        hash = hash * 31 + ch;
    }
    return (hash % table_size + table_size) % table_size;
}


void HashTable::insert(string date, string product, string category, string symptoms){

    int index = rehashTable(category, table_size); //key will be the product name


    list<Node*> bucket = hashTable[index];



    if (load_factor == max_load_factor) {
        table_size *= 2;

        //vector<list<Node*>> newHashTable; //resize a new table
        //newHashTable.resize(table_size);

        hashTable.resize(table_size);

        for (auto& row : hashTable) {
            row.clear(); // clear rows to avoid duplicates after rehashing
        }

        for (auto& row : hashTable) {
            for (auto& entry : row) {
                size_t new_index = rehashTable(entry->category, table_size);
                hashTable[new_index].push_back(entry);

            }
        } //end if for loop

        //hashTable=newHashTable;



    } //end of if statement

    hashTable[index].push_back(new Node(date, product, category, symptoms));
    curr_size++;
    load_factor = double(curr_size) / double(table_size);


}
vector<Node> HashTable::search(string category, string date){
    vector<Node> products;
    int index = rehashTable(category, table_size);
    auto bucket = hashTable[index];
    for (const auto& nodePtr : bucket) {
        // Dereference the pointer to access the Node object
        const Node& node = *nodePtr;
        if(node.date.find(date) != string::npos && node.category == category){
            products.push_back(node);
        }
    }
    return products;

}


HashTable::~HashTable() {
    for (auto row : hashTable) {
        for (auto entry : row) {
            delete entry;
        }
        row.clear(); // clear entire row
    }
}
string HashTable::getYear() {
    return year;
}
string HashTable::getCategory() {
    return category;
}

void HashTable::setYear(string year) {
    this->year = year;
}
void HashTable::setCategory(string category) {
    this->category = category;
}
string HashTable::displayOutput(vector<Node> list, int output_option) {
    string s = "";
    if (output_option == 1) {
        for (auto& node : list) {
            s += "Dates: " + node.date + " Product Names: " +
                 node.product + " Symptoms: " + node.symptoms;
            s += "\n\n\n\n\n";
        }
    }
    else if (output_option == 2) {
        for (auto& node : list) {
            s += "Dates: " + node.date;
            s += "\n\n\n\n\n";
        }
    }
    else if (output_option == 3) {
        for (auto& node : list) {
            s += "Product Names: " + node.product;
            s += "\n\n\n\n\n";
        }
    }
    else if (output_option == 4) {
        for (auto& node : list) {
            s += "Symptoms: " + node.symptoms;
            s += "\n\n\n\n\n";
        }
    }
    else {

            s += "Number of cases: " + to_string(list.size());
        s += "\n\n\n\n\n";


    }
    return s;
}

