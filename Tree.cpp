
#include "Tree.h"
#include <queue>
#include <iostream>
using namespace std;


Tree::Tree(){
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
            queue<Node*> q; // create a queue to store the nodes of the tree
            for(int i = 0; i < root->children.size();i++){
                q.push(root->children.at(i)); // push all of the children to the queue
            }
            while(!q.empty())
            {
                Node* front = q.front();
                q.pop();
                if(front->children.size() < 20) // if this node has a space in its vector of children, add new node
                {
                    front->children.push_back(new Node(date, product, category, symptoms));
                    treeSize += 1;
                    return;
                }
                else // add all of this node's children to the queue
                {
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
    searchHelper(root, nodes, year, category); // call searchHelper
    return nodes;
}
void Tree::searchHelper(Node* root, vector<Node> &nodes, string year, string category){
    if(root != nullptr){

        if(root->date.find(year) != string::npos && root->category == category) // check if it matches the year and category
        {
            nodes.push_back(*root);
        }
        for(int i =0; i < root->children.size(); i++) // call searchHelper on each child
            searchHelper(root->children.at(i), nodes, year, category);


    }
}
// getter and setter functions
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


string Tree::displayOutput(vector<Node> list, int output_option) {
    string s = "";
    if (output_option == 1) // output option 1: print all information of the node
    {
        for (auto& node : list) {
            s += "Dates: " + node.date + " Product Names: " +
                                node.product + " Symptoms: " + node.symptoms;
            s += "\n\n\n\n\n";
        }
    }
    else if (output_option == 2)  // output option 2: print each node's date
    {
        for (auto& node : list) {
            s += "Dates: " + node.date;
            s += "\n\n\n\n\n";
        }
    }
    else if (output_option == 3) // output option 3: print each node's product name
    {
        for (auto& node : list) {
            s += "Product Names: " + node.product;
            s += "\n\n\n\n\n";
        }
    }
    else if (output_option == 4) // print each node's symptoms
    {
        for (auto& node : list) {

            s += "Symptoms: " + node.symptoms;
            s += "\n\n\n\n\n";
        }
    }
    else // print total number of cases
    {

        s += "Number of cases: " + to_string(list.size());
        s += "\n\n\n\n\n";

    }
    return s;
}
