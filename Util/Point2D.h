#ifndef _H_POINT_2D_H
#define _H_POINT_2D_H


/// <summary>Class that represent a point on the 2D screen, the class is self explanable</summary>
class Point2D
{
public:
	Point2D(float x, float y);
	Point2D();

private:
	float m_x;
	float m_y;

public:
	float GetX() const;
	float GetY() const;
	void SetX(float x);
	void SetY(float y);

public:
	Point2D Normalize();
	float Length();

public:
	Point2D& operator+=(const Point2D& rhs);
	Point2D& operator-=(const Point2D& rhs);
	Point2D& operator*=(const float val);
	Point2D& operator/=(const float val);
	Point2D& operator*=(const int val);
	Point2D& operator/=(const int val);
};

Point2D operator+(const Point2D& lhs, const Point2D& rhs);
Point2D operator-(const Point2D& lhs, const Point2D& rhs);
Point2D operator*(const Point2D& lhs, const float val);
Point2D operator*(const Point2D& lhs, const int val);
Point2D operator/(const Point2D& lhs, const int val);
Point2D operator/(const Point2D& lhs, const float val);
Point2D operator*(const float val, const Point2D& rhs);
Point2D operator*(const int val, const Point2D& rhs);

#endif