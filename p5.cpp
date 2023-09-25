#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>


using namespace std;

struct Node {
    int key;
    struct Node *left, *right;
    Node(int keyEntered) {
        key = keyEntered;
    }
};

int getIndex(vector <int> nums, int num) {
    for (long unsigned int x = 0; x < nums.size(); x++) {
        if (nums.at(x) == num) {
            return x;
        }
    }
    return -1;//element not found
}

int firstToAppear(vector <int> levelOrder, vector <int> inOrder) {
    for (long unsigned int x = 0; x < levelOrder.size(); x++) {
        for (long unsigned int y = 0; y < inOrder.size(); y++) {
            if (levelOrder.at(x) == inOrder.at(y) && levelOrder.at(x) != -1) {
                return levelOrder.at(x);
            }
        }
    }
    return -1;//no elements in the arrays match
}

void buildTree(vector <int> inOrder, vector <int> levelOrder, Node *root) {
    int rootKey = root->key;
    levelOrder.at(getIndex(levelOrder, rootKey)) = -1;//extracts the root from the level order traversal
    vector <int> leftNums;
    vector <int> rightNums;
    long unsigned int rootIndex = getIndex(inOrder, root->key);
    for (long unsigned int x = 0; x < inOrder.size(); x++) {
        if (x < rootIndex) {
            leftNums.push_back(inOrder.at(x));
        }
        else if (x > rootIndex) {
            rightNums.push_back(inOrder.at(x));
        }
    }

    bool recursed = false;

    if (leftNums.size() > 0) {
        int leftChildKey = firstToAppear(levelOrder, leftNums);

        Node *leftChild = new Node(leftChildKey);
        root->left = leftChild;

        //Recursive call to buildTree
        recursed = true;
        buildTree(leftNums, levelOrder, leftChild);
    }
    
    if (rightNums.size() > 0) {
        int rightChildKey = firstToAppear(levelOrder, rightNums);

        Node *rightChild = new Node(rightChildKey);
        root->right = rightChild;

        //Recursive call to buildTree
        recursed = true;
        buildTree(rightNums, levelOrder, rightChild);
    }

    if (!recursed) {
        root->right = nullptr;
        root->left = nullptr;
        return;
    } 

}

int main(int argc, char* argv[]) {
    //Get file input in vector form
    string inOrderFile = argv[1];
    string levelOrderFile = argv[2];
    string encodedTextFile = argv[3];
    ifstream inOrderifs(inOrderFile);
    ifstream levelOrderifs(levelOrderFile);
    ifstream encodedTextifs(encodedTextFile);
    vector <int> levelOrder;
    vector <int> inOrder;
    vector <char> encodedText;

    int curr;
    while (inOrderifs >> curr) {
        inOrder.push_back(curr);
    }
    while (levelOrderifs >> curr) {
        levelOrder.push_back(curr);
    }
    char currChar;
    while (encodedTextifs >> currChar) {
        encodedText.push_back(currChar);
    }
    //Make first root
    //Make initial call to buildTree
    Node *root = new Node(levelOrder.at(0));
    buildTree(inOrder, levelOrder, root);

    //Decode and print text
    Node *currNode = root;
    while (encodedText.size() > 0) {
        if (encodedText.at(0) == '1') {
            currNode = currNode->right;
        }
        else {
            currNode = currNode->left;
        }
        encodedText.erase(encodedText.begin());
        
        if ((currNode->left == nullptr && currNode->right == nullptr)) {
        cout << char(currNode->key);
        currNode = root;
    }
    }
}