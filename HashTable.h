#pragma once
#include <vector>
#include <list>
#include "Node.h"


class HashTable {
private:

    vector<list<Node*>> hashTable;
    double load_factor;
    double max_load_factor;
    int table_size;
    int curr_size;
    string category;
    string year;
    size_t rehashTable(string& key, int table_size);
public:
    void insert(string date, string product, string category, string symptoms);
    HashTable();
    int get_size();
    vector<list<Node*>> get_hashTable();
    void setYear(string year);
    void setCategory(string category);
    string getYear();
    string getCategory();
    vector<Node> search(string category, string date);
    string displayOutput(vector<Node> list, int output_option);

    ~HashTable();
};

