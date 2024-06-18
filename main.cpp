#include <Novice.h>

const char kWindowTitle[] = "GC2A_02_アリマ_ナオト";

struct Rect {
    float x, y; // 左上の座標
    float width, height; // 幅と高さ
    unsigned int color; // 色
};

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

    // ライブラリの初期化
    Novice::Initialize(kWindowTitle, 1280, 720);

    // キー入力結果を受け取る箱
    char keys[256] = { 0 };
    char preKeys[256] = { 0 };

    // 短形の初期化
    Rect rectangles[3] = {
        { 200, 200, 100, 100, WHITE },
        { 400, 200, 100, 100, WHITE },
        { 600, 200, 100, 100, WHITE }
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

        // マウスが短形の内部にあるか判定
        for (int i = 0; i < 3; i++) {
            if (mouseX >= rectangles[i].x && mouseX <= rectangles[i].x + rectangles[i].width &&
                mouseY >= rectangles[i].y && mouseY <= rectangles[i].y + rectangles[i].height) {
                rectangles[i].color = RED; // マウスが短形の内部にある場合は赤色に変更
            }
            else {
                rectangles[i].color = WHITE; // マウスが短形の内部にない場合は白色に戻す
            }
        }

        ///
        /// ↓描画処理ここから
        ///

        // 短形を描画
        for (int i = 0; i < 3; i++) {
            Novice::DrawBox((int)rectangles[i].x, (int)rectangles[i].y,
                (int)rectangles[i].width, (int)rectangles[i].height,
                0.0f, rectangles[i].color, kFillModeSolid);
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
