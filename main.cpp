#include <Novice.h>
#define _USE_MATH_DEFINES
#include <math.h>

const char kWindowTitle[] = "GC2A_02_アリマ_ナオト";

struct Circle {
    float x, y; // 中心座標
    float radius; // 半径
    unsigned int color; // 色
    bool isMoving; // 円が動いているかどうか
};

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

    // ライブラリの初期化
    Novice::Initialize(kWindowTitle, 1280, 720);

    // キー入力結果を受け取る箱
    char keys[256] = { 0 };
    char preKeys[256] = { 0 };

    // 円の初期化
    Circle circle = { 0, 360, 50, WHITE, false };

    // ウィンドウの×ボタンが押されるまでループ
    while (Novice::ProcessMessage() == 0) {
        // フレームの開始
        Novice::BeginFrame();

        // キー入力を受け取る
        memcpy(preKeys, keys, 256);
        Novice::GetHitKeyStateAll(keys);

        // スペースキーが押されたときに円を発射
        if (preKeys[DIK_SPACE] == 0 && keys[DIK_SPACE] != 0) {
            circle.x = 0;
            circle.y = 360;
            circle.isMoving = true;
        }

        // 円の移動
        if (circle.isMoving) {
            circle.x += 5; // 右に進む

            // 合成波による上下移動
            float wave1 = 20 * sinf(circle.x * 0.05f);
            float wave2 = 10 * sinf(circle.x * 0.1f);
            circle.y = 360 + wave1 + wave2;

            // 画面外に出たら停止
            if (circle.x > 1280 + circle.radius) {
                circle.isMoving = false;
            }
        }

        ///
        /// ↓描画処理ここから
        ///
        Novice::DrawEllipse((int)circle.x, (int)circle.y, 
                            (int)circle.radius, (int)circle.radius, 
                            0.0f, circle.color, kFillModeSolid);
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
