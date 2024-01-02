#include "BVH.hpp"
#include "particle.hpp"
#include "Bounds.hpp"
#include <vector>
#include "collision_hdl.hpp"
#include "timer.hpp"
#include <ctime>

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

BVHNodeArray sortBVHNodeArrX(BVHNodeArray arr)
{
    std::sort(arr.begin(), arr.end(), []( BVHNode* nodeA, BVHNode* nodeB)
    {
        return nodeA->_Bound2D->getCentroid().x < nodeB->_Bound2D->getCentroid().x;
    });
}

BVHNodeArray sortBVHNodeArrY(BVHNodeArray arr)
{
    std::sort(arr.begin(), arr.end(), []( BVHNode* nodeA, BVHNode* nodeB)
    {
        return nodeA->_Bound2D->getCentroid().y < nodeB->_Bound2D->getCentroid().y;
    });

    return arr;
}

BVHNode* SAH(const BVHNodeArray& arr, unsigned int maxRetry = 3,
            const Bounds2D& ttBound, float Tt, float Ti, BVHNode* root)
{
    if(!root) 
        return NULL;

    // if array has no element then the splitting is done
    if(arr.size() <= 0) 
        return NULL;

    std::pair<float, float> min_x = {-1 ,FLT_MAX};
    std::pair<float, float> min_y = {-1 ,FLT_MAX};

    // sorted the vector before doing any further
    // check for x axis first
    BVHNodeArray x_arr = sortBVHNodeArrX(arr);

    // go through each primitive and calculate the 
    // minimum cost 
    min_x = minCost(getMinCostXAxis(x_arr, ttBound, Tt, Ti ), min_x);

    // do the same with y axis
    BVHNodeArray y_arr = sortBVHNodeArrY(arr);
    min_y = minCost(getMinCostYAxis(y_arr, ttBound, Tt, Ti ), min_y);

    /**
     *  both have value FLT_MAX then the slit can not be done,
     *  there sure to be collision, so handle it until there 
     *  can be a splitting done
     * */ 
    if(min_x.second == FLT_MAX && min_y.second == FLT_MAX)
    { 
        try 
        {
            if(maxRetry > 0)
            {
                // loop through all bounds in this array and handle 
                // the collision
                for(int i = 0; i < arr.size() -1; i++)
                {
                    COLLISION_HDL::collisionHDL(arr[i]->_Bound2D->getShape(), 
                                                arr[i+1]->_Bound2D->getShape());
                }
                //delay for a short period of time
                TIMER::static_delay(100, clock());

                // after this continue with the splitting
                SAH(arr,maxRetry-1,ttBound,Tt,Ti,root);
            }
            else 
            {
                // if retry for maxRetry time but still failed, throw exception
                throw (maxRetry);
            }
        }
        catch (unsigned int maxRetry)
        {
            std::cout << "Have tried for " << maxRetry << " times but failed";
        }
    }

    std::pair<Bounds2D, Bounds2D> p_bounds;

    // if slitting using x axis is cheaper, use it
    if(min_x.second < min_y.second)
    {
        p_bounds = splitAxis(ttBound, min_x.second, -1 );
    }
    // if not splitting using y axis
    else 
    {
        p_bounds = splitAxis(ttBound, -1, min_y.second );
    }

    BVHNode* l_node = initNode(p_bounds.first);
    BVHNode* r_node = initNode(p_bounds.second);

    root->left = l_node;
    root->right = r_node;

    // recursively creating the tree

    // left first 
    SAH(BVHNodeArray l_arr(x_arr.begin(), x_arr.begin() + pos), maxRetry,p_bounds.first, Tt, Ti, l_node);

    // right after left is done
    SAH(BVHNodeArray l_arr(x_arr.begin(), x_arr.begin() + pos), maxRetry,p_bounds.first, Tt, Ti, r_node);
}

std::pair<float, float> getMinCostYAxis(const BVHNodeArray& arr, 
                                        const Bounds2D& ttBound,
                                        float Tt, float Ti)
{
    std::pair<float, float> min = {0, FLT_MAX};
    for( int pos = 0 ; pos < arr.size(); pos++ )
    {
        min = minCost(getCost(arr,ttBound,pos,Tt,Ti,axis::yAxis), min);
    }

    return min;
}

std::pair<float, float> getMinCostXAxis(const BVHNodeArray& arr, 
                                        const Bounds2D& ttBound,
                                        float Tt, float Ti)
{
    std::pair<float, float> min = {0, FLT_MAX};
    for( int pos = 0 ; pos < arr.size(); pos++ )
    {
        min = minCost(getCost(arr,ttBound,pos,Tt,Ti,axis::xAxis), min);
    }

    return min;
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
        if(pos == 0)
        {
            if(arr[pos]->_Bound2D->getpMax().x > arr[pos+1]->_Bound2D->getpMin().x)
                return FLT_MAX;
            
            splitPos = arr[pos]->_Bound2D->getpMax().x
        }
        else if(pos == arr.size() - 1)
        {
            if( arr[pos]->_Bound2D->getpMin().x < arr[pos-1]->_Bound2D->getpMax().x)
                return FLT_MAX;
            
            splitPos = arr[pos]->_Bound2D->getpMin().x;
        }

        // Make sure the splitting can be done
        else if(arr[pos]->_Bound2D->getpMin().x < arr[pos-1]->_Bound2D->getpMax().x &&
            arr[pos]->_Bound2D->getpMax().x > arr[pos+1]->_Bound2D->getpMin().x)
        {
            // check for potential collision
            return FLT_MAX;      
        }
        
        // In case centroid x value touchs left Bound
        else if(arr[pos]->_Bound2D->getpMin().x < arr[pos-1]->_Bound2D->getpMax().x)
        {
            splitPos = arr[pos]->_Bound2D->getpMax().x;
        }

        // In case centroid x value touchs right Bound
        else if(arr[pos]->_Bound2D->getpMax().x > arr[pos+1]->_Bound2D->getpMin().x)
        {
            splitPos = arr[pos]->_Bound2D->getpMin().x;
        }

        twoSide = splitAxis(ttBound ,splitPos);

    }
    else
    {
        if(pos == 0)
        {
            if(arr[pos]->_Bound2D->getpMax().y > arr[pos+1]->_Bound2D->getpMin().y)
                return FLT_MAX;
            
            splitPos = arr[pos]->_Bound2D->getpMax().y
        }
        else if(pos == arr.size() - 1)
        {
            if( arr[pos]->_Bound2D->getpMin().y < arr[pos-1]->_Bound2D->getpMax().y)
                return FLT_MAX;
            
            splitPos = arr[pos]->_Bound2D->getpMin().y;
        }

        // Make sure the splitting can be done
        else if(arr[pos]->_Bound2D->getpMin().y < arr[pos-1]->_Bound2D->getpMax().y &&
            arr[pos]->_Bound2D->getpMax().y > arr[pos+1]->_Bound2D->getpMin().y)
        {
            // check for potential collision
            return FLT_MAX;      
        }
        
        // In case edge x value touchs left Bound
        else if(arr[pos]->_Bound2D->getpMin().y < arr[pos-1]->_Bound2D->getpMax().y)
        {
            splitPos = arr[pos]->_Bound2D->getpMax().y;
        }

        // In case centroid x value touchs right Bound
        else if(arr[pos]->_Bound2D->getpMax().y > arr[pos+1]->_Bound2D->getpMin().y)
        {
            splitPos = arr[pos]->_Bound2D->getpMin().y;
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