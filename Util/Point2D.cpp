#include "Point2D.h"
#include <cmath>

Point2D::Point2D(float x, float y)
{
	m_x=x;
	m_y=y;
}

Point2D::Point2D() : m_x(0), m_y(0)
{

}

Point2D& Point2D::operator+=(const Point2D& rhs)
{
	m_x+=rhs.GetX();
	m_y+=rhs.GetY();

	return *this;
}

Point2D& Point2D::operator-=(const Point2D& rhs)
{
	m_x-=rhs.GetX();
	m_y-=rhs.GetY();

	return *this;
}

Point2D& Point2D::operator*=(const float val)
{
	m_x*=val;
	m_y*=val;

	return *this;
}

Point2D& Point2D::operator/=(const float val)
{
	m_x/=val;
	m_y/=val;

	return *this;
}

Point2D& Point2D::operator*=(const int val)
{
	m_x*=val;
	m_y*=val;

	return *this;
}

Point2D& Point2D::operator/=(const int val)
{
	m_x/=val;
	m_y/=val;

	return *this;
}

Point2D Point2D::Normalize()
{
	float length=Length();
	if(length==0)
	{
		return Point2D(0, 0);
	}
	float x=m_x/length;
	float y=m_y/length;

	return Point2D(x, y);
}

float Point2D::Length()
{
	return sqrt(m_x*m_x + m_y*m_y);
}

float Point2D::GetX() const
{
	return m_x;
}

float Point2D::GetY() const
{
	return m_y;
}

void Point2D::SetX(float x)
{
	m_x=x;
}

void Point2D::SetY(float y)
{
	m_y=y;
}

Point2D operator+(const Point2D& lhs, const Point2D& rhs)
{
	Point2D r=rhs;
	r+=lhs;

	return r;
}

Point2D operator-(const Point2D& lhs, const Point2D& rhs)
{
	Point2D r=lhs;
	r-=rhs;

	return r;
}

Point2D operator*(const Point2D& lhs, const float val)
{
	Point2D r=lhs;
	r*=val;

	return r;
}

Point2D operator*(const Point2D& lhs, const int val)
{
	Point2D r=lhs;
	r*=val;

	return r;
}

Point2D operator/(const Point2D& lhs, const float val)
{
	Point2D r=lhs;
	r/=val;

	return r;
}

Point2D operator/(const Point2D& lhs, const int val)
{
	Point2D r=lhs;
	r/=val;

	return r;
}

Point2D operator*(const float val, const Point2D& rhs)
{
	Point2D r=rhs;
	r*=val;

	return r;
}

Point2D operator*(const int val, const Point2D& rhs)
{
	Point2D r=rhs;
	r*=val;

	return r;
}
