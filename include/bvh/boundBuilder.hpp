#include "bounds.hpp"


// Builder design pattern
// There is too many overloading constructor in Bounds2D which could 
// cause a lot of confusion whenever someone trying to create a new 
// object. 
// It also looks extremelly messy somehow. Builder pattern can resolve 
// this by allowing creating the object with customization. Eventhough 
// it requires some work, but if can help to clean up those messy 
// constructor, it worths the effort

// Since maybe in a long furture we will have different kind of bound,
// creating an interface here called BoundBuilder would help the user
// add new kind of bound builder. 

// Imagine if there is another function which receive the builder object 
// as argument, adding new kind of builder in here would requires either 
// open this old function to write a condition checking type or overriding 
// the function, both of them violating the open-close principle. Thus could 
// be prone to error. The interface BoundBuilder would help to resolve this. 
// Afterward, if the user desire to add new builder, they shall not have to 
// make change to the function but simply override the pure virtual function 
// in the concreate builder class

// interface
class BoundBuilder
{
public: 
    // TODO
    // should have written an interface point
    // anyway just stick with this first since 
    // there is only one type of point
    virtual BoundBuilder& buildPMin(point2D pMin) = 0;
    virtual BoundBuilder& buildPMax(point2D pMax) = 0;
    virtual BoundBuilder& buildCentroid(point2D centroid) = 0;
    virtual BoundBuilder& buildHeight(const float height) = 0;
    virtual BoundBuilder& buildWidth(const float width) = 0;
    virtual BoundBuilder& buildShape(SHAPE* shape) = 0;
    virtual BoundBuilder& buildNumOfPrimitives(const int numOfPrimitives) = 0;
};

// concreate class 
class Bound2DBuidler : public BoundBuilder
{
private:
    Bounds2D* bound2D;
public:
    Bound2DBuidler();
    BoundBuilder& buildPMin(point2D pMin);
    BoundBuilder& buildPMax(point2D pMax);
    BoundBuilder& buildCentroid(point2D centroid);
    BoundBuilder& buildHeight(float height);
    BoundBuilder& buildWidth(float width);
    BoundBuilder& buildShape(SHAPE* shape);
    BoundBuilder& buildNumOfPrimitives(int numOfPrimitives);
    
    // TODO
    // should have put this as override function, maybe do this later 
    // when there is a new Bound type
    Bounds2D* getResult();

};
