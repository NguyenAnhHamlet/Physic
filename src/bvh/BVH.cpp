#include "bvh/BVH.hpp"
#include "base/particle.hpp"
#include "bvh/bounds.hpp"
#include <vector>
#include "collision/collision_hdl.hpp"
#include "common/timer.hpp"
#include <ctime>
#include <memory>

BVHNode* initNode(Bounds2D* bound2D)
{
    BVHNode* node = new BVHNode();
    node->left = NULL;
    node->right = NULL;
    node->_Bound2D = bound2D;
    node->isroot = false;
    node->isPrimitive = false;
    return node;
}

BVHNode* rootNode(Bounds2D* b2d)
{
    BVHNode* node = new BVHNode();
    node->left = NULL;
    node->right = NULL;
    node->_Bound2D = b2d;
    node->isroot = true;
    node->isPrimitive = false;
    return node;
}

BVHNode* priNode(Bounds2D* b2d)
{
    BVHNode* node = new BVHNode();
    node->left = NULL;
    node->right = NULL;
    node->_Bound2D = b2d;
    node->isroot = false;
    node->isPrimitive = true;
    return node;
}

BVHNodeArray generateBVHNodeArr(const bounds_vector& b_vec)
{
    BVHNodeArray res;
    BVHNode* node = NULL;
    for(int i=0; i < b_vec.size(); i++)
    {
        BVHNode* node = initNode(const_cast<Bounds2D*>(&(b_vec[i])));
        res.push_back(node);
    }

    return res;
}

BVHNodeArray sortBVHNodeArrX(BVHNodeArray arr)
{
    std::sort(arr.begin(), arr.end(), []( BVHNode* nodeA, BVHNode* nodeB)
    {
        return nodeA->_Bound2D->getCentroid().x < nodeB->_Bound2D->getCentroid().x;
    });

    return arr;
}

BVHNodeArray sortBVHNodeArrY(BVHNodeArray arr)
{
    std::sort(arr.begin(), arr.end(), []( BVHNode* nodeA, BVHNode* nodeB)
    {
        return nodeA->_Bound2D->getCentroid().y < nodeB->_Bound2D->getCentroid().y;
    });

    return arr;
}

// TODO
// Seperating the function into 2 type: first check and other check
// to reduce the condition checking in here
void SAH(BVHNodeArray arr, unsigned int maxRetry, const Bounds2D& ttBound,
        float Tt, float Ti, BVHNode* root, bool hdl_collision)
{
    if(!root) 
        return ;

    // if array less then zero element then the splitting is done
    if(arr.size() <= 0) 
        return ;

    // assign new bound
    if(root->isroot)
    {
        if(root->_Bound2D) delete root->_Bound2D;
        root->_Bound2D = new Bounds2D(ttBound);
    }

    // printf("arr size: %d\n", arr.size());
    // for(BVHNode* node : arr)
    // {
    //     printf("Value : %d && bounds : %f -- %f -- %f -- %f\n", node->_Bound2D->num, 
    //             node->_Bound2D->getpMin().x, node->_Bound2D->getpMin().y,
    //             node->_Bound2D->getpMax().x, node->_Bound2D->getpMax().y);
    // }
    // printf("\n\n");

    // if there is only one element, assign final node
    // if(arr.size() == 1 && root == arr[0])
    //     return;

    if(arr.size() == 1)
    {
        root->left = arr[0];
        return;
    }

    // if(arr.size() == 2 && root->right == NULL)

    cost_infos min_x = {-1 ,{ {0, 0}, FLT_MAX} };
    cost_infos min_y = {-1 ,{ {0, 0}, FLT_MAX} };

    // sorted the vector before doing any further
    // check for x axis first
    BVHNodeArray x_arr = sortBVHNodeArrX(arr);

    // go through each primitive and calculate the 
    // minimum cost 
    min_x = minCost(getMinCostXAxis(x_arr, ttBound, Tt, Ti ), min_x);

    BVHNodeArray y_arr = sortBVHNodeArrY(arr);
    min_y = minCost(getMinCostYAxis(y_arr, ttBound, Tt, Ti ), min_y);

    std::pair<Bounds2D*, Bounds2D*> p_bounds;
    unsigned int pos = 0;

    // printf("arr2 size: %d\n", arr.size());
    // for(BVHNode* node : arr)
    // {
    //     printf("Value : %d && bounds : %f -- %f -- %f -- %f\n", node->_Bound2D->num, 
    //             node->_Bound2D->getpMin().x, node->_Bound2D->getpMin().y,
    //             node->_Bound2D->getpMax().x, node->_Bound2D->getpMax().y);
    // }
    // printf("\n\n");

    /**
     *  both have value FLT_MAX then the slit can not be done,
     *  there sure to be collision, so handle it until there 
     *  can be a splitting done
     * */ 
    if(min_x.second.second == FLT_MAX && min_y.second.second == FLT_MAX)
    { 
        
        if(hdl_collision)
        {
            // handle the collision
            for(int i = 0; i < arr.size()-1; i++)
            {     
                COLLISION_HDL::collisionHDL(arr[i]->_Bound2D->getShape(), 
                                            arr[i+1]->_Bound2D->getShape());
            }
        }
    }

    // if slitting using x axis is cheaper, use it
    if(min_x.second.second < min_y.second.second)
    {
        pos = min_x.first +1;
        arr = x_arr;

        p_bounds = min_x.second.first;
    }
    // if not splitting using y axis
    else if(min_x.second.second > min_y.second.second)
    {
        pos = min_y.first +1;
        arr = y_arr;

        p_bounds = min_y.second.first;
    }
    else
    {
        // Such case can be handle by choosing  
        // the pos of first node for splitting
        // and creating a bound 

        pos = 1;
        arr = x_arr;

        p_bounds = splitAxis(ttBound, {arr[0]->_Bound2D->getpMax().x, arr[1]->_Bound2D->getpMin().x},
                             axis::xAxis);
    }

    // printf("arr2 size: %d\n", arr.size());
    // for(BVHNode* node : arr)
    // {
    //     printf("Value : %d && bounds : %f -- %f -- %f -- %f\n", node->_Bound2D->num, 
    //             node->_Bound2D->getpMin().x, node->_Bound2D->getpMin().y,
    //             node->_Bound2D->getpMax().x, node->_Bound2D->getpMax().y);
    // }
    // printf("\n\n");

    // have to deallocate the node first if there is one to prevent memory leak
    // make sure the node that is about to be delete is not primitive, delete such 
    // node (which not simply a container of other primitives) would cause issue
    // coredump  
    if(root->left && !root->left->isPrimitive)
    {
        delete root->left->_Bound2D;
        delete root->left;
    } 
    if(root->right && !root->right->isPrimitive) 
    {
        delete root->right->_Bound2D;
        delete root->right;
    }
    
    root->left = initNode(p_bounds.first);
    root->right = initNode(p_bounds.second);

    // printf("arr2 size: %d\n", arr.size());
    // for(BVHNode* node : arr)
    // {
    //     printf("Value : %d && bounds : %f -- %f -- %f -- %f\n", node->_Bound2D->num, 
    //             node->_Bound2D->getpMin().x, node->_Bound2D->getpMin().y,
    //             node->_Bound2D->getpMax().x, node->_Bound2D->getpMax().y);
    // }
    // printf("\n\n");

    // printf("node : %p\n", root);
    // printf("node->left: %p\n", root->left);

    root->left->_Bound2D->setNumPrimitives(pos +1);
    root->right->_Bound2D->setNumPrimitives(arr.size() - 1 - pos);

    // recursively creating the tree

    // left first 
    SAH(root->left->arr = BVHNodeArray(arr.begin(), arr.begin() + pos), 
        3, *(p_bounds.first), Tt, Ti, root->left,hdl_collision);

    // right after left is done
    SAH(root->right->arr = BVHNodeArray(arr.begin() + pos, arr.end()), 
        3, *(p_bounds.second), Tt, Ti, root->right,hdl_collision);

}

cost_infos getMinCostYAxis( const BVHNodeArray& arr, 
                            const Bounds2D& ttBound,
                            float Tt, float Ti)
{
    cost_infos min = {0, { {0 ,0},FLT_MAX}};
    for( int pos = 0 ; pos < arr.size(); pos++ )
    {
        min = minCost(getCost(arr,ttBound,pos,Tt,Ti,axis::yAxis), min);
    }

    return min;
}

cost_infos getMinCostXAxis(const BVHNodeArray& arr, 
                        const Bounds2D& ttBound,
                        float Tt, float Ti)
{
    cost_infos min = {0, { {0,0}, FLT_MAX}};
    for( int pos = 0 ; pos < arr.size(); pos++ )
    {
        min = minCost(getCost(arr,ttBound,pos,Tt,Ti,axis::xAxis), min);
    }

    return min;
}

float getArea(const Bounds2D& b)
{
    return (b.getPoints().second.x - b.getPoints().first.x) 
            * (b.getPoints().second.y - b.getPoints().first.y);
}

cost_infos getCost(const BVHNodeArray& arr, const Bounds2D& ttBound, 
             unsigned int pos, float Tt, float Ti, axis Axis)
{
    cost_infos res = {0, {{0, 0}, FLT_MAX}};

    // if this node at the end of arr, no need to split it with 
    // next node since there is no next node
    if(pos == arr.size() -1) return res;

    // Calculate intersection cost
    float intersectCost = arr.size() * Ti;

    // Calculate traversal cost
    float traversalCost = Tt;

    float splitPos1, splitPos2;

    std::pair<Bounds2D*, Bounds2D*> twoSide;

    // Split the bounding box along the x-axis
    if (Axis == axis::xAxis) 
    {
        if(pos != arr.size() - 1)
        {
            if(arr[pos]->_Bound2D->getpMax().x >= arr[pos+1]->_Bound2D->getpMin().x )
                return res;

            splitPos1 = arr[pos]->_Bound2D->getpMax().x;
            splitPos2 = arr[pos+1]->_Bound2D->getpMin().x;

            std::pair<float, float> p_split = {splitPos1, splitPos2};
            
            twoSide = splitAxis(ttBound, p_split, axis::xAxis );
        }
    }
    else
    {
        if(pos != arr.size() - 1)
        {
            if(arr[pos]->_Bound2D->getpMax().y >= arr[pos+1]->_Bound2D->getpMin().y )
                return res;

            splitPos1 = arr[pos]->_Bound2D->getpMax().y;
            splitPos2 = arr[pos+1]->_Bound2D->getpMin().y;

            std::pair<float, float> p_split = {splitPos1, splitPos2};
        
            twoSide = splitAxis(ttBound, p_split, axis::yAxis );
        }
    }

    // Calculate surface areas
    float ttArea = getArea(ttBound);
    float Area_1 = getArea(*(twoSide.first));
    float Area_2 = getArea(*(twoSide.second));

    // Calculate probabilities
    float P1 = Area_1/ttArea;
    float P2 = Area_2/ttArea;

    // deallocate 
    // delete twoSide.first;
    // delete twoSide.second;

    // Calculate and return the SAH cost
    return res = {pos, { twoSide , traversalCost + intersectCost + P1*Area_1 + P2*Area_2}} ; 

}

cost_infos minCost( cost_infos cost_1, 
                    cost_infos cost_2 )
{
    return cost_1.second.second > cost_2.second.second ? cost_2 : cost_1;
}

void upgradeBoundAll(BVHNode* root)
{
    if(!root || !root->_Bound2D) return;

    Bounds2D b;

    if(root->arr.size() > 0) 
        b = getBoundAll(root->arr);
    
    root->_Bound2D->setpMin(point2D(std::min(b.getpMin().x, root->_Bound2D->getpMin().x),
                                    std::min(b.getpMin().y, root->_Bound2D->getpMin().y)));
    root->_Bound2D->setpMax(point2D(std::max(b.getpMax().x, root->_Bound2D->getpMax().x),
                                    std::max(b.getpMax().y, root->_Bound2D->getpMax().y)));

    // left first
    upgradeBoundAll(root->left);

    // then right
    upgradeBoundAll(root->right);
}

void DFS(BVHNode* root, float Tt, float Ti)
{
    if(!root) return;

    if((root->left && root->right) && doOverlap(*(root->left->_Bound2D), *(root->right->_Bound2D)))
    {
        SAH(root->arr, 3, 
            getTotalBounds( *(root->left->_Bound2D), 
                            *(root->right->_Bound2D)),
            Tt, Ti, root,1);
    }

    // if there is none overlapping or the SAH is done performing
    // continue performing DFS till reach leaf

    // left first
    DFS(root->left, Tt, Ti);

    // right later
    DFS(root->right, Tt, Ti);
    
}

Bounds2D getBoundAll(const BVHNodeArray& arr )
{
    Bounds2D res;

    for(auto node : arr)
    {
        res = getTotalBounds(res, *(node->_Bound2D) );
    }

    return res;
}

void upgrade_Bound( BVHNode* root)
{
    for(auto node: root->arr)
    {
        node->_Bound2D->update();
    }
}

BVHNode* rootNode(Bounds2D* tt_b, const BVHNodeArray& arr  )
{
    BVHNode* root = new BVHNode;
    root->arr = arr;
    root->_Bound2D = tt_b;

    return root;
}

void addNode(BVHNode* root, BVHNode* newNode, float Tt, float Ti)
{
    // adding guard
    if(!root || !newNode) return ;

    // push node into root->arr since newNode is inside the bound
    root->arr.push_back(newNode);

    if(root->isroot && !root->left )
    {
        root->left = newNode;
        root->_Bound2D = getTotalBounds( root->left->_Bound2D, 
                                         root->left->_Bound2D);
        return;
    } 
    if(root->isroot && !root->right )
    {
        root->right = newNode;
        root->_Bound2D = getTotalBounds( root->right->_Bound2D, 
                                         root->left->_Bound2D);
        return;
    }

    if(isInBounds(root->_Bound2D, newNode->_Bound2D))
    {
        // newNode's Bound is within this node's bound, just need to 
        // check whether it is within left or right node 
        // keep going down until the second condition is met
        // printf("This case achieved\n");
        if(root->left && isInBounds(root->left->_Bound2D, newNode->_Bound2D))
            addNode(root->left, newNode, Tt, Ti);
        else if(root->right && isInBounds(root->right->_Bound2D, newNode->_Bound2D))
            addNode(root->right, newNode, Tt, Ti);
        else 
            SAH(root->arr, 3, 
            getTotalBounds( *(root->_Bound2D), 
                            *(newNode->_Bound2D)),
            Tt, Ti, root,1);

    }
    else
    {
        // doesn't belong to any bound on both left and right
        // side, need to perform SAH again to update BVH tree
        // here the second condition is met after trarvesing
        // which mean we can add the new node into appropriate
        // position within the BVH tree

        // printf("HERE");
        // Bounds2D boundAll = getBoundAll(root->arr);
        SAH(root->arr, 3, 
            getTotalBounds( *(root->_Bound2D), 
                            *(newNode->_Bound2D)),
            Tt, Ti, root,1);
    }
}
