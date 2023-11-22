#include <iostream>
#include <sstream>
using namespace std;



enum class Color {black, red};

template <typename T>
struct RBTNode {

    T data;
    int index;
    RBTNode<T>* parent, * left, * right;
    Color color;

    RBTNode(const T& value, int idx) : data(value), index(idx), parent(nullptr), left(nullptr), right(nullptr), color(Color::red) {}


};


template <typename T>
class RBT {


private:

    RBTNode<T>* root;
    int size;

    void LeftRotate(RBTNode<T>* xNode);

    void RightRotate(RBTNode<T>* yNode);

    void InsertFix(RBTNode<T>* newNode);

    void PreOrder(RBTNode<T>* node);

    void InOrder(RBTNode<T>* node);

    int GetHeight(RBTNode<T>* node);

    void ClearPrivate(RBTNode<T>* node);


public:

    RBT() : root(nullptr), size(0) {}
    
    RBTNode<T>* Search(const T& key);
    
    void Insert(const T& value);

    void ClearTree();
    
    void DisplayTree(int switcher);

    

    ~RBT() {
        ClearTree();
    };

    

};


template<typename T>
RBTNode<T>* RBT<T>::Search(const T& key)
{
    RBTNode<T>* current = root;

    while (current != nullptr) {
        if (key == current->data) {
            return current; // Found the node with the matching key
        }
        else if (key < current->data) {
            current = current->left; // Traverse left subtree
        }
        else {
            current = current->right; // Traverse right subtree
        }
    }

    return nullptr; // Key not found, return nullptr
}

template<typename T>
void RBT<T>::Insert(const T& value)
{

    RBTNode<T>* newNode = new RBTNode<T>(value, size);
    size++;

    RBTNode<T>* current = root;
    RBTNode<T>* parent = nullptr;

    while (current != nullptr) {
        parent = current;
        if (value < current->data) {
            current = current->left;
        }
        else {
            current = current->right;
        }
    }

    newNode->parent = parent;
    if (parent == nullptr) {
        root = newNode;
    }
    else if (value < parent->data) {
        parent->left = newNode;
    }
    else {
        parent->right = newNode;
    }

    InsertFix(newNode);
}


template<typename T>
void RBT<T>::LeftRotate(RBTNode<T>* xNode)
{

    if (xNode == nullptr || xNode->right == nullptr) {
        return; // Cannot perform rotation if xNode or its right child is null
    }

    RBTNode<T>* yNode = xNode->right;
    xNode->right = yNode->left;

    if (yNode->left != nullptr) {
        yNode->left->parent = xNode;
    }

    yNode->parent = xNode->parent;

    if (xNode->parent == nullptr) {
        root = yNode;
    }
    else if (xNode == xNode->parent->left) {
        xNode->parent->left = yNode;
    }
    else {
        xNode->parent->right = yNode;
    }

    yNode->left = xNode;
    xNode->parent = yNode;

}

template<typename T>
void RBT<T>::RightRotate(RBTNode<T>* yNode)
{

    if (yNode == nullptr || yNode->left == nullptr) {
        return; // Cannot perform rotation if yNode or its left child is null
    }

    RBTNode<T>* xNode = yNode->left;
    yNode->left = xNode->right;

    if (xNode->right != nullptr) {
        xNode->right->parent = yNode;
    }

    xNode->parent = yNode->parent;

    if (yNode->parent == nullptr) {
        root = xNode;
    }
    else if (yNode == yNode->parent->left) {
        yNode->parent->left = xNode;
    }
    else {
        yNode->parent->right = xNode;
    }

    xNode->right = yNode;
    yNode->parent = xNode;

}

template<typename T>
void RBT<T>::InsertFix(RBTNode<T>* newNode)
{

    while (newNode->parent != nullptr && newNode->parent->color == Color::red) {
        RBTNode<T>* parent = newNode->parent;
        RBTNode<T>* grandparent = parent->parent;

        if (grandparent == nullptr) {
            break; // If the grandparent is null, exit the loop
        }

        // Case 1: Parent is a left child of the grandparent
        if (parent == grandparent->left) {
            RBTNode<T>* uncle = grandparent->right;

            // Case 1A: Uncle is red
            if (uncle != nullptr && uncle->color == Color::red) {
                parent->color = Color::black;
                uncle->color = Color::black;
                grandparent->color = Color::red;
                newNode = grandparent;
            }
            else {
                // Case 1B: Uncle is black or null
                if (newNode == parent->right) {
                    newNode = parent;
                    LeftRotate(newNode);
                    parent = newNode->parent;
                }

                parent->color = Color::black;
                grandparent->color = Color::red;
                RightRotate(grandparent);
            }
        }
        else {
            // Case 2: Parent is a right child of the grandparent
            RBTNode<T>* uncle = grandparent->left;

            // Case 2A: Uncle is red
            if (uncle != nullptr && uncle->color == Color::red) {
                parent->color = Color::black;
                uncle->color = Color::black;
                grandparent->color = Color::red;
                newNode = grandparent;
            }
            else {
                // Case 2B: Uncle is black or null
                if (newNode == parent->left) {
                    newNode = parent;
                    RightRotate(newNode);
                    parent = newNode->parent;
                }

                parent->color = Color::black;
                grandparent->color = Color::red;
                LeftRotate(grandparent);
            }
        }
    }

    root->color = Color::black; // Ensure the root is black

}


template<typename T>
void RBT<T>::DisplayTree(int switcher)
{

    if (switcher == 1) {
        cout << "Red Black Tree: " << endl;
        cout << "Size: " << size << endl;
        cout << "Height: " << GetHeight(root) << endl;
        PreOrder(root);
    }
    else {
        cout << "Red Black Tree: " << endl;
        cout << "Size: " << size << endl;
        cout << "Height: " << GetHeight(root) << endl;
        InOrder(root);
    }

}


template<typename T>
void RBT<T>::PreOrder(RBTNode<T>* node)
{
    if (node != nullptr) {
        string color_str = (node->color == Color::red) ? "red" : "black";
        string parent_str = "NULL";
        string left_str = "NULL";
        string right_str = "NULL";

        stringstream ss;

        if (node->parent != nullptr) {
            ss << node->parent->index;
            ss >> parent_str;
        }
        if (node->left != nullptr) {
            ss.clear();
            ss << node->left->index;
            ss >> left_str;
        }
        if (node->right != nullptr) {
            ss.clear();
            ss << node->right->index;
            ss >> right_str;
        }

        cout << "(" << node->index << ": [" << color_str << ", p: " << parent_str << ", l: " << left_str << ", r: " << right_str << "] (" << node->data << "))," << endl;

        PreOrder(node->left);
        PreOrder(node->right);
    }
}

template<typename T>
void RBT<T>::InOrder(RBTNode<T>* node)
{
    if (node != nullptr) {
        string color_str = (node->color == Color::red) ? "red" : "black";
        string parent_str = "NULL";
        string left_str = "NULL";
        string right_str = "NULL";

        stringstream ss;

        InOrder(node->left);

        if (node->parent != nullptr) {
            ss << node->parent->index;
            ss >> parent_str;
        }
        if (node->left != nullptr) {
            ss.clear();
            ss << node->left->index;
            ss >> left_str;
        }
        if (node->right != nullptr) {
            ss.clear();
            ss << node->right->index;
            ss >> right_str;
        }

        cout << "(" << node->index << ": [" << color_str << ", p: " << parent_str << ", l: " << left_str << ", r: " << right_str << "] (" << node->data << "))," << endl;

        InOrder(node->right);
    }
}

template<typename T>
int RBT<T>::GetHeight(RBTNode<T>* node)
{
    if (node == nullptr) {
        return 0; // Base case: If node is null, return 0
    }

    int leftHeight = GetHeight(node->left);
    int rightHeight = GetHeight(node->right);

    // Return the maximum of left and right subtree heights, plus 1 (for the current node)
    return 1 + max(leftHeight, rightHeight);
}

template<typename T>
void RBT<T>::ClearPrivate(RBTNode<T>* node)
{
    if (node == nullptr) {
        return;
    }

    ClearPrivate(node->left);
    ClearPrivate(node->right);

    delete node;
}

template<typename T>
void RBT<T>::ClearTree()
{
    ClearPrivate(root);
    root = nullptr; // Reset the root pointer after clearing all nodes
    size = 0; // Reset the size of the tree
}



int main()
{
    
    RBT<int> rbTree;
    RBTNode<int>* node;

    int inputData[] = { 55, 69, 62, 57, 35, 83, 72 ,74 };

    for (int i = 0; i < 8; i++) {
        rbTree.Insert(inputData[i]);
        
    }

    bool work = true;
    int choice;
    while (work) {
        cout << "Choose an option:" << endl;
        cout << "1. Search" << endl;
        cout << "2. Print Preorder" << endl;
        cout << "3. Print Inorder" << endl;
        cout << "4. Clear Tree" << endl;
        cout << "5. Exit" << endl;
        cin >> choice;

        switch (choice) {
        case 1:
        {
            int data;
            cout << "Enter data to search: ";
            cin >> data;
            node = rbTree.Search(data);
            if (node) {
                cout << "Data found in the tree." << endl;
            }
            else {
                cout << "Data not found in the tree." << endl;
            }
        }
        break;

        case 2:
            rbTree.DisplayTree(1); // Print in preorder
            break;
        case 3:
            rbTree.DisplayTree(2); // Print in inorder
            break;
        case 4:
            rbTree.ClearTree();
            cout << "Tree cleared." << endl;
            break;
        case 5:
            work = false;
            cout << "Exiting." << endl;
            break;
        default:
            cout << "Invalid choice. Please try again." << endl;
        }

    }
}


