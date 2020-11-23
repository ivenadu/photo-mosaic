/**
 * @file rgbtree.cpp
 * Implementation of rgbtree class.
 */

#include <utility>
#include <algorithm>
#include <cassert>

#include "rgbtree.h"

using namespace std;

int get_v(const RGBAPixel &pixel, int dim)
{
  switch (dim)
  {
  case 0:
    return pixel.r;
  case 1:
    return pixel.g;
  case 2:
    return pixel.b;
  }
  assert(false);
  return -1;
}

rgbtree::rgbtree(const map<RGBAPixel, string> &photos)
{
  for (const auto &x : photos)
  {
    tree.push_back(x.first);
  }

  make_tree(0, tree.size() - 1, 0);
}

void rgbtree::make_tree(int start, int end, int depth)
{
  if (start >= end)
    return;

  int p = (start + end) / 2;
  quickSelect(start, end, p, depth);

  make_tree(start, p - 1, (depth + 1) % 3);
  make_tree(p + 1, end, (depth + 1) % 3);
}

int dist(const RGBAPixel& p0, const RGBAPixel& p1)
{
  int sum = 0;
  int i = p0.r - p1.r;
  sum += i*i;

  i = p0.g - p1.g;
  sum += i*i;

  i = p0.b - p1.b;
  sum += i*i;

  return sum;
}

void rgbtree::find(const RGBAPixel& query, int start, int end, int dim, int& cur_best, int& cur_dist) const
{
  if(start > end) return;

  int p = (start + end )/2;
  if(tree[p] == query){
    cur_dist = 0;
    cur_best = p;
    return;
  }

  int d = dist(query, tree[p]);
  if(d < cur_dist){
    cur_dist = d;
    cur_best = p;
  }

  //if(distToSplit(query, tree[p], dim) < cur_best){
  if(cur_dist > 0)
    find(query, start, p-1, (dim + 1) % 3, cur_best, cur_dist);
  if(cur_dist > 0)
      find(query, p+1, end, (dim + 1) % 3, cur_best, cur_dist);
  //}
}
RGBAPixel rgbtree::findNearestNeighbor(const RGBAPixel &query) const
{
  int cur_best = -1;
  int cur_dist = 9999999;
  find(query, 0, tree.size()-1, 0, cur_best, cur_dist);
  assert(cur_best != -1);
  return tree[cur_best];
}

bool rgbtree::smallerByDim(const RGBAPixel &first,
                           const RGBAPixel &second, int curDim) const
{
  return get_v(first, curDim) < get_v(second, curDim);
}

/**
 * This function splits the trees[start..end] subarray at position start k
 */
void rgbtree::quickSelect(int start, int end, int k, int d)
{

  /* your code here! */
  if (start >= end)
    return;

  int p = partition(start, end, d);
  if (p == k)
    return;

  if (k < p)
    quickSelect(start, p - 1, k, d);
  if (k > p)
    quickSelect(p + 1, end, k, d);
}

bool rgbtree::willswap(int i, int lo, int d)
{
  return smallerByDim(tree[i], tree[lo], d);
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
  int i = get_v(query, dimension) - get_v(curr, dimension);
  return i * i;
}
