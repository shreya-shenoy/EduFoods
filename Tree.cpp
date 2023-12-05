
#include "Tree.h"
#include <queue>
#include <iostream>
using namespace std;


Tree::Tree(){
    //httplib::Server svr;
    treeSize = 0;
    levelCount = 0;
    count = 0;
    root = nullptr;
}
void Tree::insert(string date, string product, string category, string symptoms){
    if(root == nullptr) // if tree is empty, make a new node for the root
    {
        root = new Node(date, product, category, symptoms);
        treeSize += 1;
        return;
    }
    else{
        if(root->children.size() < 20) // if there are less than 20 children, make this a child
        {
            root->children.push_back(new Node(date, product, category, symptoms));
            treeSize += 1;
            return;
        }
        else // go through all children to see if there is a spot for this node
        {
            queue<Node*> q;
            for(int i = 0; i < root->children.size();i++){
                q.push(root->children.at(i));
            }
            while(!q.empty()){
                Node* front = q.front();
                q.pop();
                if(front->children.size() < 20){
                    front->children.push_back(new Node(date, product, category, symptoms));
                    treeSize += 1;
                    return;
                }
                else{
                    for(int i = 0; i < front->children.size();i++){
                        q.push(front->children.at(i));
                    }
                }
            }

        }
    }

}
vector<Node> Tree::search(string year, string category){
    vector<Node> nodes;
    searchHelper(root, nodes, year, category);
    return nodes;
}
void Tree::searchHelper(Node* root, vector<Node> &nodes, string year, string category){
    if(root != nullptr){
        //cout << root->date << ", " << root->product << ", " << root->category << ", " << root->symptoms << endl;
        //cout << year << endl;
       // cout << category << endl;
        if(root->date.find(year) != string::npos && root->category == category)
        {
            //cout << root->date << ", " << root->product << ", " << root->category << ", " << root->symptoms << endl;
            nodes.push_back(*root);
        }
        for(int i =0; i < root->children.size(); i++)
            searchHelper(root->children.at(i), nodes, year, category);


    }
}
/*void Tree::searchProd(string category){
    searchProdHelper(root, category);
}
void Tree::searchProdHelper(Node* root, string category){
    if(root != nullptr){
        if(root->category == category)
        {
            cout << root->date << ", " << root->product << ", " << root->category << ", " << root->symptoms << endl;
        }
        for(int i =0; i < root->children.size(); i++)
            searchProdHelper(root->children.at(i), category);


    }
}*/
int Tree::getSize(){
    return treeSize;
}
Tree::~Tree(){
    delete root;
}
string Tree::getYear() {
    return year;
}
string Tree::getCategory() {
    return category;
}

void Tree::setYear(string year) {
    this->year = year;
}
void Tree::setCategory(string category) {
    this->category = category;
}

void Tree::outputAll(vector<Node> nodes) {
    for (auto node : nodes) {
        // Dereference the pointer to access the Node object

        // Print the contents of the Node
        std::cout << "Date: " << node.date
                  << ", Product: " << node.product
                  << ", Category: " << node.category
                  << ", Symptoms: " << node.symptoms
                  << std::endl;
    }
}
string Tree::displayOutput(vector<Node> list, int output_option) {
    string s = "";
    if (output_option == 1) {
        for (auto& node : list) {
           /* std::cout << "Categories: " << node.category <<
                      "Dates: " << node.date << "Product Names: " <<
                      node.product << "Symptoms: " << node.symptoms           << "Number of cases: " << list.size() <<                  std::endl;*/
            s += "Dates: " + node.date + " Product Names: " +
                                node.product + " Symptoms: " + node.symptoms;
            s += "\n\n\n\n\n";
        }
    }
    else if (output_option == 2) {
        for (auto& node : list) {
           // std::cout << "Dates: " << node.date << std::endl;
            s += "Dates: " + node.date;
            s += "\n\n\n\n\n";
        }
    }
    else if (output_option == 3) {
        for (auto& node : list) {
            //std::cout << "Product Names: " << node.product <<        std::endl;
            s += "Product Names: " + node.product;
            s += "\n\n\n\n\n";
        }
    }
    else if (output_option == 4) {
        for (auto& node : list) {
           // std::cout << "Symptoms: " << node.symptoms <<            std::endl;
            s += "Symptoms: " + node.symptoms;
            s += "\n\n\n\n\n";
        }
    }
    else {

            //std::cout << "Number of cases: " << list.size() <<
                     // std::endl;
            s += "Number of cases: " + to_string(list.size());
        s += "\n\n\n\n\n";

    }
    return s;
}
