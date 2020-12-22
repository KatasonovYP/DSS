#include "Point.h"

namespace dss {


    std::istream& operator>>(std::istream& in, Point p)
    {
        return in >> p.x >> p.y;
    }


    std::ostream& operator<<(std::ostream& out, const Point& p)
    {
        return out << '(' << p.x << "; " << p.y << ")\n";
    }


    double dss::center_of_line(double x, Point p1, Point p2)
    {
        return (x - p1.x) * (p2.y - p1.y) / (p2.x - p1.x) + p1.y;
    }


}
