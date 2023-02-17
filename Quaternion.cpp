#include "Quaternion.h"
#include<cmath>		//sqrt

Quaternion::Quaternion()
	: x(0), y(0), z(0), w(0),v(0,0,0)
{
}

Quaternion::Quaternion(float x, float y, float z, float w)
	: x(x), y(y), z(z), w(w)
{
}

Quaternion Quaternion::Multiply(const Quaternion& lhs, const Quaternion& rhs)
{
	Quaternion temp;
	temp.w = lhs.w * rhs.w - lhs.v.dot(rhs.v);
	temp.v = lhs.v.cross(rhs.v) + rhs.w * lhs.v + lhs.w * rhs.v;
	temp.x = temp.v.x;
	temp.y = temp.v.y;
	temp.z = temp.v.z;
	return temp;
}

Quaternion Quaternion::IdentityQuaternion()
{
	Quaternion temp;
	temp.w = 1;
	temp.v = { 0,0,0 };
	return temp;
}

Quaternion Quaternion::Conjugate(const Quaternion& quaternion)
{
	Quaternion temp;
	temp = quaternion;
	temp.x *= -1;
	temp.y *= -1;
	temp.z *= -1;
	return temp;
}

float Quaternion::Norm(const Quaternion& quaternion)
{
	Quaternion temp = quaternion;

	return (float)sqrt(temp.w * temp.w + temp.x * temp.x + temp.y * temp.y + temp.z * temp.z);
}

Quaternion Quaternion::Normalize(const Quaternion& quaternion)
{
	Quaternion temp;
	float len;
	temp = quaternion;
	len = Norm(quaternion);
	if (len != 0)
	{
		return temp /= len;
	}
	return temp;
}

Quaternion Quaternion::Inverse(const Quaternion& quaternion)
{
	Quaternion temp;
	temp = Conjugate(quaternion);
	temp /= Norm(quaternion)*Norm(quaternion);
	temp.x *= -1;
	temp.y *= -1;
	temp.z *= -1;

	return temp;
}

Quaternion& Quaternion::operator/=(float s)
{
	w /= s;
	x = v.x;
	x /= s;
	y = v.y;
	y /= s;
	z = v.z;
	z /= s;

	return *this;
}



