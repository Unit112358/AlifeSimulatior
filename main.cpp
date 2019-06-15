
#include "Dxlib\DxLib.h"

int WINAPI WinMain(HINSTANCE,HINSTANCE,LPSTR,int){
        ChangeWindowMode(TRUE);             // ウィンドウモード変更
        DxLib_Init();                       // 初期化
        SetDrawScreen(DX_SCREEN_BACK);      //裏画面設定

        // メインループ
        // while( 裏画面を表画面に反映, メッセージ処理, 画面クリア )
        while( ScreenFlip()==0 && ProcessMessage()==0 && ClearDrawScreen()==0 )
        {
            ;
        }
        
        DxLib_End();                        // DXライブラリ終了処理
        return 0;
}  
