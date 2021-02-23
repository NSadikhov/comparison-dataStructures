#include <iostream>
#include <chrono>
#include <algorithm>
//#include <vector>
#include <cassert>
#include <random>
#include <fstream>
#include <iomanip>

#include "windows.h"

#include "BST.h"
#include "AVL.h"
#include "util.h"

using namespace std;

constexpr int step = 100;
constexpr int maxlen = 10000;
constexpr int times = 100;

constexpr long long nanoseconds = 1000000000L;

template <typename T>
long long timeitInsert(T &_tree,const int *arr, int len)
{
    LARGE_INTEGER begin, end;
//    auto begin = chrono::steady_clock::now();
    QueryPerformanceCounter(&begin);
    constructTree<T>(_tree, arr, len);
    QueryPerformanceCounter(&end);
//    auto end = chrono::steady_clock::now();

    long long total = end.QuadPart - begin.QuadPart;
    return total;
}

template <typename T>
long long timeitISearch(T &_tree, int value)
{
    LARGE_INTEGER begin, end;
//    auto begin = chrono::steady_clock::now();
    QueryPerformanceCounter(&begin);
    _tree.search(value);
    QueryPerformanceCounter(&end);
//    auto end = chrono::steady_clock::now();

    long long total = end.QuadPart - begin.QuadPart;
    return total;
}

// Method from Professor
void swaps(int *arr, int n, mt19937 &gen)
{
    uniform_int_distribution<int> dist(0, n - 1);

    for (int i = 0; i < 2 * (int)sqrt(n); ++i)
    {
        int first = dist(gen);
        int second = first;

        while(second == first)
        {
            second = dist(gen);
        }
        swap(arr[first], arr[second]);
    }
}


int main()
{
    mt19937 gen(chrono::high_resolution_clock::now().time_since_epoch().count());

    ofstream file("results.csv");

    cout << "ArrSize,BST-ordered,BST-ordered-searchIn,BST-ordered-searchOut,";
    cout << "BST-slightly-ordered,BST-slightly-ordered-searchIn,BST-slightly-ordered-searchOut,";
    cout << "BST-shuffled,BST-shuffled-searchIn,BST-shuffled-searchOut,";
    cout << "AVL-ordered,AVL-ordered-searchIn,AVL-ordered-searchOut,";
    cout << "AVL-slightly-ordered,AVL-slightly-ordered-searchIn,AVL-slightly-ordered-searchOut,";
    cout << "AVL-shuffled,AVL-shuffled-searchIn,AVL-shuffled-searchOut" << endl;

    file << "ArrSize,BST-ordered,BST-ordered-searchIn,BST-ordered-searchOut,";
    file << "BST-slightly-ordered,BST-slightly-ordered-searchIn,BST-slightly-ordered-searchOut,";
    file << "BST-shuffled,BST-shuffled-searchIn,BST-shuffled-searchOut,";
    file << "AVL-ordered,AVL-ordered-searchIn,AVL-ordered-searchOut,";
    file << "AVL-slightly-ordered,AVL-slightly-ordered-searchIn,AVL-slightly-ordered-searchOut,";
    file << "AVL-shuffled,AVL-shuffled-searchIn,AVL-shuffled-searchOut" << endl;

    for(int len = step; len < maxlen; len += step)
    {

//        LARGE_INTEGER fr;
//        QueryPerformanceFrequency(&fr);
//        double freq = fr.QuadPart/1.0;

//      I set frequency to 1 to obtain lower values
        double freq = 1.0;

        // BST
        long long BTS_ordered = 0;
        long long BTS_slightly_ordered = 0;
        long long BTS_shuffled = 0;

        long long BTS_ordered_search_IN = 0;
        long long BTS_slightly_ordered_search_IN = 0;
        long long BTS_shuffled_search_IN = 0;

        long long BTS_ordered_search_OUT = 0;
        long long BTS_slightly_ordered_search_OUT = 0;
        long long BTS_shuffled_search_OUT = 0;

        // AVL
        long long AVL_ordered = 0;
        long long AVL_slightly_ordered = 0;
        long long AVL_shuffled = 0;

        long long AVL_ordered_search_IN = 0;
        long long AVL_slightly_ordered_search_IN = 0;
        long long AVL_shuffled_search_IN = 0;

        long long AVL_ordered_search_OUT = 0;
        long long AVL_slightly_ordered_search_OUT = 0;
        long long AVL_shuffled_search_OUT = 0;

        int *ordered = new int[len];
        for (int i = 0; i < len; i++)
        {
            ordered[i] = i;
        }

        int *slightlyOrdered = new int[len];
        int *shuffled = new int[len];


        uniform_int_distribution<int> dist(0, step - 1);


        BSTree _BSTtree;
        AVLTree _AVLtree;

        for(int t = 0; t < times; ++t)
        {

            int randomNum = dist(gen);

            copy(ordered, ordered + len, slightlyOrdered);
            swaps(slightlyOrdered, len, gen);

            copy(ordered, ordered + len, shuffled);
            shuffle(shuffled, shuffled + len, gen);

            //BST
            BTS_ordered += timeitInsert<BSTree>(_BSTtree, ordered, len);
            BTS_ordered_search_IN += timeitISearch<BSTree>(_BSTtree, randomNum);
            BTS_ordered_search_OUT += timeitISearch<BSTree>(_BSTtree, len);

            _BSTtree.empty();


            BTS_slightly_ordered += timeitInsert<BSTree>(_BSTtree, slightlyOrdered, len);
            BTS_slightly_ordered_search_IN += timeitISearch<BSTree>(_BSTtree, randomNum);
            BTS_slightly_ordered_search_OUT += timeitISearch<BSTree>(_BSTtree, len);

            _BSTtree.empty();


            BTS_shuffled += timeitInsert<BSTree>(_BSTtree, shuffled, len);
            BTS_shuffled_search_IN += timeitISearch<BSTree>(_BSTtree, randomNum);
            BTS_shuffled_search_OUT += timeitISearch<BSTree>(_BSTtree, len);

            _BSTtree.empty();

            // AVL
            AVL_ordered += timeitInsert<AVLTree>(_AVLtree, ordered, len);
            AVL_ordered_search_IN += timeitISearch<AVLTree>(_AVLtree, randomNum);
            AVL_ordered_search_OUT += timeitISearch<AVLTree>(_AVLtree, len);

            _AVLtree.empty();


            AVL_slightly_ordered += timeitInsert<AVLTree>(_AVLtree, slightlyOrdered, len);
            AVL_slightly_ordered_search_IN += timeitISearch<AVLTree>(_AVLtree, randomNum);
            AVL_slightly_ordered_search_OUT += timeitISearch<AVLTree>(_AVLtree, len);

            _AVLtree.empty();


            AVL_shuffled += timeitInsert<AVLTree>(_AVLtree, shuffled, len);
            AVL_shuffled_search_IN += timeitISearch<AVLTree>(_AVLtree, randomNum);
            AVL_shuffled_search_OUT += timeitISearch<AVLTree>(_AVLtree, len);

            _AVLtree.empty();

        }

        cout << len << "," << BTS_ordered / freq / times << "," << BTS_ordered_search_IN / freq / times << "," << BTS_ordered_search_OUT / freq / times << ",";
        cout << BTS_slightly_ordered / freq / times << "," << BTS_slightly_ordered_search_IN / freq / times << "," << BTS_slightly_ordered_search_OUT / freq / times << ",";
        cout << BTS_shuffled / freq / times << "," << BTS_shuffled_search_IN / freq / times << "," << BTS_shuffled_search_OUT / freq / times << ",";
        cout << AVL_ordered / freq / times << "," << AVL_ordered_search_IN / freq / times << "," << AVL_ordered_search_OUT / freq / times << ",";
        cout << AVL_slightly_ordered / freq / times << "," << AVL_slightly_ordered_search_IN / freq / times << "," << AVL_shuffled_search_OUT / freq / times << ",";
        cout << AVL_shuffled / freq / times << "," << AVL_shuffled_search_IN / freq / times << "," << AVL_shuffled_search_OUT / freq / times << endl;

        file << len << "," << BTS_ordered / freq / times << "," << BTS_ordered_search_IN / freq / times << "," << BTS_ordered_search_OUT / freq / times << ",";
        file << BTS_slightly_ordered / freq / times << "," << BTS_slightly_ordered_search_IN / freq / times << "," << BTS_slightly_ordered_search_OUT / freq / times << ",";
        file << BTS_shuffled / freq / times << "," << BTS_shuffled_search_IN / freq / times << "," << BTS_shuffled_search_OUT / freq / times << ",";
        file << AVL_ordered / freq / times << "," << AVL_ordered_search_IN / freq / times << "," << AVL_ordered_search_OUT / freq / times << ",";
        file << AVL_slightly_ordered / freq / times << "," << AVL_slightly_ordered_search_IN / freq / times << "," << AVL_shuffled_search_OUT / freq / times << ",";
        file << AVL_shuffled / freq / times << "," << AVL_shuffled_search_IN / freq / times << "," << AVL_shuffled_search_OUT / freq / times << endl;


//        printArr(ordered, len);
//        printArr(slightlyOrdered, len);
//        printArr(shuffled, len);


        delete [] ordered;
        delete [] slightlyOrdered;
        delete [] shuffled;
    }
    file.close();
}
