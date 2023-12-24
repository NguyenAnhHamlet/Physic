#ifndef __BVH__
#define __BVH__

#include<iostream>
#include<vector>

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
BVHNode* addNode(BVHNode* root, BVHNode* node);
BVHNodeArray convert(BVHNode* root);
BVHNode* SAH(const BVHNodeArray& arr);

#endif
