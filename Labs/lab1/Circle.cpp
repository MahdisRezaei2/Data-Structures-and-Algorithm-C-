#include <iostream> //As we need to print data
#include "Circle.h" // the header file for the class- we need this
#include <cmath>
#include "math.h"
#include <stdexcept>
using namespace std;
// Initializing count and countleft variables
int Circle::count = 0;
int Circle::countOnLeft = 0;
// Default constructor

Circle::Circle()
{
    radius = 10.0;
    x = 0;
    y = 0;
    count++;
}

// Construtor with parameters for x,y  and radius

Circle::Circle(int x1, int y1, double radius1)
{
    x = x1;
    y = y1;
    if (radius1 > 0)
    {
        radius = radius1;
    }
    else
    {
        throw std::invalid_argument(" Negative value for radius is not acceptable");
    }
    count++;

    if (x < 0 && radius <= abs(x))
    {
        countOnLeft++;
    }
}

// Destructor

Circle::~Circle()
{
    count--;
    if (x < 0 && radius <= abs(x))
    {
        countOnLeft--;
    }
}

// Copy Constructor

Circle::Circle(Circle &myCircle)
{
    x = myCircle.x;
    y = myCircle.y;
    radius = myCircle.radius;
    count++;
    if (x < 0 && radius <= abs(x))
    {
        countOnLeft++;
    }
}
// Getters that return info about the circle

// getX

int Circle::getX() const
{
    return x;
}

// getY
int Circle::getY() const
{
    return y;
}

// getRadius
double Circle::getRadius() const
{
    return radius;
}

// translateXY: moves the centre of circle by x and y
void Circle::translateXY(int xNew, int yNew)
{
    x = x + xNew;
    y = y + yNew;
}

// setRadius: changes the circle's radius to r
void Circle::setRadius(double r)
{
    if (r > 0)
    {
        radius = r;
    }
    else
    {
        throw std::invalid_argument(" Negative value for radius is not acceptable");
    }
}

// computeArea: computes and returns the circle's area
double Circle::computeArea()
{
    return M_PI * pow(radius, 2);
}

// displayCircle: Displays the circle's attributes
void Circle::displayCircle()
{

    cout << "[x= " << x << " ,"
         << "y= " << y << " ,"
         << "radius= " << radius << " ]" << endl;
}

// Check to see if circles have intersection
bool Circle::intersect(Circle c2)
{

    double distance = sqrt(pow(c2.x - x, 2) + pow(c2.y - y, 2));
    if (distance <= c2.radius + radius)
    {
        return true;
    }
    else
    {
        return false;
    }
}


