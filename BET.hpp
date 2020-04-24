// **********************************************************
// * Name: Christelle Nieves                                *                                *
// * Assignment: Assignment 4: Binary Expression Tree       *
// * Date: March 15, 2020                                   *                                  *
// **********************************************************

#ifndef _BET_HPP
#define _BET_HPP

#include <iostream>
#include <sstream>
#include <stack>

#include "BET.h"

using namespace std;

// Helper function prototypes
void error();
bool isOperand(string);
bool isOperator(string);
int getPrecedence(string);

// Default zero-parameter constructor for a BET
BET::BET()
{
    root = nullptr;
}

// One-parameter constructor for a BET. Constructs a BET from a postfix string.
BET::BET(const string& postfix)
{
    // Build the BET
    bool built = buildFromPostfix(postfix);

    // If the BET was not able to be built, display an error.
    if (!built)
    {
        if (!empty())
        {
            makeEmpty(root);
        }
    }
}

// Copy Constructor
BET::BET(const BET& t)
{
    root = clone(t.root);
}

// Destructor
BET::~BET()
{
    makeEmpty(root);
}

// Assignment Operator
const BET& BET::operator=(const BET& t)
{
    root = clone(t.root);
    return *this;
}

// Build a BET from a postfix string
bool BET::buildFromPostfix(const string& postfix)
{
    stringstream ss(postfix);
    stack<BinaryNode*> stk;
    string token;

    // If the BET already contains nodes, delete them.
    if (!empty())
    {
        makeEmpty(root);
    }

    // Parse the postfix string and separate into tokens by spaces.
    while (getline(ss, token, ' '))
    {
        // If the token is an operand, create a node for it and push it to the stack.
        if (isOperand(token))
        {
            BinaryNode * newNode = new BinaryNode();
            newNode->element = token;
            newNode->right = newNode->left = nullptr;
            root = newNode;
            stk.push(newNode);
        }
        // If the token is an operator, create a node for it, pop 2 elements from the
        // stack, and set them as the operators right and left children nodes.
        else if (isOperator(token))
        {
            // If we encounter an operator but do not have 2 elements in the stack,
            // call an error and return false.
            if (stk.size() < 2)
            {
                error();
                return false;
            }

            // Pop 2 elements from the stack and add them as children to the new operator node.
            BinaryNode * newNode = new BinaryNode();
            newNode->element = token;
            newNode->right = stk.top();
            stk.pop();
            newNode->left = stk.top();
            stk.pop();
            root = newNode;
            stk.push(newNode);
        }
    }

    // If the stack does not only contain one element, we have encountered an error so return false.
    if (stk.size() != 1)
    {
        error();
        return false;
    }

    // Return true if the BET was built with no errors.
    return true;
}

// Return true if the BET is empty, false otherwise.
bool BET::empty() 
{
    return size() == 0;
}

// Return the size of the BET by calling the private recursive size function.
size_t BET::size()
{
    return size(root);
}

// Return the number of leaf nodes in the BET by calling the private recursive leaf_nodes function.
size_t BET::leaf_nodes()
{
    return leaf_nodes(root);
}

// Print the postfix expression of the BET by calling the recursive printPostfixExpression function.
void BET::printPostfixExpression()
{
    printPostfixExpression(root);
    cout << endl;
}

// Print the infix expression of the BET by calling the recursive printInfixExpression funcrtion.
void BET::printInfixExpression()
{
    printInfixExpression(root);
    cout << endl;
}

// Recursively print the corresponding postfix expression from a BET.
void BET::printPostfixExpression(BinaryNode *t)
{
    // If the tree is non-empty, print the postorder traversal of the tree.
    if (t != nullptr)
    {
        printPostfixExpression(t->left);
        printPostfixExpression(t->right);
        cout << t->element << " ";
    }
}

// Recursively print the correspinding infix expression from a BET.
void BET::printInfixExpression(BinaryNode *t)
{
    /* When printing an expression tree in infix form we only need to print parentheses
     around sub-expressions (children) where the operator has a lower precedence than 
     the operator of the main (parent) expression.
    */

    // In the case we have an empty tree, stop here.
    if (t == nullptr)
    {
        cout << "Empty Tree." << endl;
        return;
    }
    // If the root is an operand, print it and return.
    else if (isOperand(t->element))
    {
        cout << t->element << " ";
        return;
    }
    else
    {
        if (t->left != nullptr)
        {
            if (isOperator(t->left->element))
            {
                // If the left child is an operator with a lower precedence than the
                // parent node, we will print parentheses around the operation.
                if (getPrecedence(t->element) > getPrecedence(t->left->element))
                {
                    cout << "( ";
                    printInfixExpression(t->left);
                    cout << ") ";
                }
                // If the left child is an operator with equal or higher precedence
                // than the parent node, we will not print any parentheses.
                else
                {
                    printInfixExpression(t->left);
                }
            }
            // If the left child is not an operator, just call the function on the left child.
            else
            {
                printInfixExpression(t->left);
            }
        }

        // Print the current node element.
        cout << t->element << " ";

        if ( t->right != nullptr)
        {
            if (isOperator(t->right->element))
            {
                // If the right child is an operator with a lower precedence than the
                // parent node, we will print parentheses around the operation.
                if (getPrecedence(t->element) > getPrecedence(t->right->element))
                {
                    cout << "( ";
                    printInfixExpression(t->right);
                    cout << ") ";
                }
                // If the right child is an operator with equal or higher precedence
                // than the parent node, we will not print any parentheses.
                else
                {
                    printInfixExpression(t->right);
                }
            }
            // If the right child is not an operator, just call the function on the right child.
            else
            {
                printInfixExpression(t->right);
            }
        }
    }
}

// Delete all nodes in the subtree pointed to by t
void BET::makeEmpty(BinaryNode * &t)
{
    // If we have a non-empty tree, set all nodes to nullptr.
    if (t != nullptr)
    {
        makeEmpty(t->left);
        makeEmpty(t->right);
        t = nullptr;
    }
}

// Private recursive function to count all nodes in the BET.
size_t BET::size(BinaryNode *t)
{
    // Return 0 if we have an empty tree.
    if (t == nullptr)
    {
        return 0;
    }

    return 1 + size(t->left) + size(t->right);
}

// Recursively count the number of leaf nodes in the BET.
size_t BET::leaf_nodes(BinaryNode *t)
{
    // Return 0 if we have an empty tree.
    if (t == nullptr)
    {
        return 0;
    }
    // If the root is the only node in tree, return 1.
    else if (t->left == nullptr && t->right == nullptr)
    {
        return 1;
    }

    return leaf_nodes(t->left) + leaf_nodes(t->right);
}

// Clone all nodes in the subtree pointed to by t.
BET::BinaryNode * BET::clone(BinaryNode *t)
{
    BinaryNode * cloneNode = nullptr;

    // If we have a non-empty tree, recursively clone all elements.
    if (t != nullptr)
    {
        cloneNode = new BinaryNode();
        cloneNode->element = t->element;
        cloneNode->left = clone(t->left);
        cloneNode->right = clone(t->right);
    }

    return cloneNode;
}

// **********************************************
// * Function Name: error()                     *
// * Description: Displays an error message.    *
// * Date: March 15, 2020                       *
// * Author: Christelle Nieves                  *
// **********************************************
void error()
{
    cout << "Error: Invalid Expression." << endl;
}

// ******************************************************************
// * Function Name: isOperand()                                     *
// * Description: Returns true if a string token represents         *
// *    an operand, false otherwise.                                *
// * Parameter Description: Takes in a string representing a token. *
// * Date: March 15, 2020                                           *
// * Author: Christelle Nieves                                      *
// ******************************************************************
bool isOperand(string token)
{
    for (int i = 0; i < token.length(); i++)
    {
        if (!isalpha(token[i]) && !isdigit(token[i]))
        {
            return false;
        }
    }
    return true;
}

// ******************************************************************
// * Function Name: isOperator()                                    *
// * Description: Returns true if a string token represents an      *
// *    operator, false otherwise.                                  *
// * Parameter Description: Takes in a string representing a token. *
// * Date: March 15, 2020                                           *
// * Author: Christelle Nieves                                      *
// ******************************************************************
bool isOperator(string token)
{
    return token == "+" || token == "-" || token == "*" || token == "/";
}

// **********************************************************************
// * Function Name: getPrecedence()                                     *
// * Description: Returns an integer corresponding to the precedence    *
// *    of the given operator token.                                    *
// * Parameter Description: Takes in a string representing an operator. *
// * Date: March 15, 2020                                               *
// * Author: Christelle Nieves                                          *
// **********************************************************************
int getPrecedence(string token)
{
    // + and - have equal lowest precedence.
    if (token == "+" || token == "-")
    {
        return 1;
    }
    // * and / have equal highest precedence.
    else if (token == "*" || token == "/")
    {
        return 2;
    }
    else
    {
        cout << "Unrecognized Operator." << endl;
        return 100;
    }
}

#endif