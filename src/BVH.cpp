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
    // sorted the vector before doing any further
    sortBVHNodeArr(arr);

    // go through each primitive and calculate the 
    // minimum cost of all axis, then take out 
    // one axis and value of that axis to split

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

float cost()
{

}
