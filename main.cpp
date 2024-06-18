#include <Novice.h>
#include <math.h> // 距離計算のために使用

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

    // 円の初期化
    Circle circles[3] = {
        { 300, 300, 100, WHITE },
        { 600, 300, 100, WHITE },
        { 900, 300, 100, WHITE }
    };

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

        // マウスが円の内部にあるか判定
        for (int i = 0; i < 3; i++) {
            float dx = mouseX - circles[i].x;
            float dy = mouseY - circles[i].y;
            float distance = sqrtf(dx * dx + dy * dy);
            if (distance <= circles[i].radius) {
                circles[i].color = RED; // マウスが円の内部にある場合は赤色に変更
            }
            else {
                circles[i].color = WHITE; // マウスが円の内部にない場合は白色に戻す
            }
        }

        ///
        /// ↓描画処理ここから
        ///

        // 円を描画
        for (int i = 0; i < 3; i++) {
            Novice::DrawEllipse((int)circles[i].x, (int)circles[i].y, (int)circles[i].radius, (int)circles[i].radius, 0.0f, circles[i].color, kFillModeSolid);
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
