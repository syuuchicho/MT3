#include <DxLib.h>
#include<cstdlib>
#include<vector>
#include"Quaternion.h"
// ウィンドウのタイトルに表示する文字列
const char TITLE[] = "xx2x_xx_ナマエ: タイトル";

// 球(Shpere)の描画
int DrawSphere3D(const Vector3& CenterPos, const float r, const int DivNum,
	const unsigned int DifColor, const unsigned int SpcColor, const int FillFlag);


//カメラの位置と姿勢の設定
int SetCameraPositionAndTargetAndUpVec(
	const Vector3& cameraPosition,				//カメラの位置
	const Vector3& cameraTarget,					//カメラの注視点
	const Vector3& cameraUp						//カメラの上の向き
);

//線分の描画
int DrawLine3D(const Vector3& Pos1, const Vector3& Pos2, const unsigned int Color);

//x,y,z 軸の描画
void DrawAxis3D(const float length);

//制御点の集合(vectorコンテナ),補間する区間の添字、時間経過率
Vector3 splinePosition(const std::vector<Vector3>& points, size_t startIndex, float t);

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine,
	_In_ int nCmdShow) {
	// ウィンドウ横幅
	const int WindowWidth = 1024;

	// ウィンドウ縦幅
	const int WindowHeight = 576;

	// ウィンドウモードに設定
	ChangeWindowMode(TRUE);

	// ウィンドウサイズを手動では変更させず、
	// かつウィンドウサイズに合わせて拡大できないようにする
	SetWindowSizeChangeEnableFlag(FALSE, FALSE);

	// タイトルを変更
	SetMainWindowText(TITLE);

	// 画面サイズの最大サイズ、カラービット数を設定(モニターの解像度に合わせる)
	SetGraphMode(WindowWidth, WindowHeight, 32);

	// 画面サイズを設定(解像度との比率で設定)
	SetWindowSizeExtendRate(1.0);

	// 画面の背景色を設定する
	SetBackgroundColor(0, 0, 64);

	// DXlibの初期化
	if (DxLib_Init() == -1) { return -1; }

	// (ダブルバッファ)描画先グラフィック領域は裏面を指定
	SetDrawScreen(DX_SCREEN_BACK);

	//Zバッファを有効にする
	SetUseZBuffer3D(TRUE);
	//Zバッファへの書き込みを有効にする
	SetWriteZBuffer3D(TRUE);


	//グリップ面　近　　　遠
	SetCameraNearFar(1.0f, 1000.0f);//カメラの有効範囲を設定
	SetCameraScreenCenter(WindowWidth / 2.0f, WindowHeight / 2.0f);//画面の中心をカメラの中心に合わせる
	SetCameraPositionAndTargetAndUpVec(
		Vector3(-20.0f, 20.0f, -200.0f),		//カメラの位置
		Vector3(0.0f, 0.0f, 0.0f),
		Vector3(0.0f, 1.0f, 0.0f));

	//時間計測に必要なデータ
	long long startCount = 0;
	long long nowCount = 0;
	long long elapsedCount = 0;

	//補間を使うデータ
	//start->endを5[s]で完了させる
	Vector3 start(-100.0f, 0, 0);		//スタート地点(P1)
	Vector3 p2(-50.0f, 50.0f, +50.0f);	//制御点(P2)
	Vector3 p3(+50.0f, -30.0f, -50.0f);	//制御点(P3)
	Vector3 end(+100.0f, 0, 0);			//エンド地点(P4)

	float maxTime = 5.0f;				//全体時間[s]
	float timeRate;						//何% 時間が進んだか(率)

	Quaternion* quaternion = nullptr;
	/*Quaternion q1 = { 2.0f, 3.0f, 4.0f, 1.0f };
	Quaternion q2 = { 1.0f, 3.0f, 5.0f, 2.0f };
	Quaternion identity = quaternion->IdentityQuaternion();
	Quaternion conj = quaternion->Conjugate(q1);
	Quaternion inv = quaternion->Inverse(q1);
	Quaternion normal = quaternion->Normalize(q1);
	Quaternion mul1 = quaternion->Multiply(q1, q2);
	Quaternion mul2 = quaternion->Multiply(q2, q1);
		 float norm = quaternion->Norm(q1);*/

	Quaternion rotation = quaternion->MakeAxisAngle({ 0.0f,0.0f,1.0f }, 3.141592f / 2.0f);
	Vector3 pointY = { 0.0f,1.0f,0.0f };
	Matrix4 rotateMatrix = quaternion->MakeRotateMatrix(rotation);
	Vector3 rotateByQuaternion = quaternion->RotateVector(pointY, rotation);
	//Vector3 rotateByMatrix = quaternion->TransformAffine(pointY, rotateMatrix);
	//p1-p2-p3-p4を通るスプライン曲線
	std::vector<Vector3>points{ start,start,p2,p3,end,end };

	//p1からスタート
	size_t startIndex = 1;

	//球の位置
	Vector3 position;

	//実行前に　カウンタ値を取得
	startCount = GetNowHiPerformanceCount();	//long long int型　64bit int

	// 最新のキーボード情報用
	char keys[256] = { 0 };

	// 1ループ(フレーム)前のキーボード情報
	char oldkeys[256] = { 0 };

	// ゲームループ
	while (true) {
		// 最新のキーボード情報だったものは1フレーム前のキーボード情報として保存
		for (int i = 0; i < 256; i++)
		{
			oldkeys[i] = keys[i];
		}
		// 最新のキーボード情報を取得
		GetHitKeyStateAll(keys);
	
		//---------  ここからプログラムを記述  ----------//


		// 更新処理
		



		// 画面クリア
		ClearDrawScreen();			//画面を消去
		// 描画処理
		DrawAxis3D(500.0f);			//xyz軸の描画
	/*	DrawFormatString(0, 0, GetColor(255, 255, 255), "%f %f %f %f :identity", identity.x, identity.y, identity.z, identity.w);
		DrawFormatString(0, 20, GetColor(255, 255, 255), "%f %f %f %f :Conjugate", conj.x, conj.y, conj.z, conj.w);
		DrawFormatString(0, 40, GetColor(255, 255, 255), "%f %f %f %f :Inverse", inv.x, inv.y, inv.z, inv.w);
		DrawFormatString(0, 60, GetColor(255, 255, 255), "%f %f %f %f :Normalize", normal.x,normal.y,normal.z,normal.w);
		DrawFormatString(0, 80, GetColor(255, 255, 255), "%f %f %f %f :Multiply(q1, q2)", mul1.x, mul1.y, mul1.z, mul1.w);
		DrawFormatString(0, 100, GetColor(255, 255, 255), "%f %f %f %f :Multiply(q2, q1)", mul2.x, mul2.y, mul2.z, mul2.w);
		DrawFormatString(0, 120, GetColor(255, 255, 255), "%f :Norm", norm);*/
		DrawFormatString(0, 0, GetColor(255, 255, 255), "%f %f %f %f :rotation", rotation.x, rotation.y, rotation.z, rotation.w);
		DrawFormatString(0, 20, GetColor(255, 255, 255), "%f %f %f :rotateByQuaternion", rotateByQuaternion.x, rotateByQuaternion.y, rotateByQuaternion.z);
		//DrawFormatString(0, 40, GetColor(255, 255, 255), "%f %f %f :rotateByMatrix", rotateByMatrix.x, rotateByMatrix.y, rotateByMatrix.z);

		//---------  ここまでにプログラムを記述  ---------//
		// (ダブルバッファ)裏面
		ScreenFlip();

		// 20ミリ秒待機(疑似60FPS)
		WaitTimer(20);

		// Windowsシステムからくる情報を処理する
		if (ProcessMessage() == -1) {
			break;
		}

		// ESCキーが押されたらループから抜ける
		if (CheckHitKey(KEY_INPUT_ESCAPE) == 1) {
			break;
		}
	}
	// Dxライブラリ終了処理
	DxLib_End();

	// 正常終了
	return 0;
}

//球の描画
int DrawSphere3D(const Vector3& CenterPos, const float r, const int DivNum,
	const unsigned int DifColor, const unsigned int SpcColor, const int FillFlag) {
	VECTOR centerPos = { CenterPos.x, CenterPos.y, CenterPos.z };		//構造体　初期化子リスト

	return DrawSphere3D(centerPos, r, DivNum, DifColor, SpcColor, FillFlag);
}

//x軸,y軸,z軸の描画
void DrawAxis3D(const float length)
{
	DrawLine3D(Vector3(-length, 0.0f, 0.0f), Vector3(+length, 0.0f, 0.0f), GetColor(255, 0, 0));	//x軸
	DrawLine3D(Vector3(0.0f, -length, 0.0f), Vector3(0.0f, +length, 0.0f), GetColor(0, 255, 0));	//y軸
	DrawLine3D(Vector3(0.0f, 0.0f, -length), Vector3(0.0f, 0.0f, +length), GetColor(0, 0, 255));	//z軸
}

//線分の描画
int DrawLine3D(const Vector3& Pos1, const Vector3& Pos2, const unsigned int Color) {
	VECTOR p1 = { Pos1.x, Pos1.y, Pos1.z };			//構造体　初期化子リスト
	VECTOR p2 = { Pos2.x, Pos2.y, Pos2.z };			//構造体　初期化子リスト

	return DrawLine3D(p1, p2, Color);
}

//カメラの位置と姿勢の設定
int SetCameraPositionAndTargetAndUpVec(
	const Vector3& cameraPosition,				//カメラの位置
	const Vector3& cameraTarget,					//カメラの注視点
	const Vector3& cameraUp						//カメラの上の向き
) {
	VECTOR position = { cameraPosition.x, cameraPosition.y, cameraPosition.z };
	VECTOR target = { cameraTarget.x, cameraTarget.y, cameraTarget.z };
	VECTOR up = { cameraUp.x, cameraUp.y, cameraUp.z };

	return SetCameraPositionAndTargetAndUpVec(position, target, up);
}

//n+2個の点使って、P1~Pnの間を、スプライン補間する
//(P0)-P1-P2-...-Pn-(Pn+1)
Vector3 splinePosition(const std::vector<Vector3>& points, size_t startIndex, float t)
{
	//補間すべき点の数
	size_t n = points.size() - 2;

	if (startIndex > n)return points[n];	//Pnの値を返す
	if (startIndex < 1)return points[1];	//P1の値を返す

	//P0~p3の制御点を取得する　P1~p2を補間する
	Vector3 p0 = points[startIndex - 1];
	Vector3 p1 = points[startIndex];
	Vector3 p2 = points[startIndex + 1];
	Vector3 p3 = points[startIndex + 2];

	//Catmull-Romの式による補間
	Vector3 position = 0.5 * (2 * p1 + (-p0 + p2) * t +
					(2 * p0 - 5 * p1 + 4 * p2 - p3) * t * t +
					(-p0 + 3 * p1 - 3 * p2 + p3) * t * t * t);

	return position;
}