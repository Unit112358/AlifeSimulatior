#include "DxLib\DxLib.h"

enum
{
    PLAY = 0,
    SETTING,
    QUIT,
    N_MENU
};

int title(int width, int height);

const TCHAR TitleStrings[][10] = {"PLAY", "SETTING", "QUIT"};

// #define TEST_TITLE

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

    return 0;
}
#endif

//進捗を生やす
int title(int width, int height)
{
    int selected = 0;
    int n_up = 0;
    int n_down = 0;

    SetFontSize(32);

    while(ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0)
    {
        for(int i = 0; i < N_MENU; i++)
        {
            if(selected == i)
            {
                SetFontSize(40);
                int str_w = GetDrawStringWidth(TitleStrings[i], strlen(TitleStrings[i]));
                DrawString((width - str_w)/2, height/2 - 200 + 100 * i, TitleStrings[i], GetColor(255, 0, 0));
                SetFontSize(32);
                continue;
            }
            int str_w = GetDrawStringWidth(TitleStrings[i], strlen(TitleStrings[i]));
            DrawString((width - str_w)/2, height/2 - 200 + 100 * i, TitleStrings[i], GetColor(255, 0, 0));
        }
        if(CheckHitKey(KEY_INPUT_UP))
        {
            n_up++;
            if(n_up%10 == 1 || n_up > 60)
                selected = (selected - 1 + N_MENU) % N_MENU;
        }
        else
            n_up = 0;
        
        if(CheckHitKey(KEY_INPUT_DOWN))
        {
            n_down++;
            if(n_down%10 == 1 || n_down > 60)
                selected = (selected + 1) % N_MENU;
        }
        else
            n_down = 0;
        
        if(CheckHitKey(KEY_INPUT_RETURN))
            break;
    }
    return selected;
}