#ifndef __POINT_H__
#define __POINT_H__

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
		p2Vector2 r;

		r.x = x - v.x;
		r.y = y - v.y;

		return(r);
	}

	Point operator + (const Point &v) const
	{
		p2Vector2 r;

		r.x = x + v.x;
		r.y = y + v.y;

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

	bool operator ==(const Point& v) const
	{
		return (x == v.x && y == v.y);
	}

	bool operator !=(const Point& v) const
	{
		return (x != v.x || y != v.y);
	}

	// Otros m�todos
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

	T DistanceTo(const Point& v) const
	{
		T fx = x - v.x;
		T fy = y - v.y;

		return sqrt((fx*fx) + (fy*fy));
	}
};

typedef Point<int> iPoint;
typedef Point<float> fPoint;

#endif	// __POINT_H__