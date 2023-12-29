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
    minCostX = minCost(getMinCostXAxis(arr, ), minCostX);

    // do the same with y axis
    sortBVHNodeArrY(arr);
    minCostY = minCost(getMinCostYAxis(), minCostY);

}

BVHNodeArray convert(BVHNode* root)
{
    
}

std::pair<float, float> getMinCostYAxis(const BVHNodeArray& arr, const Bounds2D& ttBound,
                    float Tt, float Ti)
{
    float minCost = FLT_MAX;
    for( int pos = 0 ; pos < arr.size(); pos++ )
    {
        minCost = std::min(getCost(arr,ttBound,pos,Tt,Ti,axis::yAxis), minCost);
    }

    return minCost;
}

std::pair<float, float> getMinCostXAxis(const BVHNodeArray& arr, const Bounds2D& ttBound,
                    float Tt, float Ti)
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

    float splitPos;


    std::pair<Bounds2D, Bounds2D> twoSide;

    // Split the bounding box along the x-axis
    if (Axis == axis::xAxis) 
    {
        if(pos == 0 && arr[pos]->_Bound2D->getCentroid().x > arr[pos+1]->_Bound2D->getpMin().x)
        {
            splitPos = arr[pos+1]->_Bound2D->getpMin().x;
        }
        else if(pos == arr.size() - 1 && arr[pos]->_Bound2D->getCentroid().x < arr[pos-1]->_Bound2D->getpMax().x)
        {
            splitPos = arr[pos-1]->_Bound2D->getpMax().x;
        }

        // Make sure the splitting can be done
        else if(arr[pos]->_Bound2D->getCentroid().x < arr[pos-1]->_Bound2D->getpMax().x &&
            arr[pos]->_Bound2D->getCentroid().x > arr[pos+1]->_Bound2D->getpMax().x)
        {
            return FLT_MAX;      
        }
        
        // In case centroid x value touchs left Bound
        else if(arr[pos]->_Bound2D->getCentroid().x < arr[pos-1]->_Bound2D->getpMax().x)
        {
            splitPos = arr[pos-1]->_Bound2D->getpMax().x;
        }

        // In case centroid x value touchs right Bound
        else if(arr[pos]->_Bound2D->getCentroid().x > arr[pos+1]->_Bound2D->getpMax().x)
        {
            splitPos = arr[pos+1]->_Bound2D->getpMax().x;
        }

        twoSide = splitAxis(ttBound ,splitPos);

    }
    else
    {
        if(pos == 0 && arr[pos]->_Bound2D->getCentroid().y > arr[pos+1]->_Bound2D->getpMin().y)
        {
            splitPos = arr[pos+1]->_Bound2D->getpMin().y;
        }
        else if(pos == arr.size() - 1 && arr[pos]->_Bound2D->getCentroid().y < arr[pos-1]->_Bound2D->getpMax().y)
        {
            splitPos = arr[pos-1]->_Bound2D->getpMax().y;
        }

        // Make sure the splitting can be done
        else if(arr[pos]->_Bound2D->getCentroid().y < arr[pos-1]->_Bound2D->getpMax().y &&
            arr[pos]->_Bound2D->getCentroid().y > arr[pos+1]->_Bound2D->getpMax().y)
        {
            return FLT_MAX;      // define the value instead of using -1 like this
        }
        
        // In case centroid x value touchs left Bound
        else if(arr[pos]->_Bound2D->getCentroid().y < arr[pos-1]->_Bound2D->getpMax().y)
        {
            splitPos = arr[pos-1]->_Bound2D->getpMax().y;
        }

        // In case centroid x value touchs right Bound
        else if(arr[pos]->_Bound2D->getCentroid().y > arr[pos+1]->_Bound2D->getpMax().y)
        {
            splitPos = arr[pos+1]->_Bound2D->getpMax().y;
        }

        twoSide = splitAxis(ttBound, -1, splitPos);
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

std::pair<float, float> minCost(std::pair<float, float> cost_1, 
                                std::pair<float, float> cost_2 )
{
    return cost_1.second > cost_2.second ? cost_2 : cost_1;
}