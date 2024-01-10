#ifndef __BVH__
#define __BVH__

#include<iostream>
#include<vector>
#include "bounds.hpp"
#include <utility>

class Bounds2D; 
class point2D;
struct BVHNode;

typedef std::vector<BVHNode*> BVHNodeArray;

typedef struct BVHNode
{
    Bounds2D* _Bound2D;
    BVHNode *left, *right;
    BVHNodeArray arr;

} BVHNode;

typedef std::pair<float, std::pair<float, float>> cost_infos;


// create a BVH Node from a bound
BVHNode* initNode(Bounds2D* bound2D);

BVHNodeArray generateBVHNodeArr(const bounds_vector& b_vec);

BVHNodeArray sortBVHNodeArrX(BVHNodeArray arr);

BVHNodeArray sortBVHNodeArrY(BVHNodeArray arr);

void SAH(const BVHNodeArray& arr, unsigned int maxRetry,
            const Bounds2D& ttBound, float Tt, float Ti, BVHNode* root);

cost_infos getCost(const BVHNodeArray& arr, const Bounds2D& ttBound, 
                unsigned int pos, float Tt, float Ti, axis Axis);

cost_infos getMinCostXAxis(const BVHNodeArray& arr, const Bounds2D& ttBound,
                                        float Tt, float Ti);

cost_infos getMinCostYAxis(const BVHNodeArray& arr, const Bounds2D& ttBound,
                                        float Tt, float Ti);

cost_infos minCost( cost_infos cost_1, 
                    cost_infos cost_2 );

float getArea(const Bounds2D& b);

void DFS(BVHNode* root, float Tt, float Ti);

// get bound of all bound inside BVHNodeArray
Bounds2D getBoundAll(const BVHNodeArray& arr );

// upgrade bound of all nodes inside array
// run this function before DFS
void upgrade_Bound(BVHNodeArray arr);

#endif
