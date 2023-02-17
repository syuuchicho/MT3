#pragma once
#include"Vector3.h"

class Quaternion
{
public:
	float x;
	float y;
	float z;
	float w;
	Vector3 v={x,y,z};
public://メンバー関数
	//コンストラクタ
	Quaternion();								
	Quaternion(float x, float y, float z,float w);		

	//Quaternionの積
	Quaternion Multiply(const Quaternion& lhs, const Quaternion& rhs);
	//単位Quaternionを返す
	Quaternion IdentityQuaternion();
	//共役
	Quaternion Conjugate(const Quaternion& quaternion);
	//Quaternionのnormを返す
	float Norm(const Quaternion& quaternion);
	//正規化したQuaternionを返す
	Quaternion Normalize(const Quaternion& quaternion);
	//逆Quaternionを返す
	Quaternion Inverse(const Quaternion& quaternion);

	Quaternion& operator/=(float s);

public:
};
	//Quaternion& operator/=(const Quaternion& v,float s);
	//const Quaternion operator/(const Quaternion& v, float s);

