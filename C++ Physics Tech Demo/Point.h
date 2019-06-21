#ifndef POINT_H
#define	POINT_H

class Point
{
	private:
	double x;
	double y;

	public:
	Point();
	Point(const double newx, const double newy);
	Point(const int newx, const int newy);
	double getX() const;
	void setX(const double newx);
	double getY() const;
	void setY(const double newy);
	Point& operator=(const Point& right);
	Point& operator+=(const Point& right);
	Point& operator+(const Point& right) const;

};

#endif
