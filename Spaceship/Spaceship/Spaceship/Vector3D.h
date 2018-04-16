#pragma once
#include <iostream>

class Vector3D
{
public:
	Vector3D();
	Vector3D(double x1, double y1, double z1);
	Vector3D(Vector3D &V);
	~Vector3D();
	std::string toString();
	double X();
	double Y();
	double Z();

	double length();
	double lenghSquared();
	void normalise();
	Vector3D unit();
	double angleBetween(Vector3D other);
	double dot(Vector3D other) const;
	Vector3D crossProduct(const Vector3D other)const;

	 Vector3D operator+(const Vector3D V1)const;
	 Vector3D operator-(const Vector3D V1)const;
	 double operator *(const double k)const;
	 Vector3D operator*(const float k)const;
	 Vector3D operator*(const int k)const;
	 Vector3D operator^(const Vector3D V1)const;
	 double operator/(const double divisor)const;
	 Vector3D operator/(const float divisor)const;
	 Vector3D operator/(const int divisor)const;

	 Vector3D operator+=(Vector3D V1);
	 Vector3D operator-=(Vector3D V1);
	 bool operator==(const Vector3D V1)const;
	 bool operator!=(const Vector3D V1)const;

private:
	double m_x;
	double m_y;
	double m_z;
};

