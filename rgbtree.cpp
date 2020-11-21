/**
 * @file rgbtree.cpp
 * Implementation of rgbtree class.
 */

#include <utility>
#include <algorithm>
#include "rgbtree.h"

using namespace std;

rgbtree::rgbtree(const map<RGBAPixel,string>& photos)
{

/* your code here! */

}

RGBAPixel rgbtree::findNearestNeighbor(const RGBAPixel & query) const
{

/* your code here! */

}

bool rgbtree::smallerByDim(const RGBAPixel & first,
                                const RGBAPixel & second, int curDim) const
{

/* your code here! */

}

/**
 * This function splits the trees[start..end] subarray at position start k
 */
void rgbtree::quickSelect(int start, int end, int k, int d)
{

/* your code here! */

}


/**
 * This method does a partition around pivot and will be used 
 * in quick select. It uses tree[lo] as the default pivot.
 * It returns the index of the pivot in the updated vector.
 * You will likely need to modify and complete this code.
 */
int rgbtree::partition(int lo, int hi, int d) 
{
    // this is the partition code from HW2 it doesn't work!!
    int p = lo;
    for( int i=lo+1; i <= hi; i++ )
      if( tree[i] < tree[lo] ) { p++; swap(tree[p], tree[i]); }
    swap(tree[lo], tree[p]);
    return p;

}


/**
 * Helper function to help determine if the nearest neighbor could 
 * be on the other side of the KD tree.
 */
int rgbtree::distToSplit(const RGBAPixel& query, const RGBAPixel& curr, int dimension) const
{

/* your code here! */

}

