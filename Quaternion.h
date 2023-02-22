#pragma once
#include"Vector3.h"
#include"Matrix4.h"


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


	//任意軸回転を表すQuaternionの生成
	Quaternion MakeAxisAngle(const Vector3& axis, float angle);
	//ベクトルをQuaternionで回転させた結果のベクトルを求める
	Vector3 RotateVector(const Vector3& vector, const Quaternion& quaternion);
	//Quaternionから回転行列を求める
	Matrix4 MakeRotateMatrix(const Quaternion& quaternion);

	//球面線形補間
	Quaternion Slerp(const Quaternion& q0, const Quaternion& q1, float t);

	//uからvへの回転を生成
	Quaternion DirectionToDirection(const Vector3& v, const Vector3& u);

public:
	Quaternion& operator/=(float s);
	//Quaternion operator*(const Quaternion& q);
};
	const Quaternion operator*(const Quaternion& q,float s);

