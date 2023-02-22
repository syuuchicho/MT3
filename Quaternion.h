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
public://�����o�[�֐�
	//�R���X�g���N�^
	Quaternion();								
	Quaternion(float x, float y, float z,float w);		

	//Quaternion�̐�
	Quaternion Multiply(const Quaternion& lhs, const Quaternion& rhs);
	//�P��Quaternion��Ԃ�
	Quaternion IdentityQuaternion();
	//����
	Quaternion Conjugate(const Quaternion& quaternion);
	//Quaternion��norm��Ԃ�
	float Norm(const Quaternion& quaternion);
	//���K������Quaternion��Ԃ�
	Quaternion Normalize(const Quaternion& quaternion);
	//�tQuaternion��Ԃ�
	Quaternion Inverse(const Quaternion& quaternion);


	//�C�ӎ���]��\��Quaternion�̐���
	Quaternion MakeAxisAngle(const Vector3& axis, float angle);
	//�x�N�g����Quaternion�ŉ�]���������ʂ̃x�N�g�������߂�
	Vector3 RotateVector(const Vector3& vector, const Quaternion& quaternion);
	//Quaternion�����]�s������߂�
	Matrix4 MakeRotateMatrix(const Quaternion& quaternion);

	//���ʐ��`���
	Quaternion Slerp(const Quaternion& q0, const Quaternion& q1, float t);

	//u����v�ւ̉�]�𐶐�
	Quaternion DirectionToDirection(const Vector3& v, const Vector3& u);

public:
	Quaternion& operator/=(float s);
	//Quaternion operator*(const Quaternion& q);
};
	const Quaternion operator*(const Quaternion& q,float s);

