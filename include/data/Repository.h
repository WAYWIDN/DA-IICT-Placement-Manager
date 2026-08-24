#ifndef REPOSITORY_H
#define REPOSITORY_H

#include <vector>
#include "../models/Record.h"
#include "../ds/AVLTree.h"
#include "../models/Query.h"

using namespace std;

class Repository
{
private:
    AVLTree<long long, Record> R1, R2, R3, R4, FR;

    void collectRecords(Node<long long, Record> *node, Query &q, vector<Record> &out)
    {
        if (!node)
            return;
        collectRecords(node->left, q, out);
        for (auto &r : node->value)
        {
            if (q.matches(r))
                out.push_back(r);
        }
        collectRecords(node->right, q, out);
    }

public:
    AVLTree<long long, Record> &GetR1()
    {
        return R1;
    }

    AVLTree<long long, Record> &GetR2()
    {
        return R2;
    }

    AVLTree<long long, Record> &GetR3()
    {
        return R3;
    }

    AVLTree<long long, Record> &GetR4()
    {
        return R4;
    }

    AVLTree<long long, Record> &GetFR()
    {
        return FR;
    }

    bool IsDataInserted()
    {
        return R1.getRoot() && R2.getRoot() && R3.getRoot() && R4.getRoot() && FR.getRoot();
    }

    void CollectRecords(AVLTree<long long, Record> &tree, Query &q, vector<Record> &out)
    {
        collectRecords(tree.getRoot(), q, out);
    }

    bool IsInData(Query &q)
    {
        vector<Record> records;
        collectRecords(R1.getRoot(), q, records);
        return records.size() ? true : false;
    }

    bool StudentExists(long long id)
    {
        Node<long long, Record> *node = R1.getRoot();
        while (node)
        {
            if (id == node->key)
                return true;
            else if (id < node->key)
                node = node->left;
            else
                node = node->right;
        }
        return false;
    }

    Record GetStudentInfo(long long id)
    {
        Node<long long, Record> *node = R1.getRoot();
        while (node)
        {
            if (id == node->key)
                return node->value[0];
            else if (id < node->key)
                node = node->left;
            else
                node = node->right;
        }
        return Record{};
    }

    int GetOfferCount(long long id)
    {
        Node<long long, Record> *node = FR.getRoot();
        while (node)
        {
            if (id == node->key)
                return (int)node->value.size();
            else if (id < node->key)
                node = node->left;
            else
                node = node->right;
        }
        return 0;
    }

    int CountInTree(AVLTree<long long, Record> &tree, Query &q)
    {
        vector<Record> records;
        collectRecords(tree.getRoot(), q, records);
        return records.size();
    }
};

#endif
