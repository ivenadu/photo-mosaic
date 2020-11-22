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
return query;
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
while (start < end) {
  int p = partition(start, end, d);
  if (k < p) quickSelect(start, p, k, d);
  if (k > p) quickSelect(p, end, k, d);
}

}

bool rgbtree::willswap(int i, int lo, int d) {
  if (d == 0) return tree[i].r < tree[lo].r;
  if (d == 1) return tree[i].g < tree[lo].g;
  if (d == 2) return tree[i].b < tree[lo].b;
  return false;
}


/**
 * This method does a partition around pivot and will be used 
 * in quick select. It uses tree[lo] as the default pivot.
 * It returns the index of the pivot in the updated vector.
 * You will likely need to modify and complete this code.
 */
int rgbtree::partition(int lo, int hi, int d) //dimension: R-0, G-1, B-2
{
    // this is the partition code from HW2 it doesn't work!!
    int p = lo;
    for( int i=lo+1; i <= hi; i++ )
      if (willswap(i, lo, d)) {p++; swap(tree[p], tree[i]); }
      //if( tree[i] < tree[lo]) { p++; swap(tree[p], tree[i]); }
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

