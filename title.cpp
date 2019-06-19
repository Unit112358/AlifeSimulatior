#include "DxLib\DxLib.h"

enum
{
    PLAY = 0,
    SETTING,
    QUIT,
    N_MENU
};

int title(int width, int height);

#define TEST_TITLE

#ifdef TEST_TITLE
const int scrWidth = 640;
const int scrHeight = 480;

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
    ChangeWindowMode(TRUE);        // ウィンドウモード変更
    DxLib_Init();                  // 初期化
    //SetDrawScreen(DX_SCREEN_FRONT); //裏画面設定
    SetWindowSize(scrWidth, scrHeight);

    title(scrWidth, scrHeight);

    DxLib_End();
}
#endif

//進捗を生やす
int title(int width, int height)
{
    DrawString(width/2, height/2 - 40, "PLAY", GetColor(255, 0, 0));
    DrawPixel(0,0,GetColor(255,255,255));

    ScreenFlip();

    WaitKey();
}