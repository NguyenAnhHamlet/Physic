#ifndef __BVH__
#define __BVH__

#include<iostream>
#include<vector>
#include "bounds.hpp"
#include <utility>

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
BVHNode* SAH(BVHNodeArray& arr, unsigned int maxRetry = 3);
BVHNodeArray convert(BVHNode* root);
float getCost(const BVHNodeArray& arr, const Bounds2D& ttBound, 
                unsigned int pos, float Tt, float Ti, axis Axis);
float getMinCostXAxis(const BVHNodeArray& arr, const Bounds2D& ttBound
                    float Tt, float Ti);
float getMinCostYAxis(const BVHNodeArray& arr, const Bounds2D& ttBound
                    float Tt, float Ti);
float getArea(const Bounds2D& b);
float getSplitVal();

#endif
