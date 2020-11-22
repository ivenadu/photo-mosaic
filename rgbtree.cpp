/**
 * @file rgbtree.cpp
 * Implementation of rgbtree class.
 */

#include <utility>
#include <algorithm>
#include <cassert>

#include "rgbtree.h"

using namespace std;

rgbtree::rgbtree(const map<RGBAPixel, string> &photos)
{
  for (const auto &x : photos)
  {
    tree.push_back(x.first);
  }

  make_tree(0, tree.size()-1, 0);
}

void rgbtree::make_tree(int start, int end, int depth)
{
  if(start >= end) return;

  int p = (start + end ) /2;
  quickSelect(start, end, p, depth);

  make_tree(start, p-1, (depth + 1) % 3);
  make_tree(p+1, end, (depth + 1) % 3);
}

RGBAPixel rgbtree::findNearestNeighbor(const RGBAPixel &query) const
{

  /* your code here! */
  return query;
}

bool rgbtree::smallerByDim(const RGBAPixel &first,
                           const RGBAPixel &second, int curDim) const
{

  /* your code here! */
}

/**
 * This function splits the trees[start..end] subarray at position start k
 */
void rgbtree::quickSelect(int start, int end, int k, int d)
{

  /* your code here! */
  if(start >= end) return;

  int p = partition(start, end, d);
  if ( p == k) return;

  if (k < p)
    quickSelect(start, p -1, k, d);
  if (k > p)
    quickSelect( p +1, end, k, d);
}

bool rgbtree::willswap(int i, int lo, int d)
{
  if (d == 0)
    return tree[i].r < tree[lo].r;
  if (d == 1)
    return tree[i].g < tree[lo].g;
  if (d == 2)
    return tree[i].b < tree[lo].b;
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
  int p = lo;
  for (int i = lo + 1; i <= hi; i++)
    if (willswap(i, lo, d))
    {
      p++;
      swap(tree[p], tree[i]);
    }
  swap(tree[lo], tree[p]);
  return p;
}

/**
 * Helper function to help determine if the nearest neighbor could 
 * be on the other side of the KD tree.
 */
int rgbtree::distToSplit(const RGBAPixel &query, const RGBAPixel &curr, int dimension) const
{

  /* your code here! */
}
