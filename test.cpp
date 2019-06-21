#include "DxLib\DxLib.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	ChangeWindowMode(true);
	SetGraphMode(1280, 1024, 16);
	if (DxLib_Init() == -1)
	{
		return -1;
	}

	while (CheckHitKeyAll() == 0 && ProcessMessage() == 0)
	{	
		ClearDrawScreen();

		ScreenFlip();
	}

	WaitKey();
	DxLib_End();

	return 0;
}
