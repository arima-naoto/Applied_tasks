#include <Novice.h>
#define _USE_MATH_DEFINES
#include <math.h>

const char kWindowTitle[] = "GC2A_02_アリマ_ナオト";

struct Circle {
    float x, y; // 中心座標
    float radius; // 半径
    unsigned int color; // 色
};

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

    // ライブラリの初期化
    Novice::Initialize(kWindowTitle, 1280, 720);

    // キー入力結果を受け取る箱
    char keys[256] = { 0 };
    char preKeys[256] = { 0 };

    // 円Aの初期化
    Circle circleA = { 400, 400, 20, WHITE };

    // 回転関連の初期化
    float angle = 0.0f;
    float deltaAngle = (1.0f / 256.0f) * float(M_PI); // 1/256πラジアン

    // 回転の中心の初期化
    bool clicked = false;
    float centerX = 0.0f;
    float centerY = 0.0f;

    // ウィンドウの×ボタンが押されるまでループ
    while (Novice::ProcessMessage() == 0) {
        // フレームの開始
        Novice::BeginFrame();

        // キー入力を受け取る
        memcpy(preKeys, keys, 256);
        Novice::GetHitKeyStateAll(keys);

        // マウスの左クリックを検出
        int mouseX, mouseY;
        Novice::GetMousePosition(&mouseX, &mouseY);

        if (!clicked && Novice::IsTriggerMouse(0)) {
            centerX = (float)mouseX;
            centerY = (float)mouseY;
            clicked = true;
        }

        // 回転計算
        if (clicked) {
            angle += deltaAngle;
            float rotatedX = centerX + cosf(angle) * (circleA.x - centerX) - sinf(angle) * (circleA.y - centerY);
            float rotatedY = centerY + sinf(angle) * (circleA.x - centerX) + cosf(angle) * (circleA.y - centerY);

            // 円Aの位置を更新
            circleA.x = rotatedX;
            circleA.y = rotatedY;
        }

        ///
        /// ↓描画処理ここから
        ///
        Novice::DrawEllipse((int)circleA.x, (int)circleA.y,
            (int)circleA.radius, (int)circleA.radius,
            0.0f, circleA.color, kFillModeSolid);

        // 回転の中心の円を描画
        if (clicked) {
            Novice::DrawEllipse((int)centerX, (int)centerY,
                10, 10,
                0.0f, RED, kFillModeSolid);
        }

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
