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
    Circle circleA = { 500, 200, 30, WHITE };

    // 回転関連の初期化
    float angle = 0.0f;
    float deltaAngle = (1.0f / 256.0f) * float(M_PI); // 1/256πラジアン
    int frameCount = 0;

    // ウィンドウの×ボタンが押されるまでループ
    while (Novice::ProcessMessage() == 0) {
        // フレームの開始
        Novice::BeginFrame();

        // キー入力を受け取る
        memcpy(preKeys, keys, 256);
        Novice::GetHitKeyStateAll(keys);

        // マウス位置を取得
        int mouseX, mouseY;
        Novice::GetMousePosition(&mouseX, &mouseY);

        // 回転方向の切り替え
        frameCount++;
        if (frameCount >= 60) { // 1秒ごとに方向を逆にする
            deltaAngle = -deltaAngle;
            frameCount = 0;
        }

        // 回転計算
        angle += deltaAngle;
        float rotatedX = circleA.x + cosf(angle) * circleA.radius;
        float rotatedY = circleA.y + sinf(angle) * circleA.radius;

        // マウスが円の内部にあるか判定
        float dx = mouseX - circleA.x;
        float dy = mouseY - circleA.y;
        float distance = sqrtf(dx * dx + dy * dy);
        if (distance <= circleA.radius) {
            circleA.color = RED; // マウスが円の内部にある場合は赤色に変更
        }
        else {
            circleA.color = WHITE; // マウスが円の内部にない場合は白色に戻す
        }

        ///
        /// ↓描画処理ここから
        ///

        // 円Aを描画
        Novice::DrawEllipse((int)rotatedX, (int)rotatedY,
            (int)circleA.radius, (int)circleA.radius,
            0.0f, circleA.color, kFillModeSolid);

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

