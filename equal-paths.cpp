#ifndef RECCHECK
//if you want to add any #includes like <iostream> you must do them here (before the next endif)

#endif

#include "equal-paths.h"
using namespace std;


// You may add any prototypes of helper functions here


bool equalPaths(Node * root)
{
    // Add your code below

    // base case 
    if (root == NULL){
        return true; 
    }

    // recursive case

    if ( root ){
        if (root->left && root->right) {
        // still have children, keep recursing 
        return equalPaths(root->left) && equalPaths(root->right); 
        }

        else if (root->left == NULL && root->right == NULL ) {
            return true;
        }

        else {
            return false; 
        }
    }
}

