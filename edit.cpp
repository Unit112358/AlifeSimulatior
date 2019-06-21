#include "DxLib\DxLib.h"
#include "utils.hpp"

int edit();

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
    ChangeWindowMode(TRUE);
	SetGraphMode(WINDOW_WIDTH, WINDOW_HEIGHT, 16);       // ウィンドウモード変更
    DxLib_Init();                  // 初期化
    SetDrawScreen(DX_SCREEN_BACK); //裏画面設定

    edit();

    WaitKey();
    DxLib_End();
}

int edit()
{
    int in_time = 100;
    for(int i = 1; i <= in_time; i++)
    {
        ClearDrawScreen();
        DrawBox(180 * i / in_time - 179, 0, 180 * i / in_time, WINDOW_HEIGHT, GetColor(255, 0, 0), 0);
        ScreenFlip();
    }
}