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
BVHNode* SAH(const BVHNodeArray& arr);
BVHNodeArray convert(BVHNode* root);

#endif
