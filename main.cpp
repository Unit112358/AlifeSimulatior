
#include "Dxlib\DxLib.h"
#include "alife.hpp"
#include "title.cpp"
#include "edit.cpp"
#include <ctime>

//using namespace std;

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
    AllocConsole();FILE* out = 0; freopen_s( &out, "CON", "w", stdout );
	printf("Program has started.\n");
    
    ChangeWindowMode(TRUE);
	SetGraphMode(WINDOW_WIDTH, WINDOW_HEIGHT, 16);       // ウィンドウモード変更
    DxLib_Init();                  // 初期化
    SetDrawScreen(DX_SCREEN_BACK); //裏画面設定

    SRand(time(NULL));
    GetMouseHWheelRotVol();

    int menuSelected = title();
    returnDown++;
    if(menuSelected != PLAY)
        goto GAME_END;

    SetFontSize(fontSize);
    while(ProcessMessage() == 0)
    {
        ClearDrawScreen();

        d_scrl = GetMouseWheelRotVol();
        GetMousePoint(&mouseX, &mouseY);
        if(GetMouseInput() && MOUSE_INPUT_LEFT)
            mouseClick++;
        else
            mouseClick = 0;
        if(CheckHitKey(KEY_INPUT_RETURN))
            returnDown++;
        else
            returnDown = 0;

        
        int forcusedId = drawBattleField();
        
        int operation = drawOperations();

        bool isFinish = drawMem(forcusedId, operation);

        if(isFinish)
            break;

        ScreenFlip();
    }

    while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0)
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

    GAME_END:
    DxLib_End(); // DXライブラリ終了処理
    return 0;
}  
