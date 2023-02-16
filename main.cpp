#include <DxLib.h>
#include<cstdlib>
#include<vector>
#include"Vector3.h"
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

	//���Ԍv���ɕK�v�ȃf�[�^
	long long startCount = 0;
	long long nowCount = 0;
	long long elapsedCount = 0;

	//��Ԃ��g���f�[�^
	//start->end��5[s]�Ŋ���������
	Vector3 start(-100.0f, 0, 0);		//�X�^�[�g�n�_(P1)
	Vector3 p2(-50.0f, 50.0f, +50.0f);	//����_(P2)
	Vector3 p3(+50.0f, -30.0f, -50.0f);	//����_(P3)
	Vector3 end(+100.0f, 0, 0);			//�G���h�n�_(P4)
	float maxTime = 5.0f;				//�S�̎���[s]
	float timeRate;						//��% ���Ԃ��i�񂾂�(��)

	//p1-p2-p3-p4��ʂ�X�v���C���Ȑ�
	std::vector<Vector3>points{ start,start,p2,p3,end,end };

	//p1����X�^�[�g
	size_t startIndex = 1;

	//���̈ʒu
	Vector3 position;

	//���s�O�Ɂ@�J�E���^�l���擾
	startCount = GetNowHiPerformanceCount();	//long long int�^�@64bit int

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
		//[R]�L�[�@�ŁA���X�^�[�g
		if (CheckHitKey(KEY_INPUT_R))
		{
			startCount = GetNowHiPerformanceCount();
			startIndex = 1;
		}

		//�o�ߎ���(elapsedTime[s])�̌v�Z
		nowCount = GetNowHiPerformanceCount();
		elapsedCount = nowCount - startCount;
		float elapsedTime = static_cast<float>(elapsedCount) / 1'000'000.0f;

		//�X�^�[�g�n�_		:start
		//�G���h�n�_		:end
		//�o�ߎ���			:elapsedTime[s]
		//�ړ������̗�(�o�ߎ���/�S�̎���):timeRate(%)

		//timeRate��1.0f�ȏ�ɂȂ�����,���̋�Ԃɐi��
		timeRate = elapsedTime / maxTime;
		//timeRate = min(elapsedTime / maxTime, 1.0f);

		if (timeRate >= 1.0f)
		{
			if (startIndex < points.size() - 3)
			{
				startIndex += 1;
				timeRate -= 1.0f;
				startCount = GetNowHiPerformanceCount();
			}
			else
			{
				timeRate = 1.0f;
			}
		}
		position = splinePosition(points,startIndex,timeRate);

		//2���x�W�G�Ȑ�
		/*Vector3 a = lerp(start, p1, timeRate);
		Vector3 b = lerp(p1, p2, timeRate);
		Vector3 c = lerp(p2, end, timeRate);
		Vector3 d = lerp(a, b, timeRate);
		Vector3 e = lerp(b, c, timeRate);*/
		//position = lerp(d, e, timeRate);



		// ��ʃN���A
		ClearDrawScreen();			//��ʂ�����
		// �`�揈��
		DrawAxis3D(500.0f);			//xyz���̕`��

		//���̕`��
		DrawSphere3D(position, 5.0f, 32, GetColor(255, 0, 0), GetColor(255, 255, 255), true);
		DrawSphere3D(start, 4.0f, 32, GetColor(0, 0, 255), GetColor(255, 255, 255), true);
		DrawSphere3D(p2, 4.0f, 32, GetColor(0, 255, 0), GetColor(255, 255, 255), true);
		DrawSphere3D(p3, 4.0f, 32, GetColor(0, 255, 255), GetColor(255, 255, 255), true);
		DrawSphere3D(end, 4.0f, 32, GetColor(255, 255, 0), GetColor(255, 255, 255), true);


		//DrawSphere3D(a, 2.0f, 32, GetColor(0, 255, 0), GetColor(255, 255, 255), true);
		//DrawSphere3D(b, 2.0f, 32, GetColor(0, 255, 0), GetColor(255, 255, 255), true);
		//DrawLine3D(a,b,GetColor(0, 255, 0));

		//
		DrawFormatString(0, 0, GetColor(255, 255, 255), "position(%6.1f,%6.1f,%6.1f)",
			position.x, position.y, position.z);

		DrawFormatString(0, 20, GetColor(255, 255, 255), "%7.3f[s]", elapsedTime);
		DrawFormatString(0, 40, GetColor(255, 255, 255), "[R]:Restart");

		DrawFormatString(0, 60, GetColor(255, 255, 255), "p0(%6.1f,%6.1f,%6.1f)",
			start.x, start.y, start.z);
		DrawFormatString(0, 80, GetColor(255, 255, 255), "p1(%6.1f,%6.1f,%6.1f)",
			p2.x, p2.y, p2.z);
		DrawFormatString(0, 100, GetColor(255, 255, 255), "p2(%6.1f,%6.1f,%6.1f)",
			p3.x, p3.y, p3.z);
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