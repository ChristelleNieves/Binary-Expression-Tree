// **********************************************************
// * Name: Christelle Nieves                                *                                *
// * Assignment: Assignment 4: Binary Expression Tree       *
// * Date: March 15, 2020                                   *                                  *
// **********************************************************

#ifndef _BET_H
#define _BET_H

#include <iostream>

class BET
{
    // Nested BinaryNode class
    class BinaryNode
    {
        public:
            std::string element;
            BinaryNode * left, * right;
    };

    public:
        BET(); // Default zero param constructor
        BET(const std::string& postfix); // One-param constructor. Postfix is string separated by spaces.
        BET(const BET&); // Copy constructor
        ~BET(); // Destructor

        bool buildFromPostfix(const std::string& postfix); // Build BET from a postfix string.
        const BET& operator=(const BET&); // Assignment operator.
        void printInfixExpression(); // Print the infix expression by calling the private recursive function.
        void printPostfixExpression(); // Print the postfix expression by calling the private recursive function.
        size_t size(); // Return the number of nodes in the tree by calling the private recursive function.
        bool empty(); // Return true if the tree is empty, false otherwise.
        size_t leaf_nodes(); // Return number of leaf nodes by calling the private recursive function.

    // BET private helper functions (Must be implemented recursively)
    private:
        void printInfixExpression(BinaryNode *n); // Print infix to std output.
        void makeEmpty(BinaryNode* &t); // Delete all nodes in the subtree pointed to by t.
        BinaryNode * clone(BinaryNode *t); // Clone all nodes in the subtree pointed to by t.
        void printPostfixExpression(BinaryNode *n); // Print postfix to std output.
        size_t size(BinaryNode *t); // Return the number of nodes in the subtree pointed to by t.
        size_t leaf_nodes(BinaryNode *t); // Return the number of lead nodes in the subtree pointed to by t.


    // BET attributes
    BinaryNode * root;
};

    #include "BET.hpp"

#endif