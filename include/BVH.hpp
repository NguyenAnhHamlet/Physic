#ifndef __BVH__
#define __BVH__

#include<iostream>
#include<vector>
#include "bounds.hpp"

class Bounds2D; 
class point2D;


typedef struct BVHNode
{
    Bounds2D* _Bound2D;
    BVHNode* left, right;

} BVHNode;

typedef std::vector<BVHNode*> BVHNodeArray;

// create a BVH Node from a bound
BVHNode* initNode(Bounds2D* bound2D);
BVHNodeArray generateBVHNodeArr(const bounds_vector& b_vec);
void sortBVHNodeArrX(BVHNodeArray& arr);
void sortBVHNodeArrY(BVHNodeArray& arr);
BVHNode* SAH(const BVHNodeArray& arr, unsigned int maxRetry = 3);
BVHNodeArray convert(BVHNode* root);
float cost();

#endif
