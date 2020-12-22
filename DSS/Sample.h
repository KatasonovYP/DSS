#pragma once

#include <algorithm>
#include <fstream>
#include <vector>

#include "Point.h"

namespace dss 
{


	class Sample 
	{
		private:
			int count_of_points;
			double left_limit, right_limit;
			double error;
			std::vector <Point> list;
		public:
			Sample(int _count_of_points, double _left_limit, double _right_limit, double _error);
			void generate();
			void approximate(double c, double step);
			void interpolate(double step);
			double nonparam(double x, double c);
			double calculate_error(double c);
			void print();
			void write();
			void read();
	};


}