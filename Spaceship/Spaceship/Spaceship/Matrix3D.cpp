#include "Matrix3D.h"



Matrix3D::Matrix3D():
	m11{ 0.0 },
	m12{ 0.0 },
	m13{ 0.0 },
	m21{ 0.0 },
	m22{ 0.0 },
	m23{ 0.0 },
	m31{ 0.0 },
	m32{ 0.0 },
	m33{ 0.0 }
{
}

Matrix3D::Matrix3D(double a11, double a12, double a13, double a21, double a22, double a23, double a31, double a32, double a33):
	m11{ a11 },
	m12{ a12 },
	m13{ a13 },
	m21{ a21 },
	m22{ a22 },
	m23{ a23 },
	m31{ a31 },
	m32{ a32 },
	m33{ a33 }
{
}

Matrix3D::Matrix3D(Vector3D row1, Vector3D row2, Vector3D row3):
	m11{ row1.X() },
	m12{ row1.Y() },
	m13{ row1.Z() },
	m21{ row2.X() },
	m22{ row2.Y() },
	m23{ row2.Z() },
	m31{ row3.X() },
	m32{ row3.Y() },
	m33{ row3.Z() }
{
}


Matrix3D::~Matrix3D()
{
}

std::string Matrix3D::toString() const
{
	char tmpbuf[512];
	sprintf_s(tmpbuf, "{ [ %g, %g, %g ] [ %g, %g, %g ] [ %g, %g, %g ] }", m11, m12, m13, m21, m22, m23, m31, m32, m33);
	return tmpbuf;
}

Matrix3D Matrix3D::operator+(const Matrix3D other) const
{
	return Matrix3D(m11 + other.m11, m12 + other.m12, m13 + other.m13,
					m21 + other.m21, m22 + other.m22, m23 + other.m23,
					m31 + other.m31, m32 + other.m32, m33 + other.m33);
}

Matrix3D Matrix3D::operator-(const Matrix3D other) const
{
	return Matrix3D(m11 - other.m11, m12 - other.m12, m13 - other.m13,
					m21 - other.m21, m22 - other.m22, m23 - other.m23,
					m31 - other.m31, m32 - other.m32, m33 - other.m33);
}

//overload
Matrix3D Matrix3D::operator*(const Matrix3D other) const
{
	return Matrix3D((m11 * other.m11) + (m12 * other.m21) + (m13 * other.m31), (m11 * other.m12) + (m12 * other.m22) + (m13 * other.m32), (m11 * other.m13) + (m12 * other.m23) + (m13 * other.m33),
					(m21 * other.m11) + (m22 * other.m21) + (m23 * other.m31), (m21 * other.m12) + (m22 * other.m22) + (m23 * other.m32), (m21 * other.m13) + (m22 * other.m23) + (m23 * other.m33),
					(m31 * other.m11) + (m32 * other.m21) + (m33 * other.m31), (m31 * other.m12) + (m32 * other.m22) + (m33 * other.m32), (m31 * other.m13) + (m32 * other.m23) + (m33 * other.m33));
}

Vector3D Matrix3D::operator*(Vector3D vector) const
{
	return Vector3D(
		(m11 * vector.X()) + (m12 * vector.Y()) + (m13 * vector.Z()),
		(m21 * vector.X()) + (m22 * vector.Y()) + (m23 * vector.Z()),
		(m31 * vector.X()) + (m32 * vector.Y()) + (m33 * vector.Z()));
}

Matrix3D Matrix3D::operator*(const double scale) const
{
	return Matrix3D((m11 * scale) + (m12 * scale) + (m13 * scale), (m11 * scale) + (m12 * scale) + (m13 * scale), (m11 * scale) + (m12 * scale) + (m13 * scale),
					(m21 * scale) + (m22 * scale) + (m23 * scale), (m21 * scale) + (m22 * scale) + (m23 * scale), (m21 * scale) + (m22 * scale) + (m23 * scale),
					(m31 * scale) + (m32 * scale) + (m33 * scale), (m31 * scale) + (m32 * scale) + (m33 * scale), (m31 * scale) + (m32 * scale) + (m33 * scale));
}

Matrix3D Matrix3D::transpose() const
{
	return Matrix3D(m11, m21, m31,
					m12, m22, m32,
					m13, m23, m33);
}

double Matrix3D::determinant() const
{
	return m11*(m22*m33 - m32*m23) - m21*(m33*m12 - m32*m13) + m31*(m23*m12 - m22*m13);
}

Matrix3D Matrix3D::inverse() const
{
	double det = determinant();
	if (det == 0)
	{
		return Matrix3D(m11, m12, m13, m21, m22, m23, m31, m32, m33);
	}
	else
	{
		det = 1 / det;

		Matrix3D matrixA(m33*m22 - m32*m23, m32*m13 - m33*m12, m23*m12 - m22*m13,
						 m31*m23 - m33*m21, m33*m11 - m31*m13, m21*m13 - m23*m11,
						 m32*m21 - m31*m22, m31*m12 - m32*m11, m22*m11 - m21*m12);

		matrixA = matrixA * det;
		return(matrixA);
	}
}

Vector3D Matrix3D::row(int row) const
{
	switch (row)
	{
	case 1:
		return Vector3D(m11, m12, m13);
		break;

	case 2:
		return Vector3D(m21, m22, m23);
		break;

	case 3:
		return Vector3D(m31, m32, m33);
		break;

	default:
		return Vector3D(0.0f, 0.0f, 0.0f);
		break;
	}
}

Vector3D Matrix3D::column(int column) const
{
	switch (column)
	{
	case 1:
		return Vector3D(m11, m21, m31);
		break;

	case 2:
		return Vector3D(m12, m22, m32);
		break;

	case 3:
		return Vector3D(m13, m23, m33);
		break;
	default:
		return Vector3D(0.0f, 0.0f, 0.0f);
		break;
	}

}

bool Matrix3D::operator==(const Matrix3D other) const
{
	if (m11 == other.m11 && m12 == other.m12 && m13 == other.m13 &&
		m21 == other.m21 && m22 == other.m22 && m23 == other.m23 &&
		m31 == other.m31 && m32 == other.m32 && m33 == other.m33)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Matrix3D::operator!=(const Matrix3D other) const
{
	Matrix3D matrixA;
	if (m11 != other.m11 || m12 != other.m12 || m13 != other.m13 ||
		m21 != other.m21 || m22 != other.m22 || m23 != other.m23 ||
		m31 != other.m31 || m32 != other.m32 || m33 != other.m33)
	{
		return true;
	}
	else
	{
		return false;
	}
}

Matrix3D Matrix3D::rotationZ(double angleRadians)
{
	double degrees = 3.14 / 180 * angleRadians;

	Matrix3D answer = { cos(degrees), -sin(degrees), 0,
						   sin(degrees), cos(degrees), 0,
						   0, 0, 1 };
	return answer;
}

Matrix3D Matrix3D::rotationY(double angleRadians)
{
	double degrees = 3.14 / 180 * angleRadians ;

	Matrix3D answer = { cos(degrees), 0, sin(degrees),
						   0, 1, 0, -sin(degrees),
					       0, cos(degrees) };
	return answer;
}

Matrix3D Matrix3D::rotationX(double angleRadians)
{
	double degrees = 3.14 / 180.0f * angleRadians;

	Matrix3D answer = { 1, 0, 0,
						0, cos(degrees), -sin(degrees),
  					    0, sin(degrees), cos(degrees) };

	return answer;
}

Matrix3D Matrix3D::translation(Vector3D displacement)
{
	return Matrix3D(1, 0, 0,
				    0, 0, 0,
					displacement.X(), displacement.Y(), 1);
}

Matrix3D Matrix3D::scale(double scalingfactor)
{
	return Matrix3D(scalingfactor, 0, 0,
					0, scalingfactor, 0,
					0, 0, 1);
}
