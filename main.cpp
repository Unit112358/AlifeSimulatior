
#include "Dxlib\DxLib.h"
#include "alife.hpp"
#include <ctime>

//using namespace std;

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
    ChangeWindowMode(TRUE);
	SetGraphMode(WINDOW_WIDTH, WINDOW_HEIGHT, 16);       // ウィンドウモード変更
    DxLib_Init();                  // 初期化
    SetDrawScreen(DX_SCREEN_BACK); //裏画面設定

    Alife::setFps(60);
    SRand(time(NULL));

    Alife *a = new Alife(200, 200, 0, 0),
          *b = new Alife(300, 200, 0, 0),
          *c = new Alife(400, 200, 0, 0),
          *d = new Alife(200, 300, 0, 0),
          *e = new Alife(300, 300, 0, 0),
          *f = new Alife(400, 300, 0, 0),
          *mother = new Alife(500, 30, 0, 0);
    a->setColor(GetColor(255,0,0));
    b->setColor(GetColor(0,255,0));
    c->setColor(GetColor(0,0,255));
    d->setColor(GetColor(0,255,255));
    e->setColor(GetColor(255,0,255));
    f->setColor(GetColor(255,255,0));
    mother->setColor(GetColor(255, 0, 0));

    byte mema[] = {JMP, 0};
    byte memb[] = {MOV_RI, RBX, 0, DEC, RBX, GETNUM_I, 50, AND_RR, RAX, RBX, NZJ, (byte)-5, GETNEAR, GETVEC_R, RAX, ADDFRC_R, RAX, JMP,  (byte)-12, EXIT, EXIT, EXIT, EXIT, EXIT};
    byte mem_biter[] = {GETNEAR, GETVEC_R, RAX, ADDFRC_R, RAX, BITE, JMP, (byte)-6};
    byte mem_biter2[] = {GETNEAR, GETVEC_R, RAX, ADDFRC_R, RAX, BITE, BITE, BITE, BITE, BITE, BITE, JMP, (byte)-11};
    byte mem_chaser[] = {GETNEAR, GETVEC_R, RAX, ADDFRC_R, RAX, JMP, (byte)-5};
    byte mem_mother[] = {DIVISION_I, 8, GETNEAR, GETVEC_R, RAX, ADDFRC_R, RAX, BITE, JMP, (byte)-3, JMP, (byte)-10};
    byte mem_cell[] = {MOV_RI, RBX, (byte)2, GETNEAR, GETVEC_R, RAX, ADDFRC_R, RAX, GETNUM_I, 200, CMP_RR, RAX, RBX, NSJ, (byte)-10, DIVISION, JMP, (byte)-13};
    byte mem_nonmove[] = {NOP, DIVISION, JMP, (byte)-1};

    a->setMem(memb, sizeof(memb));
    b->setMem(memb, sizeof(memb));
    c->setMem(mem_biter2, sizeof(mem_biter2));
    d->setMem(mem_biter2, sizeof(mem_biter2));
    e->setMem(mem_biter2, sizeof(mem_biter2));
    f->setMem(mem_biter2, sizeof(mem_biter2));
    mother->setMem(mem_mother, sizeof(mem_mother));
    // メインループ
    // while( 裏画面を表画面に反映, メッセージ処理, 画面クリア )
    while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0 && CheckHitKeyAll() == 0)
    {
        for(auto ite : Alife::alife_list)
        {
            Alife* p = ite.second;
            if(!(p->update()))
            {
                Alife::alife_list.erase(p->getId());
                delete p;
            }
        }
    }

    DxLib_End(); // DXライブラリ終了処理
    return 0;
}  
