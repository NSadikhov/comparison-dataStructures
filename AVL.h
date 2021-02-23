#ifndef AVL
#define AVL

#include "util.h"

using namespace std;

enum RotationCase { left_left, left_right, right_left, right_right };

struct AVLNode : Node<AVLNode>
{
    AVLNode *parent;

    AVLNode() : parent(nullptr), Node(Type::AVL_Tag) {}

//    ~AVLNode() { delete parent; }
};

struct AVLTree : Tree<AVLNode>
{
    AVLTree() : Tree() {}

    void insert(int v)
    {
        AVLNode *prt = getParent(v);
        AVLNode *inserted = new AVLNode;
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
                inserted->parent = prt;
            }
            else
            {
                prt->right = inserted;
                inserted->parent = prt;
            }
            updateBF(prt);
        }
    }


    void updateBF(AVLNode* node)
    {
        if(node != nullptr)
        {
            signed char balance = getBalance(node);
            if(balance != 0)
            {

                if(balance == -2)
                {
                    signed char lc_balance = getBalance(node->left);

                    if(lc_balance == -1)
                        rotate(node->left, RotationCase::left_left);
                    else if(lc_balance == 1)
                        rotate(node->left, RotationCase::left_right);
                }
                else if(balance == 2)
                {
                    signed char rc_balance = getBalance(node->right);

                    if(rc_balance == -1)
                        rotate(node->right, RotationCase::right_left);
                    else if(rc_balance == 1)
                        rotate(node->right, RotationCase::right_right);
                }
                else
                {
                    updateBF(node->parent);
                }

            }
        }
    }


    void rotate(AVLNode* node, RotationCase _case)
    {
        AVLNode *tmp1 = node;
        AVLNode *tmp2 = node->parent;
        AVLNode *tmp3 = node->parent->parent;

        switch(_case)
        {
        case RotationCase::left_left:
            if(node->right != nullptr)
            {
                node->parent->left = tmp1->right;
                node->right->parent = tmp2;
            }
            else
            {
                node->parent->left = nullptr;
            }

            node->right = tmp2;
            node->right->parent = tmp1;


            if(root == tmp2)
            {
                node->parent = nullptr;
                root = tmp1;
            }
            else
            {
                node->parent = tmp3;

                if(tmp2->value < tmp3->value)
                    node->parent->left = tmp1;
                else
                    node->parent->right = tmp1;
            }

            updateBF(node);

            break;
        case RotationCase::left_right:

            node->parent->left = tmp1->right;
            node->right->parent = tmp2;

            node->parent = tmp1->right;

            if(node->right->left != nullptr)
            {
                node->right = node->right->left;
                node->right->parent = tmp1;
                node->parent->left = tmp1;
            }
            else
            {
                node->right->left = tmp1;
                node->right = nullptr;
            }


            rotate(node->parent, RotationCase::left_left);

            break;
        case RotationCase::right_left:

            node->parent->right = tmp1->left;
            node->left->parent = tmp2;

            node->parent = tmp1->left;

            if(node->left->right != nullptr)
            {
                node->left = node->left->right;
                node->left->parent = tmp1;
                node->parent->right = tmp1;
            }
            else
            {
                node->left->right = tmp1;
                node->left = nullptr;
            }

            rotate(node->parent, RotationCase::right_right);

            break;
        case RotationCase::right_right:

            if(node->left != nullptr)
            {
                node->parent->right = tmp1->left;
                node->left->parent = tmp2;
            }
            else
            {
                node->parent->right = nullptr;
            }

            node->left = tmp2;

            node->left->parent = tmp1;

            if(root == tmp2)
            {
                node->parent = nullptr;
                root = tmp1;
            }
            else
            {
                node->parent = tmp3;
                if(tmp2->value < tmp3->value)
                    node->parent->left = tmp1;
                else
                    node->parent->right = tmp1;
            }

            updateBF(node);

            break;
        default:
            break;
        }
    }

};

#endif // AVL
