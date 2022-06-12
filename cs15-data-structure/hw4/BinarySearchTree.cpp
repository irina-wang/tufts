/*
 * BinarySearchTree.cpp
 * Comp15
 * Spring 2019
 * HW4
 *
 * Author : Mengqi Irina Wang
 * Date: 2/27/2019
 */

#include <iostream>
#include <climits>
#include <fstream>
#include <sstream>

#include "BinarySearchTree.h"
#include <limits.h>

using namespace std;

// Constructor
BinarySearchTree::BinarySearchTree()
{
        root = NULL; // root starts as NULL
}

// Destructor 
BinarySearchTree::~BinarySearchTree()
{
        // walk tree in post-order traversal and delete
        post_order_delete(root);
        root = NULL;   // not really necessary, since the tree is going 
                       // away, but might want to guard against someone
                       // using a pointer after deleting
}

// post_order_delete
//   The function that post-orderly delete a tree
//
// Parameter : Node, a node pointer
// Return    : none
// Does      : delete the tree post orderly using recursion
// Note      : none
void BinarySearchTree::post_order_delete(Node *node)
{
        if(node == NULL)
                return;
        if(node->left != NULL)
                post_order_delete(node->left);
        if(node->right != NULL)
                post_order_delete(node->right);

        delete node;
        return;                
}

// copy constructor
BinarySearchTree::BinarySearchTree(const BinarySearchTree &source)
{
        // use pre-order traversal to copy the tree
        root = pre_order_copy(source.root);
}

// assignment overload
BinarySearchTree &BinarySearchTree::operator= (const BinarySearchTree &source)
{
        if(this != &source) {
                post_order_delete(root); // delete current tree if it exists
                root = pre_order_copy(source.root);// use pre-order traversal 
                                                   // to copy the tree
        }
        return *this;
}

// pre_order_copy
//   The function that pre-orderly copy a tree
//
// Parameter : Node, a node pointer
// Return    : Node, new_node, the node that's inserted
//             return NULL when node is NULL
// Does      : copy the tree pre-orderly
// Note      : call newNode function
Node *BinarySearchTree::pre_order_copy(Node *node) const
{
        if (node == NULL)
                return NULL;

        Node *new_node = newNode(node->data, node->count, 
                pre_order_copy(node->left), pre_order_copy(node->right));
        return new_node;
}

// find_min
//   The function that returns the minimum value for the tree(public)
//
// Parameter : none
// Return    : int, minimum value of the tree found by private find_min
//             return INT_MIN when the root is NULL
// Does      : find the minimum value of the tree
// Note      : called by the client
int BinarySearchTree::find_min() const
{
        if (root == NULL)
                return INT_MIN;
        return find_min(root)->data;
}

// find_min
//   The function that returns the minimum value for the tree(private)
//
// Parameter : Node, a node pointer
// Return    : Node, node of the smallest value
// Does      : find the minimum value of the tree
// Note      : implement by the implementor; keep accessing the node on the left
//             until it's the last
Node *BinarySearchTree::find_min(Node *node) const
{
        if(node->left == NULL)
                return node;
        else
                return find_min(node->left);
}

// find_max
//   The function that returns the maximum value for the tree(public)
//
// Parameter : none
// Return    : int, maximum value of the tree found by private find_max
//             return INT_MAX when the root is NULL
// Does      : find the maximum value of the tree
// Note      : called by the client
int BinarySearchTree::find_max() const
{
        if (root == NULL)
                return INT_MAX; 
        return find_max(root)->data;
}

// find_max
//   The function that returns the maximum value for the tree(private)
//
// Parameter : Node, a node pointer
// Return    : Node, node of the largest value
// Does      : find the maximum value of the tree
// Note      : implement by the implementor; keep accessing the node on the 
//             right until it's the last
Node *BinarySearchTree::find_max(Node *node) const
{
        if(node->right == NULL)
                return node;
        else
                return find_max(node->right);
}

// contains
//   The function that check if the tree contains a certain value(public)
//
// Parameter : int, value, the value to be search
// Return    : bool, the value returned by the private contains function
//             bool false when the root is NULL
// Does      : check if the tree contains a certain value
// Note      : called by the client
bool BinarySearchTree::contains(int value) const
{
        if (root == NULL)
                return false;
        return contains(root, value);
}

// contains
//   The function that check if the tree contains a certain value(private)
//
// Parameter : Node, a node pointer, the tree to searched with
//             int, value, the value to be search
// Return    : bool, true, if find the value
//             bool false when the root is NULL
//             else recursively call itself
// Does      : recursively check if the tree contains a certain value by 
//             comparing the value of current node with the value passed in
// Note      : implement by the implementor
bool BinarySearchTree::contains(Node *node, int value) const
{
        if(node == NULL)
                return false;
        if(node->data == value)
                return true;
        else if(node->data < value) // have to search for larger
                return contains(node->right,value);
        else 
                return contains(node->left,value);
}

// insert
//   The function that insert a value to a tree(public)
//
// Parameter : int, value, the value to be inserted
// Return    : none
// Does      : insert a value to a tree
// Note      : called by the client
void BinarySearchTree::insert(int value)
{
        insert(root, NULL, value);
}

// insert
//   The function that insert a value to a tree(private)
//
// Parameter : Node pointer, node, node to tranverse with 
//             Node pointer, parent, keep track of the parent of current node
//             int, value, the value to be inserted
// Return    : none
// Does      : insert a value to a tree
// Note      : call newNode function to insert
void BinarySearchTree::insert(Node *node, Node *parent, int value)
{
        if(root == NULL){
                root = newNode(value, 1, NULL, NULL);
                return;
        }if(node == NULL){
                if(parent->data < value)
                        parent->right = newNode(value, 1, NULL, NULL);
                else 
                        parent->left = newNode(value, 1, NULL, NULL);
        } else {
                if(value == node->data){ //renew count
                        node->count += 1;
                        return;
                } else if(value < node->data){ // on the left
                        insert(node->left, node, value);
                } else{ // on the right
                        insert(node->right,node, value);
                }
        }
        return;
}

// newNode
//   The function that make a new node(private)
//
// Parameter : int, data, the value to be inserted
//             int, count, how many time this node has been inserted
//             Node pointer, left, left children
//             Node pointer, right, right children 
// Return    : Node, newnode pointer
// Does      : make a new node
// Note      : helper function
Node *BinarySearchTree::newNode(int data, int count, Node *left, Node *right) 
const
{
        Node *newnode = new Node;
        newnode->data = data;
        newnode->count = count;
        newnode->left = left;
        newnode->right = right;

        return newnode;
}

// remove
//   The function that remove a node from a tree(public)
//
// Parameter : int, value, the value to be removed
// Return    : bool, the value private remove function returns, if removed
//             or not
// Does      : remove a node from a tree
// Note      : called by the client
bool BinarySearchTree::remove(int value)
{
        return remove(root, NULL, value);
}

// remove
//   The function that remove a node from a tree(private)
//
// Parameter : Node pointer, node, node to tranverse with 
//             Node pointer, parent, keep track of the parent of current node
//             int, value, the value to be removed
// Return    : bool, true if removed and false if unable to remove
//             otherwise recursively call itself
// Does      : remove a node from a tree
// Note      : special cases were considered regarding the children and
//             the count's number
bool BinarySearchTree::remove(Node *node, Node *parent, int value)
{
        if(node == NULL) return false;
        if(node->data == value){
                if(node->count > 1){ // count more than 1
                        node->count -= 1;
                        return true;
                } if(node->left == NULL and node->right == NULL){ // no children
                        update_parent(parent, node, NULL);
                        delete node;
                        return true;
                } else if(node->left == NULL) { // one child : right
                        update_parent(parent, node, node->right);
                        delete node;
                        return true;
                } else if(node->right == NULL) { // one child : left
                        update_parent(parent, node, node->left);
                        delete node;
                        return true;
                } else { // two children
                        Node *replace_node = find_min(node->right); // right min
                        Node *new_parent = find_parent(root, replace_node);
                        node->data = replace_node->data;
                        node->count = replace_node->count;
                        return remove(replace_node, new_parent, node->data);} 
        } else{
                if(node->data < value) // check larger
                        return remove(node->right, node, value);
                else return remove(node->left, node, value);} // check smaller 
}

// update_parent
//   The function that undate the parent pointer(private)
//
// Parameter : Node pointer, parent, parents's node
//             Node pointer, node, child's node
//             Node pointer, update_to, the node to be updated to
// Return    : none
// Does      : undate the parent pointer left/right child to update_to depending
//             on the which child node is 
// Note      : helper function
void BinarySearchTree::update_parent(Node *parent, Node *node, Node *update_to)
{
        if(parent == NULL)
                root = update_to;
        else if(parent->left == node)
                parent->left = update_to;
        else
                parent->right = update_to;
}

// height
//   The function that gets the height of a tree(public)
//
// Parameter : none
// Return    : int, the height private height function returns 
// Does      : gets the height of a tree
// Note      : called by the client
int BinarySearchTree::tree_height() const
{
        return tree_height(root);
}

// height
//   The function that gets the height of a tree(private)
//
// Parameter : Node, node pointer, the tree to seek height of
// Return    : -1 when the tree is empty, or the height of tree
// Does      : gets the height of a tree
// Note      : calls a helper function return_larger_one_of
int BinarySearchTree::tree_height(Node *node) const
{
        if(node == NULL)
                return -1; // no root
        else 
                return return_larger_one_of(tree_height(node->left), 
                                            tree_height(node->right));
}

// return_larger_one_of
//   The function that returns the larger int(private)
//
// Parameter : int, left_result, height of left branch
//             int, right_result, height of right branch
// Return    : int, the larger one
// Does      : returns the larger int
// Note      : helper function
int BinarySearchTree::return_larger_one_of(int left_result, int right_result) 
const
{
        if(left_result > right_result)
                return left_result+1;
        else
                return right_result+1;
}

// node_count
//   The function that returns the total number of nodes(public)
//
// Parameter : none
// Return    : int, the number private node count function returns 
// Does      : returns the total number of nodes
// Note      : called by the client
int BinarySearchTree::node_count() const
{
        return node_count(root);
}

// node_count
//   The function that returns the total number of nodes(private)
//
// Parameter : Node, node pointer, tree to count with 
// Return    : int, the number of nodes the function contains 
// Does      : returns the total number of nodes
// Note      : Not including duplicates
int BinarySearchTree::node_count(Node *node) const
{
        if(node == NULL) 
                return 0; 
        else
                return node_count(node->left)+1+node_count(node->right);
}

// count_total
//   The function that returns the sum of all the node values including 
// duplicates(public)
//
// Parameter : none
// Return    : int, the number private count total function returns 
// Does      : returns the sum of all the node values including duplicates
// Note      : called by the client
int BinarySearchTree::count_total() const
{
        return count_total(root);
}

// count_total
//   The function that returns the sum of all the node values including 
// duplicates(private)
//
// Parameter : Node, node pointer, tree to count with 
// Return    : int, the sum of all nodes
// Does      :  returns the sum of all the node values including duplicates
// Note      : including duplicates
int BinarySearchTree::count_total(Node *node) const
{
        if(node == NULL)
                return 0;
        else{
               return count_total(node->left)
                        +(node->count)*(node->data)
                        +count_total(node->right);
        }

}

// print_tree
//   The function use the printPretty helper to make the tree look nice
//
// Parameter : none
// Return    : none
// Does      : print a nicer tree
// Note      : written by others
void BinarySearchTree::print_tree() const
{
        printPretty(root, 1, 0, std::cout);
}

// find_parent
//   The function finds the parent of the given children
//
// Parameter : Node pointer, parent, parents's node
//             Node pointer, node, child's node
// Return    : parent node pointer of the given child
// Does      : finds the parent of the given children
// Note      : written by others
Node *BinarySearchTree::find_parent(Node *node, Node *child) const
{
        if (node == NULL) return NULL;

        // if either the left or right is equal to the child,
        // we have found the parent
        if (node->left == child or node->right == child) {
                return node; 
        }

        // Use the binary search tree invariant to walk the tree
        if (child->data > node->data) {
                return find_parent(node->right, child); 
        } else {
                return find_parent(node->left, child); 
        }
}
