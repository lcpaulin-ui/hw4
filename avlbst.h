#ifndef AVLBST_H
#define AVLBST_H

#include <iostream>
#include <exception>
#include <cstdlib>
#include <cstdint>
#include <algorithm>
#include "bst.h"

struct KeyError { };

/**
* A special kind of node for an AVL tree, which adds the balance as a data member, plus
* other additional helper functions. You do NOT need to implement any functionality or
* add additional data members or helper functions.
*/
template <typename Key, typename Value>
class AVLNode : public Node<Key, Value>
{
public:
    // Constructor/destructor.
    AVLNode(const Key& key, const Value& value, AVLNode<Key, Value>* parent);
    virtual ~AVLNode();

    // Getter/setter for the node's height.
    int8_t getBalance () const;
    void setBalance (int8_t balance);
    void updateBalance(int8_t diff);

    // Getters for parent, left, and right. These need to be redefined since they
    // return pointers to AVLNodes - not plain Nodes. See the Node class in bst.h
    // for more information.
    virtual AVLNode<Key, Value>* getParent() const override;
    virtual AVLNode<Key, Value>* getLeft() const override;
    virtual AVLNode<Key, Value>* getRight() const override;

protected:
    int8_t balance_;    // effectively a signed char
};

/*
  -------------------------------------------------
  Begin implementations for the AVLNode class.
  -------------------------------------------------
*/

/**
* An explicit constructor to initialize the elements by calling the base class constructor
*/
template<class Key, class Value>
AVLNode<Key, Value>::AVLNode(const Key& key, const Value& value, AVLNode<Key, Value> *parent) :
    Node<Key, Value>(key, value, parent), balance_(0)
{

}

/**
* A destructor which does nothing.
*/
template<class Key, class Value>
AVLNode<Key, Value>::~AVLNode()
{

}

/**
* A getter for the balance of a AVLNode.
*/
template<class Key, class Value>
int8_t AVLNode<Key, Value>::getBalance() const
{
    return balance_;
}

/**
* A setter for the balance of a AVLNode.
*/
template<class Key, class Value>
void AVLNode<Key, Value>::setBalance(int8_t balance)
{
    balance_ = balance;
}

/**
* Adds diff to the balance of a AVLNode.
*/
template<class Key, class Value>
void AVLNode<Key, Value>::updateBalance(int8_t diff)
{
    balance_ += diff;
}

/**
* An overridden function for getting the parent since a static_cast is necessary to make sure
* that our node is a AVLNode.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getParent() const
{
    return static_cast<AVLNode<Key, Value>*>(this->parent_);
}

/**
* Overridden for the same reasons as above.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getLeft() const
{
    return static_cast<AVLNode<Key, Value>*>(this->left_);
}

/**
* Overridden for the same reasons as above.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getRight() const
{
    return static_cast<AVLNode<Key, Value>*>(this->right_);
}


/*
  -----------------------------------------------
  End implementations for the AVLNode class.
  -----------------------------------------------
*/


template <class Key, class Value>
class AVLTree : public BinarySearchTree<Key, Value>
{
public:
    virtual void insert (const std::pair<const Key, Value> &new_item); // TODO
    virtual void remove(const Key& key);  // TODO
protected:
    virtual void nodeSwap( AVLNode<Key,Value>* n1, AVLNode<Key,Value>* n2);

    // Add helper functions here
    // insert-fix
    // remove-fix 
    void rotateLeft(AVLNode<Key, Value>* ptr); 
    void rotateRight(AVLNode<Key, Value>* ptr);
    void insertFix(AVLNode<Key, Value>* parent, AVLNode<Key, Value>* child); 
    void insert_help(const std::pair<const Key, Value> &keyValuepair, AVLNode<Key, Value>* ptr, AVLNode<Key, Value>* parent); 
    void removeFix(AVLNode<Key, Value>* node, int8_t diff); 

};

template<class Key, class Value>
void AVLTree<Key, Value>::rotateLeft(AVLNode<Key, Value>* ptr){ 

    // a - b - c all to the left 
    // ptr =  a 
    // promote left child to its place 
    AVLNode<Key, Value>* right_c = ptr->getRight(); 
   AVLNode<Key, Value>* ptr_parent = ptr->getParent(); 
   AVLNode<Key, Value>* left_sub_lef = right_c->getLeft(); 

   ptr->setRight(left_sub_lef); 
   // check if its not null, if its not, set ptr as its parent
   if (left_sub_lef){
    left_sub_lef->setParent(ptr); 
   }

   // set left sub tree as new; root's right subtree
   right_c->setLeft(ptr); 
   ptr->setParent(right_c);

   if (ptr_parent == NULL ) // THIS means that the parent was the root, just set the left_c to root now
  { this->root_ = right_c; 
   right_c->setParent(NULL); // safety check 
    }

    else if (ptr_parent->getLeft() == ptr) { // ptr was a left child 
        // this means that 
        ptr_parent->setLeft(right_c); 
        right_c->setParent(ptr_parent); 
    }

    else { // ptr was a RIGHT child 
        // this means that 
        ptr_parent->setRight(right_c); 
        right_c->setParent(ptr_parent); 
    }

    /// REELINKING NODES HERE 

}

template<class Key, class Value>
void AVLTree<Key, Value>::rotateRight(AVLNode<Key, Value>* ptr){
    
   // take left child, amke it parent, make og parent its right child 
   // right subtree of left child becomes left subtree of new rogjht child 

   AVLNode<Key, Value>* left_c = ptr->getLeft(); 
   AVLNode<Key, Value>* ptr_parent = ptr->getParent(); 
   AVLNode<Key, Value>* right_sub_lef = left_c->getRight(); 

   ptr->setLeft(right_sub_lef); 
   // check if its not null, if its not, set ptr as its parent
   if (right_sub_lef){
    right_sub_lef->setParent(ptr); 
   }

   // set left sub tree as new; root's right subtree
   left_c->setRight(ptr); 
   ptr->setParent(left_c);

   if (ptr_parent == NULL ) // THIS means that the parent was the root, just set the left_c to root now
  { this->root_ = left_c; 
   left_c->setParent(NULL); // safety check 
    }

    else if (ptr_parent->getLeft() == ptr) { // ptr was a left child 
        // this means that 
        ptr_parent->setLeft(left_c); 
        left_c->setParent(ptr_parent); 
    }

    else { // ptr was a left child 
        // this means that 
        ptr_parent->setRight(left_c); 
        left_c->setParent(ptr_parent); 
    }
}

template<class Key, class Value>
void AVLTree<Key, Value>::insertFix(AVLNode<Key, Value>* parent, AVLNode<Key, Value>* child) {

   
    if (parent == NULL || parent->getParent() == NULL ) {
        return; // no way to be inbalanced w just two 
    }

    AVLNode<Key, Value>* grandp = parent->getParent(); 

    // left child case, parent is left child of gp 
    if (parent == grandp->getLeft() ){
        grandp->updateBalance(-1);
        int8_t g_bal = grandp->getBalance(); 

        if (g_bal == 0) {return; }
        else if (g_bal == -1 ){ insertFix(grandp, parent); }
        else if (g_bal == -2){
            // zig zig or zig zag???
            // zig zig: child is ALSO left child 
            if (child == parent->getLeft()){
                rotateRight(grandp);
                parent->setBalance(0);
                grandp->setBalance(0); 
            }
            
            // zig zag: child is right child 
            else {
                rotateLeft(parent);
                rotateRight(grandp); 

                if (child->getBalance() == -1 ) {
                    child->setBalance(0);
                    parent->setBalance(0);
                    grandp->setBalance(1);
                 }

                 else if (child->getBalance() == 0 ) {
                    child->setBalance(0);
                    parent->setBalance(0);
                    grandp->setBalance(0);
                 }

                    else  {
                  
                        child->setBalance(0);
                        parent->setBalance(-1);
                        grandp->setBalance(0);
                    }
                }
            }
        }

        // right child case 
        else if (parent == grandp->getRight() ){
            grandp->updateBalance(1);
            int8_t g_bal = grandp->getBalance(); 
    
            if (g_bal == 0) {return; }
            else if (g_bal == 1 ){ insertFix(grandp, parent); }
            else if (g_bal == 2){
                // zig zig or zig zag???
                // zig zig: child is ALSO left child 
                if (child == parent->getRight()){
                    rotateLeft(grandp);
                    parent->setBalance(0);
                    grandp->setBalance(0); 
                }
                
                // zig zag: child is right child 
                else {
                    rotateRight(parent);
                    rotateLeft(grandp); 
    
                    if (child->getBalance() == 1 ) {
                        child->setBalance(0);
                        parent->setBalance(0);
                        grandp->setBalance(-1);
                     }
    
                     else if (child->getBalance() == 0 ) {
                        child->setBalance(0);
                        parent->setBalance(0);
                        grandp->setBalance(0);
                     }
    
                        else  {
                      
                            child->setBalance(0);
                            parent->setBalance(1);
                            grandp->setBalance(0);
                        }
                    }
                }
            }


}


// helper function to find where i am going to on the binary tree
// will look for where to insert the new node 
// use dfs logic / recursion 

template<class Key, class Value>
void AVLTree<Key, Value>::insert_help(const std::pair<const Key, Value> &keyValuepair, AVLNode<Key, Value>* ptr, AVLNode<Key, Value>* parent)
{

    if (ptr == NULL){
        AVLNode<Key, Value>* n_ptr = new AVLNode<Key, Value>(keyValuepair.first, keyValuepair.second, parent); 
        n_ptr->setBalance(0); 
        // return; 

        // if has a parent

    if (parent != NULL){
        // left child case 
        if (keyValuepair.first < parent->getKey() ){
            parent->setLeft(n_ptr); 
        }
        else {
            parent->setRight(n_ptr);
        }
    // right child case 
    }
    return; 
}

    else if (keyValuepair.first < ptr->getKey() )  { // traverse left subtree 
        AVLNode<Key, Value>* l_ptr = ptr->getLeft(); 
         insert_help(keyValuepair, l_ptr, ptr);  // continue recursion 
         //ptr->setLeft(l_ptr); 
        } 

    else {
        AVLNode<Key, Value>* r_ptr = ptr->getRight(); 
        insert_help(keyValuepair, r_ptr, ptr);  
        //ptr->setRight(r_ptr); 
     }
}

/*
 * Recall: If key is already in the tree, you should 
 * overwrite the current value with the updated value.
 */

 // guide: class slides 
template<class Key, class Value>
void AVLTree<Key, Value>::insert(const std::pair<const Key, Value> &new_item)
{
    // TODO

    // if tree is null, set new item as root and finish
    if (this->root_ == NULL){
        this->root_ = new AVLNode<Key, Value>(new_item.first, new_item.second, NULL); 

        //     return static_cast<AVLNode<Key, Value>*>(this->right_);
        static_cast<AVLNode<Key, Value>*>(this->root_)->setBalance(0); 
        //this->root_->setBalance(0);
        return; 


    }

    Node<Key,Value>* find_ptr = this->internalFind(new_item.first); 
    AVLNode<Key, Value>* find = static_cast<AVLNode<Key, Value>*>(find_ptr); 

    // static_cast<AVLNode<Key, Value>*>(find_ptr) = internalFind(new_item.first);

    // static_cast<AVLNode<Key, Value>*>(this->find) = internalFind(new_item.first);
    //AVLNode<Key, Value>* find = internalFind(new_item.first); 
    // already on tree case 
    // dont have to change anything 

    if (find != NULL){ 
        find->setValue(new_item.second);
        return;  
    }
    
    // 

    else { // tree is not empty AND key was not alr in tree 
            // static_cast<AVLNode<Key, Value>*>(find_ptr) = internalFind(new_item.first);
        AVLNode<Key, Value>* av_ptr = static_cast<AVLNode<Key, Value>*>(this->root_); 
        // av_ptr = static_cast<AVLNode<Key, Value>*>(this->root_); 
        insert_help(new_item, av_ptr, NULL); // use dfs from bst implementation 
        //this->root_ = av_ptr; 

        // find where i inserted 
        Node<Key,Value>* find_ptr = this->internalFind(new_item.first); 
        AVLNode<Key, Value>* find = static_cast<AVLNode<Key, Value>*>(find_ptr); 


        AVLNode<Key, Value>* parent = find->getParent(); // i'm assured to have a parent here 
        //int8_t b_p = parent->getBalance(); 
 
        if (parent->getBalance() == - 1) { parent->setBalance(0); }
        else if (parent->getBalance() == 1) {parent->setBalance(0); } 
        else // parent balance was 0 
        { 
            // left child 
            if (find == parent->getLeft()) { parent->updateBalance(-1); }
            // right child 
            else if (find == parent->getRight() ){ parent->updateBalance(1); }
            insertFix(parent, find);
        }

    }
}

template<class Key, class Value>
void AVLTree<Key, Value>::removeFix(AVLNode<Key, Value>* node, int8_t diff){

    if (node == NULL) {return; }
    int8_t next_diff = 0; 
    int8_t node_balance = node->getBalance(); 
    // get next recurisve calls argument 
    AVLNode<Key, Value>* parent = node->getParent(); 
    if (parent != NULL){
        if (parent->getLeft() == node){
            next_diff = 1; 
        }
        else {
            next_diff = -1; 
        }
    }

    AVLNode<Key, Value>* child; 

    if (diff == -1){ // left subtree is taller aka left heavy
        child = node->getLeft();
        
        
        int8_t child_balance = child->getBalance(); 

        if (node_balance + diff == -2 ){
            
            if (child_balance == -1 ){
                rotateRight(node); 
                node->setBalance(0);
                child->setBalance(0); 
                removeFix(parent, next_diff); 


            }

            else if (child_balance == 0){
                rotateRight(node); 
                node->setBalance(-1);
                child->setBalance(1); 


            }

            else if (child_balance == 1){
                AVLNode<Key, Value>* grandc = child->getRight(); 
                int8_t grandc_balance = grandc->getBalance(); 
                rotateLeft(child);
                rotateRight(node);

                if (grandc_balance == 1){
                    node->setBalance(0);
                    child->setBalance(-1);
                    grandc->setBalance(0); 
                }

                else if (grandc_balance == 0){
                    node->setBalance(0);
                    child->setBalance(0);
                    grandc->setBalance(0); 
                }

                else if (grandc_balance == -1){
                    node->setBalance(1);
                    child->setBalance(0);
                    grandc->setBalance(0); 
                }
                removeFix(parent, next_diff); 
            }
        }

        else if (node_balance + diff == -1 ){
            node->setBalance(-1); 
        }
        else if (node_balance + diff == 0){
            node->setBalance(0); 
            removeFix(parent, next_diff); 
        }
    }

    if (diff == 1){ // left subtree is taller aka left heavy
        
        child = node->getRight(); 
        int8_t child_balance = child->getBalance(); 

        if (node_balance + diff == 2 ){


            if (child_balance == 1 ){
                rotateLeft(node); 
                node->setBalance(0);
                child->setBalance(0); 
                removeFix(parent, next_diff); 


            }

            else if (child_balance == 0){
                rotateLeft(node); 
                node->setBalance(1);
                child->setBalance(-1); 


            }

            else if (child_balance == -1){
                AVLNode<Key, Value>* grandc = child->getLeft(); 
                int8_t grandc_balance = grandc->getBalance(); 
                rotateRight(child);
                rotateLeft(node);

                if (grandc_balance == -1){
                    node->setBalance(0);
                    child->setBalance(1);
                    grandc->setBalance(0); 
                }

                else if (grandc_balance == 0){
                    node->setBalance(0);
                    child->setBalance(0);
                    grandc->setBalance(0); 
                }

                else if (grandc_balance == 1){
                    node->setBalance(-1);
                    child->setBalance(0);
                    grandc->setBalance(0); 
                }
                removeFix(parent, next_diff); 
            }
        }

        else if (node_balance + diff == 1 ){
            node->setBalance(1); 
        }
        else if (node_balance + diff == 0){
            node->setBalance(0); 
            removeFix(parent, next_diff); 
        }
    } 
}

/*
 * Recall: The writeup specifies that if a node has 2 children you
 * should swap with the predecessor and then remove.
 */
template<class Key, class Value>
void AVLTree<Key, Value>::remove(const Key& key)
{
    // TODO

    // find node to remove by walking tree 
    Node<Key, Value>* find = this->internalFind(key); 
    AVLNode<Key, Value>* to_remove = static_cast<AVLNode<Key,Value>*>(find); 

    // check that its not null to avoid seg faults / invalid reads 
    if (to_remove == NULL) { return; }

    // if node to remove has 2(!!!!) children 
    // swap with inorder predecessor first to reduce to 1 / 0 child case 
    if (to_remove->getLeft() && to_remove->getRight() ) {
        // swap with its in order predecessor 
        Node<Key, Value>* pred = this->predecessor(find); 
        AVLNode<Key, Value>* av_pred = static_cast<AVLNode<Key,Value>*>(pred); 
        nodeSwap(to_remove, av_pred); 
    }

    // now if i had two children i swapped 

    // go on: find parent 
    //bool found = false; 

    AVLNode<Key, Value>* parent = to_remove->getParent(); 
    AVLNode<Key, Value>* curr;
    int8_t diff = 0; 

    if (parent != NULL){
        // not a root node 
        // if its a left child 

        if (to_remove == parent->getLeft()){
            diff = 1; 
            parent->updateBalance(1); 
        }
        else if (to_remove == parent->getRight()){
            diff = -1; 
            parent->updateBalance(-1); 
        }

    }
    // to_remove is node i'm deleting 
    // parent is node's parent 

    bool found = false;

    // 1 child case // only left child 
    if (to_remove->getLeft() && to_remove->getRight() ){
        //promote left child to parent 
        parent = to_remove->getParent();
        curr = to_remove->getLeft(); 
        found = true; 
    }

    // only RIGHT child 
    else if ( (to_remove->getRight() && to_remove->getLeft() == NULL)){
        parent = to_remove->getParent();
        curr = to_remove->getRight(); 
        found = true; 
    }

    if (found && parent == NULL){
        // i'm removing root 
        this->root_ = curr;
        curr->setParent(NULL); 
    }

    else if (found && parent->getLeft() == to_remove ){
        // removing left child
        parent->setLeft(curr);
        curr->setParent(parent); 
    }

    else if (found && parent->getRight() == to_remove){
        parent->setRight(curr);
        curr->setParent(parent); 
    }

    if (!found){
         // leaf
         // detach

         AVLNode<Key, Value>* parent = to_remove->getParent();


         if (parent == NULL){this->root_ = NULL; }
         else if (parent->getLeft() == to_remove){
            parent->setLeft(NULL);
         }
         else if (parent->getRight() == to_remove){
            parent->setRight(NULL);
         }

    }

    to_remove->setLeft(NULL);
    to_remove->setRight(NULL);
    to_remove->setParent(NULL);
    delete to_remove;
    removeFix(parent, diff); 
    return; 

}

template<class Key, class Value>
void AVLTree<Key, Value>::nodeSwap( AVLNode<Key,Value>* n1, AVLNode<Key,Value>* n2)
{
    BinarySearchTree<Key, Value>::nodeSwap(n1, n2);
    int8_t tempB = n1->getBalance();
    n1->setBalance(n2->getBalance());
    n2->setBalance(tempB);
}


#endif
