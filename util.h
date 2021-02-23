#ifndef UTIL
#define UTIL

#include <typeinfo>

using namespace std;

enum Type { BST_Tag, AVL_Tag };

void printArr(int *arr, int len)
{
    cout << "[";
    for (int i = 0 ; i < len ; i ++)
    {
        cout << arr[i];
        if(i != len - 1)
            cout << ", ";
    }
    cout << "]" << endl;
}

template <typename T>
struct Node
{
    int value;
//    signed char balance;

    T *left;
    T *right;

    Type type;

    Node(Type _type) : value(0), left(nullptr), right(nullptr), type(_type) {}
//    ~Node()
//    {
//        delete left;
//        delete right;
//    }
};

template <typename T>
struct Tree
{
    T *root;

    Tree() : root(nullptr) {}

    ~Tree()
    {
        erase(root);
    }

    void empty()
    {
        erase(root);
		root = nullptr;
    }

    void erase(T *node)
    {
        if(node != nullptr)
        {
            erase(node->left);
            erase(node->right);

            delete node;
        }
    }

    bool search(int v)
    {
        T *prt = getParent(v, true);

        if(prt == nullptr || v != prt->value)
            return false;

        return true;
    }

    void printTree()
    {
        printTree(">", root, false);
    }

protected:

    T* getParent(int v, bool forSearch = false)
    {
        T *prt = nullptr;
        T *tmp = root;
        while (tmp != nullptr)
        {
            if (v < tmp->value)
            {
                prt = tmp;
                tmp = tmp->left;
            }
            else
            {
                prt = tmp;
                tmp = tmp->right;
            }

            if(forSearch && v == prt->value) break;
        }

        return prt;
    }

    signed char getHeight(const T *node)
    {
        signed char height = 0;
        if(node != nullptr)
        {
            signed char left_height = getHeight(node->left);
            signed char right_height = getHeight(node->right);

            height = left_height > right_height ? left_height + 1 : right_height + 1;
        }

        return height;
    }

    signed char getBalance(const T *node)
    {
        signed char left_height = getHeight(node->left);
        signed char right_height = getHeight(node->right);

        return right_height - left_height;
    }

private:
    void printTree(const string& prefix, const T* node, bool isLeft)
    {
        if( node != nullptr )
        {
            cout << prefix;

            cout << (isLeft ? "|--" : "'--" );

            cout << node->value;

            if(node->type == Type::AVL_Tag)
                cout << " (balance: " << (int)getBalance(node) << ")";

            cout << endl;

            printTree( prefix + (isLeft ? "|   " : "    "), node->left, true);
            printTree( prefix + (isLeft ? "|   " : "    "), node->right, false);
        }
    }
};


template <typename T>
void constructTree(T &tree, const int *arr, int n)
{
    for(int i = 0; i < n; ++i)
    {
        tree.insert(arr[i]);
    }
}

#endif // UTIL
