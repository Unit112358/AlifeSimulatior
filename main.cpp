
#include "Dxlib\DxLib.h"
#include "alife.hpp"

using namespace std;

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
    ChangeWindowMode(TRUE); 
	SetGraphMode(WINDOW_WIDTH, WINDOW_HEIGHT, 16);       // ウィンドウモード変更
    DxLib_Init();                  // 初期化
    SetDrawScreen(DX_SCREEN_BACK); //裏画面設定

    Alife::setFps(60);

    Alife *a = new Alife(200, 200, 0, 0),
          *b = new Alife(400, 200, 0, 0),
          *biter = new Alife(400, 400, 0, 0);
    a->setColor(GetColor(255,0,0));
    b->setColor(GetColor(255, 0, 0));
    biter->setColor(GetColor(0,0,255));

    byte mema[] = {JMP, 0};
    byte memb[] = {MOV_RI, RBX, 0, DEC, RBX, GETNUM_I, 50, AND_RR, RAX, RBX, NZJ, (byte)-5, GETNEAR, GETVEC_R, RAX, ADDFRC_R, RAX, JMP,  (byte)-12, EXIT, EXIT, EXIT, EXIT, EXIT};
    byte mem_biter[] = {GETNEAR, GETVEC_R, RAX, ADDFRC_R, RAX, BITE, JMP, (byte)-6};
    
    a->setMem(mema, sizeof(mema));
    b->setMem(mema, sizeof(mema));
    biter->setMem(mem_biter, sizeof(mem_biter));
    // メインループ
    // while( 裏画面を表画面に反映, メッセージ処理, 画面クリア )
    while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0 && CheckHitKeyAll() == 0)
    {
        // a.addForce((200 - a.getX()), (200 - a.getY()));
        for(Alife* p : Alife::alife_list)
        {
            if(p == nullptr)continue;
            if(!(p->update()))delete p;
        }
    }

    DxLib_End(); // DXライブラリ終了処理
    return 0;
}  
