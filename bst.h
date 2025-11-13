#ifndef BST_H
#define BST_H

#include <iostream>
#include <exception>
#include <cstdlib>
#include <utility>
#include <stack>
#include <algorithm> 
#include <cmath> 

/**
 * A templated class for a Node in a search tree.
 * The getters for parent/left/right are virtual so
 * that they can be overridden for future kinds of
 * search trees, such as Red Black trees, Splay trees,
 * and AVL trees.
 */
template <typename Key, typename Value>
class Node
{
public:
    Node(const Key& key, const Value& value, Node<Key, Value>* parent);
    virtual ~Node();

    const std::pair<const Key, Value>& getItem() const;
    std::pair<const Key, Value>& getItem();
    const Key& getKey() const;
    const Value& getValue() const;
    Value& getValue();

    virtual Node<Key, Value>* getParent() const;
    virtual Node<Key, Value>* getLeft() const;
    virtual Node<Key, Value>* getRight() const;

    void setParent(Node<Key, Value>* parent);
    void setLeft(Node<Key, Value>* left);
    void setRight(Node<Key, Value>* right);
    void setValue(const Value &value);

protected:
    std::pair<const Key, Value> item_;
    Node<Key, Value>* parent_;
    Node<Key, Value>* left_;
    Node<Key, Value>* right_;
};

/*
  -----------------------------------------
  Begin implementations for the Node class.
  -----------------------------------------
*/

/**
* Explicit constructor for a node.
*/
template<typename Key, typename Value>
Node<Key, Value>::Node(const Key& key, const Value& value, Node<Key, Value>* parent) :
    item_(key, value),
    parent_(parent),
    left_(NULL),
    right_(NULL)
{

}

/**
* Destructor, which does not need to do anything since the pointers inside of a node
* are only used as references to existing nodes. The nodes pointed to by parent/left/right
* are freed by the BinarySearchTree.
*/
template<typename Key, typename Value>
Node<Key, Value>::~Node()
{

}

/**
* A const getter for the item.
*/
template<typename Key, typename Value>
const std::pair<const Key, Value>& Node<Key, Value>::getItem() const
{
    return item_;
}

/**
* A non-const getter for the item.
*/
template<typename Key, typename Value>
std::pair<const Key, Value>& Node<Key, Value>::getItem()
{
    return item_;
}

/**
* A const getter for the key.
*/
template<typename Key, typename Value>
const Key& Node<Key, Value>::getKey() const
{
    return item_.first;
}

/**
* A const getter for the value.
*/
template<typename Key, typename Value>
const Value& Node<Key, Value>::getValue() const
{
    return item_.second;
}

/**
* A non-const getter for the value.
*/
template<typename Key, typename Value>
Value& Node<Key, Value>::getValue()
{
    return item_.second;
}

/**
* An implementation of the virtual function for retreiving the parent.
*/
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getParent() const
{
    return parent_;
}

/**
* An implementation of the virtual function for retreiving the left child.
*/
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getLeft() const
{
    return left_;
}

/**
* An implementation of the virtual function for retreiving the right child.
*/
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getRight() const
{
    return right_;
}

/**
* A setter for setting the parent of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setParent(Node<Key, Value>* parent)
{
    parent_ = parent;
}

/**
* A setter for setting the left child of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setLeft(Node<Key, Value>* left)
{
    left_ = left;
}

/**
* A setter for setting the right child of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setRight(Node<Key, Value>* right)
{
    right_ = right;
}

/**
* A setter for the value of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setValue(const Value& value)
{
    item_.second = value;
}

/*
  ---------------------------------------
  End implementations for the Node class.
  ---------------------------------------
*/

/**
* A templated unbalanced binary search tree.
*/
template <typename Key, typename Value>
class BinarySearchTree
{
public:
    BinarySearchTree(); //TODO
    virtual ~BinarySearchTree(); //TODO
    virtual void insert(const std::pair<const Key, Value>& keyValuePair); //TODO
    virtual void remove(const Key& key); //TODO
    void clear(); //TODO
    bool isBalanced() const; //TODO
    void print() const;
    bool empty() const;

    template<typename PPKey, typename PPValue>
    friend void prettyPrintBST(BinarySearchTree<PPKey, PPValue> & tree);
public:
    /**
    * An internal iterator class for traversing the contents of the BST.
    */
    class iterator  // TODO
    {
    public:
        iterator();

        std::pair<const Key,Value>& operator*() const;
        std::pair<const Key,Value>* operator->() const;

        bool operator==(const iterator& rhs) const;
        bool operator!=(const iterator& rhs) const;

        iterator& operator++();

    protected:
        friend class BinarySearchTree<Key, Value>;
        iterator(Node<Key,Value>* ptr);
        Node<Key, Value> *current_;

        // new data member: stack to iterate through bst 
        std::stack< Node<Key,Value>* > nodes; 
    };

public:
    iterator begin() const;
    iterator end() const;
    iterator find(const Key& key) const;
    Value& operator[](const Key& key);
    Value const & operator[](const Key& key) const;

protected:
    // Mandatory helper functions
    Node<Key, Value>* internalFind(const Key& k) const; // TODO
    Node<Key, Value> *getSmallestNode() const;  // TODO
    static Node<Key, Value>* predecessor(Node<Key, Value>* current); // TODO
    // Note:  static means these functions don't have a "this" pointer
    //        and instead just use the input argument.

    // Provided helper functions
    virtual void printRoot (Node<Key, Value> *r) const;
    virtual void nodeSwap( Node<Key,Value>* n1, Node<Key,Value>* n2) ;

    // Add helper functions here

    Node <Key, Value>* search(Node<Key,Value>* ptr, const Key& key) const; 

   
    // helper function to find where to insert new pair 
    void where_to(const std::pair<const Key, Value> &keyValuepair, Node<Key, Value>*& ptr, Node<Key, Value>* parent);
    int dfs(Node<Key, Value>* ptr); 
    void clear_helper(Node<Key, Value>* current); 




protected:
    Node<Key, Value>* root_;
    // You should not need other data members
};

/*
--------------------------------------------------------------
Begin implementations for the BinarySearchTree::iterator class.
---------------------------------------------------------------
*/

/**
* Explicit constructor that initializes an iterator with a given node pointer.
*/
template<class Key, class Value>
BinarySearchTree<Key, Value>::iterator::iterator(Node<Key,Value> *ptr)
{
    // TODO
    current_ = ptr; 
    // put all of the left childs in the stack first 
    while (ptr != NULL){
        nodes.push(ptr);
        ptr = ptr->getLeft(); 
    }
    // first to come out will be the next ptr following the inorder traversal logic 
    if (!nodes.empty())
    {current_ = nodes.top(); }
    else {
        current_ = NULL; 
    }

}

/**
* A default constructor that initializes the iterator to NULL.
*/
template<class Key, class Value>
BinarySearchTree<Key, Value>::iterator::iterator() 
{
    // TODO
    current_ = NULL; 

}

/**
* Provides access to the item.
*/
template<class Key, class Value>
std::pair<const Key,Value> &
BinarySearchTree<Key, Value>::iterator::operator*() const
{
    return current_->getItem();
}

/**
* Provides access to the address of the item.
*/
template<class Key, class Value>
std::pair<const Key,Value> *
BinarySearchTree<Key, Value>::iterator::operator->() const
{
    return &(current_->getItem());
}

/**
* Checks if 'this' iterator's internals have the same value
* as 'rhs'
*/
template<class Key, class Value>
bool
BinarySearchTree<Key, Value>::iterator::operator==(
    const BinarySearchTree<Key, Value>::iterator& rhs) const
{
    // TODO
    return current_ == rhs.current_; 
}

/**
* Checks if 'this' iterator's internals have a different value
* as 'rhs'
*/

// should return true if != 
template<class Key, class Value>
bool
BinarySearchTree<Key, Value>::iterator::operator!=(
    const BinarySearchTree<Key, Value>::iterator& rhs) const
{
    // TODO
    return current_ != rhs.current_; 

}


/**
* Advances the iterator's location using an in-order sequencing
*/
// in order: left, root, right

template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator&
BinarySearchTree<Key, Value>::iterator::operator++()
{
    // I HAVE a stack, nodes, which has all of the left childs

    if (!nodes.empty()){
        // current node will always be on top of stack 
        current_ = nodes.top(); 
        nodes.pop(); 
        Node<Key, Value>* temp = current_; 
        // now add nodes that owuld go next (right subtree ) if necessary 
        while (temp != NULL ){
            // if its a parent, push right once 
            if ( temp->getRight() ){
                temp = temp->getRight(); 
                nodes.push(temp);

                // if right sub has left children, push all of them 
                    while (temp->getLeft()){
                        temp = temp->getLeft(); 
                        nodes.push(temp); 
                    }
    
                }    

            // leaf node 
            else { break; }
        }

    }
}


/*
-------------------------------------------------------------
End implementations for the BinarySearchTree::iterator class.
-------------------------------------------------------------
*/

/*
-----------------------------------------------------
Begin implementations for the BinarySearchTree class.
-----------------------------------------------------
*/

/**
* Default constructor for a BinarySearchTree, which sets the root to NULL.
*/
template<class Key, class Value>
BinarySearchTree<Key, Value>::BinarySearchTree() 
{
    root_ = NULL; 
}

template<typename Key, typename Value>
BinarySearchTree<Key, Value>::~BinarySearchTree()
{
    // TODO

}

/**
 * Returns true if tree is empty
*/
template<class Key, class Value>
bool BinarySearchTree<Key, Value>::empty() const
{
    return root_ == NULL;
}

template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::print() const
{
    printRoot(root_);
    std::cout << "\n";
}

/**
* Returns an iterator to the "smallest" item in the tree
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator
BinarySearchTree<Key, Value>::begin() const
{
    BinarySearchTree<Key, Value>::iterator begin(getSmallestNode());
    return begin;
}

/**
* Returns an iterator whose value means INVALID
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator
BinarySearchTree<Key, Value>::end() const
{
    BinarySearchTree<Key, Value>::iterator end(NULL);
    return end;
}


/**
* Returns an iterator to the item with the given key, k
* or the end iterator if k does not exist in the tree
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator
BinarySearchTree<Key, Value>::find(const Key & k) const
{
    Node<Key, Value> *curr = internalFind(k);
    BinarySearchTree<Key, Value>::iterator it(curr);
    return it;
}




/**
 * @precondition The key exists in the map
 * Returns the value associated with the key
 */
template<class Key, class Value>
Value& BinarySearchTree<Key, Value>::operator[](const Key& key)
{
    Node<Key, Value> *curr = internalFind(key);
    if(curr == NULL) throw std::out_of_range("Invalid key");
    return curr->getValue();
}
template<class Key, class Value>
Value const & BinarySearchTree<Key, Value>::operator[](const Key& key) const
{
    Node<Key, Value> *curr = internalFind(key);
    if(curr == NULL) throw std::out_of_range("Invalid key");
    return curr->getValue();
}



/**
* An insert method to insert into a Binary Search Tree.
* The tree will not remain balanced when inserting.
* Recall: If key is already in the tree, you should 
* overwrite the current value with the updated value.
*/

template<class Key, class Value>
void BinarySearchTree<Key, Value>::where_to(const std::pair<const Key, Value> &keyValuepair, Node<Key, Value>*& ptr, Node<Key, Value>* parent)
{
    if (ptr == NULL){
        ptr = new Node<Key, Value>(keyValuepair.first, keyValuepair.second, parent); 
        return; 
    }

    else if (keyValuepair.first < ptr->getKey() )  {
        Node<Key, Value>* l_ptr = ptr->getLeft(); 
         where_to(keyValuepair, l_ptr, ptr);  
         ptr->setLeft(l_ptr); 
        } 

    else {
        Node<Key, Value>* r_ptr = ptr->getRight(); 
        where_to(keyValuepair, r_ptr, ptr);  
        ptr->setRight(r_ptr); 
     }

}

template<class Key, class Value>
void BinarySearchTree<Key, Value>::insert(const std::pair<const Key, Value> &keyValuePair)
{
    if (root_ == NULL){
        root_ = new Node<Key, Value>(keyValuePair.first, keyValuePair.second, NULL); 
        return; 
    }
    
    Node<Key, Value>* find = internalFind(keyValuePair.first); 
    if (find != NULL){
        find->setValue(keyValuePair.second);
        return;  
    }

    else {
        where_to(keyValuePair, root_, NULL); 
    }
}


/**
* A remove method to remove a specific key from a Binary Search Tree.
* Recall: The writeup specifies that if a node has 2 children you
* should swap with the predecessor and then remove.
*/

// have to fix this function
template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::remove(const Key& key)
{
    //TODO 

    // find key 
    Node<Key, Value>* find = internalFind(key); 
    // if key not in treee, do nothing 
    if (find == NULL){ return; } 


    if (find->getParent() == NULL ) // ROOT  
    {
        root_ = NULL; 
    }

    // 1 child case
    // only left child 
    else if (find->getLeft() && !find->getRight() ){
        // promote left child to parent 
        Node<Key, Value>* parent = find->getParent(); 
        Node<Key, Value>* curr = find->getLeft(); 

        curr->setParent(parent); 
    }

     // only RIGHT child 
     else if (find->getRight() && !find->getLeft()){
        // swap parent and node 
        Node<Key, Value>* parent = find->getParent(); 
        Node<Key, Value>* curr = find->getRight(); 

        curr->setParent(parent);  
    }

    // 2 children case
    // swap with predecessor and remove from new loc 
    else if (find->getLeft() && find->getRight() ){
        Node<Key, Value>* pred = predecessor(find); 
        nodeSwap(find, pred); 
    }

    else { // leaf node 
        // detach 
        Node<Key, Value>* parent = find->getParent(); 
        if (parent->getLeft() == find ) {parent->setLeft(NULL); }
        else if (parent->getRight() == find ) {parent->setRight(NULL); }
    }

    delete find;
    return; 
}



template<class Key, class Value>
Node<Key, Value>*
BinarySearchTree<Key, Value>::predecessor(Node<Key, Value>* current)
{
    // TODO
    // IF im dealing with a root node 
    if (current->getParent() == NULL){
        return NULL; 
    }

    // if it has left child, pred is right-most node of left subtree
    if (current->getLeft()){
        current = current->getLeft(); 

        // find right-most node of left subtree
        while (current){
            current = current->getRight(); 
        }
    }

    // else walk up to parent, find first node who is right child, its parent is the predecessor 
    else {
        // go to parent 
        current = current->getParent(); 

        while (current) {
            // find a right child 
            if (current->getRight()){
                current = current->getRight(); // found 
                break; 
            }
            else { 
                current = current->getParent(); 
            }
        }
    }

    return current; 
}

template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::clear_helper(Node<Key, Value>* current)
{
    // TODO make this function to help cler the binary tree

    if (current == NULL){
        return; 
    }

    clear_helper( current->getLeft() ); 
    clear_helper( current->getRight() ); 
    delete current; 
}


/**
* A method to remove all contents of the tree and
* reset the values in the tree for use again.
*/
template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::clear()
{
    // TODO
    clear_helper(root_); 
    delete root_;
    root_ = NULL; 

}


/**
* A helper function to find the smallest node in the tree.
*/
template<typename Key, typename Value>
Node<Key, Value>*
BinarySearchTree<Key, Value>::getSmallestNode() const
{
    // TODO
}

/** helper function added by me 
* returns pointer to the found value, if not found return null 
*/
template<typename Key, typename Value>
Node <Key, Value>* BinarySearchTree<Key, Value>::search(Node<Key,Value>* ptr, const Key& key) const {

    if (ptr == NULL){
        return NULL; 
    }

    if(ptr->getKey() == key) {
        return ptr;
    }

    else if (key < ptr->getKey() ) { return search(ptr->getLeft(), key);  }
    else if (key > ptr->getKey()  ) { return search(ptr->getRight(), key);  }

    return NULL;
}

/**
* Helper function to find a node with given key, k and
* return a pointer to it or NULL if no item with that key
* exists
*/
template<typename Key, typename Value>
Node<Key, Value>* BinarySearchTree<Key, Value>::internalFind(const Key& key) const
{
    // TODO
    Node<Key,Value>* ptr = root_; 
    Node<Key,Value>* find = search(ptr, key); 

    if (find == NULL) {return NULL; }
    else {
        return find; 
    }
}

template<typename Key, typename Value>
int BinarySearchTree<Key, Value>::dfs(Node<Key, Value>* ptr) {

    if(ptr == NULL){ // leaf node 
        return 0; 
    }

    else {
        int left = 1 + dfs(ptr->getLeft() );
        int right = 1+ dfs(ptr->getRight() ); 
        return std::max(left, right); 
    }
}

/**
 * Return true iff the BST is balanced.
 */
template<typename Key, typename Value>
bool BinarySearchTree<Key, Value>::isBalanced() const
{
    // TODO

    // recursively check if it is balanced 

    if (root_ == NULL){
        return true; 
        // all roots are balanced (height one)
    }
    else {
        bool balance =  std::abs( dfs(root_->getRight() ) - dfs( root_->getRight() )) <= 1; 
        return balance && isBalanced(root_->getLeft()) && isBalanced(root_->getRight()); 
    }
    
}







template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::nodeSwap( Node<Key,Value>* n1, Node<Key,Value>* n2)
{
    if((n1 == n2) || (n1 == NULL) || (n2 == NULL) ) {
        return;
    }
    Node<Key, Value>* n1p = n1->getParent();
    Node<Key, Value>* n1r = n1->getRight();
    Node<Key, Value>* n1lt = n1->getLeft();
    bool n1isLeft = false;
    if(n1p != NULL && (n1 == n1p->getLeft())) n1isLeft = true;
    Node<Key, Value>* n2p = n2->getParent();
    Node<Key, Value>* n2r = n2->getRight();
    Node<Key, Value>* n2lt = n2->getLeft();
    bool n2isLeft = false;
    if(n2p != NULL && (n2 == n2p->getLeft())) n2isLeft = true;


    Node<Key, Value>* temp;
    temp = n1->getParent();
    n1->setParent(n2->getParent());
    n2->setParent(temp);

    temp = n1->getLeft();
    n1->setLeft(n2->getLeft());
    n2->setLeft(temp);

    temp = n1->getRight();
    n1->setRight(n2->getRight());
    n2->setRight(temp);

    if( (n1r != NULL && n1r == n2) ) {
        n2->setRight(n1);
        n1->setParent(n2);
    }
    else if( n2r != NULL && n2r == n1) {
        n1->setRight(n2);
        n2->setParent(n1);

    }
    else if( n1lt != NULL && n1lt == n2) {
        n2->setLeft(n1);
        n1->setParent(n2);

    }
    else if( n2lt != NULL && n2lt == n1) {
        n1->setLeft(n2);
        n2->setParent(n1);

    }


    if(n1p != NULL && n1p != n2) {
        if(n1isLeft) n1p->setLeft(n2);
        else n1p->setRight(n2);
    }
    if(n1r != NULL && n1r != n2) {
        n1r->setParent(n2);
    }
    if(n1lt != NULL && n1lt != n2) {
        n1lt->setParent(n2);
    }

    if(n2p != NULL && n2p != n1) {
        if(n2isLeft) n2p->setLeft(n1);
        else n2p->setRight(n1);
    }
    if(n2r != NULL && n2r != n1) {
        n2r->setParent(n1);
    }
    if(n2lt != NULL && n2lt != n1) {
        n2lt->setParent(n1);
    }


    if(this->root_ == n1) {
        this->root_ = n2;
    }
    else if(this->root_ == n2) {
        this->root_ = n1;
    }

}

/**
 * Lastly, we are providing you with a print function,
   BinarySearchTree::printRoot().
   Just call it with a node to start printing at, e.g:
   this->printRoot(this->root_) // or any other node pointer

   It will print up to 5 levels of the tree rooted at the passed node,
   in ASCII graphics format.
   We hope it will make debugging easier!
  */

// include print function (in its own file because it's fairly long)
#include "print_bst.h"

/*
---------------------------------------------------
End implementations for the BinarySearchTree class.
---------------------------------------------------
*/

#endif
