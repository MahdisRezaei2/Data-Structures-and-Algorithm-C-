#ifndef CIRCLE_H
#define CIRCLE_H
#include <iostream>
#include "math.h"
#include <stdexcept>

// Description: this class models a circle

class Circle
{

private:
       int x;
       int y;
       double radius;
       static int count;
       static int countOnLeft;
       // static variables have a lifetime equal to the program's lifetime, but they still follow scoping rules based on where they are
       // declared.

public:
       // Default construtor : creates a circle of radius 10 at position (0,0)
       Circle();

       // Parameterized consructor : x, y and radius as parameters
       Circle(int x, int y, double radius);

       // Destructor
       ~Circle();

       // Copy constructor

       Circle(Circle &myCircle);

       // Getters that return info about the circle
       int getX() const;
       int getY() const;
       double getRadius() const;

       // Setters
       // changes the circle radius to r, if r is invalid it throws an exception to the caller function
       void setRadius(double r);

       // Moves the center of the circle  by x and y
       void translateXY(int x, int y);

       // computes and returns the circles area
       double computeArea();

       // displayes the circle's attributes
       void displayCircle();

       // checks the intersection
       bool intersect(Circle c2);

       // count number of total circles
       static int getNubmerOfCurrentCircles()
       {
              return count;
       }

       // Count number of circles on the left of y-axis
       static int getNumberOfCirclesOnLeft()
       {
              return countOnLeft;
       }
};

#endif