#ifndef BST
#define BST

#include "util.h"

using namespace std;

struct BSTNode : Node<BSTNode>
{
    BSTNode() : Node(Type::BST_Tag) {}
};

struct BSTree : Tree<BSTNode>
{
    BSTree() : Tree() {}

    void insert(int v)
    {
        BSTNode *prt = getParent(v);
        BSTNode *inserted = new BSTNode;
        inserted->value = v;

        if (prt == nullptr)
        {
            root = inserted;
        }
        else
        {
            if (v < prt->value)
            {
                prt->left = inserted;
            }
            else
            {
                prt->right = inserted;
            }
        }
    }

};

#endif // BST
