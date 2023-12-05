#pragma once
#include <string>
#include <vector>

using namespace std;
class Node {
public:
    Node();
    Node(string date, string product, string category, string symptoms);
    vector<Node*> children;
    string date;
    string product;
    string category;
    string symptoms;
    int height = 0;


};