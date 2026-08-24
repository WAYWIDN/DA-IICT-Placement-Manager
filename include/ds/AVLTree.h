#ifndef AVL_TREE_H
#define AVL_TREE_H

#include <iostream>
#include <queue>
#include <algorithm>
#include <vector>
using namespace std;

template <typename T, typename U>
class Node
{
public:
    T key;
    vector<U> value;
    int height;
    Node *left;
    Node *right;

    Node(T key, U value)
    {
        this->key = key;
        this->value.push_back(value);
        height = 1;
        left = NULL;
        right = NULL;
    }
};

template <typename T, typename U>
class AVLTree
{
private:
    Node<T, U> *root;

    int getHeight(Node<T, U> *node)
    {
        if (!node)
            return 0;
        return node->height;
    }

    int getBalanceFactor(Node<T, U> *node)
    {
        if (!node)
            return 0;

        return getHeight(node->left) - getHeight(node->right);
    }

    Node<T, U> *rightRotation(Node<T, U> *node)
    {
        Node<T, U> *child = node->left;
        Node<T, U> *childRight = child->right;

        // Rotation
        child->right = node;
        node->left = childRight;

        // Update heights
        node->height = 1 + max(getHeight(node->left), getHeight(node->right));
        child->height = 1 + max(getHeight(child->left), getHeight(child->right));

        return child;
    }

    Node<T, U> *leftRotation(Node<T, U> *node)
    {
        Node<T, U> *child = node->right;
        Node<T, U> *childLeft = child->left;

        // Rotation
        child->left = node;
        node->right = childLeft;

        // Update heights
        node->height = 1 + max(getHeight(node->left), getHeight(node->right));
        child->height = 1 + max(getHeight(child->left), getHeight(child->right));

        return child;
    }

    Node<T, U> *insertNode(Node<T, U> *node, T key, U value)
    {
        // End
        if (!node)
            return new Node<T, U>(key, value);

        // Go Left
        if (key < node->key)
        {
            node->left = insertNode(node->left, key, value);
        }

        // Go Right
        else if (key > node->key)
        {
            node->right = insertNode(node->right, key, value);
        }

        // Same Key
        else
        {
            node->value.push_back(value);
            return node;
        }

        node->height = 1 + max(getHeight(node->left), getHeight(node->right));

        int balance = getBalanceFactor(node);

        // LL Case
        if (balance > 1 && key < node->left->key)
        {
            return rightRotation(node);
        }

        // LR Case
        if (balance > 1 && key > node->left->key)
        {
            node->left = leftRotation(node->left);
            return rightRotation(node);
        }

        // RR Case
        if (balance < -1 && key > node->right->key)
        {
            return leftRotation(node);
        }

        // RL Case
        if (balance < -1 && key < node->right->key)
        {
            node->right = rightRotation(node->right);
            return leftRotation(node);
        }

        return node;
    }

    void deleteTree(Node<T, U> *node)
    {
        if (!node)
            return;

        deleteTree(node->left);
        deleteTree(node->right);
        delete node;
    }

public:
    AVLTree()
    {
        root = NULL;
    }

    ~AVLTree()
    {
        deleteTree(root);
    }

    void insert(T key, U value)
    {
        root = insertNode(root, key, value);
    }

    Node<T, U> *getRoot()
    {
        return root;
    }

};

#endif