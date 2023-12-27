#include "BVH.hpp"
#include "particle.hpp"
#include "Bounds.hpp"
#include <vector>

BVHNode* initNode(Bounds2D* bound2D)
{
    BVHNode* node = new BVHNode;
    node->_Bound2D = bound2D;

    return node;
}

BVHNodeArray generateBVHNodeArr(const bounds_vector& b_vec)
{
    BVHNodeArray res;
    for(auto it : b_vec)
    {
        res.push_back(initNode(it));
    }

    return res;
}

void sortBVHNodeArrX(BVHNodeArray& arr)
{
    std::sort(arr.begin(), arr.end(), []( BVHNode* nodeA, BVHNode* nodeB)
    {
        return nodeA->_Bound2D->getCentroid().x < nodeB->_Bound2D->getCentroid().x;
    });
}

void sortBVHNodeArrY(BVHNodeArray& arr)
{
    std::sort(arr.begin(), arr.end(), []( BVHNode* nodeA, BVHNode* nodeB)
    {
        return nodeA->_Bound2D->getCentroid().y < nodeB->_Bound2D->getCentroid().y;
    });
}

BVHNode* SAH(const BVHNodeArray& arr, unsigned int maxRetry = 3)
{
    float minCostX = FLT_MAX;
    float minCostY = FLT_MAX;

    // sorted the vector before doing any further
    // check for x axis first
    sortBVHNodeArrX(arr);

    // go through each primitive and calculate the 
    // minimum cost 
    minCostX = std::min(getMinCost(), minCostX);

    // do the same with y axis
    sortBVHNodeArrY(arr);
    minCostY = std::min(getMinCost(), minCostY);


    // if the splitting can not be done with one 
    // or more primitives, there will be a high 
    // chance that a collision happen, try to add 
    // some space to address the problem but after 
    // multiple try the problem seems to be persist,
    // check for the clossion and handle it. Should 
    // ignore it first and proceed with the splitting 
    // on other primitives, but in case there are only 
    // them be remaining, check for collison and handle 
    // it

    // create two node for 2 side 

    // recursively perform SAH with all of them


}

BVHNodeArray convert(BVHNode* root)
{
    
}

float getCost(const BVHNodeArray& arr, unsigned int index)
{

}

float getMinCostYAxis(const BVHNodeArray& arr, const Bounds2D& ttBound,
                                        float Tt, float Ti)
{
    float minCost = FLT_MAX;
    for( int pos = 0 ; pos < arr.size(); pos++ )
    {
        minCost = std::min(getCost(arr,ttBound,pos,Tt,Ti,axis::yAxis), minCost);
    }

    return minCost;
}

float getMinCostXAxis(const BVHNodeArray& arr)
{
    float minCost = FLT_MAX;
    for( int pos = 0 ; pos < arr.size(); pos++ )
    {
        minCost = std::min(getCost(arr,ttBound,pos,Tt,Ti,axis::xAxis), minCost);
    }

    return minCost;
}

float getArea(const Bounds2D& b)
{
    return (b.getPoints().second.x - b.getPoints.first.x) 
            * (b.getPoints().second.y - b.getPoints.first.y)
}

float getCost(const BVHNodeArray& arr, const Bounds2D& ttBound, 
             unsigned int pos, float Tt, float Ti, axis Axis)
{
    // Calculate intersection cost
    float intersectCost = arr.size() * Ti;

    // Calculate traversal cost
    float traversalCost = Tt;

    // Split the bounding box along the x-axis
    if (Axis == axis::xAxis) 
    {
        // Make sure the splitting can be done

        std::pair<Bounds2D, Bounds2D> twoSide = splitAxis(ttBound , 
                                                        arr[pos]->_Bound2D->getCentroid().x);

    }
    else
    {
        // Make sure the splitting can be done

        std::pair<Bounds2D, Bounds2D> twoSide = splitAxis(ttBound, -1, 
                                                        arr[pos]->_Bound2D->getCentroid().y);

    }

    // Calculate surface areas
    float ttArea = getArea(ttBound);
    float Area_1 = twoSide.first;
    float Area_2 = twoSide.second;

    // Calculate probabilities
    float P1 = Area_1/ttArea;
    float P2 = Area_2/ttArea;

    // Calculate and return the SAH cost
    return traversalCost + intersectCost + P1*Area_1 + P2*Area_2; 
    
}