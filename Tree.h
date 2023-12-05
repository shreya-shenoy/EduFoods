
#include "Node.h"
#include <string>

using namespace std;

class Tree{
private:
    int treeSize;
    int levelCount;
    int count;
    Node* root = nullptr;
    string year;
    string category;
    void searchHelper(Node* root, vector<Node> &nodes, string year, string category);
    void searchProdHelper(Node* root, string category);


public:
    Tree();
    ~Tree();
    void insert(string date, string product, string category, string symptoms);
    vector<Node> search(string year, string category);
    int getSize();
    int getLevelCount();
    void setYear(string year);
    void setCategory(string category);
    string getYear();
    string getCategory();
    void outputAll(vector<Node> nodes);
    string displayOutput(vector<Node> list, int output_option);



};