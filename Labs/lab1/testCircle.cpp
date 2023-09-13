#include "Circle.h"
#include "Circle.cpp"
#include <iostream>

int main()
{
    Circle c1;
    Circle c2(-10, 5, 2);
    Circle cCopy(c2);
    std::cout << "x value of circle 1 (default) is : " << c1.getX() << std::endl;
    std::cout << "y value of circle 1 (default) is : " << c1.getY() << std::endl;
    std::cout << "radius value of circle 1 (default) is : " << c1.getRadius() << std::endl;
    std::cout << "x value of circle 2 is : " << c2.getX() << std::endl;
    std::cout << "y value of circle 2 is : " << c2.getY() << std::endl;
    std::cout << "radius value of circle 2 is : " << c2.getRadius() << std::endl;
    std::cout << "x value of copied circle is : " << cCopy.getX() << std::endl;
    std::cout << "y value of copied circle is : " << cCopy.getY() << std::endl;
    std::cout << "radius value of copied circle is : " << cCopy.getRadius() << std::endl;
    int n;

    try
    {
        std::cout << "You can set a radius for the circle, Notice: this will change the radius of first circle " << std::endl;
        std::cin >> n;
        c1.setRadius(n);
    }
    catch (const std::invalid_argument &e)
    {
        std::cout << " Negative value for radius is not acceptable, You can try again " << std::endl;
        std::cin >> n;
        c1.setRadius(n);
    }
    std::cout << "radius value of circle 1 after change is : " << c1.getRadius() << std::endl;
    c1.translateXY(5, 9);
    std::cout << "x1 after translation : " << c1.getX() << " y1 after translation :  " << c1.getY() << std::endl;
    std::cout << "Area of circle 1 : " << c1.computeArea() << std::endl;
    std::cout << "Area of circle 2 : " << c2.computeArea() << std::endl;
    std::cout << "Area of copied circle  : " << cCopy.computeArea() << std::endl;
    c1.displayCircle();
    c2.displayCircle();
    cCopy.displayCircle();
    printf("Does circle 1 and circle 2 have intersection ?  %s\n", c1.intersect(c2) ? "true" : "false");
    int counting = Circle::getNubmerOfCurrentCircles();
    std::cout << "Number of circles:  " << counting << std::endl;
    int leftCounting = Circle::getNumberOfCirclesOnLeft();
    std::cout << "Number of circles on left: " << leftCounting << std::endl;

        return 0;
}