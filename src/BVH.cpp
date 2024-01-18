#include "BVH.hpp"
#include "particle.hpp"
#include "bounds.hpp"
#include <vector>
#include "collision_hdl.hpp"
#include "timer.hpp"
#include <ctime>

BVHNode* initNode(Bounds2D* bound2D)
{
    BVHNode* node = new BVHNode;
    node->_Bound2D = bound2D;

    // std::cout << "Value of bound in initNode: " << node->_Bound2D->getpMax().x << " " << node->_Bound2D->getpMax().y << '\n'; 

    return node;
}

BVHNodeArray generateBVHNodeArr(const bounds_vector& b_vec)
{
    BVHNodeArray res;
    BVHNode* node = NULL;
    for(int i=0; i < b_vec.size(); i++)
    {
        // std::cout << "Value of b in b_vec: " << b.getpMax().x << " " << b.getpMax().y << '\n'; 
        BVHNode* node = initNode(const_cast<Bounds2D*>(&(b_vec[i])));
        // std::cout << "Value of node: " << node->_Bound2D->getpMax().x << " " << node->_Bound2D->getpMax().y << 'n'; 
        res.push_back(node);
    }

    for( int i=0; i < res.size(); i++)
    {
        // std::cout << "Value of node: " << res[i]->_Bound2D->getpMax().x << " " << res[i]->_Bound2D->getpMax().y << 'n'; 
        // std::cout << node << '\n';
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

void SAH(const BVHNodeArray& arr, unsigned int maxRetry,
            const Bounds2D& ttBound, float Tt, float Ti, BVHNode* root)
{
    if(!root) 
        return ;

    // std::cout << arr.size() << '\n';

    // if array less then one element then the splitting is done
    if(arr.size() <= 1) 
        return ;

    cost_infos min_x = {-1 ,{ 0, FLT_MAX} };
    cost_infos min_y = {-1 ,{ 0, FLT_MAX} };

    // sorted the vector before doing any further
    // check for x axis first
    BVHNodeArray x_arr = sortBVHNodeArrX(arr);

    // for( auto node : x_arr)
    // {
    //     std::cout << node->_Bound2D->getShape()->getCenter()->x << " " << node->_Bound2D->getShape()->getCenter()->y <<   '\n';
    // }

    // go through each primitive and calculate the 
    // minimum cost 
    min_x = minCost(getMinCostXAxis(x_arr, ttBound, Tt, Ti ), min_x);


    // do the same with y axis
    BVHNodeArray y_arr = sortBVHNodeArrY(arr);
    min_y = minCost(getMinCostYAxis(y_arr, ttBound, Tt, Ti ), min_y);

    std::cout << min_x.second.second << min_y.second.second << '\n';
    

    /**
     *  both have value FLT_MAX then the slit can not be done,
     *  there sure to be collision, so handle it until there 
     *  can be a splitting done
     * */ 
    if(min_x.second.second == FLT_MAX && min_y.second.second == FLT_MAX)
    { 
        if(maxRetry > 0)
        {
            // loop through all bounds in this array and handle 
            // the collision
            for(int i = 0; i < arr.size()-1; i++)
            {
                // std::cout << "START" << '\n';
                // // std::cout << arr[i]->_Bound2D->getCentroid().x << " " << arr[i]->_Bound2D->getCentroid().y << '\n' ;
                // // std::cout << arr[i+1]->_Bound2D->getCentroid().x << " " << arr[i+1]->_Bound2D->getCentroid().y << '\n' ;

                // std::cout << arr[i]->_Bound2D->getpMin().x << " " << arr[i]->_Bound2D->getpMin().y << '\n' ;
                // std::cout << arr[i+1]->_Bound2D->getpMin().x << " " << arr[i+1]->_Bound2D->getpMin().y << '\n' ;

                // std::cout << arr[i]->_Bound2D->getpMax().x << " " << arr[i]->_Bound2D->getpMax().y << '\n' ;
                // std::cout << arr[i+1]->_Bound2D->getpMax().x << " " << arr[i+1]->_Bound2D->getpMax().y << '\n' ;

                // // if(arr[i]->_Bound2D->getShape() == NULL || arr[i+1]->_Bound2D->getShape() == NULL )
                // //     std::cout << "NULL" << '\n';
                // std::cout << "END" << '\n';

                COLLISION_HDL::collisionHDL(arr[i]->_Bound2D->getShape(), 
                                            arr[i+1]->_Bound2D->getShape());
            }

            // std::cout << "RUNNING" <<'\n';
            //delay for a short period of time
            TIMER::static_delay(100, clock());

            // after this continue with the splitting
            SAH(arr,maxRetry-1,ttBound,Tt,Ti,root);
        }
        else 
        {

            for(int i = 0; i < arr.size()-1; i++)
            {
                std::cout << "START" << '\n';
                // std::cout << arr[i]->_Bound2D->getCentroid().x << " " << arr[i]->_Bound2D->getCentroid().y << '\n' ;
                // std::cout << arr[i+1]->_Bound2D->getCentroid().x << " " << arr[i+1]->_Bound2D->getCentroid().y << '\n' ;

                std::cout << arr[i]->_Bound2D->getpMin().x << " " << arr[i]->_Bound2D->getpMin().y << '\n' ;
                std::cout << arr[i+1]->_Bound2D->getpMin().x << " " << arr[i+1]->_Bound2D->getpMin().y << '\n' ;

                std::cout << arr[i]->_Bound2D->getpMax().x << " " << arr[i]->_Bound2D->getpMax().y << '\n' ;
                std::cout << arr[i+1]->_Bound2D->getpMax().x << " " << arr[i+1]->_Bound2D->getpMax().y << '\n' ;

                // if(arr[i]->_Bound2D->getShape() == NULL || arr[i+1]->_Bound2D->getShape() == NULL )
                //     std::cout << "NULL" << '\n';
                std::cout << "END" << '\n';
            // if retry for maxRetry time but still failed, stop trying to 
            // split
            }
            return;
        }
        
    }

    // std::cout << "Value Min" << '\n';
    // std::cout << min_x.second.second<<'\n';
    // std::cout << min_y.second.second<<'\n';
    // std::cout << "END"<<'\n';

    std::pair<Bounds2D*, Bounds2D*> p_bounds;
    unsigned int pos = 0;

    // if slitting using x axis is cheaper, use it
    if(min_x.second.second < min_y.second.second)
    {
        pos = min_x.first;

        // check which edge
        if(min_x.second.first == x_arr[pos]->_Bound2D->getpMax().x)
            pos++;

        p_bounds = splitAxis(ttBound, min_x.second.first, -1 );
    }
    // if not splitting using y axis
    else 
    {
        pos = min_y.first;

        // check which edge
        if(min_x.second.first == x_arr[pos]->_Bound2D->getpMax().y)
            pos++;

        p_bounds = splitAxis(ttBound, -1, min_y.second.first );
    }

    root->left = initNode(p_bounds.first);
    root->right = initNode(p_bounds.second);

    root->left->_Bound2D->setNumPrimitives(pos +1);
    root->right->_Bound2D->setNumPrimitives(arr.size() - 1 - pos);

    // std::cout << p_bounds.first->getpMin().x <<'\n';
    // std::cout << p_bounds.first->getpMin().y <<'\n';
    // std::cout << p_bounds.first->getpMax().x <<'\n';
    // std::cout << p_bounds.first->getpMax().y <<'\n';
    // std::cout << "END"<<'\n';

    // recursively creating the tree

    // left first 
    SAH(root->left->arr = BVHNodeArray(x_arr.begin(), x_arr.begin() + pos), 
        maxRetry, *(p_bounds.first), Tt, Ti, root->left);

    // std::cout << "LEFT" << '\n';

    // right after left is done
    SAH(root->right->arr = BVHNodeArray(x_arr.begin() + pos, x_arr.end()), 
        maxRetry, *(p_bounds.second), Tt, Ti, root->right);

    // std::cout << "RIGHT" << '\n';
}

cost_infos getMinCostYAxis(const BVHNodeArray& arr, 
                                        const Bounds2D& ttBound,
                                        float Tt, float Ti)
{
    cost_infos min = {0, {0,FLT_MAX}};
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
    std::pair<float, std::pair<float, float>> min = {0, {0,FLT_MAX}};
    // std::cout << "START HERE" <<'\n';
    for( int pos = 0 ; pos < arr.size(); pos++ )
    {
        // std::cout << arr[0]->_Bound2D->getpMax().x << "\n";
        // std::cout << arr[0]->_Bound2D->getpMin().x << "\n";
        min = minCost(getCost(arr,ttBound,pos,Tt,Ti,axis::xAxis), min);
    }

    // std::cout << "END HERE" <<'\n';

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
    cost_infos res = {0, {0, FLT_MAX}};

    // Calculate intersection cost
    float intersectCost = arr.size() * Ti;

    // Calculate traversal cost
    float traversalCost = Tt;

    float splitPos;

    std::pair<Bounds2D*, Bounds2D*> twoSide;

    std::cout << arr.size() << '\n';

    // Split the bounding box along the x-axis
    if (Axis == axis::xAxis) 
    {
        // std::cout << "Value of Axis " << arr[pos]->_Bound2D->getpMax().x << '\n';
        if(pos == 0)
        {
            if(arr[pos]->_Bound2D->getpMax().x > arr[pos+1]->_Bound2D->getpMin().x)
                return res;
            
            splitPos = arr[pos]->_Bound2D->getpMax().x;
        }
        else if(pos == arr.size() - 1)
        {
            if( arr[pos]->_Bound2D->getpMin().x < arr[pos-1]->_Bound2D->getpMax().x)
                return res;
            
            splitPos = arr[pos]->_Bound2D->getpMin().x; 
        }

        // Make sure the splitting can be done
        else if(arr[pos]->_Bound2D->getpMin().x < arr[pos-1]->_Bound2D->getpMax().x &&
            arr[pos]->_Bound2D->getpMax().x > arr[pos+1]->_Bound2D->getpMin().x)
        {
            // check for potential collision
            return res;      
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

        std::cout << "END FUNCTION" << '\n';

        twoSide = splitAxis(ttBound ,splitPos);

    }
    else
    {
        if(pos == 0)
        {
            if(arr[pos]->_Bound2D->getpMax().y > arr[pos+1]->_Bound2D->getpMin().y)
                return res;
            
            splitPos = arr[pos]->_Bound2D->getpMax().y;
        }
        else if(pos == arr.size() - 1)
        {
            if( arr[pos]->_Bound2D->getpMin().y < arr[pos-1]->_Bound2D->getpMax().y)
                return res;
            
            splitPos = arr[pos]->_Bound2D->getpMin().y;
        }

        // Make sure the splitting can be done
        else if(arr[pos]->_Bound2D->getpMin().y < arr[pos-1]->_Bound2D->getpMax().y &&
            arr[pos]->_Bound2D->getpMax().y > arr[pos+1]->_Bound2D->getpMin().y)
        {
            // check for potential collision
            return res;      
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

    // std::cout << "END FUNCTION" << '\n';

    // Calculate surface areas
    float ttArea = getArea(ttBound);
    float Area_1 = getArea(*(twoSide.first));
    float Area_2 = getArea(*(twoSide.second));

    // Calculate probabilities
    float P1 = Area_1/ttArea;
    float P2 = Area_2/ttArea;

    // std::cout << "getCost" <<'\n';
    // std::cout << "Value of splitPos :" << splitPos <<'\n';

    // Calculate and return the SAH cost
    return res = {pos, {splitPos , traversalCost + intersectCost + P1*Area_1 + P2*Area_2}} ; 

}

cost_infos minCost( cost_infos cost_1, 
                    cost_infos cost_2 )
{
    return cost_1.second.second > cost_2.second.second ? cost_2 : cost_1;
}

void DFS(BVHNode* root, float Tt, float Ti)
{
    if(!root) return;

    // Before using DFS to traverse the tree and check for 
    // overlap, have to update the bounds
    
    // 1. update the bound of each node inside vector
    upgrade_Bound(root->left->arr);
    upgrade_Bound(root->right->arr);

    // 2. create the entire bound again using function getBoundAll
    // 3. update the bound of left and right 
    *(root->left->_Bound2D) = getBoundAll(root->left->arr);
    *(root->right->_Bound2D) = getBoundAll(root->right->arr);

    // if there is ovarlap between 2 bounds, then have to check 
    // for collision and perform SAH from this root downward
    
    if(doOverlap(*(root->left->_Bound2D), *(root->right->_Bound2D)))
    {
        COLLISION_HDL::collisionHDL(root->left->_Bound2D->getShape(),
                                    root->right->_Bound2D->getShape());

        //delay for a short period of time
        TIMER::static_delay(100, clock());

        // done handle the collision, perform SAH
        SAH(root->arr, 3, 
            getTotalBounds( *(root->left->_Bound2D), 
                            *(root->right->_Bound2D)),
            Tt, Ti, root);
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

void upgrade_Bound(BVHNodeArray arr)
{
    for(auto node: arr)
    {
        node->_Bound2D->update();
    }
}