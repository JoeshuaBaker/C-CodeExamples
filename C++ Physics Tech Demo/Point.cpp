#include "Point.h"

Point::Point()
: x(0.0), y(0.0)
{
	
}

Point::Point(const double newx, const double newy)
: x(newx), y(newy)
{
	
}

Point::Point(const int newx, const int newy)
: x((double)newx), y((double)newy)
{
	
}

double Point::getX() const
{
	return x;
}

void Point::setX(const double newx)
{
	x = newx;
}

double Point::getY() const
{
	return y;
}

void Point::setY(const double newy)
{
	y = newy;
}

Point& Point::operator=(const Point& right)
{
	if(this == &right)
	{
		return *this;
	}
	
	x = right.getX();
	y = right.getY();
	return *this;
}

Point& Point::operator+=(const Point& right)
{
	setX(x + right.getX());
	setY(y + right.getY());
	return *this;
}

Point& Point::operator+(const Point& right) const
{
	Point p(x + right.getX(), y + right.getY());
	return p;
}