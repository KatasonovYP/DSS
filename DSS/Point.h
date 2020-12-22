#pragma once

#include <cmath>
#include <iostream>

#include "Constants.h"

namespace dss 
{


    class Point 
    {
        public:
            double x, y;
            Point(double x, double y) : x(x), y(y) {}
            Point() = default;
            friend std::istream& operator>>(std::istream& in, Point p);
            friend std::ostream& operator<<(std::ostream& out, const Point& p);
    };


    double center_of_line(double x, Point p1, Point p2);


}