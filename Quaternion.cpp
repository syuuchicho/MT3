#include "Quaternion.h"
#include<cmath>		//sqrt

Quaternion::Quaternion()
	: x(0), y(0), z(0), w(0), v(0, 0, 0)
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
	temp.v *= -1;
	return temp;
}

float Quaternion::Norm(const Quaternion& quaternion)
{
	Quaternion temp = quaternion;

	return (float)sqrt(temp.x * temp.x + temp.y * temp.y + temp.z * temp.z + temp.w * temp.w);

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
	temp /= Norm(quaternion) * Norm(quaternion);

	return temp;
}

Quaternion Quaternion::MakeAxisAngle(const Vector3& axis, float angle)
{
	Quaternion temp;

	temp.v = axis * sinf(angle / 2.0f);
	temp.x = temp.v.x;
	temp.y = temp.v.y;
	temp.z = temp.v.z;
	temp.w = cosf(angle / 2.0f);
	return temp;
}

Vector3 Quaternion::RotateVector(const Vector3& vector, const Quaternion& quaternion)
{
	Quaternion r;
	r.x = vector.x;
	r.y = vector.y;
	r.z = vector.z;
	r.w = 0;
	r.v = vector;

	Quaternion q1 = Multiply(Multiply(quaternion, r), Inverse(quaternion));

	return q1.v;
}

Matrix4 Quaternion::MakeRotateMatrix(const Quaternion& quaternion)
{
	Matrix4 temp;
	temp.m[0][0] = quaternion.w * quaternion.w + quaternion.x * quaternion.x - quaternion.y * quaternion.y - quaternion.z * quaternion.z;
	temp.m[0][1] = (quaternion.x * quaternion.y + quaternion.w * quaternion.z) * 2;
	temp.m[0][2] = (quaternion.x * quaternion.z - quaternion.w * quaternion.y) * 2;
	temp.m[0][3] = 0;
	temp.m[1][0] = (quaternion.x * quaternion.y - quaternion.w * quaternion.z) * 2;
	temp.m[1][1] = quaternion.w * quaternion.w - quaternion.x * quaternion.x + quaternion.y * quaternion.y - quaternion.z * quaternion.z;
	temp.m[1][2] = (quaternion.y * quaternion.z + quaternion.w * quaternion.x) * 2;
	temp.m[1][3] = 0;
	temp.m[2][0] = (quaternion.x * quaternion.z + quaternion.w * quaternion.y) * 2;
	temp.m[2][1] = (quaternion.y * quaternion.z + quaternion.w * quaternion.x) * 2;
	temp.m[2][2] = quaternion.w * quaternion.w - quaternion.x * quaternion.x - quaternion.y * quaternion.y + quaternion.z * quaternion.z;
	temp.m[2][3] = 0;
	temp.m[3][0] = 0;
	temp.m[3][1] = 0;
	temp.m[3][2] = 0;
	temp.m[3][3] = 1;
	return temp;
}

Quaternion Quaternion::Slerp(const Quaternion& q0, const Quaternion& q1, float t)
{
	float dot = q0.x * q1.x + q0.y * q1.y + q0.z * q1.z + q0.w * q1.w;
	Quaternion temp = q0;
	Quaternion temp1 = q1;

	if (dot<0)
	{
		temp.x *= -1;
		temp.y *= -1;
		temp.z *= -1;
		temp.v *= -1;
		temp.w *= -1;
		dot = -dot;
	}
	//�Ȃ��p�����߂�
	float theta = std::acos(dot);
	//theta��sin���g���ĕ�ԌW��scale0,scale1�����߂�
	float scale0 = sin((1 - t) * theta) / sin(theta);
	float scale1 = sin(t * theta) / sin(theta);

	Quaternion ans = temp * scale0;
	Quaternion ans1 = temp1 * scale1;
	Quaternion ans2 = { ans.x + ans1.x,ans.y + ans1.y,ans.z + ans1.z,ans.w + ans1.w };

	return ans2;
}

Quaternion& Quaternion::operator/=(float s)
{
	w /= s;
	x /= s;
	y /= s;
	z /= s;

	return *this;
}

const Quaternion operator*(const Quaternion& q, float s)
{
	Quaternion temp(q);
	temp.x *= s;
	temp.y *= s;
	temp.z *= s;
	temp.w *= s;
	temp.v *= s;


	return temp;
}
