#pragma once
#include "Vector3D.h"
class Matrix3D
{
public:
	Matrix3D();
	Matrix3D(
		double a11, double a12, double a13,
		double a21, double a22, double a23,
		double a31, double a32, double a33);
	Matrix3D(Vector3D row1, Vector3D row2, Vector3D row3);
	~Matrix3D();

	std::string toString()const;
	Matrix3D operator +(const Matrix3D other) const;
	Matrix3D operator -(const Matrix3D other) const;
	Matrix3D operator *(const Matrix3D other) const;
	Vector3D operator *(Vector3D vector) const;
	Matrix3D operator *(const double scale) const;

	Matrix3D transpose() const;
	double determinant() const;
	Matrix3D inverse() const;

	Vector3D row(int row) const;
	Vector3D column(int column) const;

	bool operator ==(const Matrix3D other) const;
	bool operator !=(const Matrix3D other) const;
	static Matrix3D rotationZ(double angleRadians);
	static Matrix3D rotationY(double angleRadians);
	static Matrix3D rotationX(double angleRadians);

	static Matrix3D translation(Vector3D displacement); //2d translaion make sure z=1
	static Matrix3D scale(double scalingfactor);

private:
	double m11;
	double m12;
	double m13;
	double m21;
	double m22;
	double m23;
	double m31;
	double m32;
	double m33;
};

