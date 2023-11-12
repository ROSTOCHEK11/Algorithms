#include <iostream>
using namespace std;



template <typename T>
class TreeNode {

public:
   
    T data;

    TreeNode* parent;
    TreeNode* right;
    TreeNode* left;
    
    int index;

    TreeNode(const T& value, int idx)
    {
        
        data = value;
        index = idx;
        parent = nullptr;
        right = nullptr;
        left = nullptr;
    
    }

};

template <typename T>
class BST {

public:
    
    TreeNode<T>* root;
    int size;


    BST();

    void AddElement(const T& value);      // a

    TreeNode<T>* Search(const T& value);   // b

    void DeleteNode(TreeNode<T>*& node);    // c

    void ClearTree();                       // f

    int CalculateHeight(TreeNode<T>* node); // g

    void DisplayTree(int switcher);         // h


    ~BST() {
        ClearTree();
    };


private :

    void ClearTreePrivate(TreeNode<T>* node);// f

    void PreOrderToString(TreeNode<T>* node);// d  

    void InOrderToString(TreeNode<T>* node); // e 


};



template<typename T>
BST<T>::BST()
{

    root = nullptr;
    size = 0;

}

template<typename T>
void BST<T>::AddElement(const T& value)
{

    TreeNode<T>* newNode = new TreeNode<T>(value, size);
    TreeNode<T>* parent = nullptr;
    TreeNode<T>* current = root;

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

    size++;

}

template<typename T>
TreeNode<T>* BST<T>::Search(const T& value)
{
    
    TreeNode<T>* current = root;

    while (current != nullptr && current->data != value) {
        if (value < current->data) {
            current = current->left;
        }
        else {
            current = current->right;
        }
    }

    return current;

}

template<typename T>
void BST<T>::DeleteNode(TreeNode<T>*& node)
{

    if (node != nullptr) {
        if (node->left == nullptr) {
            TreeNode<T>* rightChild = node->right;
            if (node->parent != nullptr) {
                if (node == node->parent->left) {
                    node->parent->left = rightChild;
                }
                else {
                    node->parent->right = rightChild;
                }
            }
            else {
                root = rightChild;
            }
            if (rightChild != nullptr) {
                rightChild->parent = node->parent;
            }
            delete node;
            node = rightChild;
        }
        else if (node->right == nullptr) {
            TreeNode<T>* leftChild = node->left;
            if (node->parent != nullptr) {
                if (node == node->parent->left) {
                    node->parent->left = leftChild;
                }
                else {
                    node->parent->right = leftChild;
                }
            }
            else {
                root = leftChild;
            }
            if (leftChild != nullptr) {
                leftChild->parent = node->parent;
            }
            delete node;
            node = leftChild;
        }
        else {
            TreeNode<T>* successor = node->right;
            while (successor->left != nullptr) {
                successor = successor->left;
            }
            node->data = successor->data;
            node->index = successor->index;
            DeleteNode(successor);
        }
        size--;
    }

}

template<typename T>
void BST<T>::ClearTree()
{
    ClearTreePrivate(root);
}

template<typename T>
void BST<T>::PreOrderToString(TreeNode<T>* node)
{

    if (node != nullptr) {
        // Print index and opening parenthesis
        cout << "(" << node->index << ": [p: ";

        // Print parent index or "NULL"
        if (node->parent != nullptr) {
            cout << node->parent->index;
        }
        else {
            cout << "NULL";
        }

        // Print left child index or "NULL"
        cout << ", l: ";
        if (node->left != nullptr) {
            cout << node->left->index;
        }
        else {
            cout << "NULL";
        }

        // Print right child index or "NULL"
        cout << ", r: ";
        if (node->right != nullptr) {
            cout << node->right->index;
        }
        else {
            cout << "NULL";
        }

        // Print data and closing parenthesis
        cout << "], data: " << node->data << "),\n";

        // Recursively traverse left and right subtrees
        PreOrderToString(node->left);
        PreOrderToString(node->right);
    }

}

template<typename T>
void BST<T>::InOrderToString(TreeNode<T>* node)
{

    if (node != nullptr) {
        
        InOrderToString(node->left);

        // Print index and opening parenthesis
        cout << "(" << node->index << ": [p: ";

        // Print parent index or "NULL"
        if (node->parent != nullptr) {
            cout << node->parent->index;
        }
        else {
            cout << "NULL";
        }

        // Print left child index or "NULL"
        cout << ", l: ";
        if (node->left != nullptr) {
            cout << node->left->index;
        }
        else {
            cout << "NULL";
        }

        // Print right child index or "NULL"
        cout << ", r: ";
        if (node->right != nullptr) {
            cout << node->right->index;
        }
        else {
            cout << "NULL";
        }

        // Print data and closing parenthesis
        cout << "], data: " << node->data << "),\n";

        
        InOrderToString(node->right);
    }

}



template<typename T>
void BST<T>::ClearTreePrivate(TreeNode<T>* node)
{
    if (node != nullptr) {
        ClearTreePrivate(node->left);
        ClearTreePrivate(node->right);
        delete node;
    }
    root = nullptr;
    size = 0;
}

template<typename T>
int BST<T>::CalculateHeight(TreeNode<T>* node)
{
    
    if (node == nullptr) {
        return 0;
    }
    else {
        int leftHeight = CalculateHeight(node->left);
        int rightHeight = CalculateHeight(node->right);
        return 1 + max(leftHeight, rightHeight);
    }

}

template<typename T>
void BST<T>::DisplayTree(int switcher)
{

    if (switcher == 1) {

        cout << " Binary search Tree by PreOrder :\n" << endl;
        cout << "Size : " << size << endl;
        //cout << "Height : " << CalculateHeight(root) << endl << endl;
        PreOrderToString(root);

    }
    else 
    {

        cout << " Binary search Tree by InOrder :\n" << endl;
        cout << "Size : " << size << endl;
       // cout << "Height : " << CalculateHeight(root) << endl << endl;
        InOrderToString(root);

    }

}






int main()
{
   
    
    BST<int> bst1;
    TreeNode<int>* node;

    int inputData[] = { 10, 15, 12, 5, 30, 25, 35, 7, -2, 33 };

    for (int i = 0; i < 10; i++) {
        bst1.AddElement(inputData[i]);
    }

    bool work = true;
    int choice;
    while (work) {
        cout << "Choose an option:" << endl;
        cout << "1. Search" << endl;
        cout << "2. Remove" << endl;
        cout << "3. Print Preorder" << endl;
        cout << "4. Print Inorder" << endl;
        cout << "5. Clear Tree" << endl;
        cout << "6. Exit" << endl;
        cin >> choice;

        switch (choice) {
        case 1:
        {
            int data;
            cout << "Enter data to search: ";
            cin >> data;
            node = bst1.Search(data);
            if (node) {
                cout << "Data found in the tree." << endl;
            }
            else {
                cout << "Data not found in the tree." << endl;
            }
        }
        break;
        case 2:
        {
            int data;
            cout << "Enter data to remove: ";
            cin >> data;
            node = bst1.Search(data);
            if (node) {
                cout << "Found the node with data " << node->data << ". Deleting it." << endl;
                bst1.DeleteNode(node);
            }
            else {
                cout << "Data not found in the tree." << endl;
            }
        }
        break;
        case 3:
            bst1.DisplayTree(1); // Print in preorder
            break;
        case 4:
            bst1.DisplayTree(2); // Print in inorder
            break;
        case 5:
            bst1.ClearTree(); break;
        case 6:
            work = false; break;
        default:
            cout << "Invalid choice. Please try again." << endl;
        }
    }


}


