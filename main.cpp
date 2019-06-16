
#include "Dxlib\DxLib.h"
#include "alife.hpp"

using namespace std;

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
    ChangeWindowMode(TRUE);        // ウィンドウモード変更
    DxLib_Init();                  // 初期化
    SetDrawScreen(DX_SCREEN_BACK); //裏画面設定

    Alife::setFps(60);

    Alife a(0, 0, 2, 0);
    a.setColor(GetColor(255,0,0));

    byte mem[] = {GETNEAR, GETVEC_R, RAX, ADDFRC_R, RAX, JMP, (byte)-5, EXIT, EXIT, EXIT, EXIT, EXIT};
    a.setMem(mem, sizeof(mem));

    // メインループ
    // while( 裏画面を表画面に反映, メッセージ処理, 画面クリア )
    while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0 && CheckHitKeyAll() == 0)
    {
        // a.addForce((200 - a.getX()), (200 - a.getY()));
        a.update();
    }

    DxLib_End(); // DXライブラリ終了処理
    return 0;
}  
