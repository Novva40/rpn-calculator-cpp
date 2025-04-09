#include <iostream>
#include <fstream>
#include <sstream>
#include <cctype>
#include <string>
using namespace std;

// Node structure for AVL Tree
struct AVLNode {
    string word;
    int count;  // Frequency of the word
    AVLNode* left;
    AVLNode* right;
    int height;

    AVLNode(string w, int c = 1) : word(w), count(c), left(nullptr), right(nullptr), height(1) {}
};

// AVL Tree class
class AVLTree {
private:
    AVLNode* root;

    // Helper function to get the height of a node
    int height(AVLNode* node) const {
        return node ? node->height : 0;
    }

    // Helper function to calculate the balance factor
    int getBalanceFactor(AVLNode* node) const {
        return node ? height(node->left) - height(node->right) : 0;
    }

    // Right rotation
    AVLNode* rightRotate(AVLNode* y) {
        AVLNode* x = y->left;
        AVLNode* T2 = x->right;

        // Perform rotation
        x->right = y;
        y->left = T2;

        // Update heights
        y->height = max(height(y->left), height(y->right)) + 1;
        x->height = max(height(x->left), height(x->right)) + 1;

        return x;
    }

    // Left rotation
    AVLNode* leftRotate(AVLNode* x) {
        AVLNode* y = x->right;
        AVLNode* T2 = y->left;

        // Perform rotation
        y->left = x;
        x->right = T2;

        // Update heights
        x->height = max(height(x->left), height(x->right)) + 1;
        y->height = max(height(y->left), height(y->right)) + 1;

        return y;
    }

    // Insert helper
    AVLNode* insert(AVLNode* node, const string& word) {
        if (!node)
            return new AVLNode(word);

        if (word < node->word) {
            node->left = insert(node->left, word);
        } else if (word > node->word) {
            node->right = insert(node->right, word);
        } else {
            // Word already exists, increment count
            node->count++;
            return node;
        }

        // Update height
        node->height = max(height(node->left), height(node->right)) + 1;

        // Balance the node
        int balance = getBalanceFactor(node);

        // Left Left Case
        if (balance > 1 && word < node->left->word)
            return rightRotate(node);

        // Right Right Case
        if (balance < -1 && word > node->right->word)
            return leftRotate(node);

        // Left Right Case
        if (balance > 1 && word > node->left->word) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }

        // Right Left Case
        if (balance < -1 && word < node->right->word) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        return node;
    }

    // In-order traversal to print the tree
    void printTree(AVLNode* node) const {
        if (node) {
            printTree(node->left);
            cout << node->word << " - " << node->count << endl;
            printTree(node->right);
        }
    }

public:
    AVLTree() : root(nullptr) {}

    void insert(const string& word) {
        root = insert(root, word);
    }

    void printTree() const {
        printTree(root);
    }
};

// WordCount class
class WordCount {
private:
    AVLTree tree;

    // Helper function to clean and split words
    void processLine(const string& line) {
        string word;
        for (char c : line) {
            if (isalnum(c)) {
                word += tolower(c);
            } else if (!word.empty()) {
                tree.insert(word);
                word.clear();
            }
        }
        if (!word.empty())
            tree.insert(word);
    }

public:
    void readFile(const string& fileName) {
        ifstream file(fileName);
        if (!file.is_open()) {
            cerr << "Error opening file: " << fileName << endl;
            return;
        }

        string line;
        while (getline(file, line)) {
            processLine(line);
        }

        file.close();
    }

    void printWordCounts() const {
        tree.printTree();
    }
};

int main() {
    WordCount wc;

    // Read the file
    wc.readFile("in/Users/novva/Downloads/CSIS-211-3443/Project 11/Project 11/WordCountTest.txtput.txt");

    // Print word counts
    cout << "Word Counts:" << endl;
    wc.printWordCounts();

    return 0;
}
