
#include "Dxlib\DxLib.h"
#include "alife.hpp"
#include "title.cpp"
#include "edit.cpp"
#include "battle.cpp"
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
        printf("a\n");
        int operation = drawOperations();
        printf("b\n");
        bool isFinish = drawMem(forcusedId, operation);
        printf("c\n");
        if(isFinish)
            break;
        printf("d\n");
        ScreenFlip();
    }

    printf("e\n");

    while (ProcessMessage() == 0)
    {
        printf("f\n");  
        ClearDrawScreen();
        battle();
        ScreenFlip();
    }

    GAME_END:
    DxLib_End(); // DXライブラリ終了処理
    return 0;
}  
