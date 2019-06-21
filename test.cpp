#include "DxLib\DxLib.h"
#include "utils.hpp"
#include "title.cpp"

int fontSize = 	18;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	AllocConsole();FILE* out = 0; freopen_s( &out, "CON", "w", stdout );
	printf("Program has started.\n");

	ChangeWindowMode(true);
	SetGraphMode(900, 600, 16);
	if (DxLib_Init() == -1)
	{
		return -1;
	}
    SetDrawScreen(DX_SCREEN_BACK); //裏画面設定
	
	GetMouseWheelRotVol();

	int selectedOperation;

	if(title(WINDOW_WIDTH, WINDOW_HEIGHT) != 0)
		exit(0);

	SetFontSize(fontSize);

	int op;

	while (ProcessMessage() == 0)
	{	
		ClearDrawScreen();

		op = DrawOperations();
		if(op > 0)
			printf("%s\n", operationStrings[op]);
		else if(op < 0)
			printf("%d\n", ~op);

		ScreenFlip();
	}

	DxLib_End();

	return 0;
}
