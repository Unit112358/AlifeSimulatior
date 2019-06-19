
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
          *b = new Alife(300, 200, 0, 0),
          *c = new Alife(400, 200, 0, 0),
          *d = new Alife(200, 300, 0, 0),
          *e = new Alife(300, 300, 0, 0),
          *f = new Alife(400, 300, 0, 0);
    a->setColor(GetColor(255,0,0));
    b->setColor(GetColor(0,255,0));
    c->setColor(GetColor(0,0,255));
    d->setColor(GetColor(0,255,255));
    e->setColor(GetColor(255,0,255));
    f->setColor(GetColor(255,255,0));

    byte mema[] = {JMP, 0};
    byte memb[] = {MOV_RI, RBX, 0, DEC, RBX, GETNUM_I, 50, AND_RR, RAX, RBX, NZJ, (byte)-5, GETNEAR, GETVEC_R, RAX, ADDFRC_R, RAX, JMP,  (byte)-12, EXIT, EXIT, EXIT, EXIT, EXIT};
    byte mem_biter[] = {GETNEAR, GETVEC_R, RAX, ADDFRC_R, RAX, BITE, JMP, (byte)-6};
    byte mem_chaser[] = {GETNEAR, GETVEC_R, RAX, ADDFRC_R, RAX, JMP, (byte)-5};

    a->setMem(mem_biter, sizeof(mem_biter));
    b->setMem(mem_biter, sizeof(mem_biter));
    c->setMem(mem_biter, sizeof(mem_biter));
    d->setMem(mem_biter, sizeof(mem_biter));
    e->setMem(mem_biter, sizeof(mem_biter));
    f->setMem(mem_biter, sizeof(mem_biter));
    // メインループ
    // while( 裏画面を表画面に反映, メッセージ処理, 画面クリア )
    while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0 && CheckHitKeyAll() == 0)
    {
        // a.addForce((200 - a.getX()), (200 - a.getY()));
        // nann no bag ga arunnya
        // eraseの引数としてイテレータを渡せるんだけど
        //なぜかバグる
        //だから今はkeyを渡すように実装してる
        // iterator　を渡すようにしてもおいしいことなくない？
        //discordを使え
        //じゃあ変更してみるよ
        //
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
