#ifndef __POINT_H__
#define __POINT_H__

#include "Globals.h"

template<class T>

class Point
{
public:
	// Constructores
	Point() {}
	Point(T x, T y) : x(x), y(y) {}

	// Atributos
	T x;
	T y;

	// Operadores
	Point operator -(const Point &v) const
	{
		Point r;

		r.x = x - v.x;
		r.y = y - v.y;

		return(r);
	}

	Point operator + (const Point &v) const
	{
		Point r;

		r.x = x + v.x;
		r.y = y + v.y;

		return(r);
	}

	Point operator * (float f) const
	{
		Point r;

		r.x = f * x;
		r.y = f * y;

		return(r);
	}

	Point operator / (float f) const
	{
		Point r;

		r.x = f / x;
		r.y = f / y;

		return(r);
	}

	const Point& operator -=(const Point &v)
	{
		x -= v.x;
		y -= v.y;

		return(*this);
	}

	const Point& operator +=(const Point &v)
	{
		x += v.x;
		y += v.y;

		return(*this);
	}

	const Point& operator *= (float f)
	{
		x *= f;
		y *= f;

		return(*this);
	}

	const Point& operator /= (float f)
	{
		x /= f;
		y /= f;

		return(*this);
	}

	bool operator ==(const Point& v) const
	{
		return (x == v.x && y == v.y);
	}

	bool operator !=(const Point& v) const
	{
		return (x != v.x || y != v.y);
	}

	// Otros métodos
	bool IsZero() const
	{
		return (x == 0 && y == 0);
	}

	Point& SetToZero()
	{
		x = y = 0;
		return(*this);
	}

	Point& Negate()
	{
		x = -x;
		y = -y;

		return(*this);
	}

	Point& Rotate(float degrees)
	{
		double rads = degrees * 2 * M_PI / 360.0;

		double cosine = cos(rads);
		double sine = sin(rads);
		float tx = (float)(x * cosine - y * sine);
		float ty = (float)(x * sine + y * cosine);

		x = tx;
		y = ty;

		return(*this);
	}

	Point& Normalize()
	{
		T norm = Norm();

		x = x / norm;
		y = y / norm;

		return(*this);
	}

	Point ProjectionOn(const Point& v) const
	{
		T norm = v.Norm();
		T product = Dot(v);
		return v * (product / norm);
	}

	T Dot(const Point& v) const
	{
		return (x * v.x) + (y * v.y);
	}

	T PerpendicularDot(const Point& v) const
	{
		return (y * v.x) - (x * v.y);
	}

	T DistanceTo(const Point& v) const
	{
		T fx = x - v.x;
		T fy = y - v.y;

		return sqrt((fx*fx) + (fy*fy));
	}

	T Norm() const
	{
		return DistanceTo({ 0, 0 });
	}
};

typedef Point<int> iPoint;
typedef Point<float> fPoint;

#endif	// __POINT_H__