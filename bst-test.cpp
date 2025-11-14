#include <iostream>
#include <map>
#include "bst.h"
#include "avlbst.h"

using namespace std;


int main(int argc, char *argv[])
{
    // // Binary Search Tree tests
    // BinarySearchTree<char,int> bt;
    // bt.insert(std::make_pair('a',1));
    // bt.insert(std::make_pair('b',2));
    
    // cout << "Binary Search Tree contents:" << endl;
    // for(BinarySearchTree<char,int>::iterator it = bt.begin(); it != bt.end(); ++it) {
    //     cout << it->first << " " << it->second << endl;
    // }
    // if(bt.find('b') != bt.end()) {
    //     cout << "Found b" << endl;
    // }
    // else {
    //     cout << "Did not find b" << endl;
    // }
    // cout << "Erasing b" << endl;
    // bt.remove('b');

    // // tests made by me: 

    // BinarySearchTree<int,int> bin; 
    // // going to make this binary tree: 
    // //    50 
    // //    ^ 
    // //   10 
    // // ^    ^
    // // 5    20 

    // bin.insert(std::make_pair(50,50));
    // bin.print(); 
    // bin.insert(std::make_pair(10, 10));
    // bin.print();
    // bin.insert(std::make_pair(20, 20));
    // bin.print();
    // bin.insert(std::make_pair(5, 5)); 

    // // chcking 
    // // cout << "checking 50,10, 20, 5" << endl; 
   

    // cout << "Binary Search Tree contents:" << endl;
    // for(BinarySearchTree<int,int>::iterator it = bin.begin(); it != bin.end(); ++it) {
    //     cout << it->first << " " << it->second << endl;
    // }

    // bin.print(); 

    AVLTree<int, int> av; 

    // BinarySearchTree<char,int> bt;
    // bt.insert(std::make_pair('a',1));
    // bt.insert(std::make_pair('b',2));


    av.insert(std::make_pair(10,10));
    av.print(); 
    av.insert(std::make_pair(20,20));
    av.print(); 
    av.insert(std::make_pair(30,30));
    av.print(); 
    av.insert(std::make_pair(40,40));
    av.print(); 
    av.insert(std::make_pair(50,50));
    av.insert(std::make_pair(60,60));
    av.insert(std::make_pair(70,70));
    av.print(); 
    av.remove(10);
    av.remove(20);
    av.remove(30);
    
    


    








    // // AVL Tree Tests
    // AVLTree<char,int> at;
    // at.insert(std::make_pair('a',1));
    // at.insert(std::make_pair('b',2));

    // cout << "\nAVLTree contents:" << endl;
    // for(AVLTree<char,int>::iterator it = at.begin(); it != at.end(); ++it) {
    //     cout << it->first << " " << it->second << endl;
    // }
    // if(at.find('b') != at.end()) {
    //     cout << "Found b" << endl;
    // }
    // else {
    //     cout << "Did not find b" << endl;
    // }
    // cout << "Erasing b" << endl;
    // at.remove('b');

    return 0;
}
