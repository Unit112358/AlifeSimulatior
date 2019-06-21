#include "DxLib\DxLib.h"
#include "utils.hpp"
#include "alife.hpp"
#include <vector>
#include <map>
#include <cmath>
#include <string>

int battle();

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
    AllocConsole();FILE* out = 0; freopen_s( &out, "CON", "w", stdout );
	printf("Program has started.\n");
    
    ChangeWindowMode(TRUE);
	SetGraphMode(WINDOW_WIDTH, WINDOW_HEIGHT, 16);      // ウィンドウモード変更
    DxLib_Init();                  // 初期化
    SetDrawScreen(DX_SCREEN_BACK); //裏画面設定
    SetFontSize(20);

    Alife *a = new Alife(100, 100), *b = new Alife(300, 300);

    a->setColor(GetColor(255,0,0));
    a->setTeam(0);
    b->setColor(GetColor(0,0,255));
    b->setTeam(1);

    byte chaser[] = {GETNEAR, ADDFRC_R, RAX, JMP, (byte)-3};
    byte mem_biter[] = {GETNEAR, GETVEC_R, RAX, ADDFRC_R, RAX, BITE, JMP, (byte)-6};

    a->setMem(mem_biter, sizeof(mem_biter));
    b->setMem(mem_biter, sizeof(mem_biter));

    while(ProcessMessage() == 0 && CheckHitKeyAll() == 0)
    {
        ClearDrawScreen();
        battle();
        ScreenFlip();
    }
}

void drawEnergy(int energy, bool left)
{
    int tmp = energy, n = 0;
    while(tmp)
    {
        tmp /= 10;
        n++;
    }

    TCHAR *str = new TCHAR[n];
    sprintf(str, "%d", energy);

    int width = GetDrawStringWidth(str, n);
    if(left)
        DrawString(WINDOW_WIDTH / 4 - width / 2, 0, str, GetColor(255,0,0), GetColor(255,255,255));
    else
        DrawString(WINDOW_WIDTH / 4 * 3 - width / 2, 0, str, GetColor(0,0,255), GetColor(0,0,255));
    
    delete[] str;
}

int battle()
{
    static int result_time = 1000;
    static int judge = 0;

    for(auto ite : Alife::alife_list)
    {
        Alife *p = ite.second;
        p->update();
        if(!p->update())
        {
            delete p;
            Alife::alife_list.erase(p->getId());
        }
    }

    drawEnergy(Alife::energy[0], true);
    drawEnergy(Alife::energy[1], false);

    DrawPixel(100,100,GetColor(255,255,255));

    if(judge)
    {
        if(judge == 1)DrawString(0,0,"Player2 Win!", GetColor(0,0,255),GetColor(0,0,255));
        if(judge == 2)DrawString(0,0,"Player1 Win!", GetColor(255,0,0),GetColor(255,0,0));
        if(judge == 3)DrawString(0,0,"Drow...",GetColor(0,255,0),GetColor(0,255,0));
    }
    else if((Alife::energy[0] == 0 && Alife::energy[1] == 0) || (Alife::team_num[0] == 0 && Alife::team_num[1] == 0))judge = 3;
    else if(Alife::energy[0] == 0 || Alife::team_num[0] == 0)judge = 1;
    else if(Alife::energy[1] == 0 || Alife::team_num[1] == 0)judge = 2;

}