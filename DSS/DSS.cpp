#include <iostream>

#include "Sample.h"

int main()
{
    dss::Sample a(20, 1, 10, 0.05);
    //a.generate();
    //a.print();
    //a.write();
    a.read();
    a.approximate(0.01, 0.01);
}
