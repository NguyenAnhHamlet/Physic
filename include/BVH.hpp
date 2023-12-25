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

    bool operator>(BVHNode* _BVHNode)
    {
        if(_Bound2D->getCentroid() > _BVHNode->_Bound2D->getCentroid() ) 
            return true;

        if(_Bound2D->getCentroid() == _BVHNode->_Bound2D->getCentroid() 
            && _Bound2D->getCentroid() > _BVHNode->_Bound2D->getCentroid() ) 
                return true;

        return false;
    }

    bool operator<(const point2D& _point2D)
    {
        if(_Bound2D->getCentroid() < _BVHNode->_Bound2D->getCentroid() ) 
            return true;

        if(_Bound2D->getCentroid() == _BVHNode->_Bound2D->getCentroid() 
            && _Bound2D->getCentroid() < _BVHNode->_Bound2D->getCentroid() ) 
                return true;

        return false;
    }

    bool operator==(const point2D& _point2D)
    {
        if(_Bound2D->getCentroid() == _BVHNode->_Bound2D->getCentroid() ) 
            return true;

        return false;
    }

} BVHNode;

typedef std::vector<BVHNode*> BVHNodeArray;

// create a BVH Node from a bound
BVHNode* initNode(Bounds2D* bound2D);
BVHNodeArray generateBVHNodeArr(const bounds_vector& b_vec);
void sortBVHNodeArr(BVHNodeArray& arr);
BVHNode* SAH(const BVHNodeArray& arr);
BVHNodeArray convert(BVHNode* root);

#endif
