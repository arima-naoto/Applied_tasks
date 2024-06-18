#include <Novice.h>
#define _USE_MATH_DEFINES
#include <math.h>

const char kWindowTitle[] = "GC2A_02_アリマ_ナオト";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = {0};
	char preKeys[256] = {0};

	const int centerX = 400;
	const int centerY = 400;
	const int orbitRadius = 200;
	const int circleRadius = 50;
	const float totalTime = 2.0f; // 円が1周するのにかかる時間
	const float frameTime = 1.0f / 60.0f; // 1フレームの時間
	float angle = 0.0f; // 現在の角度

	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		///
		/// ↓更新処理ここから
		///

		angle += (2.0f * float(M_PI) / totalTime) * frameTime; // 角度を更新
		if (angle >= 2.0f * float(M_PI)) {
			angle -= 2.0f * float(M_PI); // 角度を2π未満に制限
		}

		float x = centerX + orbitRadius * cosf(angle);
		float y = centerY + orbitRadius * sinf(angle);

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		Novice::DrawEllipse((int)x, (int)y, circleRadius, circleRadius, 0.0f, RED, kFillModeSolid);

		///
		/// ↑描画処理ここまで
		///

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}
