#include "Sample.h"

namespace dss 
{


	double func(double x)
	{
		return std::sin(x);
	}


	double smoothing(double x) 
	{
		double y;
		if (x * x <= 5) 
		{
			y = 0.335 - 0.067 * x * x;
		}
		else 
		{
			y = 0;
		}
		return y;
	}


	double random(double left_limit, double right_limit)
	{
		return (rand() / double(RAND_MAX) * (right_limit - left_limit) + left_limit);
	}


	Sample::Sample(int _count_of_points, double _left_limit, double _right_limit, double _error)
	{
		count_of_points = _count_of_points;
		left_limit = _left_limit;
		right_limit = _right_limit;
		error = _error;
	}


	void dss::Sample::generate()
	{
		for (int i = 0; i < count_of_points; i++) 
		{
			double xt = random(left_limit, right_limit);
			Point pt(xt, func(xt) + random(-error, error));
			list.push_back(pt);
		}
		sort(list.begin(), list.end(),
			[](const Point& a, const Point& b) -> bool 
			{
				return a.x < b.x;
			});
	}

	void Sample::approximate(double c, double step)
	{
		std::vector <Point> approx;
		double y;
		for (double x = left_limit; x <= right_limit; x += step) 
		{
			double sum1 = 0, sum2 = 0;
			for (const auto& it : list) 
			{
				sum1 += it.y * smoothing((x - it.x) / c);
				sum2 += smoothing((x - it.x) / c);
			}
			if (sum2 == 0) sum2 = 1;
			y = sum1 / sum2;
			approx.push_back(Point(x, y));
		}
		list = approx;
	}

	void Sample::interpolate(double step)
	{
		int left(0), right(1);
		double y;
		for (double x = left_limit; x <= right_limit; x += step) 
		{
			if (x < list[0].x) 
			{
				y = list[0].y;
			}
			else if (x > list[list.size() - 1].x) 
			{
				y = list[list.size() - 1].y;
			}
			else if (x == list[left].x) 
			{
				y = list[left].y;
			}
			else if (x == list[right].x) 
			{
				y = list[right].y;
			}
			else 
			{
				if (x > list[right].x) 
				{
					left++;
					right++;
				}
				y = center_of_line(x, list[left], list[right]);
			}
			printf("(%f; %f)\n", x, y);
		}
	}


	double Sample::nonparam(double x, double c)
	{
		double y = 0;
		double sum1(0), sum2(0);
		for (const auto& it : list)
		{
			sum2 += smoothing((x - it.x) / c);
			sum1 += it.y * sum2;
		}
		if (sum2 != 0) y = sum1 / sum2;
		return y;
	}


	double Sample::calculate_error(double c)
	{
		double E = 0;
		for (const auto& it : list)
		{
			double dy = (it.y - nonparam(it.x, c));
			E += dy * dy;
		}
		E = std::sqrt(E) / double(list.size());
		return E;
	}


	void dss::Sample::print()
	{
		for (const auto& point : list)
		{
			std::cout << point;
		}
	}


	void dss::Sample::write()
	{
		std::ofstream out("data_points.txt");
		for (auto& point : list) 
		{
			out << point.x << ' ' << point.y << '\n';
		}
	}


	void dss::Sample::read()
	{
		std::ifstream in("data_points.txt");
		double x, y;
		while (in >> x >> y)
		{
			Point p(x, y);
			list.push_back(p);
		}
		sort(list.begin(), list.end(),
			[](const Point& a, const Point& b) -> bool
			{
				return a.x < b.x;
			});
	}


}