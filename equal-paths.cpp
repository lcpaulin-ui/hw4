#ifndef RECCHECK
//if you want to add any #includes like <iostream> you must do them here (before the next endif)

#endif

#include "equal-paths.h"
using namespace std;


// You may add any prototypes of helper functions here

// idea: use a helper function to determine the depth of any leaf
int depth (Node* root){
    if (root == NULL){
        return 0;
    }

    if (root->left == NULL && root->right == NULL){
        // found leaf node 
        return 1; 
    }

    if (root->left){
        return 1 + depth(root->left);
    }

    else if (root->right){
        return 1 + depth(root->right);
    }

    return 1;
}

bool same_path(Node* root, int ref, int curr) {
    if (root == NULL){
        return true; 
    }

    if (root->left == NULL && root->right == NULL){
        return (ref == curr + 1); 
    }

    return same_path(root->left, ref, curr +1 ) && same_path(root->right, ref, curr + 1); 
}


bool equalPaths(Node * root)
{
    // Add your code below

    // base case 
    if (root == NULL){
        return true; 
    }

    int ref = depth(root); 
    return same_path(root, ref, 0); 

    // recursive case


}

