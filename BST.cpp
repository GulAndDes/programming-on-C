#include <iostream>
using namespace std;


struct NodeBST {
    int value;
    NodeBST* left = nullptr;
    NodeBST* right = nullptr;
    int height = 1;

    NodeBST(int value) {
        this->value = value;
    }
};



NodeBST* addNodeBST(NodeBST* elem, int value) {
    if (!elem) {
        elem = new NodeBST(value);
    } 
    else if (value < elem->value) {
        elem->left = addNodeBST(elem->left, value);
    } 
    else if (value > elem->value) {
        elem->right = addNodeBST(elem->right, value);
    }

    int left_height = (elem->left) ? elem->left->height : 0;
    int right_height = (elem->right) ? elem->right->height : 0;
    elem->height = 1 + (left_height > right_height ? left_height : right_height);
    return elem;
}

int height(NodeBST* elem) {
    return elem ? elem->height : 0;
}

int balanceFactor(NodeBST* elem) {
    return height(elem->left) - height(elem->right);
}

NodeBST* right_turn(NodeBST* elem) {
    NodeBST* left_child = elem->left;
    elem->left = left_child->right;
    left_child->right = elem;
    return left_child;
}

NodeBST* left_turn(NodeBST* elem) {
    NodeBST* right_child = elem->right;
    elem->right = right_child->left;
    right_child->left = elem;
    return right_child;
}

NodeBST* right_big_turn(NodeBST* elem) {
    NodeBST* new_left_child = left_turn(elem->left);
    elem->left = new_left_child;

    return right_turn(elem);
}

NodeBST* left_big_turn(NodeBST* elem) {
    elem->right = right_turn(elem->right);
    return left_turn(elem);
}

NodeBST* _balance(NodeBST* root) {
    int bf = balanceFactor(root);
    if (bf < -1) {
        if (balanceFactor(root->right) < 0) {
            return left_turn(root);
        } else {
            return left_big_turn(root);
        }
    } else if (bf > 1) {
        if (balanceFactor(root->left) > 0) {
            return right_turn(root);
        } else {
            return right_big_turn(root);
        }
    }

    return root;
}

NodeBST* insert(NodeBST* root, int value) {
    root = addNodeBST(root, value);
    return _balance(root);
}

void printNodeBST(NodeBST *root){
    if (root != nullptr){
        cout<<" v = "<< root->value<<"\t l = "<< root->left;
        cout<<" r = "<<root->right<<endl;
        cout<<"                "<< endl;
    }
}


void printLeftRootRight(NodeBST *root){
        if (root == nullptr) return;
        printLeftRootRight(root->left);
        printNodeBST(root);
        printLeftRootRight(root->right);
} 


int main() {
    struct NodeBST *root = nullptr; 
    root = addNodeBST(root, 5);
    root = addNodeBST(root, 4);
    root = addNodeBST(root, 3);
    root = addNodeBST(root, 6);
    root = addNodeBST(root, 8);
    root = addNodeBST(root, 1);
    root = addNodeBST(root, 10);
    root = addNodeBST(root, 11);
    root = addNodeBST(root, 12);

    cout<<balanceFactor(root)<< endl;
    printLeftRootRight(root);

    root = _balance(root);
    cout<<"BALANCE TREE"<<endl;
    printLeftRootRight(root);
}