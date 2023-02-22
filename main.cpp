#include <DxLib.h>
#include<cstdlib>
#include<vector>
#include"Quaternion.h"
// �E�B���h�E�̃^�C�g���ɕ\�����镶����
const char TITLE[] = "xx2x_xx_�i�}�G: �^�C�g��";

// ��(Shpere)�̕`��
int DrawSphere3D(const Vector3& CenterPos, const float r, const int DivNum,
	const unsigned int DifColor, const unsigned int SpcColor, const int FillFlag);


//�J�����̈ʒu�Ǝp���̐ݒ�
int SetCameraPositionAndTargetAndUpVec(
	const Vector3& cameraPosition,				//�J�����̈ʒu
	const Vector3& cameraTarget,					//�J�����̒����_
	const Vector3& cameraUp						//�J�����̏�̌���
);

//�����̕`��
int DrawLine3D(const Vector3& Pos1, const Vector3& Pos2, const unsigned int Color);

//x,y,z ���̕`��
void DrawAxis3D(const float length);

//����_�̏W��(vector�R���e�i),��Ԃ����Ԃ̓Y���A���Ԍo�ߗ�
Vector3 splinePosition(const std::vector<Vector3>& points, size_t startIndex, float t);

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine,
	_In_ int nCmdShow) {
	// �E�B���h�E����
	const int WindowWidth = 1024;

	// �E�B���h�E�c��
	const int WindowHeight = 576;

	// �E�B���h�E���[�h�ɐݒ�
	ChangeWindowMode(TRUE);

	// �E�B���h�E�T�C�Y���蓮�ł͕ύX�������A
	// ���E�B���h�E�T�C�Y�ɍ��킹�Ċg��ł��Ȃ��悤�ɂ���
	SetWindowSizeChangeEnableFlag(FALSE, FALSE);

	// �^�C�g����ύX
	SetMainWindowText(TITLE);

	// ��ʃT�C�Y�̍ő�T�C�Y�A�J���[�r�b�g����ݒ�(���j�^�[�̉𑜓x�ɍ��킹��)
	SetGraphMode(WindowWidth, WindowHeight, 32);

	// ��ʃT�C�Y��ݒ�(�𑜓x�Ƃ̔䗦�Őݒ�)
	SetWindowSizeExtendRate(1.0);

	// ��ʂ̔w�i�F��ݒ肷��
	SetBackgroundColor(0, 0, 64);

	// DXlib�̏�����
	if (DxLib_Init() == -1) { return -1; }

	// (�_�u���o�b�t�@)�`���O���t�B�b�N�̈�͗��ʂ��w��
	SetDrawScreen(DX_SCREEN_BACK);

	//Z�o�b�t�@��L���ɂ���
	SetUseZBuffer3D(TRUE);
	//Z�o�b�t�@�ւ̏������݂�L���ɂ���
	SetWriteZBuffer3D(TRUE);


	//�O���b�v�ʁ@�߁@�@�@��
	SetCameraNearFar(1.0f, 1000.0f);//�J�����̗L���͈͂�ݒ�
	SetCameraScreenCenter(WindowWidth / 2.0f, WindowHeight / 2.0f);//��ʂ̒��S���J�����̒��S�ɍ��킹��
	SetCameraPositionAndTargetAndUpVec(
		Vector3(-20.0f, 20.0f, -200.0f),		//�J�����̈ʒu
		Vector3(0.0f, 0.0f, 0.0f),
		Vector3(0.0f, 1.0f, 0.0f));

	Quaternion* quaternion = nullptr;
	Vector3 direction1 = { 1.0f,0.0f,1.0f };
	Vector3 direction2 = { 1.0f,1.0f,0.0f };
	Quaternion dirToDir = quaternion->DirectionToDirection(direction1, direction2);



	// �ŐV�̃L�[�{�[�h���p
	char keys[256] = { 0 };

	// 1���[�v(�t���[��)�O�̃L�[�{�[�h���
	char oldkeys[256] = { 0 };

	// �Q�[�����[�v
	while (true) {
		// �ŐV�̃L�[�{�[�h��񂾂������̂�1�t���[���O�̃L�[�{�[�h���Ƃ��ĕۑ�
		for (int i = 0; i < 256; i++)
		{
			oldkeys[i] = keys[i];
		}
		// �ŐV�̃L�[�{�[�h�����擾
		GetHitKeyStateAll(keys);

		//---------  ��������v���O�������L�q  ----------//


		// �X�V����




		// ��ʃN���A
		ClearDrawScreen();			//��ʂ�����
		// �`�揈��
		DrawAxis3D(500.0f);			//xyz���̕`��
		DrawFormatString(0, 0, GetColor(255, 255, 255), "%f %f %f %f :dirToDir", dirToDir.x, dirToDir.y, dirToDir.z, dirToDir.w);


		//---------  �����܂łɃv���O�������L�q  ---------//
		// (�_�u���o�b�t�@)����
		ScreenFlip();

		// 20�~���b�ҋ@(�^��60FPS)
		WaitTimer(20);

		// Windows�V�X�e�����炭�������������
		if (ProcessMessage() == -1) {
			break;
		}

		// ESC�L�[�������ꂽ�烋�[�v���甲����
		if (CheckHitKey(KEY_INPUT_ESCAPE) == 1) {
			break;
		}
	}
	// Dx���C�u�����I������
	DxLib_End();

	// ����I��
	return 0;
}

//���̕`��
int DrawSphere3D(const Vector3& CenterPos, const float r, const int DivNum,
	const unsigned int DifColor, const unsigned int SpcColor, const int FillFlag) {
	VECTOR centerPos = { CenterPos.x, CenterPos.y, CenterPos.z };		//�\���́@�������q���X�g

	return DrawSphere3D(centerPos, r, DivNum, DifColor, SpcColor, FillFlag);
}

//x��,y��,z���̕`��
void DrawAxis3D(const float length)
{
	DrawLine3D(Vector3(-length, 0.0f, 0.0f), Vector3(+length, 0.0f, 0.0f), GetColor(255, 0, 0));	//x��
	DrawLine3D(Vector3(0.0f, -length, 0.0f), Vector3(0.0f, +length, 0.0f), GetColor(0, 255, 0));	//y��
	DrawLine3D(Vector3(0.0f, 0.0f, -length), Vector3(0.0f, 0.0f, +length), GetColor(0, 0, 255));	//z��
}

//�����̕`��
int DrawLine3D(const Vector3& Pos1, const Vector3& Pos2, const unsigned int Color) {
	VECTOR p1 = { Pos1.x, Pos1.y, Pos1.z };			//�\���́@�������q���X�g
	VECTOR p2 = { Pos2.x, Pos2.y, Pos2.z };			//�\���́@�������q���X�g

	return DrawLine3D(p1, p2, Color);
}

//�J�����̈ʒu�Ǝp���̐ݒ�
int SetCameraPositionAndTargetAndUpVec(
	const Vector3& cameraPosition,				//�J�����̈ʒu
	const Vector3& cameraTarget,					//�J�����̒����_
	const Vector3& cameraUp						//�J�����̏�̌���
) {
	VECTOR position = { cameraPosition.x, cameraPosition.y, cameraPosition.z };
	VECTOR target = { cameraTarget.x, cameraTarget.y, cameraTarget.z };
	VECTOR up = { cameraUp.x, cameraUp.y, cameraUp.z };

	return SetCameraPositionAndTargetAndUpVec(position, target, up);
}

//n+2�̓_�g���āAP1~Pn�̊Ԃ��A�X�v���C����Ԃ���
//(P0)-P1-P2-...-Pn-(Pn+1)
Vector3 splinePosition(const std::vector<Vector3>& points, size_t startIndex, float t)
{
	//��Ԃ��ׂ��_�̐�
	size_t n = points.size() - 2;

	if (startIndex > n)return points[n];	//Pn�̒l��Ԃ�
	if (startIndex < 1)return points[1];	//P1�̒l��Ԃ�

	//P0~p3�̐���_���擾����@P1~p2���Ԃ���
	Vector3 p0 = points[startIndex - 1];
	Vector3 p1 = points[startIndex];
	Vector3 p2 = points[startIndex + 1];
	Vector3 p3 = points[startIndex + 2];

	//Catmull-Rom�̎��ɂ����
	Vector3 position = 0.5 * (2 * p1 + (-p0 + p2) * t +
		(2 * p0 - 5 * p1 + 4 * p2 - p3) * t * t +
		(-p0 + 3 * p1 - 3 * p2 + p3) * t * t * t);

	return position;
}