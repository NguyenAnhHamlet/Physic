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

BVHNode* SAH(const BVHNodeArray& arr)
{

}

BVHNodeArray convert(BVHNode* root)
{
    
}
