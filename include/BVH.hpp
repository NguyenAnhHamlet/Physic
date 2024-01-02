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
    BVHNode *left, *right;

} BVHNode;

typedef std::vector<BVHNode*> BVHNodeArray;

// create a BVH Node from a bound
BVHNode* initNode(Bounds2D* bound2D);

BVHNodeArray generateBVHNodeArr(const bounds_vector& b_vec);

BVHNodeArray sortBVHNodeArrX(BVHNodeArray arr);

BVHNodeArray sortBVHNodeArrY(BVHNodeArray arr);

BVHNode* SAH(const BVHNodeArray& arr, unsigned int maxRetry = 3,
            const Bounds2D& ttBound, float Tt, float Ti, BVHNode* root);

float getCost(const BVHNodeArray& arr, const Bounds2D& ttBound, 
                unsigned int pos, float Tt, float Ti, axis Axis);

std::pair<float, float> getMinCostXAxis(const BVHNodeArray& arr, const Bounds2D& ttBound,
                                        float Tt, float Ti);

std::pair<float, float> getMinCostYAxis(const BVHNodeArray& arr, const Bounds2D& ttBound,
                                        float Tt, float Ti);

std::pair<float, float> minCost(std::pair<float, float> cost_1, 
                                std::pair<float, float> cost_2 );

float getArea(const Bounds2D& b);

#endif
