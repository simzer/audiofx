#ifndef AUDIOFX_MATH_POINT_H
#define AUDIOFX_MATH_POINT_H

#include <algorithm>
#include <limits>
#include <cmath>

namespace afx
{
namespace math
{

struct Point
{
	double x;
	double y;

	Point() {
		x = y = 0.0;
	}

	static Point Invalid()
	{
		return Point(NAN, NAN);
	}

	static Point Max() {
		return Point(std::numeric_limits<double>::max(),
					 std::numeric_limits<double>::max());
	}

	static Point Min() {
		return Point(std::numeric_limits<double>::lowest(),
					 std::numeric_limits<double>::lowest());
	}

	Point(double x, double y)
		: x(x), y(y)
	{}

	static Point Polar(double radius, double angle)
	{
		return Point(radius * cos(angle),
					 radius * sin(angle));
	}

	static Point X(double x) {
		return Point(x, 0);
	}

	static Point Y(double y) {
		return Point(0, y);
	}

	Point operator*(double factor) const {
		return Point(x * factor, y * factor);
	}

	Point operator*=(double factor)
	{
		*this = *this * factor;
		return *this;
	}

	Point operator/(double divisor) const {
		if (divisor == 0) return Invalid();
		return Point(x / divisor, y / divisor);
	}

	Point operator/=(double divisor)
	{
		*this = *this / divisor;
		return *this;
	}

	Point operator+(const Point &other) const
	{
		return Point(x + other.x, y + other.y);
	}

	Point operator+=(const Point &other)
	{
		*this = *this + other;
		return *this;
	}

	Point operator-(const Point &other) const
	{
		return Point(x - other.x, y - other.y);
	}

	Point operator-=(const Point &other)
	{
		*this = *this - other;
		return *this;
	}

	Point operator*(const Point &other) const
	{
		return Point(x * other.x, y * other.y);
	}

	Point operator*=(const Point &other)
	{
		*this = *this * other;
		return *this;
	}

	Point operator/(const Point &other) const
	{
		if (other.x == 0 || other.y == 0) return Invalid();
		return Point(x / other.x, y / other.y);
	}

	Point operator/=(const Point &other)
	{
		*this = *this / other;
		return *this;
	}

	double operator^(const Point &p)
	{
		return x * p.y - y * p.x;
	}

	double abs() const {
		return sqrt(x * x + y * y);
	}

	double manhattan() const {
		return ::fabs(x) + ::fabs(y);
	}

	double chebyshev() const {
		return std::max(::fabs(x), ::fabs(y));
	}

	double sqrAbs() const {
		return x * x + y * y;
	}

	double angle() const {
		return atan2f((float)y, (float)x);
	}

	Point toPolar() const {
		return Point( abs(), angle() );
	}

	bool operator==(const Point &other) const {
		return x == other.x && y == other.y;
	}

	bool operator!=(const Point &other) const {
		return !(*this == other);
	}

	Point normalized() const
	{
		return *this / abs();
	}

	bool isNull() const { return x == 0 && y == 0; }

	bool isValid() const { return !std::isnan(x) && !std::isnan(y); }
};

static inline Point operator*(double factor, const Point &point)
{
	return point * factor;
}

}
}

#endif
