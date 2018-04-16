#include "Vector3D.h"


//default constructor
//zero vector
Vector3D::Vector3D():
	m_x(0.0),
	m_y(0.0),
	m_z(0.0)
{
}

//constructor taking sfml vector 3f
Vector3D::Vector3D(double x1, double y1, double z1):
	m_x(x1),
	m_y(y1),
	m_z(z1)
{
}

Vector3D::Vector3D(Vector3D & V)
{
	m_x = V.m_x;
	m_y = V.m_y;
	m_z = V.m_z;
}

//default deconstructor
Vector3D::~Vector3D()
{
}

std::string Vector3D::toString()
{
	char tmpbuf[256];
	sprintf_s(tmpbuf, "[%g,%g,%g}", m_x, m_y, m_z);
	return tmpbuf;
}

//returns a vector
double Vector3D::X()
{
	return m_x;
}

//returns a vector
double Vector3D::Y()
{
	return m_y;
}

//returns a vector
double Vector3D::Z()
{
	return m_z;
}

double Vector3D::length()
{
	return sqrt(m_x * m_x + m_y * m_y + m_z * m_z);
}

double Vector3D::lenghSquared()
{
	return (m_x * m_x + m_y * m_y + m_z * m_z);
}

void Vector3D::normalise()
{
	if (length() > 0.0)
	{
		double len = length();
		m_x /= len;
		m_y /= len;
		m_x /= len;
	}
}

Vector3D Vector3D::unit() 
{
	double x = 0.0;
	double y = 0.0;
	double z = 0.0;
	double vectorLength = length();
	if (vectorLength != 0)
	{
		x = m_x / vectorLength;
		y = m_y / vectorLength;
		y = m_z / vectorLength;
	}
	return Vector3D(x, y, z);
}

double Vector3D::angleBetween(Vector3D other)
{
	const double cosine = unit().dot(other.unit());
	const double angleInRadians = std::acos(cosine);
	const double angleInDegrees = angleInRadians * 180 / 3.14159265359;
	return angleInDegrees;
}

double Vector3D::dot(Vector3D other) const
{
	const double result = (m_x * other.m_x) + (m_y * other.m_y) + (m_z * other.m_z);
	return result;
}

Vector3D Vector3D::crossProduct(const Vector3D other) const
{
	return Vector3D((m_y * other.m_z) - (m_z*  other.m_y), (m_z * other.m_y) - (m_z * other.m_z), (m_x * other.m_y) - (m_y * other.m_x));
}

Vector3D Vector3D::operator+(const Vector3D V1)const
{
	return Vector3D(m_x + V1.m_x, m_y + V1.m_y, m_z + V1.m_z);
}

Vector3D Vector3D::operator-(const Vector3D V1)const
{
	return Vector3D(V1.m_x - m_x, V1.m_y - m_y, V1.m_z - m_z);
}

double Vector3D::operator*(const double k)const
{
	return double(m_x * k), (m_y * k), (m_z * k);
}

Vector3D Vector3D::operator*(const float k)const
{
	return Vector3D(m_x * k, m_y * k, m_z * k);
}

Vector3D Vector3D::operator*(const int k) const
{
	return Vector3D(m_x * k, m_y * k, m_z * k);
}

Vector3D Vector3D::operator^(const Vector3D V1)const
{
	return Vector3D(V1.m_y * m_z - V1.m_z * m_y, V1.m_z * m_x - V1.m_x * m_z, V1.m_x * m_y - V1.m_y * m_x);
}

double Vector3D::operator/(const double divisor)const
{
		if (divisor != 0)
		{
			return(m_x / divisor, m_y / divisor, m_z / divisor);
		}
		return double();
}

Vector3D Vector3D::operator/(const float divisor) const
{
	if (divisor != 0) // don't divide by zero
	{
		return Vector3D(m_x / divisor, m_y / divisor, m_z);
	}
	return Vector3D();
}

Vector3D Vector3D::operator/(const int divisor) const
{
	if (divisor != 0) // don't divide by zero
	{
		return Vector3D(m_x / divisor, m_y / divisor, m_z);
	}
	return Vector3D();
}

Vector3D Vector3D::operator+=(Vector3D V1)
{
	V1.m_x += m_x;
	V1.m_y += m_y;
	V1.m_z += m_z;
	return Vector3D(V1.m_x, V1.m_y, V1.m_z);
}

Vector3D Vector3D::operator-=(Vector3D V1)
{
	V1.m_x -= m_x;
	V1.m_y -= m_y;
	V1.m_z -= m_z;
	return Vector3D(V1.m_x, V1.m_y, V1.m_z);
}

bool Vector3D::operator==(const Vector3D V1) const
{
	return (m_x == V1.m_x && m_y == V1.m_y && m_z == V1.m_z);
}

bool Vector3D::operator!=(const Vector3D V1) const
{
	return !(m_x == V1.m_x && m_y == V1.m_y && m_z == V1.m_z);
}



