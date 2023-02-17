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

	Quaternion& operator/=(float s);

public:
};
	//Quaternion& operator/=(const Quaternion& v,float s);
	//const Quaternion operator/(const Quaternion& v, float s);

