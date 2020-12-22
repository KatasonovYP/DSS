#include <iostream>

#include "Sample.h"

int main()
{
    int count_of_points(40);
    double generate_error(0.05);
    double left_limit(1), right_limit(10);
    double step(0.1);
    double c(0.3);

    dss::Sample a(count_of_points, left_limit, right_limit, generate_error);
    a.generate();
    //a.write();
    //a.read();
    //a.interpolate(step);
    a.approximate(c, step);
    a.print();
    std::cout << a.calculate_error(c);
}
